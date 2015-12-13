#!/bin/sh
export PREFIX=$PWD/rootsys
export PATH=$PATH:$PWD/rootsys/bin:$PREFIX/usr/bin
export TARGET=i686-pc-dayos
export CC=$TARGET-gcc
export CXX=$TARGET-g++

sh
