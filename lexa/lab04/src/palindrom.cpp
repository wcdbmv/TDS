#include "palindrom.h"

#include <cassert>
#include "stack_array.h"
#include "stack_linked_list.h"

bool palindrom(IStack<char> const* stack, int mode) {
	assert(stack->size());

	IStack<char>* s1 = nullptr;
	IStack<char>* s2 = nullptr;

	std::size_t const n = stack->size();
	std::size_t const m = n / 2;

	if (mode == 0) {
		s1 = new StackArray<char>((StackArray<char>*) stack);
		s2 = new StackArray<char>(m);
	}
	else if (mode == 1) {
		s1 = new StackLinkedList<char>((StackLinkedList<char>*) stack);
		s2 = new StackLinkedList<char>();
	}
	else {
		assert(0);
	}

	for (std::size_t i = 0; i != m; ++i)
		s2->push(s1->pop());

	if (n & 1)
		s1->pop();

	bool ret = true;
	for (std::size_t i = 0; i != m; ++i) {
		if (s1->pop() != s2->pop()) {
			ret = false;
			break;
		}
	}

	delete s1;
	delete s2;

	return ret;
}
