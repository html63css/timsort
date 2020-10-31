#pragma once
#include "List.cpp"

template <class T, class V> class Stack
{
private:
	list<T,V> A;
public:
	int count;
	Stack()
	{
		count = 0;
	}
	T mini_pop_ptr()
	{
		if (count == 0) return 0;
		else return A.end->ptr_subarray;
	};
	V mini_pop_length()
	{
		if (count == 0) return 0;
		else return A.end->length_subarray;
	};
	void push(T new_element_data1, V new_element_data2)
	{
		A.add_end(new_element_data1, new_element_data2);
		++count;
	};
	element_list<T,V>* operator [](int index)
	{
		element_list<T,V>* i;
		for (i = A.begin; index != 0; --index)
		{
			i = i->link;
		}
		return i;
	}
	void pop()
	{
		if (count != 0)
		{
			if (A.begin == A.end)
			{
				delete A.begin;
			}
			else
			{
				auto i = A.begin;
				for (; i->link != A.end; i = i->link);
				delete A.end;
				A.end = i;
			}
			--count;
			if (count == 0)
			{
				A.begin = new element_list<T,V>;
				A.begin->link = A.begin;
				A.end = A.begin;
			}
		}
		else
		{
			std::cout << "\nERROR\n";
		}
	};
	void del(int ind)
	{
		if (count > 1)
		{

			if (ind == 0)
			{
				auto i = A.begin;
				A.begin = A.begin->link;
				delete i;
			}
			else if (ind == count - 1)
			{
				auto i = A.begin;
				for (; i->link != A.end; i = i->link);
				delete A.end;
				A.end = i;
			}
			else
			{
				element_list<T,V> *element_delete = A.begin;
				for (; ind != 0; --ind)
				{
					element_delete = element_delete->link;
				}
				element_list<T,V> *i = A.begin;
				for (; i->link != element_delete; i = i->link);
				i->link = element_delete->link;
				delete element_delete;
			}
			--count;
		}
		else
		{
			count = 0;
			delete A.begin;
			//A.new_element = nullptr;
			A.begin = new element_list<T, V>;
			A.begin->link = A.begin;
			A.end = A.begin;
		}
	}
};

