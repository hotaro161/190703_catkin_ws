#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/aruco.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Point.h>
#include <std_msgs/Empty.h>
#include <sys/times.h>
#include <time.h>
#include <stdbool.h>
#include <termios.h>
#include <unistd.h>
#include "../include/cv_test/bebop_controller.hpp"
using namespace cv;
using namespace std;
#define speed 0.175
// 抽出する画像の輝度値の範囲を指定


/*********************************************class publisher and subscriber**********************************************/
class ImgDataSub{
private:
/**************opencv**************/
public:
    Mat image;
    Mat frame;
    Mat img;
    Mat org;
    ImgDataSub();
    void imageCallback(const sensor_msgs::ImageConstPtr& msg);
};
/***************************constructor********************************/
ImgDataSub::ImgDataSub(){

}
/***********************get image frome bebop***************************/
void ImgDataSub::imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
    #define H_MAX 130		//赤　180   青130
    #define H_MIN 100		//赤　160	青100
    #define S_MAX 255		//赤  255
    #define S_MIN 85		//赤  50
    #define V_MAX 255		//赤  255
    #define V_MIN 85		//赤  50

    #define H1_MAX 5		//赤　180   青130
    #define H1_MIN 0		//赤　160	青100
    #define S1_MAX 255		//赤  255
    #define S1_MIN 85		//赤  50
    #define V1_MAX 255		//赤  255
    #define V1_MIN 85		//赤  50

    try {
	    image = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8)->image;
    }
    catch (cv_bridge::Exception& e) {
	    ROS_ERROR("cv_bridge exception: %s", e.what());
    }
    const int height = image.rows;
    const int width = image.cols;
    resize(image,image,cv::Size(),0.2,0.2);
    //imageが元データ
    frame=image;
    //orgがコピーしたデータ
    frame.copyTo(org);
    cv::imshow("aaa",org);

    imwrite("org.jpg", org);
    string input_filename = "org.jpg";
    // 画像を3チャンネル(BGR)で読み込む
  Mat input_image_rgb = imread(input_filename, CV_LOAD_IMAGE_COLOR);
  if (input_image_rgb.empty()) {
    cout << "入力画像が見つかりません" << endl;
  }

  // BGRからHSVへ変換
  Mat hsv_image, mask_image, output_image;
  cvtColor(input_image_rgb, hsv_image, CV_BGR2HSV, 3);


  //コピーしてみた
  Mat hsv_blur_image = hsv_image.clone();
  //青色抽出

  // inRangeを用いてフィルタリング
  Scalar s_min = Scalar(H_MIN, S_MIN, V_MIN);
  Scalar s_max = Scalar(H_MAX, S_MAX, V_MAX);
  inRange(hsv_blur_image, s_min, s_max, mask_image);
  // マスクを基に入力画像をフィルタリング
  input_image_rgb.copyTo(output_image, mask_image);

  // 結果の表示と保存
  //namedWindow("output");
  //imshow("output", output_image);
  imwrite("output.jpg", output_image);





  //取得した青色より輪郭と座標検出

  //const char *imagename = argc > 1 ? argv[1] : "C:/Users/kawabata yuusuke/Desktop/PD3/zikkenn/zikkenn3.png";
  //const char *imagename = argc > 1 ? argv[1] : "C:/Users/kawabata yuusuke/Desktop/PD3/zikkenn/koukuushasin6.png";
  const char *imagename = "output.jpg";
  //const int contour_index = argc > 2 ? atoi(argv[2]) : 1;
  //const int max_level = argc > 3 ? atoi(argv[3]) : 0;

  const int contour_index = -1;	//輪郭の指定
  const int max_level = 100;		//太さ
  int x_1[100] = { 0 };
  int y_1[100] = { 0 };


  cv::Mat src_img = cv::imread(imagename, 1);
  //if (src_img.empty()) return -1;

  // 2値化
  cv::Mat gray_img, bin_img;
  cv::cvtColor(src_img, gray_img, CV_BGR2GRAY);
  cv::threshold(gray_img, bin_img, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);			//単純な閾値値処理　設定した値より上か下で黒か白に配色する

  /// 輪郭の検出
  std::vector<std::vector<cv::Point> > contours;
  std::vector<cv::Vec4i> hierarchy;
  // 2値画像，輪郭（出力），階層構造（出力），輪郭抽出モード，輪郭の近似手法
  cv::findContours(bin_img, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

  int a = 0;

  /// 輪郭の描画
  // 画像，輪郭，描画輪郭指定インデックス(指定した輪郭だけを描画、-1で全指定)，色，太さ，種類，階層構造，描画輪郭の最大レベル
  cv::drawContours(src_img, contours, contour_index, cv::Scalar(150, 150, 0), 3, CV_AA, hierarchy, max_level);
  //cv::namedWindow("Contours", CV_WINDOW_AUTOSIZE | CV_WINDOW_FREERATIO);
  //cv::imshow("Contours", src_img);
  //cv::waitKey(0);
  //}

  double max_area = 300;
  int zahyou[10000] = { 0 };
  int b = 0;
  for (int j = 0; j < contours.size(); j++){				//contours.size()　　輪郭個数	//全ての輪org.jpg郭を対象にしている	at()は括弧の中身の数字にし互い値を指定する。配列のようなもの
    double area = contourArea(contours.at(j));			//contourArea()　輪郭面積計算　contours.at(j)　輪郭指定
    if (max_area < area){
      zahyou[b] = j;
      b++;
    }
  }

  for (int c = 0; c < b; c++){

    int count = contours.at(zahyou[c]).size();
    double x = 0;
    double y = 0;
    for (int k = 0; k < count; k++){
      x += contours.at(zahyou[c]).at(k).x;
      y += contours.at(zahyou[c]).at(k).y;
    }
    x /= count;
    y /= count;
    x_1[a] = x;						//青点の検出	座標格納
    y_1[a] = y;
    cv::circle(src_img, cv::Point(x, y), 25, cv::Scalar(0, 255, 255), 3, 4);
    std::cout << "個数" << a << "  X= " << (int)x << "  Y=  " << (int)y << std::endl;
    a++;
    //追加ここまで
  }


		//cout << "x1=" << x_1[0] << "   x2=" << x_1[1] <<"   x3="<< x_1[2] <<"   x4="<< x_1[3] << endl;
		//cout << "y1=" << y_1[0] << "   y2=" << y_1[1] << "   y3=" << y_1[2] << "   y4=" << y_1[3] << endl;
		int sendx[4] = { 0 };
		int sendy[4] = { 0 };
		for (int ka = 1; ka < a; ka++){
			for (int kb = 0; kb < a; kb++){
				for (int kc = 0; kc < a; kc++){
					for (int kd = 0; kd < a; kd++){
						if (x_1[ka] < x_1[kd] && y_1[ka] < y_1[kb] && x_1[ka] < x_1[kc] && y_1[ka] < y_1[kc]){	//それぞれの点kaが左上,kbが左下,kcが右下,kdが右上の座標を表すもののみを表す.
							if (x_1[kb] < x_1[kc] && x_1[kb] < x_1[kd] && y_1[kb] > y_1[kd]){
								if (y_1[kc] > y_1[kd]){
									sendx[0] = x_1[ka];
									sendx[1] = x_1[kb];
									sendx[2] = x_1[kc];
									sendx[3] = x_1[kd];

									sendy[0] = y_1[ka];
									sendy[1] = y_1[kb];
									sendy[2] = y_1[kc];
									sendy[3] = y_1[kd];
								}
							}
						}
					}
				}
			}
		}

		cout << "x1=" << sendx[0] << "   x2=" << sendx[1] << "   x3=" << sendx[2] << "   x4=" << sendx[3] << endl;
		cout << "y1=" << sendy[0] << "   y2=" << sendy[1] << "   y3=" << sendy[2] << "   y4=" << sendy[3] << endl;


		cv::imshow("blur_img", src_img); //変更







    //cv::imshow("aa", image);
   //cv::waitKey(1);
}
int main(int argc,char **argv){
    geometry_msgs::Twist bebop_cmd;
    geometry_msgs::Twist bebop_camera;
    ros::init(argc,argv,"cv_test");
    //ros::init(argc,argv,"bebop_driver");
    ros::NodeHandle nh;
    ImgDataSub imgSub;
    image_transport::ImageTransport it(nh);
    image_transport::Subscriber image_sub = it.subscribe("bebop2/image_raw",10,&ImgDataSub::imageCallback,&imgSub);
    BebopDriver driver(nh);
    char quit;




    while(quit != '@'){
        char ch = waitKey(1);
        if(ch == -1){
            ch = quit;
        }else
        quit = ch;
        //driver.camera_control(bebop_camera.angular.y,bebop_camera.angular.z);
        driver.camera_control(-60,0);
        ros::spinOnce();
    }
    //driver.land();
    return 0;
}
