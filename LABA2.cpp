#include <iostream>
#include <vector>
#include "Stack.cpp"
#include <fstream>


int GetMinrun(int n)
{
    int r = 0;
    while (n >= 64)
    {
        r |= n & 1;
        n >>= 1;
    }
    return n + r;
}

void insertion_sort(int* arr, int n)
{
    for (int j = 1; j < n; ++j)
    {
        int value = arr[j];
        int i = j - 1;
        while (i >= 0 && arr[i] > value)
        {
            arr[i + 1] = arr[i];
            arr[i] = value;
            i -= 1;
        }
    }
}

void merge(Stack<int*,int>& STACK, int ind1, int ind2)
{
    int lenght_final_array = STACK[ind1]->length_subarray + STACK[ind2]->length_subarray;
    int* final_array = new int[lenght_final_array];
    int i = 0, j = 0, k = 0;
    for (; i != STACK[ind1]->length_subarray && j != STACK[ind2]->length_subarray;)
    {
        if (STACK[ind1]->ptr_subarray[i] < STACK[ind2]->ptr_subarray[j])
        {
            final_array[k] = STACK[ind1]->ptr_subarray[i];
            ++i;
            ++k;
        }
        else
        {
            final_array[k] = STACK[ind2]->ptr_subarray[j];
            ++j;
            ++k;
        }
    }
    for (;i != STACK[ind1]->length_subarray;)
    {
        final_array[k] = STACK[ind1]->ptr_subarray[i];
        ++i;
        ++k;
    }
    for (; j != STACK[ind2]->length_subarray;)
    {
        final_array[k] = STACK[ind2]->ptr_subarray[j];
        ++j;
        ++k;
    }
    ////delete[] STACK[ind1]->ptr_subarray;
    ////delete[] STACK[ind2]->ptr_subarray;
    STACK.del(ind1);
    STACK.del(ind2);
    STACK.push(final_array, k);
}

void timsort(int* arr, int n)
{
    int minrun = GetMinrun(n);
    std::vector <int*> subarrays;
    int* ptr_subarray = new int [minrun];
    int number_subarray = 0;
    std::vector <int> length_subarray = { 0 };
    subarrays.push_back(ptr_subarray);
    length_subarray[number_subarray]++;
    ptr_subarray[0] = arr[0];
    int j = 1;
    bool orientation = (arr[0] <= arr[1])? 0 : 1; // 0 - возрастание.1 - убывание
    for (int i = 1; i < n; ++i)
    {
        if ((arr[i] >= arr[i - 1] && !orientation) || (arr[i] < arr[i - 1] && orientation))
        {
            ptr_subarray[j] = arr[i];
            length_subarray[number_subarray]++;
            j++;
        }
        else
        {
            if (j < minrun)
            {
                while (j < minrun)
                {
                    ptr_subarray[j] = arr[i];
                    length_subarray[number_subarray]++;
                    j++;
                    i++;
                }
            }
            int lenght_new_subarray;
            orientation = (arr[i] <= arr[i + 1]) ? 0 : 1; // 0 - возрастание.1 - убывание
            j = 1;
            int summ = 0;
            for (auto i : length_subarray) summ += i;
            if (n - summ < minrun)
            {
                lenght_new_subarray = n - summ;
            }
            else
            {
                lenght_new_subarray = minrun;
            }
            if (lenght_new_subarray != 0)
            {
                length_subarray.push_back(0);
                ++number_subarray;
                ptr_subarray = new int[lenght_new_subarray];
                length_subarray[number_subarray]++;
                subarrays.push_back(ptr_subarray);
                ptr_subarray[0] = arr[i];
            }
        }
    }
    for (unsigned int i = 0; i < length_subarray.size();++i)
    {
        insertion_sort(subarrays[i],length_subarray[i]);
    }
    Stack <int*, int> stack_subarray;
    for (int i = 0; i < length_subarray.size(); ++i)
    {
        stack_subarray.push(subarrays[i],length_subarray[i]);
    }
    while (stack_subarray.count > 2)
    {
        int ind1 = stack_subarray.count - 1;
        int ind2 = stack_subarray.count - 2;
        int ind3 = stack_subarray.count - 3;
        if ((stack_subarray[ind1]->length_subarray > stack_subarray[ind2]->length_subarray + stack_subarray[ind3]->length_subarray) && stack_subarray[ind2]->length_subarray > stack_subarray[ind3]->length_subarray)
        {
            merge(stack_subarray, ind1, ind2);
        }
        else
        {
            if (stack_subarray[ind1]->length_subarray > stack_subarray[ind3]->length_subarray)
                merge(stack_subarray, ind2, ind3);
            else
                merge(stack_subarray, ind1, ind2);
        }
    }
    merge(stack_subarray, 0, 1);
    for (int i = 0; i < n; ++i)
    {
        arr[i] = stack_subarray[0]->ptr_subarray[i];
    }
    //delete [] stack_subarray[0]->ptr_subarray;
    //std::cout << "i" << '\t' << "ptr" << '\t' << "length" << '\n';
    //for (int i = 0; i < length_subarray.size(); ++i)
    //{
    //    std::cout << i << '\t' << stack_subarray[i]->ptr_subarray << '\t' << stack_subarray[i]->length_subarray << '\n';
    //}
}

int main()
{
    std::cout << "input";
    std::string index;
    std::cin >> index;
    std::ifstream stream_input(("input" + index + ".txt"));
    int buff;
    int i = 0;
    if (stream_input.is_open())
    {
        for (stream_input >> buff; !stream_input.eof(); stream_input >> buff) ++i;
    }
    else
    {
        std::cout << "ERROR";
        exit(0);
    }
    int LENGTH = i;
    int* ARR_SORT = new int[LENGTH];
    i = 0;
    stream_input.close();
    stream_input.open(("input" + index + ".txt"));
    for (stream_input >> buff; !stream_input.eof(); stream_input >> buff)
    {
        ARR_SORT[i] = buff;
        ++i;
    }
    if (i <= 1)
    {
        exit(0);
    }
    else
    {
        timsort(ARR_SORT, LENGTH);
    
        std::ofstream stream_output("output" + index + ".txt");
        for (int i = 0; i < LENGTH; ++i)
        {
            stream_output << ARR_SORT[i] << ' ';
        }
    }
    return 0;
}