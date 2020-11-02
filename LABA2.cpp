#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

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

void insertion_sort(vector <int>& arr, int n)
{
    for (int j = 0; j < n; ++j)
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

vector <int> merge(vector <int> arr1, vector <int> arr2)
{
    unsigned int i(0), j(0);
    vector <int> final_arr;
    for (; i < arr1.size() && j < arr2.size();)
    {
        if (arr1[i] < arr2[j])
        {
            final_arr.push_back(arr1[i]);
            ++i;
        }
        else
        {
            final_arr.push_back(arr2[j]);
            ++j;
        }
    }
    for (; i < arr1.size(); ++i)
    {
        final_arr.push_back(arr1[i]);
    }
    for (; j < arr2.size(); ++j)
    {
        final_arr.push_back(arr2[j]);
    }
    return final_arr;
}

void timsort(vector<int>& arr, const unsigned int n)
{
    unsigned int minrun = GetMinrun(n);
    vector <int> subarray[2];
    int actual_subarray = 0;
    bool orientation = (arr[0] <= arr[1]) ? 0 : 1; // 0 - возрастание.1 - убывание
    subarray[actual_subarray].push_back(arr[0]);
    for (unsigned int i = 1; i < n; ++i)
    {
        if ((arr[i] >= arr[i - 1] && !orientation) || (arr[i] < arr[i - 1] && orientation))
        {
            subarray[actual_subarray].push_back(arr[i]);
        }
        else
        {
            orientation = !orientation;
            while (subarray[actual_subarray].size() < minrun && (subarray[0].size() + subarray[1].size()) < n)
            {
                subarray[actual_subarray].push_back(arr[i]);
                ++i;
            }
            insertion_sort(subarray[actual_subarray], subarray[actual_subarray].size());
            if (actual_subarray == 1)
            {
                vector<int> buff = merge(subarray[0], subarray[1]);
                subarray[0].clear();
                for (unsigned int i = 0; i < buff.size(); ++i)
                {
                    subarray[0].push_back(buff[i]);
                }
                subarray[1].clear();
            }
            actual_subarray = 1;
            --i;
        }
    }
    for (unsigned int i = 0; i < n; ++i)
    {
        arr[i] = subarray[0][i];
    }
}

int main()
{
    cout << "input";
    string index;
    cin >> index;
    ifstream stream_input(("input" + index + ".txt"));
    int buff;
    vector<int> ARR;
    if (stream_input.is_open())
    {
        for (stream_input >> buff; !stream_input.eof(); stream_input >> buff)
        {
            ARR.push_back(buff);
            buff = 0;
        }
        if (buff != 0) ARR.push_back(buff);
    }
    else
    {
        cout << "ERROR";
        exit(0);
    }
    stream_input.close();
    timsort(ARR, ARR.size());
    std::ofstream stream_output("output" + index + ".txt");
    for (unsigned int i = 0; i < ARR.size(); ++i)
    {
        stream_output << ARR[i] << ' ';
    }
    stream_output.close();
    return 0;
}