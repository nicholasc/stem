#!/bin/bash

echo "Preparing to install libraries"

# create the libs folder
if [ ! -d "libs" ]; then
  echo "Creating libs folder"
  mkdir libs
else
  echo "Cleaning libs folder"
  rm -rf libs/*
fi

cd libs

echo "Downloading & installign GLFW"
curl -LO --retry 20 -O --progress-bar https://github.com/glfw/glfw/releases/download/3.3.4/glfw-3.3.4.zip
unzip glfw-3.3.4.zip
rm -f glfw-3.3.4.zip
mv glfw-3.3.4 glfw