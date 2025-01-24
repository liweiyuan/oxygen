#include "util.h"

int mini_main(int argc, char *argv[]) {
  // 打印命令行参数
  print_args(argc, argv);

  // 检查参数数量
  if (argc < 2) {
    print_usage(argv[0]);
    return 1;
  }

  // 根据命令调用相应处理函数
  if (string_compare(argv[1], "open") == 0) {
    return handle_open_command(argc, argv);
  } else if (string_compare(argv[1], "write") == 0) {
    return handle_write_command(argc, argv);
  } else {
    print_error("Unknown command");
    return 1;
  }
}
