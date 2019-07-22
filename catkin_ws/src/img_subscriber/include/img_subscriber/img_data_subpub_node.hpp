#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/aruco.hpp>
#include <iostream>
#include <geometry_msgs/Point.h>
#include <std_msgs/Int8.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <sys/times.h>
#define IMAGE_WIDTH 1280/2
#define IMAGE_HEIGHT 720/2
#define WIDTH 1280
#define HEIGHT 720

#define uH 120
#define dH 30
#define uS 80
#define dS 0
#define uV 250
#define dV 160
using namespace cv;
using namespace std;

/*********************************************class publisher and subscriber**********************************************/
class ImgData{
private:
/**************publisher ros**************/
    ros::NodeHandle ni_;
    ros::Publisher img_data_pub_[4];
    ros::Publisher obstacle_data_pub_[5][4];
  //  ros::Publisher obstacle_flag_pub_[5];
    geometry_msgs::Point img_data[4];
    geometry_msgs::Point obstacle_data[5][4];
//    std_msgs::Int8 obstacle_flag[5];
/**************opencv**************/
    Mat image;
    Mat hsv;
    Mat frame;
    Mat img;
    Mat org;
    Mat result;
    Mat contourIm[2];
/*************valiable**************/

    cv::aruco::PREDEFINED_DICTIONARY_NAME dictionary_name = cv::aruco::DICT_4X4_50;
    cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(dictionary_name);
    double x[1][4], y[1][4];
	std::vector<int> marker_ids;
	std::vector<std::vector<cv::Point2f> > marker_corners;
public:
    ImgData(ros::NodeHandle &nh);
    void imageCallback(const sensor_msgs::ImageConstPtr& msg);
    void imageDataPub();
    void markerCreate();
};
