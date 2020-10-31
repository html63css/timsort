#include <iostream>

template <class T, class V> class element_list
{
public:
	T ptr_subarray;
	V length_subarray;
	element_list<T,V>* link;
};

template <class T, class V> class list
{
private:
	element_list<T,V>* new_element;
public:
	element_list<T,V>* begin;
	element_list<T,V>* end;
	list()
	{
		new_element = nullptr;
		begin = new element_list<T,V>;
		begin->link = begin;
		end = begin;
	};
	void add_end(T ptr_subarray, V length_subarray)
	{
		if (begin->link == begin)
		{
			begin->ptr_subarray = ptr_subarray;
			begin->length_subarray = length_subarray;
			begin->link = nullptr;
		}
		else
		{
			new_element = new element_list<T,V>;
			new_element->ptr_subarray = ptr_subarray;
			new_element->length_subarray = length_subarray;
			new_element->link = nullptr;
			end->link = new_element;
			end = new_element;
		}
	};
};
