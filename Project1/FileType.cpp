#include "FileType.h"

using namespace std;

// Operator = to support deep copy
FileType & FileType::operator=(const FileType & data) {
	if (this != &data) {
		SetName(data.GetName());
		SetExtension(data.GetExtension());
		SetLocation(data.GetLocation());
		SetParent(data.GetParent());
		SetCreateDate(data.GetCreateDate());
		SetModifyDate(data.GetModifyDate());
		SetAccessDate(data.GetAccessDate());
	}

	return *this;
}

// Operator == to support compare two FolderType
bool FileType::operator==(const FileType & data) {
	if (m_Name == data.GetName()
		&& m_Extension == data.GetExtension()
		&& m_Location == data.GetLocation()) {
		return true;
	}
	else {
		return false;
	}
}

// Set file create date to now
void FileType::SetCreateDateToNow() {
	time_t date;
	time(&date);

	m_CreateDate = FormatTimeToString(date);
}

// Set file modify date to now
void FileType::SetModifyDateToNow() {
	time_t date;
	time(&date);

	m_ModifyDate = FormatTimeToString(date);
}

// Set file access date to now
void FileType::SetAccessDateToNow() {
	time_t date;
	time(&date);

	m_AccessDate = FormatTimeToString(date);
}

// Set file name from keyboard.
void FileType::SetNameFromKB() {
	string temp;

	while (true) {
		cout << "\tFile Name: ";
		cin >> temp;

		if (Windows::IsValidName(temp)) {
			m_Name = temp;
			break;
		} else {
			cout << endl << "\tNot allowed character included." << endl;
		}
	}
}

// Set file extension from keyboard.
void FileType::SetExtensionFromKB() {
	string temp;

	while (true) {
		cout << "\tFile Extension: ";
		cin >> temp;

		if (Windows::IsValidName(temp)) {
			m_Extension = temp;
			break;
		} else {
			cout << endl << "\tNot allowed character included." << endl;
		}
	}
}

// Set file location from keyboard.
void FileType::SetLocationFromKB() {
	cout << "\tFile Location: ";
	cin >> m_Location;
}

// Set File property from keyboard.
void FileType::SetPropertyFromKB(string location) {
	SetNameFromKB();
	SetExtensionFromKB();
	SetLocation(location);
}

// Set File property from keyboard.
void FileType::SetPropertyFromKB() {
	SetNameFromKB();
	SetExtensionFromKB();
	SetLocationFromKB();
}

// Convert time_t to string format.
string FileType::FormatTimeToString(time_t date) {
	struct tm ti;
	localtime_s(&ti, &date);

	stringstream ss;
	ss << setw(4) << ti.tm_year + 1900 << setfill('0') << "."
		<< setw(2) << ti.tm_mon + 1 << setfill('0') << "."
		<< setw(2) << ti.tm_mday << setfill('0') << " "
		<< setw(2) << ti.tm_hour << setfill('0') << ":"
		<< setw(2) << ti.tm_min << setfill('0') << ":"
		<< setw(2) << ti.tm_sec << "\0";

	return ss.str();  // copy the stream buffer to name
}