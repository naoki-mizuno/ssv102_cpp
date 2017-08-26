#include <ssv102/ssv102.h>

#include <ros/ros.h>
#include <nmea_msgs/Sentence.h>

#include <map>
#include <string>

int
main(int argc, char* argv[]) {
    ros::init(argc, argv, "ssv102_node");
    ros::NodeHandle nh{"~"};

    // Get parameters
    std::string port;
    int baud;
    std::map<std::string, std::string> msg_rates;
    std::string frame_id;

    nh.getParam("port", port);
    nh.param("baud", baud, 115200);
    nh.param("jascs", msg_rates, std::map<std::string, std::string>{
        {"GPGGA", "10"},
        {"GPHDT", "10"},
    });
    nh.param("frame_id", frame_id, std::string{"heading_frame"});


    SSV102 ssv102{port, static_cast<unsigned>(baud)};
    try {
        ssv102.connect();
        ROS_INFO("Connected to device:");
        ROS_INFO_STREAM("  PORT: " << port);
        ROS_INFO_STREAM("  BAUD: " << baud);
    }
    catch (const serial::PortNotOpenedException& e) {
        ROS_ERROR_STREAM(e.what());
        return 1;
    }
    catch (const serial::IOException& e) {
        ROS_ERROR_STREAM(e.what());
        return 1;
    }

    ssv102.send_jasc(msg_rates);

    ros::Publisher nmea_pub = nh.advertise<nmea_msgs::Sentence>("/nmea_sentence", 10);
    nmea_msgs::Sentence nmea;
    while (ros::ok()) {
        auto msg = ssv102.read_sentence();
        // ROS_INFO_STREAM(msg);
        if (msg.empty()) {
            continue;
        }

        nmea.header.stamp = ros::Time::now();
        nmea.header.frame_id = frame_id;
        nmea.sentence = msg;
        nmea_pub.publish(nmea);

        ros::spinOnce();
    }

    return 0;
}
