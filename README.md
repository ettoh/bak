# Back It Up

Simple CLI tool to create numbered backups of files and directories.

## Building Example
Currently, the project consists of a single cpp source file. You can compile it like in the example below. Please make sure that at least a C++ standard version of 17 or above is required.
```bash
cd /path/to/this/project
mkcd build
g++ -std=c++17 -o bak ../bak.cpp
```

## Usage
```bash
bak file1 [file2 ...]
```

This will create a copy of the given files (or folders) in the same directory as the original file. The backup will be named ``<file>-00.bak``. This is essentially the original filename (including its extension) with a unique backup ending. If there are previous backups present, the counter in this ending will increase accordingly.

To restore a backup, simply remove the backup specific ending.