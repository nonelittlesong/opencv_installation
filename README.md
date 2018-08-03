## Websites
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
cmake_minimum_required(VERSION 2.8)  
project( Display )  
set(OpenCV_DIR "/usr/local/opencv2/share/OpenCV")  
set(OpenCV_FOUND 1)  
find_package( OpenCV REQUIRED )  
add_executable( Display display.cpp )  
target_link_libraries( Display ${OpenCV_LIBS} )  
## Notes
__updatedb:__  
用来创建或更新slocate命令所必需的数据库文件。updatedb命令的执行过程较长，因为在执行时它会遍历整个系统的目录树，并将所有的文件信息写入slocate数据库文件中。  
## Problems
