#ifndef _MINI_LIB_H_
#define _MINI_LIB_H_

#define __MINI_ALIGN(__value, __alignment)                                     \
  (((__value) + (__alignment) - 1) & ~((__alignment) - 1))

#define NULL 0
#define AT_FDCWD -100
#define O_RDONLY 00000000
#define O_WRONLY 00000001
#define O_RDWR 00000002
#define O_CREAT 00000100
#define O_TRUNC 00001000
#define O_APPEND 00002000

// mmap相关常量定义
#define PROT_READ 0x1
#define PROT_WRITE 0x2
#define MAP_SHARED 0x01      /* Share changes.  */
#define MAP_PRIVATE 0x02     /* Changes are private.  */
#define MAP_ANONYMOUS 0x20   /* Don't use a file.  */
#define MAP_STACK 0x20000    /* Stack mapping.  */
#define MAP_GROWSDOWN 0x0100 /* Stack grows down.  */
#define MAP_HUGETLB 0x40000  /* Create huge page mapping.  */
#define MAP_FIXED 0x10       /* Interpret addr exactly.  */
#define MAP_FILE 0
#define MAP_ANON MAP_ANONYMOUS
#define MAP_FAILED ((void *)-1)

enum { SEEK_SET = 0, SEEK_CUR, SEEK_END };

// 文件操作函数声明
int mini_write(int fd, const void *buf, int count);

// 文件打开函数声明
int mini_open(const char *pathname, int flags, int mode);

// 文件关闭函数声明
int mini_close(int fd);

// lseek 函数声明
int mini_lseek(int fd, int offset, int whence);

// mmap 函数声明
void *mini_mmap(void *addr, long size, int prot, int flags, int fd,
                long offset);

// unmmap 函数申明
int mini_munmap(void *addr, long size);

#endif