*wiki*  
* [opencv in android](https://github.com/nonelittlesong/study-opencv/wiki/opencv-in-android)

## References
- [github](https://github.com/opencv)  
- [opencv.org](https://opencv.org/)  
- [Ubuntu - OpenCV 源码安装与测试](https://www.aiuai.cn/aifarm792.html) by aiuai.cn  

## [Install](https://docs.opencv.org/2.4.13.6/doc/tutorials/introduction/linux_install/linux_install.html?highlight=install)
官方推荐依赖：  
```
[compiler] sudo apt-get install build-essential
[required] sudo apt-get install cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
[optional] sudo apt-get install python-dev python-numpy libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev libjasper-dev libdc1394-22-dev
```
OPENGL 支持依赖库：  
```
sudo apt-get install freeglut3-dev \
                     mesa-common-dev \
                     libgtkglext1 \
                     libgtkglext1-dev
```
视频解码支持依赖库：  
```
sudo apt-get install checkinstall \
                     yasm \
                     libgstreamer0.10-dev \
                     libgstreamer-plugins-base0.10-dev \
                     libv4l-dev \
                     libtbb-dev \
                     libqt4-dev \
                     libgtk2.0-dev \
                     libmp3lame-dev \
                     libtheora-dev \
                     libvorbis-dev \
                     libxvidcore-dev \
                     x264 \
                     v4l-utils
```
其它可能依赖项：  
```
sudo apt-get install libgphoto2-dev \
                     libavresample-dev \ 
                     liblapacke-dev \
                     gtk+-3.0 \
                     libgtk-3-dev \ 
                     libeigen3-dev \ 
                     tesseract-ocr \
                     liblept5 \
                     leptonica-progs \
                     libleptonica-dev
```

# 下载
$ wget http://downloads.sourceforge.net/project/opencvlibrary/opencv-unix/2.4.13/opencv-2.4.13.zip
$ unzip opencv-2.4.13.zip
$ cd opencv-2.4.13
$ mkdir release
$ cd release
# 编译
$ cmake -G "Unix Makefiles" -DCMAKE_CXX_COMPILER=/usr/bin/g++ CMAKE_C_COMPILER=/usr/bin/gcc -DCMAKE_BUILD_TYPE=RELEASE -DCMAKE_INSTALL_PREFIX=/usr/local -DWITH_TBB=ON -DBUILD_NEW_PYTHON_SUPPORT=ON -DWITH_V4L=ON -DINSTALL_C_EXAMPLES=ON -DINSTALL_PYTHON_EXAMPLES=ON -DBUILD_EXAMPLES=ON -DWITH_QT=ON -DWITH_OPENGL=ON -DBUILD_FAT_JAVA_LIB=ON -DINSTALL_TO_MANGLED_PATHS=ON -DINSTALL_CREATE_DISTRIB=ON -DINSTALL_TESTS=ON -DENABLE_FAST_MATH=ON -DWITH_IMAGEIO=ON -DBUILD_SHARED_LIBS=OFF -DWITH_GSTREAMER=ON ..
$ make all -j2 # 2 cores
$ sudo make install
```

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
### 构造和赋值
```
Mat A, C;                                 // creates just the header parts
A = imread(argv[1], CV_LOAD_IMAGE_COLOR); // here we'll know the method used (allocate matrix)
Mat B(A);                                 // Use the copy constructor
C = A;                                    // Assignment operator
```
上述对象，都指向同一个矩阵。  
Mat(int _rows, int _cols, int _type, void* _data, size_t _step=AUTO_STEP);  

## 3. Problems
### warning: CPACK_PACKAGE_VERSION does not match version provided by version.hpp header!
无视他  
