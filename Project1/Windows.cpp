#include "Windows.h"

namespace fs = std::filesystem;

namespace Windows {
	// Validate if there is no special characters
	bool IsValidName(const string& name) {
		if (name.find_first_of("\\/:*?\"<>|,.") == string::npos) {
			return true;
		} else {
			return false;
		}
	}
	// Create directory in specific location
	bool CreateDirectoryWithPath(string folderWithPath) {
		try {
			return fs::create_directories(folderWithPath);
		} catch (...) {
			return false;
		}
	}

	// Rename directory in specific location
	void RenameDirectoryWithPath(string location, string name, string rename) {
		try {
			fs::rename(location + name, location + rename);
		} catch (...) {}
	}

	// Delete directory in specific location
	bool DeleteDirectoryWithPath(string location, string name) {
		try {
			return fs::remove_all(location + name);
		} catch (...) {
			return false;
		}
	}

	// Create file in specific location
	bool CreateFileWithPath(string location, string name, string extension) {
		ofstream out;
		out.open(location + name + "." + extension);

		if (out.fail()) {
			out.close();
			return false;
		} else {
			out.close();
			return true;
		}
	}

	// Rename file in specific location
	void RenameFileWithPath(string location, string name, string extension, string rename, string reextension) {
		try {
			fs::rename(location + name + "." + extension, location + rename + "." + reextension);
		} catch (...) {}
	}

	// Delete file in specific location
	bool DeleteFileWithPath(string location, string name, string extension) {
		try {
			return fs::remove(location + name + "." + extension);
		} catch (...) {
			return false;
		}
	}

	// Execute file in Windows
	int ExecuteFile(string location, string name, string extension) {
		string file = location + name + "." + extension;
		try {
			system(file.c_str());
			return true;
		} catch (...) {
			return false;
		}
	}

	// TODO: Read Structure From Windows
	bool ReadStructureFromSystem(FolderType& root) {
		return false;
	}
}