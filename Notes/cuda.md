## /usr/bin/ld: cannot find -lopencv_dep_cudart

- OpenCV => 2.4.13  
- cuda => 9.0.125
- Operating System / Platform => Ubuntu 16.04  
- Compiler => gcc  

成功编译 opencv 和 cuda，在使用 opencv 时，出现问题：  
```diff
- /usr/bin/ld: cannot find -lopencv_dep_cudart
- /usr/bin/ld: cannot find -lopencv_dep_nppial
- /usr/bin/ld: cannot find -lopencv_dep_nppicc
- /usr/bin/ld: cannot find -lopencv_dep_nppicom
- /usr/bin/ld: cannot find -lopencv_dep_nppidei
- /usr/bin/ld: cannot find -lopencv_dep_nppif
- /usr/bin/ld: cannot find -lopencv_dep_nppig
- /usr/bin/ld: cannot find -lopencv_dep_nppim
- /usr/bin/ld: cannot find -lopencv_dep_nppist
- /usr/bin/ld: cannot find -lopencv_dep_nppisu
- /usr/bin/ld: cannot find -lopencv_dep_nppitc
```

原因：  
只对 OpenCV 2.4 测试了 CUDA 6.5 / 7.5。 不支持 CUDA 8 / 9。  

解决方案：  
```sh
ln -s /usr/local/cuda-9.0/targets/x86_64-linux/lib/libcudart.so /usr/local/lib/libopencv_dep_cudart.so
ln -s /usr/local/cuda-9.0/targets/x86_64-linux/lib/libnppial.so /usr/local/lib/libopencv_dep_nppial.so
ln -s /usr/local/cuda-9.0/targets/x86_64-linux/lib/libnppicc.so /usr/local/lib/libopencv_dep_nppicc.so
ln -s /usr/local/cuda-9.0/targets/x86_64-linux/lib/libnppicom.so /usr/local/lib/libopencv_dep_nppicom.so
ln -s /usr/local/cuda-9.0/targets/x86_64-linux/lib/libnppidei.so /usr/local/lib/libopencv_dep_nppidei.so
ln -s /usr/local/cuda-9.0/targets/x86_64-linux/lib/libnppif.so /usr/local/lib/libopencv_dep_nppif.so
ln -s /usr/local/cuda-9.0/targets/x86_64-linux/lib/libnppig.so /usr/local/lib/libopencv_dep_nppig.so
ln -s /usr/local/cuda-9.0/targets/x86_64-linux/lib/libnppim.so /usr/local/lib/libopencv_dep_nppim.so
ln -s /usr/local/cuda-9.0/targets/x86_64-linux/lib/libnppist.so /usr/local/lib/libopencv_dep_nppist.so
ln -s /usr/local/cuda-9.0/targets/x86_64-linux/lib/libnppisu.so /usr/local/lib/libopencv_dep_nppisu.so
ln -s /usr/local/cuda-9.0/targets/x86_64-linux/lib/libnppitc.so /usr/local/lib/libopencv_dep_nppitc.so
```
 
