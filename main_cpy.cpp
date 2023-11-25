#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <chrono>
#include <ratio>
#include <queue>
using namespace std;

int partition (int array[], int left, int right, int pivotIndex);
void printArray (int array[], int size);
int median3(int array[], int left, int right);



/*************************************************
        Quick Sort (Basic) Implementation
**************************************************/

void quickSort(int array[], int left, int right)
{
    if (left < right)
    {
        int pivotIndex = left;

        int newpivotIndex = partition(array, left, right, pivotIndex);

        //Recursively Sort Array to left and right of pivot respectively
        quickSort(array, left, newpivotIndex - 1);
        quickSort(array, newpivotIndex + 1, right);
    }
}

int partition (int array[], int left, int right, int pivotIndex)
{
    int pivotValue = array[pivotIndex];

    int sortedPivotIndex = left;         //Place where the pivot will be placed after sorting

    //Bring pivot to end of array
    swap(array[pivotIndex], array[right]);

    //Now bring all elements less than pivot to the left end of array
    for (int i = left; i < right; i++)
    {
        if (array[i] < pivotValue)
        {
            swap(array[i], array[sortedPivotIndex]);
            sortedPivotIndex++;
        }
    }

    //Place the pivot back to its correct position
    swap(array[sortedPivotIndex], array[right]);

    return sortedPivotIndex;
}

/*************************************************
        Quick Sort (Better) Implementation
**************************************************/

void betterQuickSort(int array[], int left, int right)
{
    if (left < right)
    {
        //Take Median of array as Pivot
        int pivotValue = median3(array, left, right);

        int i = left, j = right - 1;

        //Begin Partitioning
        for(;;)
        {
            while(array[++i] < pivotValue) { }
            while(array[--j] > pivotValue) { }
            if (i < j)
                swap (array[i], array[j]);
            else
                break;
        }

        //Move Median back to its original location
        swap(array[i], array[right-1]);

        //Recursively sort array
        betterQuickSort(array, left, i - 1);
        betterQuickSort(array, i + 1, right);
    }
}

int median3(int array[], int left, int right)
{
    int center = (left+right) / 2;

    if (array[left] > array[center])
        swap(array[center], array[left]);

    if (array[left] > array[right])
        swap(array[left],array[right]);

    if (array[center] > array[right])
        swap(array[right], array[center]);


    //placing median (pivot) at 2nd last position
    swap(array[center], array[right - 1]);



    return array[right-1];
}
/**************************************************/
int getMaxNumber(int array[], int size){
  int max = array[0];
  for(int i = 0; i < size; i++){
    if(array[i] > max)
      max = array[i];
  }
  
  return max;
}

void radixSort(int array[], int size) {
  // Determine the maximum number of digits required
  int maxNum = getMaxNumber(array, size);
  int digit = 1;
  int current = 0;
  queue<int> count[10];

  // Iterate through each digit position
  while (maxNum / digit > 0) {
    // Count occurrences of each digit in the current position
    for (int i = 0; i < size; i++) {
      current = (array[i] / digit) % 10;
      count[current].push(array[i]);
    }

    // Distribute elements into their respective queues
    int index = 0;
    for (int i = 0; i < 10; i++) {
      while (!count[i].empty()) {
        array[index++] = count[i].front();
        count[i].pop();
      }
    }

    digit *= 10; // Move to the next digit position
  }
}

void printArray(int array[], int size)
{
    cout << "[ ";
    for (int i = 0; i < size; i++)
        cout << array[i] << " ";
    cout << "] " << endl;
}
double sumQuick = 0, sumBetterQuick = 0, sumRadix = 0;

void utilFunction(int size){
     srand(time(NULL));
    cout << size;
    //Dynamically create an array
    int* arrayQuick = new int[size];
    int* arrayBetterQuick = new int[size];
    int* arrayRadix = new int[size];
    
    for(int i = 0; i < size; i++)
    {
      arrayQuick[i] = rand() % 10001;
      arrayBetterQuick[i] = arrayQuick[i];
      arrayRadix[i] = arrayQuick[i];
    }
//    printArray(array, size);
    auto startQuickSort = std::chrono::high_resolution_clock::now();
    quickSort(arrayQuick, 0, size - 1);
    auto endQuickSort = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsedQuickSort = endQuickSort - startQuickSort;
    sumQuick += elapsedQuickSort.count();
    cout << "\t" << elapsedQuickSort.count();
    auto startBetterQuickSort = std::chrono::high_resolution_clock::now();
    betterQuickSort(arrayBetterQuick, 0, size - 1);
    auto endBetterQuickSort = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsedBetterQuickSort = endBetterQuickSort - startBetterQuickSort;
    sumBetterQuick += elapsedBetterQuickSort.count();
    cout << "\t\t" << elapsedBetterQuickSort.count(); 
    auto startRadix = std::chrono::high_resolution_clock::now();
    radixSort(arrayRadix, size);
    auto endRadix = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsedRadix = endRadix - startRadix;
    sumRadix += elapsedRadix.count();
    cout << "\t\t" << elapsedRadix.count(); 
 // printArray(arrayRadix, size);
  delete [] arrayQuick;
  delete [] arrayBetterQuick;
  delete [] arrayRadix;
}

int main()
{
  double avgQuick[8], avgBetterQuick[8], avgRadix[8];
  int loopCount = 0;
  int size = 0;
  cout << "N\tQuickSort\tBetterQuickSort\tRadixSort" << endl;
  while (loopCount < 8) {
    sumQuick = 0;
    sumBetterQuick = 0;
    sumRadix = 0;
    size += 10000000;
   for(int i = 0; i < 3; i++)
   {
    utilFunction(size);
    cout << endl;
   }
   cout << "Average\t" << sumQuick / 3.0 << "\t\t" << sumBetterQuick / 3.0 << "\t\t" << sumRadix / 3.0 << endl;
   avgQuick[loopCount] = sumQuick / 3.0;
   avgBetterQuick[loopCount] = sumBetterQuick / 3.0;
   avgRadix[loopCount] = sumRadix / 3.0;
   cout << endl;
    loopCount++;
  }
  cout << "N[";
  size = 0;
    for(int i = 0; i < 8; i++)
  {
    size += 10000;
    if(i < 7)
    cout <<  size << ", " ;
    else
      cout << size;
  }
    cout << "]" << endl;

  cout << "QuickSort[";
  for(int i = 0; i < loopCount; i++)
  {
    if(i < loopCount - 1)
    cout << avgQuick[i] << ", ";
    else
      cout << avgQuick[i];
  }
  cout << "]" <<  endl << "BetterQuickSort [";
  for(int i = 0; i < loopCount; i++)
  {
    if(i < loopCount - 1)
    cout << avgBetterQuick[i] << ", ";
    else
      cout << avgBetterQuick[i];
  }
  cout << "]" << endl;
  cout << "RadixSort [";
  for(int i = 0; i < loopCount; i++)
  {
    if(i < loopCount - 1)
    cout << avgRadix[i] << ", ";
    else
      cout << avgRadix[i];
  }
  cout << "]" << endl;

    return 0;
}

