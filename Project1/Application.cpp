#include "Application.h"

// 프로그램 실행
void Application::Run()
{
	m_Command = -1;
	bool cFlag = false;

	while (1) {
		system("cls");
		DisplayProperty();

		if (m_Command == -1) {
			m_Command = GetFolderCommand();
		} else if (!cFlag) {
			switch (m_Command) {
			case 1:		// 폴더 및 파일 전체 검색
				Search();
				break;
			case 2:		// 최근 열어본 폴더 및 파일 출력
				DisplayRecent();
				break;
			case 3:		// 좋아하는 폴더 및 파일 출력
				DisplayFavorite();
				break;
			case 4:		// 자주 사용한 폴더 및 파일 출력
				DisplayFrequent();
				break;
			case -1:	// 다음 명령어
				break;
			case 0:		// 탐색기 종료
				return;
			default:
				cout << "\tIllegal selection...\n";
				break;
			}

			// Execute command successfully.
			m_Command = -999;
			cFlag = true;
		}

		system("cls");
		DisplayProperty();
		if (m_Command == -1) {
			m_Command = GetFileCommand();
		} else if (!cFlag) {
			// if m_Command is not next command, execute folder command
			switch (m_Command) {
			case 1:		// 새 폴더 생성
				NewFolder();
				break;
			case 2:		// 서브 폴더 삭제
				DeleteFolder();
				break;
			case 3:		// 서브 폴더명 변경
				RenameFolder();
				break;
			case 4:		// 서브 폴더 열기
				OpenFolder();
				break;
			case 5:		// 자주가는 폴더 등록
				SetAsFavoriteFolder();
				break;
			case 6:		// 현재 폴더 속성
				DisplayProperty();
				break;
			case 7:		// 상위 폴더로 이동
				MoveToParentFolder();
				break;
			case 8:		// 현재 폴더 복사
				CopyFolder();
				break;
			case 9:		// 현재 폴더 잘라내기
				CutFolder();
				break;
			case 10:	// 현재 폴더 붙여넣기
				PasteFolder();
				break;
			case -1:	// 다음 명령어
				break;
			case 0:		// 탐색기 종료
				return;
			default:
				cout << "\tIllegal selection...\n";
				break;
			}

			// Execute command successfully.
			m_Command = -999;
			cFlag = true;
		}

		system("cls");
		DisplayProperty();
		if (m_Command == -1){
			m_Command = GetExplorerCommand();
		} else if (!cFlag) {
			switch (m_Command) {
			case 1:		// 파일 생성하기 (텍스트)
				NewFile();
				break;
			case 2:		// 파일 삭제하기 (이름)
				DeleteFile();
				break;
			case 3:		// 파일 수정하기 (이름)
				RenameFile();
				break;
			case 4:		// 파일 열기
				OpenFile();
				break;
			case 5:		// 자주가는 폴더 등록
				SetAsFavoriteFolder();
				break;
			case 6:		// 현재 폴더 복사
				CopyFolder();
				break;
			case 7:		// 현재 폴더 잘라내기
				CutFolder();
				break;
			case 8:		// 현재 폴더 붙여넣기
				PasteFolder();
				break;
			case -1:	// 다음 명령어
				break;
			case 0:		// 탐색기 종료
				return;
			default:
				cout << "\tIllegal selection...\n";
				break;
			}

			// Execute command successfully.
			m_Command = -999;
			cFlag = true;
		}

		m_Command = -1, cFlag = false;
	}
}

// 화면에 명령어를 보여주고 키보드 입력을 받음.
int Application::GetFolderCommand() {
	int command;
	cout << endl << endl;
	cout << "\t-- ID -- Command ----- " << endl;
	cout << "\t   1  : Create folder" << endl;
	cout << "\t   2  : Delete folder" << endl;
	cout << "\t   3  : Rename folder" << endl;
	cout << "\t   4  : Open folder" << endl;
	cout << "\t   5  : Set as favorite" << endl;
	cout << "\t   6  : Property of folder" << endl;
	cout << "\t   7  : Move to parent folder" << endl;
	cout << "\t   8  : Copy this folder" << endl;
	cout << "\t   9  : Cut this folder" << endl;
	cout << "\t  10  : Paste this folder" << endl;
	cout << "\t  -1  : Next commands" << endl;
	cout << "\t   0  : Quit" << endl;

	cout << endl << "\t Choose a Command--> ";
	cin >> command;
	cout << endl;

	return command;
}

// 화면에 명령어를 보여주고 키보드 입력을 받음.
int Application::GetFileCommand() {
	int command;
	cout << endl << endl;
	cout << "\t-- ID -- Command ----- " << endl;
	cout << "\t   1  : Create new file" << endl;
	cout << "\t   2  : Delete file" << endl;
	cout << "\t   3  : Rename file" << endl;
	cout << "\t   4  : Open file" << endl;
	cout << "\t   5  : Set as favorite" << endl;
	cout << "\t   6  : Copy file" << endl;
	cout << "\t   7  : Cut file" << endl;
	cout << "\t   8  : Paste file" << endl;
	cout << "\t  -1  : Next commands" << endl;
	cout << "\t   0  : Quit" << endl;

	cout << endl << "\t Choose a Command--> ";
	cin >> command;
	cout << endl;

	return command;
}

