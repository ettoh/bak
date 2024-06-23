# Back It Up

Simple CLI tool to create numbered backups of files and directories.

Do you want to make changes to a file or a folder but want to keep a copy of the original just in case? Just back it up with `bak`!

## Prerequisites

-   C++20 or above
-   CMake

## Building

Compile the project using the steps below.

```bash
# Navigate to the project directory
cd /path/to/this/project

# Ceate and change to the build directory
mkdir build
cd build

# Generate the build files
cmake ../ -DCMAKE_BUILD_TYPE=Release

# Build the project
cmake --build .
```

## Usage

To use the `bak` tool, simply execute the following command:

```bash
bak file1 [file2 ...]
```

This will create numbered backups of the specified files (or folders) in the same directory as the original. The backups will be named `<file>-00.bak`, `<file>-01.bak`, etc. The number will increment based on the existing backups.

To restore a backup, simply remove the backup specific ending.

### Example

Suppose you have a file named `example.txt`. Running the following command:

```bash
bak example.txt
```

will create a backup named `example.txt-00.bak`. If you run the command again, it will create `example.txt-01.bak`, and so on.

## Limitations

By default, symlinks are not followed.
