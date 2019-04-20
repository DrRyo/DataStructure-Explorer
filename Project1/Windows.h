#pragma once

#ifndef _WINDOWS_H
#define _WINDOWS_H

#include <string>
#include <fstream>
#include <ShlObj.h>

#include "FolderType.h"

using namespace std;

namespace Windows {
	/**
	*	@brief	Convert string to PCWSTR (Pointer to Constant unicode Wide_STRing)
	*	@pre	string variable is given
	*	@post	PCWSTR variable returns
	*	@param	str:	string variable that converts to PCWSTR
	*/
	PCWSTR StringToPCWSTR(const string& str);

	/**
	*	@brief	Create directory in specific location
	*	@pre	특정 위치의 폴더 문자열이 주어진다.
	*	@post	새 폴더를 생성한다.
	*	@param	folderWithPath:	생성되어야 하는 폴더
	*/
	int CreateDirectoryWithPath(string folderWithPath);

	/**
	*	@brief	Create file in specific location
	*	@pre	특정 위치의 파일 문자열이 주어진다.
	*	@post	빈 파일이 생성된다.
	*	@param	location:	파일 위치
	*	@param	name:		파일명
	*	@param	extension:	파일 확장자
	*/
	int CreateFileWithPath(string location, string name, string extension);

	/**
	*	@brief	Execute file in Windows
	*	@pre	특정 위치의 파일 문자열이 주어진다.
	*	@post	Windows에 설정된 대로 실행시킨다.
	*	@param	location:	파일 위치
	*	@param	name:		파일명
	*	@param	extension:	파일 확장자
	*/
	int ExecuteFile(string location, string name, string extension);

	/**
	*	@brief	Read Structure From Windows
	*	@pre	root 폴더가 존재해야한다.
	*	@post	폴더 구조를 읽어 메모리에 할당한다.
	*/
	int ReadStructureFromSystem(FolderType& root);
}

#endif //_WINDOWS_H