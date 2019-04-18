#include "FolderType.h"
#include "SortedList.h"

using namespace std;

// Operator = to support deep copy
FolderType & FolderType::operator=(const FolderType & data) {
	if (this != &data) {
		SetName(data.GetName());
		SetLocation(data.GetLocation());
		SetCreateDate(data.GetCreateDate());
		SetModifyDate(data.GetModifyDate());
		SetAccessDate(data.GetAccessDate());
		SetFolderNumber(data.GetFolderNumber());
		SetFileNumber(data.GetFileNumber());
		SetSubFolderList(data.GetSubFolderList());
		SetFileList(data.GetFileList());
		SetParent(data.GetParent());
	}

	return *this;
}

// Operator == to support compare two FolderType
bool FolderType::operator==(const FolderType & data) {
	if (m_Name == data.GetName() && m_Location == data.GetLocation()) {
		return true;
	} else {
		return false;
	}
}

// Set folder create date to now
void FolderType::SetCreateDateToNow() {
	time_t date;
	time(&date);

	m_CreateDate = FormatTimeToString(date);
}

// Set folder modify date to now
void FolderType::SetModifyDateToNow() {
	time_t date;
	time(&date);

	m_ModifyDate = FormatTimeToString(date);
}

// Set folder access date to now
void FolderType::SetAccessDateToNow() {
	time_t date;
	time(&date);

	m_AccessDate = FormatTimeToString(date);
}

// Set number of folder
void FolderType::SetFolderNumber(int number) {
	m_folderNumber = number;
}

// Set number of file
void FolderType::SetFileNumber(int number) {
	m_fileNumber = number;
}

// Set sub folder list
void FolderType::SetSubFolderList(SortedList<FolderType> * fType) {
	m_folderList = NULL;
	if (fType)
		m_folderList = new SortedList<FolderType>(*fType);
}

void FolderType::SetFileList(SortedList<FileType> * fType) {
	m_fileList = NULL;
	if (fType)
		m_fileList = new SortedList<FileType>(*fType);
}

// Set folder name from keyboard.
void FolderType::SetNameFromKB() {
	cout << "\tFolder Name: ";
	cin >> m_Name;
}

// Set folder location from keyboard.
void FolderType::SetLocationFromKB() {
	cout << "\tFolder Location: ";
	cin >> m_Location;
}

// Set folder property from keyboard.
void FolderType::SetPropertyFromKB(string location) {
	SetNameFromKB();
	SetLocation(location);
}

// Set folder property from keyboard.
void FolderType::SetPropertyFromKB() {
	SetNameFromKB();
	SetLocationFromKB();
}

// Convert time_t to string format.
string FolderType::FormatTimeToString(time_t date) {
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