#!/bin/sh
export PATH=$PATH:$PWD/rootsys/bin:$PWD/rootsys/usr/bin
export TARGET=i686-pc-dayos
export CC=$TARGET-gcc
export CXX=$TARGET-g++

sh
