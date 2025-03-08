cmake_minimum_required(VERSION 3.6)

project(zwhmxsSLBPlugins)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./output/)

include_directories(include/)

if(MSVC)
    add_compile_options(/utf-8)
else()
    add_compile_options(-finput-charset=UTF-8 -fexec-charset=UTF-8)
endif()

aux_source_directory(./include/SlackBot/ SLBPluginBase)

add_library(HoroscopeToday SHARED HoroscopeToday.cpp ${SLBPluginBase})
add_library(HoroscopeTodayEX SHARED HoroscopeTodayEx.cpp ${SLBPluginBase})
add_library(BanLists SHARED BanLists.cpp ${SLBPluginBase})