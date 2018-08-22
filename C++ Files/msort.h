// This is the .h file that uses templates and merge sort
// Everywhere instead of compare < or > or something just use 
// the Comparator. 

#include <iostream>
#include <cstdlib>
#include <vector>
#include "mydatastore.h"

using namespace std;


template <class T, class Comparator>
void merge(vector<T>& input, vector<T>& output, int s1, int e1, int s2, int e2, Comparator comp) {

	int i = s1;

	while(s1<=e1 && s2<=e2) {
		if(comp(input[s1], input[s2])) {	
			output[i] = input[s1];
			s1++;
		}
		else {
			output[i] = input[s2];
			s2++;
		}
		i++;
	}

	while (s1 <= e1)	//change this condition?
    {
        output[i] = input[s1];
        i++;
        s1++;
    }
    while (s2 <= e2)	//change this condition?
    {
        output[i] = input[s2];
        i++;
        s2++;
    }

    input = output;

}

template <class T, class Comparator>
void split(vector<T>& input, vector <T>& myArray, int start, int end, Comparator comp) {
	
	if(start>=end) {
		return;
	}

	int mid = (start + end)/2;
	split(input, myArray, start, mid, comp);
	split(input, myArray, mid+1, end, comp);

	merge(input, myArray, start, mid, mid+1, end, comp);
}

template <class T, class Comparator>
void mergeSort(vector<T>& myArray, Comparator comp) {

	if (myArray.size() == 0 || myArray.size() == 1)
	{
		return;
	}
	class vector<T> input(myArray);
	split(input, myArray, 0, myArray.size() - 1, comp);

}