#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class SortAlg
{
public:

	void BubbleSort(vector<int>& array)
	{
		for(int i = 0; i < array.size() ; i++)
		{
			for(int j = 0; j < array.size() - i - 1; j++)
			{
	 			if(array[j] > array[j + 1])
				{
					swap(array[j], array[j + 1]);
		
				}	
			}
		}
	}
	void SelectSort(vector<int>& array)
	{
		int size = array.size();
		for(int i = 0; i < size; i++)
		{
			int temp = array[i];
			int index = i;
			for(int j = i;  j < size; j++)
			{
				if(array[j] < temp)
				{
					temp  = array[j];
					index =	j;
				}
						
			}
			
			swap(array[i], array[index]);
		}
		return;	
	}
	void InsertSort(vector<int>& array)
	{
		int size = array.size();
		for(int i = 0; i < size; i++)
		{
			int j = i - 1;
			while( j >= 0 && array[j + 1] < array [j])
			{
				swap(array[j + 1], array[j]);
				j--;
					
			}
		
			
		}
		return;
	}
	void QuickSort(vector<int>& array, int begin, int end)
	{
		if(begin == end)
			return;
		int temp       = array[begin];
		int temp_begin = begin;
		int temp_end   = end;
		while(begin != end)
		{
			while(begin < end && array[end] >= temp)
				end--;
			if(begin < end)
              		{
				array[begin++] = array[end];
				
			}
			while(begin < end && array[begin] < temp)
				begin++;
			if(begin < end)
			{
				array[end] = array[begin];			
			}
			
			
		}
		array[begin] = temp;
		if(begin-1 > temp_begin)
			QuickSort(array, temp_begin, begin-1);
		if(temp_end > end + 1)
			QuickSort(array, end + 1, temp_end);
		return;
		
	}
	void adjust_heap(vector<int>& array, int size, int index)
	{
		int left  = 2 * index + 1;
		int right = 2 * index + 2;
	
		int max_index = index;
		if(left < size && array[left] > array[max_index])
			max_index = left;
		if(right < size && array[right] > array[max_index])
			max_index = right;
		if(max_index != index)
		{
			swap(array[max_index], array[index]);
			adjust_heap(array, size, max_index);
		}		
	}
	void heapSort(vector<int>& array, int size)
	{
		for(int i = size / 2 - 1; i >= 0; i--)
		{
			adjust_heap(array, size, i);
		}

		for(int i = size - 1; i > 0; i--)
		{
			swap(array[0], array[i]);
			adjust_heap(array, i, 0);
		}
	}

	void MergeHelp(vector<int> &array, int left, int mid, int right)
	{
		vector<int> help(right - left + 1);
		int lIndex = left;
		int rIndex = mid + 1;
		int i = 0;
		while(lIndex <= mid && rIndex <= right)
			help[i++] = array[lIndex] < array[rIndex]? array[lIndex++]:array[rIndex++];

		while(lIndex <= mid)
			help[i++] = array[lIndex++];
		while(rIndex <= right)
			help[i++] = array[rIndex++];
		for(int i = 0; i < help.size(); i++)
			array[left++] = help[i];

	}
	void MergeSort(vector<int> &array, int left, int right)
	{
		if(left < right)
		{
			int mid = (left + right) / 2;
			MergeSort(array, left, mid);
			MergeSort(array, mid + 1, right);
			MergeHelp(array, left, mid, right);
		
		}
	}

};
int main()
{
	
	vector<int> array{4,5,1,6,6,7,3,8,6};
	SortAlg solution;
	solution.heapSort(array,array.size());
	vector<int>::iterator it = array.begin();
	while(it != array.end())
		cout<<*it++<<endl;
	return 0;
	
}
