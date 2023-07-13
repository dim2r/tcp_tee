cmake_minimum_required(VERSION 3.9)

project(tcp_tee CXX)
set(CMAKE_CXX_STANDARD 20)

# обратите внимание на аргумент TARGETS у команды conan_basic_setup
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)

conan_basic_setup(TARGETS)

#find_package(Threads REQUIRED)
find_package(Boost COMPONENTS log log_setup REQUIRED)

add_executable(${PROJECT_NAME} 
src/tcp_tee_main.cpp
)

# используем "импортированную" цель CONAN_PKG::boost
target_include_directories(${PROJECT_NAME} PRIVATE CONAN_PKG::boost)
target_link_libraries(${PROJECT_NAME} CONAN_PKG::boost)
