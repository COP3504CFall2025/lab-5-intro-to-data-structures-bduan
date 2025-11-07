#pragma once
#include <iostream>
using namespace std;



template <typename T>
class LinkedList {
public:
	struct Node {
    	T data;
    	Node* prev;
    	Node* next;

		Node(const T& d) {
			data = d;
			prev = nullptr;
			next = nullptr;
		}
	};
	// Behaviors
	void printForward() const {
		Node* temp = head;
		while (temp != nullptr) {
			std::cout << temp->data << std::endl;
		}
		temp = temp->next;
	}
	void PrintReverse() const {
		Node* temp = tail;
		while (temp != nullptr) {
			std::cout << temp->data<< std::endl;
		}
		temp = temp->prev;
	}

	// Accessors
	[[nodiscard]] unsigned int getCount() const {
		return count;
	}
	Node* getHead() {
		return head;
	}
	const Node* getHead() const {
		return head;
	}
	Node* getTail() {
		return tail;
	}
	const Node* getTail() const {
		return tail;
	}

	// Insertion	
	void AddHead(const T& data) {
		Node* newHead = new Node(data);
		if (head == nullptr) {
			head = newHead;
			tail = newHead;
		}
		else {
			newHead->next = head;
			head->prev = newHead;
			head = newHead;
		}
		count++;
	}
	void AddTail(const T& data) {
		Node* newTail = new Node(data);
		if (head == nullptr) {
			tail = newTail;
			head = newTail;
		}
		else {
			newTail->prev = tail;
			tail->next = newTail;
			tail = newTail;
		}
		count++;
	}

	// Removal
	bool RemoveHead() {
		if (head == nullptr) {
			return false;
		}
		if (head == tail) {
			Node* tempHead = head;
			head = nullptr;
			tail = nullptr;
			delete tempHead;
		}
		else {
			Node* tempHead = head;
			head = head->next;
			head->prev = nullptr;
			delete tempHead;
		}
		count--;
		return true;
	}
	bool RemoveTail() {
		if (tail == nullptr) {
			return false;
		}
		else if (tail == head) {
			Node* tempTail = tail;
			tail = nullptr;
			head = nullptr;
			delete tempTail;
		}
		else {
			Node* tempTail = tail;
			tail = tail->prev;
			tail->next = nullptr;
			delete tempTail;
		}
		count--;
		return true;
	}
	void Clear() {
		while (head != nullptr && head != tail){
			Node* temp = head;
			head = head->next;
			head->prev = nullptr;
			delete temp;
		}
		if (head == tail)
		{
			Node* temp = head;
			head = nullptr;
			tail = nullptr;
			delete temp;
		}
		count = 0;
	}

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept {
		if (this == &other) {
			return *this;
		}

		Clear();
		
		if (other.count == 0) {
			head = nullptr;
			tail = nullptr;
			count = 0;
			return *this;
		}
		else {
			Node* temp = other.head;
			while (temp != nullptr) {
				AddTail(temp->data);
				temp = temp->next;
			}
			return *this;
		}
	}
	LinkedList<T>& operator=(const LinkedList<T>& rhs) {
		if (this == &rhs) {
			return *this;
		}
		Clear();

		Node* temp = rhs.head;

		while (temp != nullptr) {
				AddTail(temp->data);
				temp = temp->next;
		}

		return *this;
	}

	// Construction/Destruction
	LinkedList() {
		head = nullptr;
		tail = nullptr;
		count = 0;
	}
	LinkedList(const LinkedList<T>& list) {
		if (list.count == 0) {
			head = nullptr;
			tail = nullptr;
			count = 0;
		}
		else {
			Node* temp = list.head;
			while (temp != nullptr) {
				AddTail(temp->data);
				temp = temp->next;
			}
		}
	}
	LinkedList(LinkedList<T>&& other) noexcept {
		head = other.head;
		tail = other.tail;
		count = other.count;

		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;
	}
	~LinkedList() {
		Clear();
	}

private:
	// Stores pointers to first and last nodes and count
	Node* head;
	Node* tail;
	unsigned int count;

};


