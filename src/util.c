#include "util.h"
#include "mini_lib.h"

void print_error(const char *message) {
  const char *error_prefix = "Error: ";
  int prefix_len = 0;
  while (error_prefix[prefix_len])
    prefix_len++;
  mini_write(2, error_prefix, prefix_len);
  int message_len = 0;
  while (message[message_len])
    message_len++;
  mini_write(2, message, message_len);
  mini_write(2, "\n", 1);
}

void print_usage(const char *program_name) {
  const char *usage = "Usage: ";
  int usage_len = 0;
  while (usage[usage_len])
    usage_len++;
  mini_write(2, usage, usage_len);
  int program_name_len = 0;
  while (program_name[program_name_len])
    program_name_len++;
  mini_write(2, program_name, program_name_len);
  mini_write(2, " [open|write] [arguments...]\n", 30);
}

void print_int(int value) {
  char buffer[12]; // 足够大以容纳一个32位整数的字符串表示
  int i = 0;
  int negative = value < 0;
  if (negative)
    value = -value;
  do {
    buffer[i++] = '0' + (value % 10);
    value /= 10;
  } while (value > 0);
  if (negative)
    buffer[i++] = '-';
  for (int j = i - 1; j >= 0; j--) {
    mini_write(1, &buffer[j], 1);
  }
}

void print_string(const char *str) {
  int len = 0;
  while (str[len])
    len++;
  mini_write(1, str, len);
}

int string_len(const char *str) {
  int len = 0;
  while (str[len]) {
    len++;
  }
  return len;
}

int string_compare(const char *s1, const char *s2) {
  while (*s1 && (*s1 == *s2)) {
    s1++;
    s2++;
  }
  return *(const unsigned char *)s1 - *(const unsigned char *)s2;
}

int string_to_int(const char *str) {
  int result = 0;
  int sign = 1;
  if (*str == '-') {
    sign = -1;
    str++;
  }
  while (*str >= '0' && *str <= '9') {
    result = result * 10 + (*str - '0');
    str++;
  }
  return sign * result;
}

// 新增辅助函数实现
void print_args(int argc, char *argv[]) {
  print_string("argc: ");
  print_int(argc);
  mini_write(1, "\n", 1);
  for (int i = 0; i < argc; i++) {
    print_string("argv[");
    print_int(i);
    print_string("]: ");
    print_string(argv[i]);
    mini_write(1, "\n", 1);
  }
}

int handle_open_command(int argc, char *argv[]) {
  if (argc < 3) {
    print_usage(argv[0]);
    return 1;
  }
  int fd = mini_open(argv[2], O_CREAT | O_APPEND | O_RDWR, 0644);
  if (fd > 0) {
    const char *success_message = "File opened successfully with fd: ";
    mini_write(fd, success_message, string_len(success_message));
    char buf[12];
    buf[0] = fd + '0';
    mini_write(fd, buf, 1);
    mini_write(fd, "\n", 1);
    mini_close(fd);
  } else {
    print_error("open");
  }
  return 0;
}

int handle_write_command(int argc, char *argv[]) {
  if (argc < 2) {
    print_usage(argv[0]);
    return 1;
  }
  mini_write(1, "hello\n", 6);
  return 0;
}

int handle_lseek_command() {
  // 测试 lseek 函数
  int fd = mini_open("test.txt", O_CREAT | O_RDWR, 0644);
  if (fd < 0) {
    print_error("open");
    return 1;
  }
  // 写入内容
  char buf[10] = "hello";
  mini_write(fd, buf, 5);
  // 移动文件指针
  int offset = 2;
  int whence = SEEK_SET;
  int result = mini_lseek(fd, offset, whence);
  if (result < 0) {
    print_error("lseek");
    return 1;
  }
  // 再次写入内容
  char buf2[10] = "world";
  mini_write(fd, buf2, 5);
  // 关闭文件
  mini_close(fd);
  return 0;
}
