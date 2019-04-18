#pragma once

#ifndef _FREQUENT_H
#define _FREQUENT_H

template <class T>
struct Frequent {
	T data;
	int count;

	Frequent() {
		count = 0;
	}

	Frequent(T d, int c) {
		data = d, count = c;
	}

	Frequent<T>& operator=(const Frequent<T>& f) {
		data = f.data;
		count = f.count;
		return *this;
	}
	
	/**
	*	@brief	Output stream에서 Frequent을 적절하게 출력한다.
	*	@pre	Frequent가 정의되어 있어야 함.
	*	@post	Frequent가 출력됨.
	*	@param	out:	출력할 스트림
	*	@param	data:	출력할 Frequent
	*/
	friend std::ostream& operator<< (std::ostream &out, const Frequent<T>& data) {
		cout << data.data << endl;
		return out;
	}
	
	/**
	*	== operator
	*/
	inline bool operator==(const Frequent<T>& f) { return data = f.data; }

	/**
	*	@brief	< operator
	*	@param	data:	비교할 Frequent 데이터
	*/
	inline bool operator< (const Frequent<T>& f) { return data < f.data; }

	/**
	*	@brief	> operator
	*	@param	data:	비교할 Frequent 데이터
	*/
	inline bool operator> (const Frequent<T>& f) { return data > f.data; }

	/**
	*	@brief	<= operator
	*	@param	data:	비교할 Frequent 데이터
	*/
	inline bool operator<=(const Frequent<T>& f) { return data <= f.data; }

	/**
	*	@brief	>= operator
	*	@param	data:	비교할 Frequent 데이터
	*/
	inline bool operator>=(const Frequent<T>& f) { return data >= f.data; }
};

#endif
