**wiki**  
* [opencv in android](https://github.com/nonelittlesong/study-opencv/wiki/opencv-in-android)

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
## 3. Problems
### warning: CPACK_PACKAGE_VERSION does not match version provided by version.hpp header!
无视他  
