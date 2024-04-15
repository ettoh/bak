#include "bak.h"

#include <format>
#include <iostream>
#include <regex>
#include <sstream>
#include <system_error>

namespace fs = std::filesystem;
using std::string;

// Transforms a string into a new string that is properly escaped to be used in
// a regex.
string Backup::escapeRegex(const string &input) {
  string output;
  for (char c : input) {
    if (c == '\\' || c == '.' || c == '*' || c == '+' || c == '?' || c == '|' ||
        c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}' ||
        c == '^' || c == '$') {
      output.push_back('\\');
    }
    output.push_back(c);
  }
  return output;
}

// Looks for all previous backups of a given file in a given directory. A backup
// is a file in the form "ORIGINAL_FILENAME-N.bak", where N is the backup ID.
// The largest backup ID is returned.
int Backup::latestBackupID(const fs::path &dir,
                           const string &original_filename) {
  // Find latest backup id.
  int latest_id = -1;  // later, +1 would yield 0
  for (auto const &file : fs::directory_iterator{dir}) {
    const std::regex backup_file_regex(escapeRegex(original_filename) +
                                       "-([0-9]+)[.]bak");
    string filename = file.path().filename().string();
    std::smatch m;
    if (std::regex_search(filename, m, backup_file_regex)) {
      const int id = std::stoi(m[1]);  // m[0] is the entire filename
      if (id > latest_id) latest_id = id;
    }
  }
  return latest_id;
}

// Destination for the backup.
fs::path Backup::getBackupPath(const fs::path &original_file) {
  // Extract base directory; use current directory if nothing else is specified.
  fs::path dir = original_file.parent_path();
  if (dir.empty()) {
    dir = "./";
  }

  // new filename format: e.g. "directory/old_filename.oldtype-03.bak"
  int latest_id = latestBackupID(dir, original_file.filename());
  fs::path new_file = dir.append(original_file.filename().string() + "-" +
                                 std::format("{:02}", latest_id + 1) + ".bak");
  return new_file;
}

// Creates a backup of a file or directory. The backup is named
// "ORIGINAL_FILENAME-N.bak", where N is the backup ID. The backup ID is
// increased for each backup (that lives in the same folder). The new file
// is stored in the same folder as the original file.
void Backup::backup(const string &path) {
  // Later, path is split into directory and filename. If the user input ends
  // with '/', the filename would be empty. Therefore, remove an ending '/'.
  fs::path original_file(path);
  if (original_file.string().back() == '/') {
    original_file = original_file.parent_path();
  }

  // Does the given file exist?
  if (!fs::exists(original_file)) {
    std::cout << "File '" << original_file.string() << "' does not exist."
              << std::endl;
    return;
  }

  // Create backup.
  fs::path new_file = getBackupPath(original_file);
  std::error_code copy_error;
  fs::copy(original_file, new_file, fs::copy_options::recursive, copy_error);
  if (copy_error) {
    std::cerr << "Error: Unable to copy file " << new_file.string()
              << ". It already exists." << std::endl;
  } else {
    string filetype = fs::is_directory(original_file) ? "Folder" : "File";
    std::cout << filetype << " '" << original_file.string()
              << "' was backed up as " << new_file.string() << std::endl;
  }
}
