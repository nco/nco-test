#!/usr/bin/env bash
cmake -H. -Bbuild 
pushd build
make
./nco_test