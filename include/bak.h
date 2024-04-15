#ifndef BAK_H
#define BAK_H

#include <filesystem>
#include <string>

class Backup {
 public:
  // Creates a backup of a file or directory. The backup is named
  // "ORIGINAL_FILENAME-N.bak", where N is the backup ID. The backup ID is
  // increased for each backup (that lives in the same folder). The new file
  // is stored in the same folder as the original file.
  static void backup(const std::string &path);

 private:
  // Transforms a string into a new string that is properly escaped to be used
  // in a regex.
  static std::string escapeRegex(const std::string &input);

  // Looks for all previous backups of a given file in a given directory. A
  // backup is a file in the form "ORIGINAL_FILENAME-N.bak", where N is the
  // backup ID. The largest backup ID is returned.
  static int latestBackupID(const std::filesystem::path &dir,
                            const std::string &original_filename);

  // Destination for the backup.
  static std::filesystem::path getBackupPath(
      const std::filesystem::path &original_file);
};

#endif