// 화면에 명령어를 보여주고 키보드 입력을 받음.
int Application::GetExplorerCommand() {
	int command;
	cout << endl << endl;
	cout << "\t-- ID -- Command ----- " << endl;
	cout << "\t   1  : Search" << endl;
	cout << "\t   2  : Recent" << endl;
	cout << "\t   3  : Favorite" << endl;
	cout << "\t   4  : Frequent" << endl;
	cout << "\t  -1  : Next commands" << endl;
	cout << "\t   0  : Quit" << endl;

	cout << endl << "\t Choose a Command--> ";
	cin >> command;
	cout << endl;

	return command;
}

// 새로운 폴더를 생성함.
void Application::NewFolder() {
	string location = m_curFolder->GetLocation() + m_curFolder->GetName() + "/";
	FolderType temp;
	temp.SetPropertyFromKB(location);
	temp.SetParent(m_curFolder);

	if (m_curFolder->GetSubFolderList()->Add(temp)) {
		m_curFolder->SetModifyDateToNow();
		m_curFolder->SetFolderNumber(m_curFolder->GetFolderNumber() + 1);
	}
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

// TODO: Rename folder
void Application::RenameFolder() {

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

// TODO: Set as favorite folder
void Application::SetAsFavoriteFolder() {
	m_FavoriteFolder.EnQueue(*m_curFolder);
}

// 최근 열어본 폴더 출력
void Application::DisplayRecentFolder() {
	cout << "\t=================" << endl;
	cout << "\t[Recent Folder]" << endl;
	cout << m_RecentFolder << endl;
}

// 좋아하는 폴더 출력
void Application::DisplayFavoriteFolder() {
	cout << "\t=================" << endl;
	cout << "\t[Favorite Folder]" << endl;
	cout << m_FavoriteFolder << endl;
}

// 자주 사용하는 폴더 출력
void Application::DisplayFrequentFolder() {
	cout << "\t=================" << endl;
	cout << "\t[Frequent Folder]" << endl;
	cout << m_FrequentFolder << endl;
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

// TODO: 폴더 복사
void Application::CopyFolder() {

}

// TODO: 폴더 자르기
void Application::CutFolder() {

}

// TODO: 폴더 붙여넣기
void Application::PasteFolder() {

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
	cout << "\t바꾸고 싶은 파일 이름을 입력해주세요." << endl;
	FileType* temp = new FileType();
	temp->SetPropertyFromKB(location);

	if (m_curFolder->GetFileList()->GetBinary(*temp) != -1) {
		cout << "\t무슨 이름으로 바꾸시겠습니까?" << endl;
		FileType renew;
		renew.SetPropertyFromKB(location);

		if (m_curFolder->GetFileList()->GetBinary(renew) == -1) {
			temp->SetAccessDateToNow();
			temp->SetName(renew.GetName());
		} else {
			cout << "\t파일명 중복입니다." << endl;
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

// TODO: Set as favorite file
void Application::SetAsFavoriteFile() {
	string location = m_curFolder->GetLocation() + m_curFolder->GetName() + "/";
	FileType* temp = new FileType();
	temp->SetPropertyFromKB(location);

	if (m_curFolder->GetFileList()->GetBinary(*temp) != -1) {
		m_FavoriteFile.EnQueue(*temp);
	} else {
		cout << "There is no such file." << endl;
	}
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
void Application::DisplayRecentFile() {
	cout << "\t=============" << endl;
	cout << "\t[Recent File]" << endl;
	cout << m_RecentFile << endl;
}

// 좋아하는 파일 출력
void Application::DisplayFavoriteFile() {
	cout << "\t=============" << endl;
	cout << "\t[Favorite File]" << endl;
	cout << m_FavoriteFile << endl;
}

// 자주 사용하는 파일 출력
void Application::DisplayFrequentFile() {
	cout << "\t=============" << endl;
	cout << "\t[Frequent File]" << endl;
	cout << m_FrequentFile << endl;
}

// Display recent folder or file
void Application::DisplayRecent() {
	DisplayRecentFolder();
	DisplayRecentFile();
}

// Display favorite folder or file
void Application::DisplayFavorite() {
	DisplayFavoriteFolder();
	DisplayFavoriteFile();
}

// Display Frequent folder or file
void Application::DisplayFrequent() {
	DisplayFrequentFolder();
	DisplayFrequentFile();
}

// TODO: 파일시스템으로부터 구조 읽어들이기
void Application::ReadDataFromSystem() {
}
