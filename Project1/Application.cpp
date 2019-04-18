#include "Application.h"

// 프로그램 실행
// TODO: Copy folder
// TODO: Cut folder
// TODO: Paste folder
// TODO: Copy file
// TODO: Cut file
// TODO: Paste file
void Application::Run()
{
	while (1)
	{
		DisplayProperty();
		m_Command = GetCommand();
		switch (m_Command) {
		case 1:	// 새 폴더 생성
			NewFolder();
			break;
		case 2: // 서브 폴더 삭제
			DeleteFolder();
			break;
		case 3:	// 서브 폴더 열기
			OpenFolder();
			break;
		case 4: // 현재 폴더 속성
			DisplayProperty();
			break;
		case 5: // 상위 폴더로 이동
			MoveToParentFolder();
			break;
		case 6:	// read data from a file
			ReadDataFromFile();
			break;
		case 7:	// save list data into a file.
			WriteDataToFile();
			break;
		case 8: // 파일 생성하기 (txt)
			NewFile();
			break;
		case 9: // 파일 삭제하기 (이름)
			DeleteFile();
			break;
		case 10: // 파일 수정하기 (이름)
			RenameFile();
			break;
		case 11: // 파일 열기
			OpenFile();
			break;
		case 12: // 폴더 및 파일 전체 검색
			Search();
			break;
		case 13: // 최근 열어본 폴더 및 파일
			Recent();
			break;
		case 0:
			return;
		default:
			cout << "\tIllegal selection...\n";
			break;
		}
	}
}

// 화면에 명령어를 보여주고 키보드 입력을 받음.
int Application::GetCommand() {
	int command;
	cout << endl << endl;
	cout << "\t---ID -- Command ----- " << endl;
	cout << "\t   1  : Create Folder" << endl;
	cout << "\t   2  : Delete sub folder" << endl;
	cout << "\t   3  : Open sub folder" << endl;
	cout << "\t   4  : Print property of folder" << endl;
	cout << "\t   5  : Move to parent folder" << endl;
	cout << "\t   6  : Get from file" << endl;
	cout << "\t   7  : Put to file" << endl;
	cout << "\t   8  : Create new file" << endl;
	cout << "\t   9  : Delete file" << endl;
	cout << "\t   10 : Rename file" << endl;
	cout << "\t   11 : Open file" << endl;
	cout << "\t   12 : Search" << endl;
	cout << "\t   13 : Recent" << endl;
	cout << "\t   0  : Quit" << endl;

	cout << endl << "\t Choose a Command--> ";
	cin >> command;
	cout << endl;

	return command;
}

// 새로운 폴더를 생성함.
void Application::NewFolder() {
	string location = m_curFolder->GetLocation() + m_curFolder->GetName() + "/";
	FolderType temp("temp", location, m_curFolder);
	temp.SetPropertyFromKB(location);
	temp.SetSubFolderList(new SortedList<FolderType>);

	if (m_curFolder->GetSubFolderList()->Add(temp)) {
		m_curFolder->SetModifyDateToNow();
		m_curFolder->SetFolderNumber(m_curFolder->GetFolderNumber() + 1);
	}
}

// 단어를 포함하는 폴더를 검색함
void Application::RetrieveFolderByName() {
	string location = m_curFolder->GetLocation() + m_curFolder->GetName() + "/";
	FolderType temp;
	temp.SetPropertyFromKB(location);

	m_curFolder->GetSubFolderList()->Get(temp);
}

// 최근 열어본 폴더 출력
void Application::RecentFolder(){
	cout << "\t===============" << endl;
	cout << "\t[Recent Folder]" << endl;
	cout << m_RecentFolder << endl;
}

// 폴더 삭제
void Application::DeleteFolder() {
	string location = m_curFolder->GetLocation() + m_curFolder->GetName() + "/";
	FolderType temp;
	temp.SetPropertyFromKB(location);
	
	if (m_curFolder->GetSubFolderList()->Delete(temp)) {
		m_curFolder->SetModifyDateToNow();
		m_curFolder->SetFolderNumber(m_curFolder->GetFolderNumber() - 1);
	}
}

// 서브 폴더 열기
void Application::OpenFolder() {
	string location = m_curFolder->GetLocation() + m_curFolder->GetName() + "/";
	FolderType temp;
	temp.SetPropertyFromKB(location);

	int n = m_curFolder->GetSubFolderList()->GetBinary(temp);

	if (n == -1) {
		cout << "해당 폴더가 존재하지 않습니다!" << endl;
		return;
	}

	FolderType& result = (m_curFolder->GetSubFolderList()->GetArray())[n];
	
	m_RecentFolder.EnQueue(result);
	m_curFolder = &result;
	m_curFolder->SetAccessDateToNow();
}

// 폴더 정보 출력
void Application::DisplayProperty() {
	cout << "\t==============" << endl; 
	cout << "\t현재 폴더 정보" << endl;
	cout << *m_curFolder << endl;

	if (m_curFolder->GetFolderNumber() > 0) {
		cout << "\t----------------" << endl;
		cout << "\t서브 폴더 리스트" << endl;
		cout << *m_curFolder->GetSubFolderList();
	}

	if (m_curFolder->GetFileNumber() > 0) {
		cout << "\t----------------" << endl;
		cout << "\t파일 리스트" << endl;
		cout << *m_curFolder->GetFileList();
	}
}

