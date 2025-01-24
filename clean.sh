#!/bin/bash
# This script is used to clean the output of the program.
# It will remove all the files that are not needed.
# Get the current directory
current_dir=$(pwd)

echo "Cleaning the build..."
# Remove all the files that are not needed
rm -rf $current_dir/build

echo "Cleaning the make..."
# Remove all the files that are not needed
rm -rf $current_dir/make

echo "Cleaning the open.txt..."
# Remove all the files that are not needed
rm -rf $current_dir/open.txt

echo "Cleaning Successful!"