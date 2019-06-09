#include "Windows.h"
#include "FolderType.h"

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

	// Copy directory in specific location
	bool CopyDirectoryWithPath(string from, string name, string to) {
		try {
			fs::copy(from + name, to + name, fs::copy_options::recursive);
			return true;
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

	// Copy file in specific location
	bool CopyFileWithPath(string from, string name, string extension, string to) {
		try {
			fs::copy_file(from + name + "." + extension, to + name + "." + extension);
			return true;
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

	// Read Structure From Windows
	bool ReadStructureFromSystem(FolderType* root) {
		string path = root->GetLocation() + root->GetName() + "\\";

		try {
			RecursiveReadStructure(root, path);
			return true;
		} catch (...) {
			return false;
		}
	}

	// Recursively read folder, file structure
	void RecursiveReadStructure(FolderType* root, string path) {
		for (const auto & entry : fs::directory_iterator(path)) {
			if (entry.is_directory()) {
				string name = entry.path().filename().u8string();
				string location = entry.path().parent_path().u8string() + "\\";

				FolderType *d = new FolderType(name, location, root);

				if (root->GetSubFolderList()->Add(d)) {
					root->SetFolderNumber(root->GetFolderNumber() + 1);
				}

				int n = root->GetSubFolderList()->GetBinary(*d);
				if (n == -1) return;

				RecursiveReadStructure(d, entry.path().u8string() + "\\");
			} else {
				size_t l = entry.path().filename().u8string().find_last_of(".");
				string name = entry.path().filename().u8string().substr(0, l);
				string extension = entry.path().extension().u8string().erase(0, 1);
				string location = entry.path().parent_path().u8string() + "\\";

				FileType *f = new FileType(name, extension, location, root);

				if (root->GetFileList()->Add(f)) {
					root->SetFileNumber(root->GetFileNumber() + 1);
				}
			}
		}
	}
}
