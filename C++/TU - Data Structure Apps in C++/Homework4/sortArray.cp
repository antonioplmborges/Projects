// sortArray.cpp
// This program sorts an array of Integers using Selection Sort

#include <iostream>

using namespace std;

#define N 10 // Size of Array

// Prototypes
void fill_array(int a[], int size, int& number_used);

void sort(int a[], int number_used);

void swap(int& v1, int& v2);

int index_of_smallest(const int a[], int start_index, int number_used);

// Start of program

int main()
{
  cout << "This program sorts numbers from lowest to highest.\n";

  int sample_array[N], number_used;

  fill_array(sample_array, N, number_used);
  sort(sample_array, number_used);

  cout << "In sorted order the numbers are: \n";
  for (int i = 0; i < number_used; i++)
    cout << sample_array[i];
  cout << endl;

  return 0;
}

void fill_array(int a[], int size, int& number_used)
{
  // size = Declared size of the array
  // number_used = is the number of values stored in
  // a[0] through a[number_used - 1]

  // In this program we assume the array a[] will be filled with the
  // the following values.

  int x[] = {8, 6, 10, 2, 16, 4, 18, 14, 12, 20};

  // We need the size of the array x[]. There is a function
  // sizeof(x) which will give us the size of x in bytes.
  // We need the size in words

  number_used = sizeof(x)/sizeof(int);
  for (int i = 0; i < number_used; i++)
    a[i] = x[i];
  
  return;
}

void sort(int a[], int number_used)
{
  int index_of_next_smallest;
  for (int i = 0; i < number_used - 1; i++)
    {
      // Place the correct value in a[i]
      index_of_next_smallest = index_of_smallest(a, i, number_used);
      swap(a[i], a[index_of_next_smallest]);
    }
  return;
}

void swap(int& v1, int& v2)
{
  int temp = v1;
  v1 = v2;
  v2 = temp;
}

int index_of_smallest(const int a[], int start_index, int number_used)
{
  int min = a[start_index],
    index_of_min = start_index;

  for (int i = start_index+1; i < number_used; i++)
    if (a[i] < min)
      {
	min = a[i];
	index_of_min = i; 
	// min is the smallest of a[start_index] through a[i]
      }
  
  return index_of_min;
}
       
