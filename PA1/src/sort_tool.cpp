// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2019/9/6 Cheng-Yun Hsieh]
// **************************************************************************

#include "sort_tool.h"
#include<iostream>

// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int>& data) {
    // Function : Insertion sort
    // TODO : Please complete insertion sort code here
    for (int i=1;i<data.size();i++){
        int key = data[i];
        int j = i-1;
        while(j >= 0 && data[j] > key){
            data[j+1] = data[j];
            j = j-1;
        }
        data[j+1] = key;
    }
    return; 
}

// Quick sort method
void SortTool::QuickSort(vector<int>& data){
    QuickSortSubVector(data, 0, data.size() - 1);
}
// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int>& data, int low, int high) {
    // Function : Quick sort subvector
    // TODO : Please complete QuickSortSubVector code here
    // Hint : recursively call 
    //        Partition function is needed
    if(low < high){
        int mid = Partition(data,low,high);
        QuickSortSubVector(data,low,mid-1);
        QuickSortSubVector(data,mid+1,high);
    }
}

int SortTool::Partition(vector<int>& data, int low, int high) {
    // Function : Partition the vector 
    // TODO : Please complete the function
    // Hint : Textbook page 171
    int x = data[high];//pivot
    int i = low - 1;
    for(int j = low;j <= high-1;j++){
        if(data[j] <= x){
            i += 1;
            swap(data[i],data[j]);
        }
    }
    swap(data[i+1],data[high]);
    return i+1;
}

// Merge sort method
void SortTool::MergeSort(vector<int>& data){
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int>& data, int low, int high) {
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    // Hint : recursively call itself
    //        Merge function is needed
    if(low < high){
        int mid = (low+high)/2;
        MergeSortSubVector(data,low,mid);
        MergeSortSubVector(data,mid+1,high);
        Merge(data,low,mid,high);
        
    }
}


// Merge
void SortTool::Merge(vector<int>& data, int low, int mid, int high) {

    // Function : Merge two sorted subvector
    // TODO : Please complete the function
    int n1 , n2;
    n1 = mid-low+1;
    n2 = high - mid ;
    vector<int> L;
    vector<int> R;
    //cout << "L: ";
    for(int i = 0;i < n1;i++){
        L.push_back(data[low+i]);
        //cout << L[i] << " ";
    }
    //cout << '\n';
    //cout << "R: ";
    for(int i = 0;i < n2;i++){
        R.push_back(data[mid+i+1]);
        //cout << R[i] <<" ";
    }
    //cout << '\n';
    L.push_back(2147483647);
    R.push_back(2147483647);
    int i = 0;
    int j = 0;
    for(int k = low;k <= high;k++ ){
        if(L[i] <= R[j]){
            data[k] = L[i];
            i+=1;
        }
        else{
            data[k] = R[j];
            j+=1;
        }
    }

} 

// Heap sort method
void SortTool::HeapSort(vector<int>& data) {
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1; i >= 1; i--) {
        swap(data[0],data[i]);
        heapSize--;
        MaxHeapify(data,0);
    }
}

//Max heapify
void SortTool::MaxHeapify(vector<int>& data, int root) {
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    // TODO : Please complete max-heapify code here
    int l = 2*root + 1;
    int r = 2*root + 2;
    int lar = -1;
    if(l <= heapSize && data[l] > data[root]){
        lar = l;
    }
    else{
        lar = root;
    } 
    if(r <= heapSize && data[r] > data[lar]){
        lar = r;
    }
    if(lar != root){
        swap(data[root],data[lar]);
        MaxHeapify(data,lar);
    }
}

//Build max heap
void SortTool::BuildMaxHeap(vector<int>& data) {
    heapSize = data.size()-1; // initialize heap size
    // Function : Make input data become a max-heap
    // TODO : Please complete BuildMaxHeap code here
    int x = (data.size()-1)/2;
    for(int i = x;i >=0;i--){
        MaxHeapify(data,i);
    }   
}