#include "Windows.h"

namespace Windows {
	// Convert string to PCWSTR (Pointer to Constant unicode Wide_STRing)
	PCWSTR StringToPCWSTR(const string& str) {
		int slength = (int)str.length() + 1;
		int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), slength, 0, 0);

		wchar_t* buf = new wchar_t[len];
		MultiByteToWideChar(CP_ACP, 0, str.c_str(), slength, buf, len);

		wstring* result = new wstring(buf);
		delete[] buf;

		PCWSTR pResult = result->c_str();
		return pResult;
	};

	// Create directory in specific location
	int CreateDirectoryWithPath(string folderWithPath) {
		return SHCreateDirectory(NULL, StringToPCWSTR(folderWithPath));
	};

	// Create file in specific location
	int CreateFileWithPath(string location, string name, string extension) {
		ofstream out;
		out.open(location + name + "." + extension);

		if (out.fail()) {
			out.close();
			return 0;
		}
		else {
			out.close();
			return 1;
		}
	};

	// Execute file in Windows
	int ExecuteFile(string location, string name, string extension) {
		int hinst = static_cast<int>(reinterpret_cast<uintptr_t>(
			ShellExecute(NULL, L"open", StringToPCWSTR(location + name + "." + extension), NULL, NULL, SW_SHOW)
			));

		if (hinst <= 32) {
			return 1;
		}
		else {
			return 0;
		}
	};

	// TODO: Read Structure From Windows
	int ReadStructureFromSystem(FolderType& root) {
		return 0;
	};
}