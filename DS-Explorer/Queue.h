#pragma once

#ifndef _QUEUE_H
#define _QUEUE_H

constexpr auto DEFAULT_SIZE = 10;

#include <fstream>

/**
*	Simple circular queue
*/
template <class T>
class Queue {
private:
	int m_Front;
	int m_Rear;
	int m_Length;
	T* m_Item;

public:
	/**
	*	default constructor
	*/
	Queue() {
		m_Front = DEFAULT_SIZE - 1;
		m_Rear = DEFAULT_SIZE - 1;
		m_Length = DEFAULT_SIZE;
		m_Item = new T[DEFAULT_SIZE];
	};

	/**
	*	@brief	size에 해당하는 크기의 배열을 동적할당
	*	@post	size의 값에 해당되는 크기의 배열이 만들어짐,각 멤버변수들이 초기화됨
	*/
	Queue(int size) {
		m_Front = size - 1;
		m_Rear = size - 1;
		m_Length = size;
		m_Item = new T[size];
	};

	/**
	*	default destructor
	*/
	~Queue() {
		delete[] m_Item;
	};

	/**
	*	@brief	Output stream에서 Queue를 적절하게 출력한다.
	*	@pre	Queue가 정의되어 있어야 함.
	*	@post	Queue가 출력됨.
	*	@param	out:	출력할 스트림
	*	@param	data:	출력할 Queue
	*/
	friend std::ostream& operator<< (std::ostream &out, Queue &data) {
		if (data.GetLength() == 0 || data.GetFront() == data.GetRear()) {
			cout << "\tQueue is empty!" << endl;
		} else {
			cout << "\t[Queue]" << endl;
			int f = data.GetFront();
			int r = data.GetRear();

			if (f > r) {
				for (int i = f + 1; i < data.GetLength(); i++) {
					cout << data.GetItem()[i];
				}

				for (int i = 0; i <= r; i++) {
					cout << data.GetItem()[i];
				}
			} else {
				for (int i = f + 1; i <= r; i++) {
					cout << data.GetItem()[i];
				}
			}
		}

		return out;
	}

	/**
	*	@brief	앞쪽 포인터를 리턴한다.
	*	@pre	앞쪽 포인터가 정의되어야 함.
	*	@post	앞쪽 포인터를 리턴함.
	*	@return	return front value
	*/
	int GetFront() const {
		return m_Front;
	};

	/**
	*	@brief	뒤쪽 포인터를 리턴한다.
	*	@pre	뒤쪽 포인터가 정의되어야 함.
	*	@post	뒤쪽 포인터를 리턴함.
	*	@return	return rear value
	*/
	int GetRear() const {
		return m_Rear;
	};

	/**
	*	@brief	길이를 리턴한다.
	*	@pre	길이가 정의되어야 함.
	*	@post	길이를 리턴함.
	*	@return	return length of queue
	*/
	int GetLength() const {
		return m_Length;
	};

	/**
	*	@brief	Queue를 리턴한다.
	*	@pre	Queue가 정의되어야 함.
	*	@post	Queue를 리턴함
	*	@return	return queue pointer
	*/
	T* GetItem() {
		return m_Item;
	};

	/**
	*	@brief	Set front pointer
	*	@param	n:	front pointer
	*/
	void SetFront(int n) {
		m_Front = n;
	};

	/**
	*	@brief	Set rear pointer
	*	@param	n:	rear pointer
	*/
	void SetRear(int n) {
		m_Rear = n;
	};

	/**
	*	@brief	Set length
	*	@param	n:	length
	*/
	void SetLength(int n) {
		m_Length = n;
	};

	/**
	*	@brief	큐를 입력받은 값으로 지정
	*	@param	t:	pointer of specific class
	*/
	void SetItem(T* t) {
		m_Item = t;
	};

	/**
	*	@brief	Queue가 가득 차있는지 확인한다.
	*	@pre	Queue가 초기화 되어야 함.
	*	@post	true / false가 리턴됨.
	*	@return	차있으면 true, 아니라면 false
	*/
	bool IsFull() const;

