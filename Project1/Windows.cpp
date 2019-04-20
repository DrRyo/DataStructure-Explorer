#include "Windows.h"

namespace fs = std::filesystem;

namespace Windows {
	// Convert string to PCWSTR (Pointer to Constant unicode Wide_STRing)
	//PCWSTR StringToPCWSTR(const string& str) {
	//	int slength = (int)str.length() + 1;
	//	int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), slength, 0, 0);

	//	wchar_t* buf = new wchar_t[len];
	//	MultiByteToWideChar(CP_ACP, 0, str.c_str(), slength, buf, len);

	//	wstring* result = new wstring(buf);
	//	delete[] buf;

	//	PCWSTR pResult = result->c_str();
	//	return pResult;
	//}

	// Create directory in specific location
	bool CreateDirectoryWithPath(string folderWithPath) {
		try {
			return fs::create_directories(folderWithPath);
		} catch (...) {
			return 0;
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
			return 0;
		}
	}

	// Create file in specific location
	bool CreateFileWithPath(string location, string name, string extension) {
		ofstream out;
		out.open(location + name + "." + extension);

		if (out.fail()) {
			out.close();
			return 0;
		} else {
			out.close();
			return 1;
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
			return 0;
		}
	}

	// Execute file in Windows
	int ExecuteFile(string location, string name, string extension) {
		string file = location + name + "." + extension;
		try {
			system(file.c_str());
			return 1;
		} catch (...) {
			return 0;
		}
	}

	// TODO: Read Structure From Windows
	int ReadStructureFromSystem(FolderType& root) {
		return 0;
	}
}