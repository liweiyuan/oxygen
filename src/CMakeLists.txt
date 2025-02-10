# 设置交叉编译工具链
set(CMAKE_C_COMPILER aarch64-linux-gnu-gcc)
set(CMAKE_ASM_COMPILER aarch64-linux-gnu-as)

# 设置编译选项
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -nostdlib -no-pie -fno-stack-protector")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -nostdlib -no-pie -e _mini_libc_entry")

# 源文件目录
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# 输出目录
set(OBJ_DIR ${CMAKE_BINARY_DIR}/obj)
set(BIN_DIR ${CMAKE_BINARY_DIR}/bin)

# 创建输出目录（如果不存在）
file(MAKE_DIRECTORY ${OBJ_DIR} ${BIN_DIR})

# 汇编文件
file(GLOB ASM_SRCS ${SRC_DIR}/*.S)

# 将汇编文件编译为目标文件
foreach(ASM_SRC ${ASM_SRCS})
    get_filename_component(ASM_NAME ${ASM_SRC} NAME_WE)
    set(ASM_OBJ ${OBJ_DIR}/${ASM_NAME}.o)
    add_custom_command(
        OUTPUT ${ASM_OBJ}
        COMMAND ${CMAKE_ASM_COMPILER} -o ${ASM_OBJ} ${ASM_SRC}
        DEPENDS ${ASM_SRC}
    )
    list(APPEND ASM_OBJS ${ASM_OBJ})
endforeach()

# 定义目标文件列表
set(TARGETS
    test_mini_lib
    test_main
)

# 定义每个目标对应的 C 源文件
set(TEST_MINI_LIB_SOURCES ${SRC_DIR}/test_mini_lib.c)
set(TEST_MAIN_SOURCES ${SRC_DIR}/util.c ${SRC_DIR}/write.c ${SRC_DIR}/open.c ${SRC_DIR}/close.c ${SRC_DIR}/lseek.c ${SRC_DIR}/main.c)


# 编译 test_mini_lib
add_executable(test_mini_lib ${TEST_MINI_LIB_SOURCES} ${ASM_OBJS})
set_target_properties(test_mini_lib PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR}
)

# 编译 test_main
add_executable(test_main ${TEST_MAIN_SOURCES} ${ASM_OBJS})
set_target_properties(test_main PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR}
)
# 调试模式
option(DEBUG "Enable debug mode" OFF)
if(DEBUG)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")
endif()

# 自定义清理目标
add_custom_target(clean_all
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${OBJ_DIR}
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${BIN_DIR}
    COMMENT "Cleaning all build files"
)

# 提示信息
message(STATUS "Use 'make clean_all' to clean build files")