cmake_minimum_required(VERSION 3.10)

# 项目名称
project(protocol_stack C)

# 设置C标准（可选）
set(CMAKE_C_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)  # 添加这一行

# 查找 pcap 库
find_package(PkgConfig REQUIRED)
pkg_check_modules(PCAP REQUIRED libpcap)

# 添加可执行文件
add_executable(main main.c device.c)

# 包含头文件路径
target_include_directories(main PRIVATE ${PCAP_INCLUDE_DIRS} ./inc)

# 链接 pcap 库
target_link_libraries(main PRIVATE ${PCAP_LIBRARIES})
