cmake_minimum_required(VERSION 3.15)
project(sfml_fs_widget)

set(CMAKE_CXX_STANDARD 20)
set(SFML_USE_STATIC_STD_LIBS ON)
set(SFML_STATIC_LIBRARIES ON)

set(sfml_fs_widget_DIR ${CMAKE_CURRENT_LIST_DIR})
find_package(sfml_fs_widget REQUIRED)

add_executable(sfml_fs_widget_main main.cpp)
target_link_libraries(sfml_fs_widget_main sfml_fs_widget)
