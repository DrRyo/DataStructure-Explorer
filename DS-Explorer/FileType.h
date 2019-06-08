#pragma once

#ifndef _FILETYPE_H
#define _FILETYPE_H

#include <iostream>
#include <sstream>
#include <string>
#include <ctime>
#include <iomanip>

#include "SortedList.h"
#include "Windows.h"

// 순환 참조를 해결하기 위함
class FolderType;

using namespace std;

/**
*	File information class
*/
class FileType {
private:
	string m_Name;
	string m_Extension;
	string m_Location;
	string m_CreateDate;
	string m_ModifyDate;
	string m_AccessDate;
	FolderType * m_Parent;

public:
	/**
	*	default constructor.
	*/
	FileType() {
		SetCreateDateToNow();
		SetModifyDateToNow();
		SetAccessDateToNow();
	}

	/**
	*	constructor.
	*/
	FileType(string name, string extension, string location, FolderType* parent) {
		m_Name = name;
		m_Extension = extension;
		m_Location = location;
		m_Parent = parent;
		SetCreateDateToNow();
		SetModifyDateToNow();
		SetAccessDateToNow();
	}

	/**
	*	default copy constructor.
	*/
	FileType(const FileType& fType) {
		operator=(fType);
	}

	FileType(FileType* fType) {
		operator=(fType);
	}

	/**
	*	destructor.
	*/
	~FileType() {}

	/**
	*	= operator
	*/
	FileType& operator= (const FileType& data);

	FileType& operator= (FileType* data);

	/**
	*	== operator
	*/
	bool operator== (const FileType& data);

	/**
	*	@brief	< operator
	*	@param	data:	비교할 FileType 데이터
	*/
	inline bool operator< (const FileType& data) { return (m_Name < data.GetName()); }

	/**
	*	@brief	> operator
	*	@param	data:	비교할 FileType 데이터
	*/
	inline bool operator> (const FileType& data) { return (m_Name > data.GetName()); }

	/**
	*	@brief	<= operator
	*	@param	data:	비교할 FileType 데이터
	*/
	inline bool operator<=(const FileType& data) { return (m_Name <= data.GetName()); }

	/**
	*	@brief	>= operator
	*	@param	data:	비교할 FileType 데이터
	*/
	inline bool operator>=(const FileType& data) { return (m_Name >= data.GetName()); }

	/**
	*	@brief	Output stream에서 FolderType을 적절하게 출력한다.
	*	@pre	FolderType가 정의되어 있어야 함.
	*	@post	FolderType가 출력됨.
	*	@param	out:	출력할 스트림
	*	@param	data:	출력할 FolderType
	*/
	friend std::ostream& operator<< (std::ostream &out, const FileType &data) {
		cout << "\t[FileType]\t" << endl;
		cout << "\tName: \t\t" << data.GetName() << "." << data.GetExtension() << endl;
		cout << "\tLocation: \t" << data.GetLocation() << endl;
		cout << "\tCreate Date: \t" << data.GetCreateDate() << endl;
		cout << "\tModify Date: \t" << data.GetModifyDate() << endl;
		cout << "\tAccess Date: \t" << data.GetAccessDate() << endl;

		return out;
	}

	/**
	*	@brief	파일명을 리턴해주는 함수
	*	@pre	none.
	*	@post	none.
	*	@return	파일명을 리턴
	*/
	string GetName() const {
		return m_Name;
	}

	/**
	*	@brief	파일 확장자를 리턴하는 함수
	*	@pre	none.
	*	@post	none.
	*	@return	파일 확장자를 리턴
	*/
	string GetExtension() const {
		return m_Extension;
	}

	/**
	*	@brief	파일 위치를 리턴하는 함수
	*	@pre	none.
	*	@post	none.
	*	@return	파일 위치를 리턴
	*/
	string GetLocation() const {
		return m_Location;
	}

	/**
	*	@brief	부모 폴더를 리턴하는 함수
	*	@pre	none.
	*	@post	none.
	*	@return	부모 폴더를 리턴
	*/
	FolderType * GetParent() const {
		return m_Parent;
	}

	/**
	*	@brief	파일 생성일을 리턴하는 함수
	*	@pre	none.
	*	@post	none.
	*	@return	파일 생성일을 리턴
	*/
	string GetCreateDate() const {
		return m_CreateDate;
	}

	/**
	*	@brief	파일 수정일을 리턴하는 함수
	*	@pre	none.
	*	@post	none.
	*	@return	파일 수정일을 리턴
	*/
	string GetModifyDate() const {
		return m_ModifyDate;
	}

	/**
	*	@brief	파일 접근일을 리턴하는 함수
	*	@pre	none.
	*	@post	none.
	*	@return	파일 접근일을 리턴
	*/
	string GetAccessDate() const {
		return m_AccessDate;
	}

	/**
	*	@brief	파일명을 지정하는 함수
	*	@pre	파일명을 받음
	*	@post	파일명을 설정함
	*	@param	name: 지정할 파일명
	*	@return	none.
	*/
	void SetName(string name) {
		m_Name = name;
	}

	/**
	*	@brief	파일 확장자를 지정하는 함수
	*	@pre	파일 확장자를 받음
	*	@post	파일 확장자를 설정함
	*	@param	extension: 지정할 파일 확장자
	*	@return none.
	*/
	void SetExtension(string extension) {
		m_Extension = extension;
	}

