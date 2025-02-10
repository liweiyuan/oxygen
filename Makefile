# 配置
CC = aarch64-linux-gnu-gcc
AS = aarch64-linux-gnu-as
CFLAGS = -nostdlib -no-pie -fno-stack-protector
LDFLAGS = -nostdlib -no-pie -e _mini_libc_entry
SRC_DIR = src
OBJ_DIR = make/obj
BIN_DIR = make/bin

# 目标文件
TARGETS = $(BIN_DIR)/test_mini_lib $(BIN_DIR)/test_main

# 汇编文件
ASM_SRCS = $(wildcard $(SRC_DIR)/*.S)
ASM_OBJS = $(patsubst $(SRC_DIR)/%.S, $(OBJ_DIR)/%.o, $(ASM_SRCS))

# 每个目标文件对应的 C 源文件
SRC_TEST_MINI_LIB = $(SRC_DIR)/test_mini_lib.c
SRC_TEST_MAIN = $(SRC_DIR)/util.c $(SRC_DIR)/write.c $(SRC_DIR)/open.c $(SRC_DIR)/close.c  $(SRC_DIR)/lseek.c $(SRC_DIR)/main.c

# 将 C 源文件转换为目标文件
OBJ_TEST_MINI_LIB = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_TEST_MINI_LIB))
OBJ_TEST_MAIN = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_TEST_MAIN))

# 默认目标
all: $(TARGETS)

# 调试模式
debug: CFLAGS += -g
debug: all

# 链接目标文件生成可执行文件
$(BIN_DIR)/test_mini_lib: $(OBJ_TEST_MINI_LIB) $(ASM_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(LDFLAGS) -o $@ $^

$(BIN_DIR)/test_main: $(OBJ_TEST_MAIN) $(ASM_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(LDFLAGS) -o $@ $^


# 编译 C 源文件
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# 汇编汇编源文件
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.S
	@mkdir -p $(OBJ_DIR)
	$(AS) -o $@ $<

# 清理生成的文件
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) test.txt

# 包含自动生成的依赖文件
-include $(OBJ_TEST_MINI_LIB:.o=.d)
-include $(OBJ_TEST_WRITE:.o=.d)

# 伪目标
.PHONY: all debug cleans