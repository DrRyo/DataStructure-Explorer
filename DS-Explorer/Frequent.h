#pragma once

#ifndef _FREQUENT_H
#define _FREQUENT_H

#include <algorithm>

using namespace std;

constexpr int MAX = 5;

/**
*	Explorer specialized key-value data structure for counting frequency
*/
template <class T>
struct Frequent {
	/**
	*	Data Length
	*/
	int length = 0;

	/**
	*	Specific class to count frequency
	*/
	T* data = new T[0];

	/**
	*	Counting data
	*/
	int* count = new int[0];

	/**
	*	default constructor
	*/
	Frequent() {}

	/**
	*	default copy constructor
	*	@param	f:	복사할 Frequent 데이터
	*/
	Frequent(const Frequent& f) {
		operator=(f);
	}

	/**
	*	constructor
	*/
	Frequent(int l, T* d, int* c) {
		delete[] data;
		delete[] count;

		data = new T[l];
		count = new int[l];

		length = l;
		for (int i = 0; i < l; i++) {
			data[i] = d[i];
			count[i] = c[i];
		}
	}

	/**
	*	destructor
	*/
	~Frequent() {
		if (length) {
			delete[] data;
			delete[] count;
		}
	}

	/**
	*	= operator
	*/
	Frequent& operator=(const Frequent& f) {
		if (this != &f) {
			delete[] data;
			delete[] count;

			data = new T[f.length];
			count = new int[f.length];

			length = f.length;
			for (int i = 0; i < f.length; i++) {
				data[i] = f.data[i];
				count[i] = f.count[i];
			}
		}

		return *this;
	}
	
	/**
	*	@brief	Output stream에서 Frequent을 적절하게 출력한다.
	*	@pre	Frequent가 정의되어 있어야 함.
	*	@post	Frequent가 출력됨.
	*	@param	out:	출력할 스트림
	*	@param	data:	출력할 Frequent
	*/
	friend std::ostream& operator<< (std::ostream &out, const Frequent& data) {
		int i, n = ((data.length > MAX) ? MAX : data.length);

		for (i = 0; i < n; i++) {
			cout << data.data[i];
			cout << "\tAccess Count: \t" << data.count[i] << endl;
			cout << endl;
		}

		return out;
	}
	
	/**
	*	== operator
	*/
	inline bool operator==(const Frequent& f) { return data = f.data; }

	/**
	*	@brief	< operator
	*	@param	f:	비교할 Frequent 데이터
	*/
	inline bool operator< (const Frequent& f) { return data < f.data; }

	/**
	*	@brief	> operator
	*	@param	f:	비교할 Frequent 데이터
	*/
	inline bool operator> (const Frequent& f) { return data > f.data; }

	/**
	*	@brief	<= operator
	*	@param	f:	비교할 Frequent 데이터
	*/
	inline bool operator<=(const Frequent& f) { return data <= f.data; }

	/**
	*	@brief	>= operator
	*	@param	f:	비교할 Frequent 데이터
	*/
	inline bool operator>=(const Frequent& f) { return data >= f.data; }

	/**
	*	@brief	Sort element
	*	@pre	Unsorted data
	*	@post	Sorted data
	*/
	void Sort() {
		for (int i = 0; i < length; i++) {
			for (int j = 1; j < length; j++) {
				if (count[j - 1] < count[j]) {
					swap(count[j - 1], count[j]);
					swap(data[j - 1], data[j]);
				} else if (count[j - 1] == count[j] && data[j - 1] < data[j]) {
					swap(count[j - 1], count[j]);
					swap(data[j - 1], data[j]);
				}
			}
		}
	}

	/**
	*	@brief	Get key if exists
	*	@return	Return 1 if success, return 0 if fail to find
	*	@param	t:	Specific type of data
	*/
	bool GetKey(const T& t) {
		for (int i = 0; i < length; i++) {
			if (data[i] == t) {
				return 1;
			}
		}

		return 0;
	};

	/**
	*	@brief	Add key if not exists
	*	@return Return 1 if success, return 0 if fail to add
	*	@param	t:	Specific type of data
	*/
	bool AddKey(const T& t) {
		int i;
		
		Sort();

		if (GetKey(t)) {
			return 0;
		}

		T* temp = new T[length + 1];
		int* temp_i = new int[length + 1];
		
		for (i = 0; i < length; i++) {
			temp[i] = data[i];
			temp_i[i] = count[i];
		}
		temp[i] = t;
		temp_i[i] = 0;

		length++;

		delete[] data;
		delete[] count;

		data = temp;
		count = temp_i;

		return 1;
	};

	/**
	*	@brief	Find key and it's index
	*	@return Index of specific key. If not, return -1.
	*	@param	t:	Specific type of data
	*/
	int GetIndexOfKey(const T& t) const {
		for (int i = 0; i < length; i++) {
			if (data[i] == t) {
				return i;
			}
		}
		return -1;
	};

	/**
	*	@brief	Find key and it's count value
	*	@return	Count value of specific key. If not, return -1.
	*	@param	t:	Specific type of data
	*/
	int GetCountByKey(const T& t) const {
		for (int i = 0; i < length; i++) {
			if (data[i] == t) {
				return count;
			}
		}
		return -1;
	};
};

#endif
