#ifndef _MINI_LIB_H_
#define _MINI_LIB_H_

#define NULL 0
#define AT_FDCWD -100
#define O_RDONLY 00000000
#define O_WRONLY 00000001
#define O_RDWR 00000002
#define O_CREAT 00000100
#define O_TRUNC 00001000
#define O_APPEND 00002000

// 文件操作函数声明
int mini_write(int fd, const void *buf, int count);

// 文件打开函数声明
int mini_open(const char *pathname, int flags, int mode);

// 文件关闭函数声明
int mini_close(int fd);

#endif