参考：
* https://blog.csdn.net/minghuang2017/article/details/79000345

## 一、 编译独立工具链
`$ ./make-standalone-toolchain.sh --help`查看用法  
运行脚本：  
```
./make-standalone-toolchain.sh \
--toolchain=arm-linux-androideabi-4.9 \
--arch=arm \
--platform=android-15
```
Package installed to /tmp/ndk-hm  
解压  

## 二、 编译so
1. 编写CmakeLists.txt
2. 编译
   ```
   cmake ..
   make
   ```
