#!/bin/bash


## ubuntu16.04
build_linux_fn () 
{
    mkdir -p build-linux
    pushd build-linux
    cmake ..
    make
    make install
    popd
}

## android armv7
build_android_fn ()
{
    mkdir -p build-android-armv7
    pushd build-android-armv7
    cmake -DCMAKE_TOOLCHAIN_FILE=../android.toolchain.cmake \
          -DANDROID_ABI="armeabi-v7a with NEON" \
          -DANDROID_NATIVE_API_LEVEL=android-9 \
          -DANDROID_FORCE_ARM_BUILD=OFF \
          -DANDROID_STL_FORCE_FEATURES=OFF ..
    make
    make install
    popd
}

build_clean_fn ()
{
    echo "remove build file"
    rm -rf build-android-armv7
    rm -rf build-linux
    echo "build clean done"
}

error_fn () 
{
    echo "unknown argument"
    echo "available targets: linux||android||clean"
}

if [ $# = 0 ]; then
    echo "error: target missing!"
    echo "available targets: linux||android"
    echo "sample usage: ./build.sh linux"
else
    if [ $1 = "linux" ]; then
        build_linux_fn
    elif [ $1 = "android" ]; then
        build_android_fn
    elif [ $1 = "clean" ]; then
        build_clean_fn        
    else
        error_fn
    fi
fi

