#include "../include/img_subscriber2/img_data_subpub_node.hpp"

/***************************constructor********************************/
ImgData::ImgData(ros::NodeHandle &nh){
    ni_ = nh;
    img_data_pub_[0] = ni_.advertise<geometry_msgs::Point>("ImgDataPub4",1);
    img_data_pub_[1] = ni_.advertise<geometry_msgs::Point>("ImgDataPub5",1);
    img_data_pub_[2] = ni_.advertise<geometry_msgs::Point>("ImgDataPub6",1);
    img_data_pub_[3] = ni_.advertise<geometry_msgs::Point>("ImgDataPub7",1);
    //obstacle
    for(int i = 0;i < 5;i++){
        for(int j = 0;j < 4;j++){
            char s[20];
            sprintf(s,"obstacleDataPub%d%d",i,j);
            obstacle_data_pub_[i][j] = ni_.advertise<geometry_msgs::Point>(s,1);
        }
    }
    for(int i = 0;i < 5;i++){
        char s[20];
        sprintf(s,"obstacleFlagPub%d",i);
 //       obstacle_flag_pub_[i] = ni_.advertise<std_msgs::int8>(s,1);
    }
}
/***********************get image frome bebop***************************/
void ImgData::imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
    try {
	    image = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8)->image;
    }
    catch (cv_bridge::Exception& e) {
	    ROS_ERROR("cv_bridge exception: %s", e.what());
    }
    const int height = image.rows;
    const int width = image.cols;
   	cv::Ptr<cv::aruco::DetectorParameters> parameters = cv::aruco::DetectorParameters::create();
	frame = image;
	frame.copyTo(org);
   // boxFilter(org,img,org.type(),cv::Size(5,5),cv::Point(-1,-1),true);
   // cvtColor(img,hsv,CV_BGR2HSV);
    /*result = Mat::zeros(HEIGHT,WIDTH,CV_8UC1);
    for(int y = 0;y < HEIGHT;y++){
        for(int x = 0;x < WIDTH;x++){
            int index = hsv.step*y + x * 3;
            if( dH<= hsv.data[index]&&hsv.data[index] <=uH &&dS <= hsv.data[index+1] && hsv.data[index+1] <= uS&&dV <= hsv.data[index+2] && hsv.data[index+2] <= uV){
                result.data[result.step*y + x] = 255;
            }
        }
    }*/
	// marker find
	cv::aruco::detectMarkers(org, dictionary, marker_corners, marker_ids, parameters);
	//replication

    for(int i = 0;i < 4;i++){
        img_data[i].x = 0;
        img_data[i].y = 0;
    }
    for(int i = 0;i < 5;i++){
        obstacle_data[i][0].z = 0;
    }
	if (marker_ids.size() > 0) {
        int id = 0;
        for(int i = 1;i <= marker_ids.size();i++){
            if(marker_ids[i-1] == 0){//target's id 0
                for(int j = 0;j < 4;j++){
                    img_data[j].x = marker_corners[i-1][j].x - IMAGE_WIDTH;
                    img_data[j].y = -marker_corners[i-1][j].y + IMAGE_HEIGHT;                  /* for(int i = 0;i < 4;i++){
                        circle(org,marker_corners[0][i],1,cv::Scalar(255,0,0),2,CV_AA);
                    }*/
                }
            }else if(marker_ids[i-1] != 0){//obstacle's ids 1~5
                for(int k = 0;k < 5;k++){
                    if(marker_ids[i-1] == k+1){
                        for(int j = 0;j < 4;j++){
                            obstacle_data[id][j].x = marker_corners[i-1][j].x - IMAGE_WIDTH;
                            obstacle_data[id][j].y = -marker_corners[i-1][j].y + IMAGE_HEIGHT;
                        }
                        obstacle_data[id][0].z = 1;
                        id++;
                        printf("%d\n",id);
                    }
                }
            }
        }
	}else{
        for(int i = 0;i < 4;i++){
            img_data[i].x = 0;
            img_data[i].y = 0;
            printf("abc\n");
        }
        for(int i = 0;i < 5;i++){
            for(int j = 0;j < 4;j++){
                obstacle_data[i][j].x = 0;
                obstacle_data[i][j].y = 0;
            }
            obstacle_data[i][0].z = 0;
        }

    }
	cv::aruco::drawDetectedMarkers(org, marker_corners, marker_ids);
    circle(org,Point(IMAGE_WIDTH,IMAGE_HEIGHT),1,cv::Scalar(255,0,0),2,CV_AA);
    cv::resize(org,org,cv::Size(),0.5,0.5);
	cv::imshow("marker_detection2", org);
    //imshow("result",result);
    //imshow("fil",img);
    imageDataPub();
    cv::waitKey(1);
}
/********************image data publisher*********************/
void ImgData::imageDataPub(){
    for(int i=0;i<4;i++){
        img_data_pub_[i].publish(img_data[i]);
       // cout <<"x"<<i<<":"<< img_data[i].x<<",y"<<i<<":"<<img_data[i].y << ",";
    }
    for(int i = 0;i < 5;i++){
        for(int j = 0;j < 4;j++){
            obstacle_data_pub_[i][j].publish(obstacle_data[i][j]);
        }
  //      obstacle_flag_pub_[i].publish(obstacle_flag[i]);
    }

    cout << endl;
}

void ImgData::markerCreate(){
    const cv::aruco::PREDEFINED_DICTIONARY_NAME dictionary_name = cv::aruco::DICT_4X4_50;
    cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(dictionary_name);
    const int side_pixels = 200;
    cv::Mat marker_img[7];
    for(int i = 0;i < 7;i++){
        cv::aruco::drawMarker(dictionary,i,side_pixels,marker_img[i]);
    }
    imshow("0",marker_img[0]);
    imshow("1",marker_img[1]);
    imshow("2",marker_img[2]);
    imshow("3",marker_img[3]);
    imshow("4",marker_img[4]);
    imshow("5",marker_img[5]);
    waitKey(0);
}