	/**
	*	@brief	파일 위치를 지정하는 함수
	*	@pre	파일 위치를 받음
	*	@post	파일 위치를 설정함
	*	@param	location: 지정할 파일 위치
	*	@return none.
	*/
	void SetLocation(string location) {
		m_Location = location;
	}

	/**
	*	@brief	부모 폴더 포인터를 설정하는 함수
	*	@pre	부모 폴더 포인터를 받음
	*	@post	부모 폴더 포인터를 설정함
	*	@param	parent:	부모 폴더 포인터
	*	@return	none.
	*/
	void SetParent(FolderType * parent) {
		m_Parent = parent;
	}

	/**
	*	@brief	Time 형식을 String 형식으로 변환하는 함수
	*	@pre	time_t 데이터를 받음.
	*	@post	string 형식의 날짜로 변환함.
	*	@param	date: 값이 지정된 time_t 형식의 데이터
	*	@return	날짜를 리턴해줌.
	*/
	string FormatTimeToString(time_t date);

	/**
	*	@brief	파일 생성일자를 string으로 설정해주는 함수
	*	@pre	string 데이터를 받음.
	*	@post	파일 생성일자를 설정함.
	*	@param	date: 값이 지정된 string 형식의 데이터
	*	@return	none.
	*/
	void SetCreateDate(string date) {
		m_CreateDate = date;
	}

	/**
	*	@brief	파일 생성일자를 받은 time_t 시점으로 잡아주는 함수
	*	@pre	time_t 데이터를 받음.
	*	@post	파일 생성일자를 설정함.
	*	@param	date: 값이 지정된 time_t 형식의 데이터
	*	@return	none.
	*/
	void SetCreateDate(time_t date) {
		m_CreateDate = FormatTimeToString(date);
	}

	/**
	*	@brief	파일 수정일자를 string으로 설정해주는 함수
	*	@pre	string 데이터를 받음.
	*	@post	파일 수정일자를 설정함.
	*	@param	date: 값이 지정된 string 형식의 데이터
	*	@return	none.
	*/
	void SetModifyDate(string date) {
		m_ModifyDate = date;
	}

	/**
	*	@brief	파일 수정일자를 받은 time_t 시점으로 잡아주는 함수
	*	@pre	time_t 데이터를 받음.
	*	@post	파일 수정일자를 설정함.
	*	@param	date: 값이 지정된 time_t 형식의 데이터
	*	@return	none.
	*/
	void SetModifyDate(time_t date) {
		m_ModifyDate = FormatTimeToString(date);
	}

	/**
	*	@brief	파일 접근일자를 string으로 설정해주는 함수
	*	@pre	string 데이터를 받음.
	*	@post	파일 접근일자를 설정함.
	*	@param	date: 값이 지정된 string 형식의 데이터
	*	@return	none.
	*/
	void SetAccessDate(string date) {
		m_AccessDate = date;
	}

	/**
	*	@brief	파일 접근일자를 받은 time_t 시점으로 잡아주는 함수
	*	@pre	time_t 데이터를 받음.
	*	@post	파일 접근일자를 설정함.
	*	@param	date: 값이 지정된 time_t 형식의 데이터
	*	@return	none.
	*/
	void SetAccessDate(time_t date) {
		m_AccessDate = FormatTimeToString(date);
	}

	/**
	*	@brief	파일 생성일자를 실행시점으로 잡아주는 함수
	*	@pre	none.
	*	@post	파일 생성일자를 설정함.
	*	@return	none.
	*/
	void SetCreateDateToNow();

	/**
	*	@brief	파일 수정일자를 실행시점으로 잡아주는 함수
	*	@pre	none.
	*	@post	파일 수정일자를 설정함.
	*	@return	none.
	*/
	void SetModifyDateToNow();

	/**
	*	@brief	파일 접근일자를 실행시점으로 잡아주는 함수
	*	@pre	none.
	*	@post	파일 접근일자를 설정함.
	*	@return	none.
	*/
	void SetAccessDateToNow();

	/**
	*	@brief	키보드에서 파일명을 입력받아 설정하는 함수
	*	@pre	파일명을 입력받음.
	*	@post	파일명이 설정됨.
	*	@return	none.
	*/
	void SetNameFromKB();

	/**
	*	@brief	키보드에서 파일 확장자를 입력받아 설정하는 함수
	*	@pre	파일 확장자를 입력받음.
	*	@post	파일 확장자가 설정됨.
	*	@return	none.
	*/
	void SetExtensionFromKB();

	/**
	*	@brief	키보드에서 파일 위치를 입력받아 설정하는 함수
	*	@pre	파일 위치를 입력받음.
	*	@post	파일 위치가 설정됨.
	*	@return	none.
	*/
	void SetLocationFromKB();

	/**
	*	@brief	키보드에서 파일 속성을 입력받아 설정하는 함수
	*	@pre	파일 속성을 입력받음.
	*	@post	파일 속성이 설정됨.
	*	@param	location:	파일 위치를 받아옴.
	*	@return	none.
	*/
	void SetPropertyFromKB(string location);

	/**
	*	@brief	키보드에서 파일 속성을 입력받아 설정하는 함수
	*	@pre	파일 속성을 입력받음.
	*	@post	파일 속성이 설정됨.
	*	@return	none.
	*/
	void SetPropertyFromKB();
};

#endif //_FILETYPE_H