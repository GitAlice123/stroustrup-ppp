cmake_minimum_required(VERSION 3.10)

project(stroustrup-ppp)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 只需要编译text_lib下的std_lib_facilities.h和calculator00.cpp
set(SOURCES
    chapter06/ex06_english.cpp
)

# 消息输出，列出所有找到的源文件
message(STATUS "Source files:")
foreach(FILE ${SOURCES})
    message(STATUS " - ${FILE}")
endforeach()

# 包含头文件目录
include_directories(.)  # 当前目录作为头文件搜索路径
# 如果有特定的子目录需要包含，可以添加如下：
include_directories(include text_lib)

# 添加一个可执行文件
add_executable(${PROJECT_NAME} ${SOURCES})

# 如果有外部库需要链接
# target_link_libraries(${PROJECT_NAME} PRIVATE some_libraries)

# 启用编译器警告
if(MSVC)
    # 对于MSVC，启用更高级别的警告
    add_compile_options(/W4)
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    # 对于GCC，启用所有警告并禁用某些警告
    add_compile_options(-Wall -Wno-unused-variable)
endif()

# 如果需要，添加自定义编译选项
# add_compile_options(-O2 -g)