// 상위 폴더로 이동
void Application::MoveToParentFolder() {
	if (m_curFolder->GetParent() == nullptr) {
		m_RecentFolder.EnQueue(m_RootFolder);
		m_RootFolder.SetAccessDateToNow();
		m_curFolder = &m_RootFolder;
	} else {
		m_RecentFolder.EnQueue(*(m_curFolder->GetParent()));
		m_curFolder->GetParent()->SetAccessDateToNow();
		m_curFolder = m_curFolder->GetParent();
	}
}

// Open a file by file descriptor as an input file. 
int Application::OpenInFile(char *fileName)
{
	m_InFile.open(fileName);	// file open for reading.

	// 파일 오픈에 성공하면 1, 그렇지 않다면 0을 리턴.
	if (!m_InFile)	return 0;
	else	return 1;
}

// Open a file by file descriptor as an output file.
int Application::OpenOutFile(char *fileName)
{
	m_OutFile.open(fileName);	// file open for writing.

	// 파일 오픈에 성공하면 1, 그렇지 않다면 0을 리턴.
	if (!m_OutFile)	return 0;
	else	return 1;
}

// Add new file
void Application::NewFile() {
	string location = m_curFolder->GetLocation() + m_curFolder->GetName() + "/";
	FileType temp;
	temp.SetPropertyFromKB(location);

	if (m_curFolder->GetFileList()->Add(temp)) {
		m_curFolder->SetModifyDateToNow();
		m_curFolder->SetFileNumber(m_curFolder->GetFolderNumber() + 1);
	}
}

// Delete file
void Application::DeleteFile() {
	string location = m_curFolder->GetLocation() + m_curFolder->GetName() + "/";
	FileType temp;
	temp.SetPropertyFromKB(location);

	if (m_curFolder->GetFileList()->Delete(temp)) {
		m_curFolder->SetModifyDateToNow();
		m_curFolder->SetFolderNumber(m_curFolder->GetFolderNumber() - 1);
	}
}

// Rename file
void Application::RenameFile() {
	string location = m_curFolder->GetLocation() + m_curFolder->GetName() + "/";
	cout << "바꾸고 싶은 파일 이름을 입력해주세요." << endl;
	FileType* temp = new FileType();
	temp->SetPropertyFromKB(location);

	if (m_curFolder->GetFileList()->GetBinary(*temp)) {
		cout << "무슨 이름으로 바꾸시겠습니까?" << endl;
		FileType renew;
		renew.SetPropertyFromKB(location);

		if (m_curFolder->GetFileList()->GetBinary(renew) == -1) {
			temp->SetAccessDateToNow();
			temp->SetName(renew.GetName());
		} else {
			cout << "파일명 중복입니다." << endl;
		}
	}
}

// Open file if exists in folder
void Application::OpenFile() {
	string location = m_curFolder->GetLocation() + m_curFolder->GetName() + "/";
	FileType *temp = new FileType();
	temp->SetPropertyFromKB(location);

	if (m_curFolder->GetFileList()->GetBinary(*temp) == -1)
		return;

	m_RecentFile.EnQueue(*temp);

	ifstream file;
	file.open(temp->GetName());

	stringstream ss;

	if (file.is_open()) {
		ss << file.rdbuf();
		cout << ss.str() << endl;
	}

	file.close();

	string str;
	cout << "\tInput? ";
	cin >> str;

	ofstream ofile;
	ofile.open(temp->GetName(), ios_base::app);

	ofile << str;

	temp->SetModifyDateToNow();
	temp->SetAccessDateToNow();

	return;
}

// Search folder or file in whole system
void Application::Search() {
	string word;
	cout << "\tSearch word? ";
	cin >> word;
	
	RecursiveSearch(&m_RootFolder, word);
}

// Temporary function to search recursively
void Application::RecursiveSearch(FolderType* f, string w) {
	FolderType a;
	FileType b;
	int i;
	a.SetName(w), b.SetName(w);

	f->GetSubFolderList()->Get(a);
	f->GetFileList()->Get(b);

	for (i = 0; i < f->GetFolderNumber(); i++) {
		if (f->GetSubFolderList()->GetArray()[i].GetFolderNumber() > 0) {
			RecursiveSearch(&f->GetSubFolderList()->GetArray()[i], w);
		}
	}

	return;
}

// 최근 열어본 파일 출력
void Application::RecentFile() {
	cout << "\t=============" << endl;
	cout << "\t[Recent File]" << endl;
	cout << m_RecentFile << endl;
}

// Show recent folder or file
void Application::Recent() {
	RecentFolder();
	RecentFile();
}

// TODO: 파일로부터 구조 읽어들이기
void Application::ReadDataFromFile() {
	int index = 0;
	FolderType data;	// 읽기용 임시 변수

	char filename[FILENAMESIZE];
	cout << "\n\tEnter Input file Name : ";
	cin >> filename;

	// file open, open error가 발생하면 0을 리턴
	if (!OpenInFile(filename))
		return;

	m_curFolder->ReadDataFromFile(m_InFile);
	m_InFile.close();	// file close

	// 현재 list 출력
	DisplayProperty();

	return;
}

// TODO: 파일로부터 구조 쓰기
void Application::WriteDataToFile() {
	FolderType data;	// 쓰기용 임시 변수

	char filename[FILENAMESIZE];
	cout << "\n\tEnter Output file Name : ";
	cin >> filename;

	// file open, open error가 발생하면 0을 리턴
	if (!OpenOutFile(filename))
		return;

	m_curFolder->WriteDataToFile(m_OutFile);
	m_OutFile.close();	// file close

	return;
}
