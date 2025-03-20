#!/bin/bash
# 1. 打开文件
qemu-aarch64 ./build/bin/test_main open open.txt
cat open.txt

# 2.标准输出
echo "-------------------"
qemu-aarch64 ./build/bin/test_main write

# 3. 文件lseek测试
echo "-------------------"
qemu-aarch64 ./build/bin/test_main lseek
cat test.txt

# 4. 文件mmap测试
echo "-------------------"
qemu-aarch64 ./build/bin/test_main mmap
cat map.txt