	/**
	*	@brief	Queue가 비어있는지 확인한다.
	*	@pre	Queue가 초기화 되어야 함.
	*	@post	true / false가 리턴됨.
	*	@return 비어있으면 ture 아니면 false
	*/
	bool IsEmpty();

	/**
	*	@brief	Queue의 마지막에 값을 채움.
	*	@pre	클래스에서 == operator를 지원해야 함.
	*	@post	중복된 값이면 지워지고 리스트의 마지막으로 들어감.
	*	@param	item:	임의의 클래스 T
	*	@return	가득 차있으면 false, 추가에 성공하면 true
	*/
	bool EnQueue(T& item);

	/**
	*	@brief	Queue에 처음 입력된 값을 지움.
	*	@param	item:	임의의 클래스 T
	*	@return	가득 차있으면 false, 추가에 성공하면 true
	*/
	bool DeQueue(T& item);

	/**
	*	@brief	Returns a copy of front item on the queue.
	*	@pre	Queue has been initialized.
	*	@post	If (stack is empty), nullptr is return; otherwise, front element is return from queue.
	*/
	T Front();

	/**
	*	@brief	Returns a copy of rear item on the queue.
	*	@pre	Queue has been initialized.
	*	@post	If (stack is empty), nullptr is return; otherwise, rear element is return from queue.
	*/
	T Rear();

	/**
	*	@brief	Make queue empty.
	*	@post	clear queue.
	*/
	void MakeEmpty();
};

// Queue가 가득 찼는지 확인
template<class T>
 bool Queue<T>::IsFull() const {
	if ((m_Rear + 1) % m_Length == m_Front) {
		return true;
	} else {
		return false;
	}
}

// Queue가 비었는지 확인
template<class T>
bool Queue<T>::IsEmpty() {
	if (m_Front == m_Rear) {
		return true;
	} else {
		return false;
	}
}

// Queue에 새로운 데이터를 추가
template<class T>
bool Queue<T>::EnQueue(T &item) {
	if (IsFull()) {
/*		T* temp = new T[m_Length++];
		for (int i = 0; i < m_Length; i++) {
			temp[i] = m_Item;
		}

		delete[] m_Item;
		m_Item = temp;
*/
		T trash;
		this->DeQueue(trash);
	}

	// Confirm array has duplicate item
	for (int i = 0; i < m_Length; i++) {
		// Don't erase allocated size, only delete it's value
		if (m_Item[i] == item) {
			if (m_Front > m_Rear) {
				if (i >= m_Front) {
					// m_Rear - m_Front - i(found) 순서
					for (int j = i; j < m_Length - 1; j++) {
						m_Item[j] = m_Item[j + 1];
					}

					for (int j = 0; j < m_Rear; j++) {
						m_Item[j] = m_Item[j + 1];
					}

					m_Rear--;
				} else {
					// i(found) - m_Rear - m_Front 순서
					for (int j = i; j < m_Rear; j++) {
						m_Item[j] = m_Item[j + 1];
					}

					m_Rear--;
				}
			} else if (m_Front < m_Rear && i >= m_Front) {
				// m_Front - i(found) - m_Rear 순서
				for (int j = i; j < m_Rear; j++) {
					m_Item[j] = m_Item[j + 1];
				}

				m_Rear--;
			}

			break;
		}
	}

	m_Rear = (m_Rear + 1) % m_Length;
	m_Item[m_Rear] = item;

	return true;
}

// Queue에서 데이터 삭제
template<class T>
bool Queue<T>::DeQueue(T& item) {
	if (IsEmpty()) {
		return false;
	}

	item = m_Item[m_Front];
	m_Front = (m_Front + 1) % m_Length;
	return true;
}

// Queue의 제일 앞 데이터를 리턴
template<class T>
T Queue<T>::Front() {
	if (IsEmpty()) {
		return T();
	} else {
		return m_Item[m_Front];
	}
}

// Queue의 제일 뒤 데이터를 리턴
template<class T>
T Queue<T>::Rear() {
	if (IsEmpty()) {
		return T();
	} else {
		return m_Item[m_Rear];
	}
}

// Queue 초기화
template<class T>
void Queue<T>::MakeEmpty() {
	m_Front = m_Length - 1;
	m_Rear = m_Length - 1;
}

#endif