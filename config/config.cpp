#include "config.hpp"
namespace YamlConfigs
{
     bool YamlLoad(std::shared_ptr<CameraData::CameraConfigParameters> camera_config_parameters,
                   std::shared_ptr<MapData::MapConfigParameters> map_config_parameters,
                   std::shared_ptr<CameraData::CameraInsideParameters> camera_inside_parameters,
                   std::shared_ptr<CameraSpace::CameraPhysicalPose> camera_physical_pose,
                   std::shared_ptr<Game::GameSide> game_side,
                   std::shared_ptr<Game::GameState> game_state)
     {
          YAML::Node global_config = YAML::LoadFile("config.yaml");
          std::cout << "loadding config.yaml..." << std::endl;
          if (global_config["camera_config_parameters"])
          {
               auto camera_config_node = global_config["camera_config_parameters"];
               camera_config_parameters->deviceID = camera_config_node["deviceID"].as<int>();
               camera_config_parameters->width = camera_config_node["width"].as<int>();
               camera_config_parameters->height = camera_config_node["height"].as<int>();
               camera_config_parameters->brightness = camera_config_node["brightness"].as<int>();
               camera_config_parameters->contrast = camera_config_node["contrast"].as<int>();
               camera_config_parameters->saturation = camera_config_node["saturation"].as<int>();
               camera_config_parameters->hue = camera_config_node["hue"].as<int>();
               camera_config_parameters->exposure = camera_config_node["exposure"].as<int>();
               std::cout << "Camera config loaded successfully." << std::endl;
          }
          else
          {
               std::cerr << "Failed to load camera config." << std::endl;
               return false;
          }

          if (global_config["camera_inside_parameters"])
          {
               auto camera_inside_node = global_config["camera_inside_parameters"];
               camera_inside_parameters->focal_length = camera_inside_node["focal_length"].as<double>();
               camera_inside_parameters->sensor_height = camera_inside_node["sensor_height"].as<double>();
               camera_inside_parameters->sensor_width = camera_inside_node["sensor_width"].as<double>();
               std::cout << "Camera inside parameters loaded successfully." << std::endl;
          }
          else
          {
               std::cerr << "Failed to load camera inside parameters." << std::endl       ;
               return false;
          }

          if (global_config["camera_physical_pose"])
          {
               auto camera_physical_pose_node = global_config["camera_physical_pose"];
               auto camera_position_node = camera_physical_pose_node["position"];
               camera_physical_pose->position = Eigen::Vector3d(
                   camera_position_node["x"].as<double>(),
                   camera_position_node["y"].as<double>(),
                   camera_position_node["z"].as<double>());
               auto camera_orientation_node = camera_physical_pose_node["orientation"];
               double roll = camera_orientation_node["roll"].as<double>();
               double pitch = camera_orientation_node["pitch"].as<double>();
               double yaw = camera_orientation_node["yaw"].as<double>();
               Eigen::AngleAxisd rollAngle(roll, Eigen::Vector3d::UnitX());
               Eigen::AngleAxisd pitchAngle(pitch, Eigen::Vector3d::UnitY());
               Eigen::AngleAxisd yawAngle(yaw, Eigen::Vector3d::UnitZ());
               Eigen::Quaterniond q = yawAngle * pitchAngle * rollAngle;
               camera_physical_pose->orientation = q.toRotationMatrix();
               std::cout << "Camera physical pose loaded successfully." << std::endl;
          }
          else
          {
               std::cerr << "Failed to load camera physical pose." << std::endl;
               return false;
          }

          if (global_config["map_config_parameters"])
          {
               auto map_node = global_config["map_config_parameters"];
               map_config_parameters->map_name = map_node["map_name"].as<std::string>();
               map_config_parameters->obj_map_file_path = map_node["obj_map_file_path"].as<std::string>();
               map_config_parameters->bin_map_file_path = map_node["bin_map_file_path"].as<std::string>();
               std::cout << "Map config parameters loaded successfully." << std::endl;
          }
          else
          {
               std::cerr << "Failed to load map config parameters." << std::endl;
               return false;
          }
          if (global_config["game_config_parameters"])
          {
               auto game_config_node = global_config["game_config_parameters"];

               game_side->enemy = game_config_node["game_side"]["enemy"].as<std::string>();
               game_side->ally = game_config_node["game_side"]["ally"].as<std::string>();
               std::cout << "set ally: " << game_side->ally << std::endl;
               std::cout << "set enemy: " << game_side->enemy << std::endl;
               std::cout << "Game side loaded successfully." << std::endl;
               game_state->state = game_config_node["game_state"].as<std::string>();
               std::cout << "Game state loaded successfully." << std::endl;
          }
          else
          {
               std::cerr << "Failed to load game side/state." << std::endl;
               return false;

          }
          return true;
     }
}
