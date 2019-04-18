#pragma once

#ifndef _APPLICATION_H
#define _APPLICATION_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "SortedList.h"
#include "FolderType.h"
#include "Queue.h"

#define FILENAMESIZE 1024

/**
*	application class for folder management simply.
*/
class Application {
private:
	ifstream m_InFile;
	ofstream m_OutFile;
	FolderType m_RootFolder;
	FolderType * m_curFolder;
	Queue<FolderType> m_RecentFolder;
	Queue<FileType> m_RecentFile;
	int m_Command;
	
public:
	/**
	*	default constructor with folder name.
	*/
	Application(string folderName = "root", string folderLocation = "/") {
		m_Command = 0;
		
		// main에서 root folder를 application class를 정의하고 제어를 root folder의 Run함수로 넘긴다
		m_RootFolder.SetName(folderName);
		m_RootFolder.SetLocation(folderLocation);
		m_RootFolder.SetCreateDateToNow();
		m_RootFolder.SetFolderNumber(0);
		m_RootFolder.SetFileNumber(0);
		m_RootFolder.SetSubFolderList(new SortedList<FolderType>);
		m_RootFolder.SetFileList(new SortedList<FileType>);

		m_curFolder = &m_RootFolder;
		m_RecentFolder.EnQueue(*m_curFolder);
	}

	/**
	*	destructor.
	*/
	~Application() {}

	/**
	*	@brief	어플리케이션 실행
	*/
	void Run();

	/**
	*	@brief	실행에 필요한 명령을 받아옴.
	*	@pre	명령어 목록을 출력한다.
	*	@post	명령을 입력받는다.
	*	@return	해당 명령어 숫자 리턴
	*/
	int GetCommand();

	/**
	*	@brief	새로운 폴더를 생성한다.
	*	@pre	폴더 정보가 필요함.
	*	@post	새로운 폴더가 생성됨.
	*/
	void NewFolder();

	/**
	*	@brief	폴더명을 기준으로 삭제한다.
	*	@pre	폴더명이 필요함.
	*	@post	폴더가 삭제됨.
	*/
	void DeleteFolder();

	/**
	*	@brief	서브 폴더를 연다.
	*	@pre	서브 폴더가 존재해야됨.
	*	@post	서브 폴더로 이동.
	*/
	void OpenFolder();

	/**
	*	@brief	폴더명을 기준으로 검색한다.
	*	@pre	폴더명이 필요함.
	*	@post	폴더 정보를 받아옴.
	*/
	void RetrieveFolderByName();

	/**
	*	@brief	최근 열어본 폴더 목록을 출력한다.
	*	@post	폴더 정보를 받아옴.
	*/
	void RecentFolder();

	/**
	*	@brief	루트 폴더의 정보와 서브 폴더 리스트의 정보를 출력한다.
	*	@post	정보가 출력됨.
	*/
	void DisplayProperty();

	/**
	*	@brief	상위 폴더로 이동함.
	*	@pre	상위 폴더가 있어야 됨.
	*	@post	상위 폴더로 이동함, 루트 폴더면 이동하지 않는다.
	*/
	void MoveToParentFolder();

	/**
	*	@brief	파일로부터 입력값을 받아온다.
	*	@pre	파일이 존재해야 함.
	*	@post	파일로부터 데이터 값을 입력받음.
	*/
	void ReadDataFromFile();

	/**
	*	@brief	데이터를 파일로 출력하는 함수
	*	@pre	데이터 값이 있어야 됨.
	*	@post	파일로 데이터 값이 출력됨.
	*/
	void WriteDataToFile();

	/**
	*	@brief	Open a file by file descriptor as an input file.
	*	@pre	a file for reading is exist.
	*	@post	open the file for reading.
	*	@param	fileName: a filename to open for reading.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int OpenInFile(char* fileName);

	/**
	*	@brief	Open a file by file descriptor as an output file.
	*	@pre	list should be initialized.
	*	@post	open the file for writing.
	*	@param	fileName: a filename to open for writing.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int OpenOutFile(char* fileName);
	
	/**
	*	@brief	새로운 파일을 생성한다.
	*	@pre	파일 정보가 필요함.
	*	@post	새로운 파일이 생성됨.
	*/
	void NewFile();

	/**
	*	@brief	파일명을 기준으로 삭제한다.
	*	@pre	파일명이 필요함.
	*	@post	파일이 삭제됨.
	*/
	void DeleteFile();

	/**
	*	@brief	파일 속성을 변경한다.
	*	@pre	파일이 존재해야 됨.
	*	@post	파일이 변경됨.
	*/
	void RenameFile();

	/**
	*	@brief	파일을 연다.
	*	@pre	파일이 존재해야 됨.
	*	@post	파일을 수정할 수 있다.
	*/
	void OpenFile();

	/**
	*	@brief	파일 및 폴더를 검색한다.
	*	@pre	이름이 입력되어야 함.
	*	@post	모든 검색결과를 출력한다.
	*/
	void Search();

	/**
	*	@brief	재귀 검색한다.
	*	@pre	폴더 위치와 이름이 입력되야 함.
	*	@post	모든 검색결과를 출력한다.
	*	@param	f:	FolderType
	*	@param	w:	Search string
	*/
	void RecursiveSearch(FolderType* f, string w);

	/**
	*	@brief	최근 열어본 파일 목록을 출력한다.
	*	@post	파일 정보를 받아옴.
	*/
	void RecentFile();

	/**
	*	@brief	최근에 열어본 폴더 및 파일을 출력한다.
	*	@pre	최근 열어본 목록이 있어야 함.
	*	@post	목록이 차례대로 출력된다.
	*/
	void Recent();
};
#endif //_APPLICATION_H
