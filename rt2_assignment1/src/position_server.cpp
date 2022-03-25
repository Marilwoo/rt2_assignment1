#include <chrono>
#include <cinttypes>
#include <inttypes.h>
#include <memory>
#include <iostream>
#include <string>
#include <math.h>
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_components/register_node_macro.hpp"
#include "rt2_assignment1/srv/random_position.hpp"

using namespace std;
using RandomPosition = rt2_assignment1::srv::RandomPosition;
using std::placeholders::_1;
using std::placeholders::_2;
using std::placeholders::_3;

namespace rt2_assignment1{
class position_server : public rclcpp::Node
{
public:
  position_server(const rclcpp::NodeOptions & options)
  : Node("random_position", options)
  {
    // Defining the service
    service_ = this->create_service<RandomPosition>("/position_server", std::bind(&position_server::handle_service, this, _1, _2, _3));
  }
  
  private:
  // Function for computing the random value between two numbers
  double randMToN(double M, double N)
  {return M + (rand() / ( RAND_MAX / (N-M) ) ) ; }
  
  // Callback for the service
  void handle_service(
  const std::shared_ptr<rmw_request_id_t> request_header,
  const std::shared_ptr<RandomPosition::Request> request,
  const std::shared_ptr<RandomPosition::Response> response)
  {
  
  (void)request_header;
  // Assigning the computed random values to the response for the client
  response->x = randMToN(request->x_min, request->x_max);
  response->y = randMToN(request->y_min, request->y_max);
  response->theta = randMToN(-3.14, 3.14);  
  }
  rclcpp::Service<RandomPosition>::SharedPtr service_;
};
}

RCLCPP_COMPONENTS_REGISTER_NODE(rt2_assignment1::position_server)
