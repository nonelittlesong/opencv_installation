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
>* --arch默认为arm
>* 没有配置--install-dir,会生成压缩包：Package installed to /tmp/ndk-hm  
>  需要人工解压
>* --install-dir不能是已存在的文件夹


## 二、 编译so
1. 编写CmakeLists.txt
2. 编译
   ```
   cmake ..
   make
   ```
