#include <iostream>
#include "List.h"

int main()
{
	List<int32_t> lst;

	lst.push_back(5);
	lst.push_front(1);
	lst.push_front(2);
	lst.pop_front();
	lst.push_back(10);
	lst.push_back(22);
	lst.insert(99,2);
	lst.pop_back();
	lst.removeAt(1);
	lst.print();

	return 0;
}