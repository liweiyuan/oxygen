#!/bin/bash
# 1. 打开文件
qemu-aarch64 ./make/bin/test_main open open.txt
cat open.txt

echo "-------------------"
# 2.标准输出
qemu-aarch64 ./make/bin/test_main write