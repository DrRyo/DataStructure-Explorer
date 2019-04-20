#pragma once

#ifndef _WINDOWS_H
#define _WINDOWS_H

#include <string>
#include <fstream>
#include <filesystem>

// 순환 참조를 해결하기 위함
class FolderType;

using namespace std;

namespace Windows {
	/**
	*	@brief	Validate if there is no special characters.
	*	@pre	문자열이 주어진다.
	*	@post	특수 문자가 있는지 확인한다.
	*	@param	name:	검사할 문자열
	*	@return	유효한 문자열일 때 true, 아닐 때 false 반환
	*/
	bool IsValidName(const string& name);

	/**
	*	@brief	Create directory in specific location
	*	@pre	특정 위치의 폴더 문자열이 주어진다.
	*	@post	새 폴더를 생성한다.
	*	@param	folderWithPath:	생성되어야 하는 폴더
	*	@return	성공 시 true, 실패 시 false 반환
	*/
	bool CreateDirectoryWithPath(string folderWithPath);

	/**
	*	@brief	Rename directory in specific location
	*	@pre	특정 위치의 폴더 문자열이 주어진다.
	*	@post	폴더명을 변경한다.
	*	@param	location:		폴더 위치
	*	@param	name:			변경되어야 하는 폴더
	*	@param	rename:			바꿀 폴더 명
	*/
	void RenameDirectoryWithPath(string location, string name, string rename);

	/**
	*	@brief	Delete directory in specific location
	*	@pre	특정 위치의 폴더 문자열이 주어진다.
	*	@post	폴더를 삭제한다.
	*	@param	location:	폴더 위치
	*	@param	name:		삭제할 폴더명
	*/
	bool DeleteDirectoryWithPath(string location, string name);

	/**
	*	@brief	Copy directory in specific location
	*	@pre	특정 위치의 폴더 문자열이 주어진다.
	*	@post	폴더를 이동한다.
	*	@param	from:	기존 폴더 위치
	*	@param	name:	복사할 폴더명
	*	@param	to:		복사할 폴더 위치
	*/
	bool CopyDirectoryWithPath(string from, string name, string to);

	/**
	*	@brief	Create file in specific location
	*	@pre	특정 위치의 파일 문자열이 주어진다.
	*	@post	빈 파일이 생성된다.
	*	@param	location:	파일 위치
	*	@param	name:		파일명
	*	@param	extension:	파일 확장자
	*/
	bool CreateFileWithPath(string location, string name, string extension);

	/**
	*	@brief	Rename file in specific location
	*	@pre	특정 위치의 파일 문자열이 주어진다.
	*	@post	파일명이 변경된다.
	*	@param	location:	파일 위치
	*	@param	name:		파일명
	*	@param	extension:	파일 확장자
	*	@param	rename:		바꿀 파일명
	*	@param	reextension:바꿀 확장자
	*/
	void RenameFileWithPath(string location, string name, string extension, string rename, string reextension);

	/**
	*	@brief	Delete file in specific location
	*	@pre	특정 위치의 파일 문자열이 주어진다.
	*	@post	파일이 삭제된다.
	*	@param	location:	파일 위치
	*	@param	name:		파일명
	*	@param	extension:	파일 확장자
	*/
	bool DeleteFileWithPath(string location, string name, string extension);

	/**
	*	@brief	Copy file in specific location
	*	@pre	특정 위치의 파일 문자열이 주어진다.
	*	@post	파일을 이동한다.
	*	@param	from:	기존 폴더 위치
	*	@param	name:	복사할 파일명
	*	@param	to:		복사할 폴더 위치
	*/
	bool CopyFileWithPath(string from, string name, string extension, string to);

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
	bool ReadStructureFromSystem(FolderType& root);
}

#endif //_WINDOWS_H