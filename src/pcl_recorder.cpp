#include <point_cloud_transport/point_cloud_transport.hpp>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <iostream>
#include <fstream>
#include <string>
// #include <pcl/io/pcd_io.h>

std::string DATASET_NAME = "road";
std::string FILE_FORMAT = ".pcd";

// void convertToBinary(const sensor_msgs::msg::PointCloud2::ConstSharedPtr &msg, int &msgIndex)
// {
//   sensor_msgs::msg::PointCloud2 output;
//   std::string msgFileName = DATASET_NAME + "_" + std::to_string(msgIndex)+;
//   pcl::io::savePCDFileASCII("")
// }

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<rclcpp::Node>("plc_recorder");
  RCLCPP_INFO_STREAM(node->get_logger(), "UWAGA BO PIERDOLNIE!");

  auto transport_hint = std::make_shared<point_cloud_transport::TransportHints>();

  std::string messagesFileName = "messages_" + transport_hint->getTransport() + ".txt";
  std::ofstream outputFile(messagesFileName);

  if (!outputFile.is_open())
  {
    std::cerr << "Nie można otworzyć pliku do zapisu." << std::endl;
    return 1;
  }
  int msgIndex = 0;
  point_cloud_transport::PointCloudTransport pct(node);
  point_cloud_transport::Subscriber pct_sub = pct.subscribe(
      "pct/point_cloud", 100,
      [&outputFile, &msgIndex, &node](const sensor_msgs::msg::PointCloud2::ConstSharedPtr &msg)
      {
        RCLCPP_INFO_STREAM(
            node->get_logger(),
            "Message received, number of points is: " << msg->width * msg->height << ", number of interation: " << std::to_string(msgIndex));

        // std::string dataAsString(reinterpret_cast<const char *>(msg->data.data()), msg->data.size());
        // convertToBinary(msg, msgIndex);
        // outputFile << dataAsString << std::endl;
        msgIndex++;
      },
      {}, transport_hint.get());

  RCLCPP_INFO_STREAM(node->get_logger(), "Waiting for point_cloud message...");

  rclcpp::spin(node);

  outputFile.close();

  rclcpp::shutdown();

  return 0;
}