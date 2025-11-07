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
	};
	// Behaviors
	void printForward() const {
		Node* temp = head;
		while (temp != nullptr) {
			std::cout << temp.data << std::endl;
		}
		temp = temp.next();
	}
	void printReverse() const {
		Node* temp = tail;
		while (temp != nullptr) {
			std::cout << temp.data<< std::endl;
		}
		temp = temp.prev();
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
	void addHead(const T& data) {
		Node* newHead = new Node(data);
		if (head == nullptr) {
			head = newHead;
		}
		else {
			newHead->next = head;
			head->prev = newHead;
			head = newHead;
		}
		count++;
	}
	void addTail(const T& data) {
		Node* newTail = new Node(data);
		if (head == nullptr) {
			tail = newTail;
		}
		else {
			newTail->prev = tail;
			tail->next = newTail;
			tail = newTail;
		}
		count++;
	}

	// Removal
	bool removeHead() {
		if (head == nullptr) {
			return false;
		}
		if (head == tail) {
			Node* tempHead = head;
			head = nullptr;
			tail = nullptr;
		}
		else {
			Node* tempHead = head;
			head = head->next;
			head->prev = nullptr;
		}
		delete tempHead;
		count--;
		return true;
	}
	bool removeTail() {
		if (tail == nullptr) {
			return false;
		}
		else if (tail == head) {
			Node* tempTail = tail;
			tail = nullptr;
			head = nullptr;
		}
		else {
			Node* tempTail = tail;
			tail = tail->prev;
			tail->next = nullptr;
		}
		delete tempTail;
		count--;
		return true;
	}
	void Clear() {
		while (head != tail && head != nullptr){
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
		if (this == other) {
			return this;
		}
		delete head;
		delete tail;
		count = 0;
		if (list.count == 0) {
			head = nullptr;
		}
		else {
			head = new Node(list->head);
			Node* tempList = list->head->next;
			if (tempList->head != tempList->tail) {
				tempList = tempList->next;
				while (count != list.count) {
					AddTail(new Node(tempList->head));
					tempList = tempList->next;
				}	
			}
		}
		return this;
	}
	LinkedList<T>& operator=(const LinkedList<T>& rhs) {
		if (this == other) {
			return other;
		}
		delete head;
		delete tail;
		head = other.head;
		tail = other.tail;
		count = other.count;

		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;

		return this;
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
		}
		else {
			head = new Node(list->head);
			Node* tempList = list->head->next;
			if (tempList->head != tempList->tail) {
				tempList = tempList->next;
				while (count != list.count) {
					AddTail(new Node(tempList->head));
					tempList = tempList->next;
				}	
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


