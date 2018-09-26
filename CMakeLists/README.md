# Android Studio 导入 OpenCV4Android 的 .a 或 .so
## Troubleshootings
### undefined cv::putText
直接配置build.gradle  
>cmake {  
  cppFlags "-std=c++11 -frtti -fexceptions -fopenmp"  
  abiFilters 'armeabi-v7a'  
  arguments "-DANDROID_STL=gnustl_shared"  
}  

yutrr
