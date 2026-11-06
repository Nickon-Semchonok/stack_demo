#pragma once
#include <format>
#include <iostream>
#include <stdexcept>

template<typename T>
struct ListNode {
	T data;
	ListNode* prev = NULL;
	ListNode* next = NULL;
};

template<typename T>
class LinkedList {
private:
	ListNode<T>* first = NULL;
	ListNode<T>* last = NULL;
	size_t size = 0;
public:
	void   add(T data);
	void   insertBefore(T data, size_t index);
	T      remove(size_t index);
	size_t getSize() const { return size; }
	void print();
};

template<typename T>
void LinkedList<T>::add(T data) {
	if (last) {
		last->next = new ListNode<T>{ data, last, NULL };
		last = last->next;
	}
	else {
		first = last = new ListNode<T>{ data, NULL, NULL };
	}
	size += 1;
}

template<typename T>
void LinkedList<T>::insertBefore(T data, size_t index) {
	if (index == 0) {
		if (first) {
			first = first->prev = new ListNode<T>{ data, NULL, first };
			size += 1;
		}
		else {
			add(data);
		}
	}
	else {
		if (index < size) {
			ListNode<T>* node = first;
			for (size_t i = 0; i < index - 1; ++i) {
				node = node->next;
			}
			node->next = new ListNode<T>{ data, node, node->next };
			node->next->next->prev = node->next;
			size += 1;
		}
		else {
			throw std::range_error(
				std::format("LinkedList<T>::insertBefore: Unable to insert element. Max list index {} but got {}", size - 1, index)
			);
		}
	}
}

template<typename T>
void LinkedList<T>::print() {
	ListNode<T>* node = first;
	if (node == NULL) {
		std::cout << "Empty list, size = " << size << std::endl;
	}
	else {
		std::cout << size << " element(s): ";
		while (node) {
			std::cout << node->data << " ";
			node = node->next;
		}
		std::cout << std::endl;
	}
}

template<typename T>
T LinkedList<T>::remove(size_t index) {
	if (index < size) {
		if (index == 0) {
			ListNode<T>* node = first;
			T data = node->data;
			first = first->next;
			if (first) {
				first->prev = NULL;
			}
			delete node;
			size -= 1;
			if (size == 0) {
				last = NULL;
			}
			return data;
		}

		if (index == size - 1) {
			ListNode<T>* node = last;
			T data = node->data;
			last = last->prev;
			if (last) {
				last->next = NULL;
			}
			delete node;
			size -= 1;
			if (size == 0) {
				first = NULL;
			}
			return data;
		}
		else {
			ListNode<T>* node = first;
			for (size_t i = 0; i < index; ++i) {
				node = node->next;
			}
			node->prev->next = node->next;
			node->next->prev = node->prev;
			T data = node->data;
			delete node;
			size -= 1;
			return data;
		}
	}
	else {
		throw std::range_error(
			std::format("LinkedList<T>::remove: Unable to remove element. Max list index {} but got {}", size - 1, index)
		);
	}
}
