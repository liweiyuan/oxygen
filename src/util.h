#ifndef _UTIL_H_
#define _UTIL_H_

void print_error(const char *);

void print_usage(const char *);

void print_string(const char *);

void print_int(int);

int string_len(const char *);

int string_compare(const char *, const char *);

int string_to_int(const char *);

// 新增文件操作相关辅助函数
void print_args(int argc, char *argv[]);
int handle_open_command(int argc, char *argv[]);
int handle_write_command(int argc, char *argv[]);

#endif
