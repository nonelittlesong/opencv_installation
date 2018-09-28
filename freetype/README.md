# freetype
参考：  
* [android编译ffmpeg，x264，freetype](https://blog.csdn.net/libin534226097/article/details/79839201)
* [Build FFmpeg with Freetype2 for ARM](https://stackoverflow.com/questions/23650885/build-ffmpeg-with-freetype2-for-arm)
* [Configure选项配置的详细介绍](https://blog.csdn.net/bamboolsu/article/details/43063617)

## Troubleshootings
### 1. 交叉编译时check失败
需要将交叉编译所使用的编译器的路径添加到PATH中  
然后./configure
```
$ PATH=/add/your/compiler/bin:$PATH #不需要export
$ ./confugure \
$ --build=x86_64-linux-gnu \ # 未验证，可省
$ --host=arm-linux-androideabi \
$ --without-zlib \
$ --without-png \
$ --prefix=/home/song/freetype-android
```
