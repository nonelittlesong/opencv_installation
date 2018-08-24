**wiki**  
* opencv in android

## 1. References
[github](https://github.com/opencv)  
[opencv.org](https://opencv.org/)  
## Install
[reference1](https://github.com/L706077/Ubuntu16.04-Install-Opencv2.4.13)  
  
__opencv3 in ubuntu:__  
<ol>
  <li>配置/etc/ld.so.conf.d/opencv.conf，再ldconfig</li>
  <li>配置bash.bashrc（.bashrc或.zshrc）</li>
  <li>updatedb</li>
  <li>CMakeLists.txt</li>
</ol>

__CMakeLists.txt:__  
```c++
cmake_minimum_required(VERSION 2.8)
set(OpenCV_DIR "/usr/local/opencv2/share/OpenCV")
project( Display )
//set(OpenCV_FOUND 1)
find_package( OpenCV REQUIRED )
add_executable( Display display.cpp )
target_link_libraries( Display ${OpenCV_LIBS} )
```
__pkg-config:__  
[https://blog.csdn.net/newchenxf/article/details/51750239](https://blog.csdn.net/newchenxf/article/details/51750239)  
## 2. Notes
[opencv doc](https://www.docs.opencv.org/2.4/)  
#### putText
Draws a text String  
```c++
void putText(Mat& img, const string& text, Point org, int fontFace, double fontScale, Scalar color, int thickness = 1, int lineType = 8, bool bottomLeftOrigin = false)
```
#### mask
```c++
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	Mat image, mask;
	Rect r1(100, 100, 250, 300);
	Mat img1, img2, img3, img4;
	image = imread("test1.jpeg");
	mask = Mat::zeros(image.size(), CV_8UC1);
	mask(r1).setTo(255);
	img1 = image(r1);
	image.copyTo(img2, mask);

	image.copyTo(img3);
	img3.setTo(0, mask);

	imshow("Image sequence", image);
	imshow("img1", img1);
	imshow("img2", img2);
	imshow("img3", img3);
	imshow("mask", mask);

	waitKey();
	return 0;
}
```
## 3. Problems
