cmake_minimum_required(VERSION 3.20)
project(PSP5 VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(psp5
  src/main.cpp
  src/core/Emulator.cpp
  src/core/Memory.cpp
  src/loader/PspLoader.cpp
  src/platform/Platform.cpp
)
target_include_directories(psp5 PRIVATE src)
if(MSVC)
  target_compile_options(psp5 PRIVATE /W4)
else()
  target_compile_options(psp5 PRIVATE -Wall -Wextra -Wpedantic)
endif()
