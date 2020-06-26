#include <vector>
#include <iostream>
#include <string>
#include <list>
#include <stack>
#include <sstream>


template<typename T>
void merge(std::vector<T> &a, int left_low, int left_high, int right_low, int right_high)
{
	std::vector<T> temp(right_high + 1);
	for (int i = left_low; i <= right_high; i++)
		temp[i] = a[i];
	int i = left_low;
	int j = right_low;

	int k = left_low;
	while (i <= left_high && j <= right_high + 1)
	{
		if (i == left_high + 1)
			while (j <= right_high)
				temp[k++] = a[j++];
		else if (j == right_high + 1)
			while (i <= left_high)
				temp[k++] = a[i++];
		else if (a[i] < a[j])
			temp[k++] = a[i++];
		else
			temp[k++] = a[j++];
	}
	for (int i = left_low; i <= right_high; i++)
		a[i] = temp[i];
}
template<typename T>
void merge_sort(std::vector<T> &a, int low, int high) {
	if (high - low < 1)               // 0 or 1 values to sort  -> sorted
		return;
	else {
		int mid = (low + high) / 2;       
		merge_sort(a, low, mid);        
		merge_sort(a, mid + 1, high);     
		merge(a, low, mid, mid + 1, high);  
	}
}
