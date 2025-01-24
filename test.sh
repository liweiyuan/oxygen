#!/bin/bash
echo "Running cmake_test.sh..."
# 执行 cmake_test.sh 脚本
./cmake_test.sh

# 检查 cmake_test.sh 的退出状态
if [ $? -ne 0 ]; then
    echo "cmake_test.sh failed. Exiting."
    exit 1
fi
echo "######################"
echo "Running make_test.sh..."
# 执行 make_test.sh 脚本
./make_test.sh

# 检查 make_test.sh 的退出状态
if [ $? -ne 0 ]; then
    echo "make_test.sh failed. Exiting."
    exit 1
fi
