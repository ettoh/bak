cmake_minimum_required(VERSION 3.20)

project(Back)
set(target_bak "bak")

# header files
include_directories(include)

# clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add the executable
add_executable(${target_bak} src/main.cc src/backup.cc)
target_compile_features(${target_bak} PRIVATE cxx_std_20)

# Enable highest warning levels
if(MSVC)
  target_compile_options(${target_bak} PRIVATE /W4)
else()
  target_compile_options(${target_bak} PRIVATE -Wall -Wextra -Wpedantic)
endif()
