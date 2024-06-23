cmake_minimum_required(VERSION 3.20)

project(Back)
set(executable_name "bak")

# header files
include_directories(include)

# clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add the executable
add_executable(${executable_name} src/main.cc src/backup.cc)
target_compile_features(${executable_name} PRIVATE cxx_std_20)

# Enable highest warning levels
if(MSVC)
  target_compile_options(${executable_name} PRIVATE /W4)
else()
  target_compile_options(${executable_name} PRIVATE -Wall -Wextra -Wpedantic)
endif()
