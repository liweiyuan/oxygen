# Oxygen 项目

这是一个基于 ARM64 架构的 mini libc 实现，旨在为嵌入式系统提供轻量级的C标准库实现。目前实现了多个基础系统调用。

## 功能特性

- 使用 ARM64 汇编直接调用系统调用
- 已实现的系统调用：
  - mini_write: 向文件描述符写入数据
  - mini_open: 打开文件
  - close: 关闭文件
  - read: 从文件描述符读取数据 //todo
- 提供实用工具函数：
  - strlen: 计算字符串长度
  - strcmp: 比较两个字符串
  - memcpy: 内存拷贝
- 提供完整的测试套件
- 支持 CMake 和 Makefile 两种构建系统

## 项目结构

```
.
├── CMakeLists.txt        # CMake 构建配置
├── Makefile              # Makefile 构建配置
├── README.md             # 项目文档
├── clean.sh              # 清理脚本
├── build/                # 构建输出目录
├── make/                 # Makefile 构建输出
└── src/                  # 源代码目录
    ├── CMakeLists.txt    # 子目录 CMake 配置
    ├── mini_lib.h        # 库头文件
    ├── mini_libc_entry.S # 汇编入口
    ├── main.c            # 示例程序
    ├── open.c            # open 系统调用实现
    ├── util.c            # 工具函数实现
    ├── util.h            # 工具函数头文件
    ├── test_mini_lib.c   # 测试代码
    └── write.c           # write 系统调用实现
```

## 使用说明

### 快速开始

```c
#include "mini_lib.h"

int main() {
    int fd = mini_open("test.txt", O_WRONLY);
    mini_write(fd, "Hello, World!\n", 14);
    mini_close(fd);
    return 0;
}
```

### 使用 Make 编译

1. 编译项目：
   ```bash
   make
   ```

2. 运行测试程序：
   ```bash
   ./make/bin/test_mini_lib
   ```

### 使用 CMake 编译

1. 创建构建目录并配置项目：
   ```bash
   mkdir build
   cd build
   cmake ..
   ```

2. 编译项目：
   ```bash
   make
   ```

3. 运行测试程序：
   ```bash
   ./build/bin/test_mini_lib
   ```

### 清理构建

```bash
./clean.sh
```

## API 文档

### 系统调用

```c
int mini_open(const char *pathname, int flags);
int mini_close(int fd);
ssize_t mini_write(int fd, const void *buf, size_t count);
ssize_t mini_read(int fd, void *buf, size_t count);
```

### 工具函数

```c
size_t mini_strlen(const char *s);
int mini_strcmp(const char *s1, const char *s2);
void *mini_memcpy(void *dest, const void *src, size_t n);
```

## 贡献指南

欢迎贡献代码！请遵循以下步骤：

1. Fork 本项目
2. 创建特性分支 (`git checkout -b feature/AmazingFeature`)
3. 提交更改 (`git commit -m 'Add some AmazingFeature'`)
4. 推送分支 (`git push origin feature/AmazingFeature`)
5. 创建 Pull Request

## 许可证

本项目采用 MIT 许可证 - 详情请参阅 [LICENSE](LICENSE) 文件

## 未来计划

- [ ] 实现更多系统调用（mmap, fork 等）
- [ ] 添加性能测试
- [ ] 支持 x86_64 架构
- [ ] 添加文档生成工具
