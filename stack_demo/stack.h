#pragma once
#include "linked_list.h"
#include <stdexcept>

template<typename T>
class Stack {
private:
	LinkedList<T>* stack = NULL;
public:
	void push(T data) { 
		stack->add(data);
	}

	T pop() {   
		if (getLength() > 0) {

			return stack->remove(getLength() - 1);
		}
		else {
			throw std::length_error("Stack<T>::pop(): Pop requested for empty stack");
		}
	}

	size_t getLength() {
		return stack->getSize();
	}

	bool isEmpty() {
		return getLength() == 0;
	}

	void print() {
		stack->print();
	}

	Stack() {
		stack = new LinkedList<T>();
	}

	Stack(Stack<T>& other) {

		stack = new LinkedList<T>();
	}

	Stack(Stack<T>&& other) noexcept {
		this->stack = other.stack;
		other.stack = NULL;
	}

	~Stack() {
		if (stack) delete stack;
	}
};
