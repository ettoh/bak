#include <filesystem>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>

namespace fs = std::filesystem;

std::string escapeRegex(const std::string &input) {
    std::string output;
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

int main(int argc, char *argv[]) {
    // TODO multiple file inputs
    if (argc != 2) {
        std::cout << "Usage: bak <filename>" << std::endl;
        return 1;
    }

    // A final '/' would leave the filename empty.
    fs::path original_file(argv[1]);
    if (original_file.string().back() == '/') {
        original_file = original_file.parent_path();
    }

    // Does the given file exist?
    if (!fs::exists(original_file)) {
        std::cout << "File '" << original_file.string() << "' does not exist."
                  << std::endl;
        return 1;
    }

    // Use current directory if nothing else is specified.
    fs::path dir = original_file.parent_path();
    std::string original_filename = original_file.filename();
    if (dir.empty()) {
        dir = "./";
    }

    // Find latest backup id.
    int latest_id = -1;  // later, +1 would yield 0
    for (auto const &file : fs::directory_iterator{dir}) {
        const std::regex backup_file_regex(escapeRegex(original_filename) +
                                           "-([0-9]+)[.]bak");
        std::string filename = file.path().filename().string();
        std::smatch m;
        if (std::regex_search(filename, m, backup_file_regex)) {
            const int id = std::stoi(m[1]);  // m[0] is the entire filename
            if (id > latest_id) latest_id = id;
        }
    }

    // Prepare file path for backup.
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << latest_id + 1;
    fs::path new_file = dir.append(original_filename + "-" + oss.str() + ".bak");

    // Create backup.
    fs::copy(original_file, new_file, fs::copy_options::recursive);
    std::cout << "File was backed up as " << new_file.string() << std::endl;

    return 0;
}
