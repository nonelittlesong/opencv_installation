#!/usr/bin/env sh

NDK_BASE=/home/song/Android/Sdk/ndk-bundle
NDK_PROCESSOR=x86_64
NDK_PLATFORM_LEVEL=15
NDK_ABI=arm
NDK_COMPILER_VERSION=4.9

# Android NDK setup
NDK_SYSROOT=$NDK_BASE/platforms/android-$NDK_PLATFORM_LEVEL/arch-$NDK_ABI
NDK_UNAME=`uname -s | tr '[A-Z]' '[a-z]'`
if [ $NDK_ABI = "x86" ]; then
  HOST=i686-linux-android
  NDK_TOOLCHAIN=$NDK_ABI-$NDK_COMPILER_VERSION
else
  HOST=$NDK_ABI-linux-androideabi
  NDK_TOOLCHAIN=$HOST-$NDK_COMPILER_VERSION
fi
NDK_TOOLCHAIN_BASE=$NDK_BASE/toolchains/$NDK_TOOLCHAIN/prebuilt/$NDK_UNAME-$NDK_PROCESSOR
echo "dpc:" $NDK_TOOLCHAIN_BASE

CC="$NDK_TOOLCHAIN_BASE/bin/$HOST-gcc --sysroot=$NDK_SYSROOT"
LD=$NDK_TOOLCHAIN_BASE/bin/$HOST-ld
STRIP=$NDK_TOOLCHAIN_BASE/bin/$HOST-strip
PREFIX=/home/song/freetype-android

simple_config(){
  ./configure \
    --host=arm-linux-androideabi \
	--without-zlib \
    --without-png \
	--prefix=$PREFIX \

 # make -j4
  #make install
}

complex_config(){
  ./configure \
  CC="$CC" \
  LD="$LD" \
  CFLAGS="-std=gnu99 -mcpu=cortex-a8 -marm -mfloat-abi=softfp -mfpu=neon" \
  --host=$HOST \
  --with-sysroot="$NDK_SYSROOT" \
  --enable-static \
  --disable-shared \
  --prefix=$PREFIX \
  --without-bzip2

  make -j4
  make install
}

#make clean
simple_config
