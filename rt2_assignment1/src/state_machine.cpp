#include <chrono>
#include <cinttypes>
#include <inttypes.h>
#include <memory>
#include <iostream>
#include <functional>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_components/register_node_macro.hpp"
#include "rt2_assignment1/srv/position.hpp"
#include "rt2_assignment1/srv/command.hpp"
#include "rt2_assignment1/srv/random_position.hpp"

using namespace std;
using Position = rt2_assignment1::srv::Position;
using RandomPosition = rt2_assignment1::srv::RandomPosition;
using user_interface = rt2_assignment1::srv::Command;
using std::placeholders::_1;
using std::placeholders::_2;
using std::placeholders::_3;

namespace rt2_assignment1 {

class state_machine  : public rclcpp::Node
{

  public:
    state_machine(const rclcpp::NodeOptions & options) : Node("state_machine", options)
    { 
    //Client for the random position service
      client1_ = this->create_client<RandomPosition>("/position_server");
      while (!client1_->wait_for_service(std::chrono::seconds(1))) {
        if (!rclcpp::ok()) {
          RCLCPP_ERROR(this->get_logger(), "client interrupted while waiting for service to appear.");
          return;
        }

      }

      //Client for go to point service
      client2_ = this->create_client<Position>("/go_to_point");
      while (!client2_->wait_for_service(std::chrono::seconds(1))) {
        if (!rclcpp::ok()) {
          RCLCPP_ERROR(this->get_logger(), "client interrupted while waiting for service to appear.");
          return;
        }

      }
      
      //Server for the user interface
      service_ = this->create_service<user_interface>("/user_interface", std::bind(&state_machine::handle_service, this, _1, _2, _3));
    }
    
    private:
    
    bool start = false;
      void call_clients(){
      
      	if (this->start) {
      	
	// Defining max and min values for the RandomPosition service
        auto random_position = std::make_shared<RandomPosition::Request>();
        random_position->x_max = 5.0;
        random_position->x_min = -5.0;
        random_position->y_max = 5.0;
        random_position->y_min = -5.0;

         auto response_callback = [this](rclcpp::Client<RandomPosition>::SharedFuture future) {
          auto goal_position = std::make_shared<Position::Request>();
          this->random_position_response=future.get();
	  
          // Assigning the random position response to the request for the Position service, to make the robot move toward the target
          goal_position->x = random_position_response->x;
          goal_position->y = random_position_response->y;
          goal_position->theta = random_position_response->theta;
          std::cout<<"Going to position: x = " << random_position_response->x << " y = "<< random_position_response->y << " theta = " << random_position_response->theta<< std::endl;
       
          auto response_callback2 = [this](rclcpp::Client<Position>::SharedFuture future2)
            {
            (void)future2;
            std::cout<< "Goal position reached" << std::endl;
	    
	   // Calling again the target to make the robot restart once reached the target
           this->call_clients();
            };
            auto result_future2 = client2_->async_send_request(goal_position, response_callback2);
            
         };
        auto result_future = client1_->async_send_request(random_position, response_callback);
      }
      else {
      // If "start" is false it doesn't do anything
      }
      }
          
       void handle_service(
       const std::shared_ptr<rmw_request_id_t> request_header,
       const std::shared_ptr<user_interface::Request> request,
       const std::shared_ptr<user_interface::Response> response)
       {
       // Assigning the user interface request to the variable for the state machine. To make the robot move
       // or stop once the target is reached
       (void)request_header;
       if (request->command == "start")
       {
	 this->start  = true;	
	 std::cout<<"Start = " << start <<std::endl;
       }
       else
       {
         this->start = false;
         std::cout<<"Start = " << start <<std::endl;
       }
       // Givng the response to the user interface and calling the function to make the robot start
       response->ok = true;
       this->call_clients();
              
       }
       rclcpp::Service<user_interface>::SharedPtr service_;
       rclcpp::Client<RandomPosition>::SharedPtr client1_;
       rclcpp::Client<Position>::SharedPtr client2_;
       std::shared_ptr<rt2_assignment1::srv::RandomPosition::Response> random_position_response;
       std::shared_ptr<rt2_assignment1::srv::Position::Response> position_response;
};
}

RCLCPP_COMPONENTS_REGISTER_NODE(rt2_assignment1::state_machine)	
