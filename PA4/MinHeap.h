#ifndef MIN_HEAP_H
#define MIN_HEAP_H

using namespace std;       

class MinHeap
{
  private:

    int *arr; // pointer to array of elements in heap 
    int capacity; // maximum possible size of min heap 
    int heap_size; // Current number of elements in min heap

  public:

    // Constructor for the MinHeap
    MinHeap(int cap) {
        heap_size = 0; 
        capacity = cap; 
        arr = new int[cap]; 
    }

    // to ge the index of parent of node at index i
    inline int parent(int i) { return (i-1)/2; } 
  
    // to get index of left child of node at index i 
    inline int left(int i) { return (2*i + 1); } 
  
    // to get index of right child of node at index i 
    inline int right(int i) { return (2*i + 2); } 

    // Returns the minimum key (key at root) from min heap 
    inline int getMin() {  return arr[0]; } 

    // Inserts a new key 'k' 
    void insertKey(int k) {
        // Remove below line after your implementation
//        if (heap_size == cap){
//            cap = cap * 2;
//        }
        heap_size += 1;
        arr[heap_size - 1] = k;
        int i = heap_size - 1;
        int counter = 0;
        while (arr[i] < arr[parent(i)] && parent(i) >= 0 && counter < 2){
            swap(arr[i], arr[parent(i)]);
            i = parent(i);
            if (parent(i) == 0){
                counter += 1;
            }
        }
    }
    
    int swapMin(int *arr, int idx){
        if (right(idx) > heap_size && arr[left(idx)] < arr[idx]){
            swap(arr[idx], arr[left(idx)]);
            return 1;
        }
        else{
            if (arr[left(idx)] < arr[right(idx)]){
                if (arr[left(idx)] < arr[idx]){
                    swap(arr[left(idx)], arr[idx]);
                    return 1;
                }
            }
            else{
                if (arr[right(idx)] < arr[idx]){
                    swap(arr[right(idx)], arr[idx]);
                    return 2;
                }
            }
        }
        return 0;
    }

    // Extract the root which is the minimum element 
    int extractMin() {
        // Remove below line after your implementation
        int ext = arr[0];
        arr[0] = arr[heap_size - 1];
        int i = 0;
        int result = 1;
        while (left(i) < heap_size && result != 0){
            result = swapMin(arr, i);
            if (result == 1){
                i = left(i);
            }
            else if (result == 2){
                i = right(i);
            }
        }
        heap_size -= 1;
        return ext;
    }
  
    // Decreases key value of key at index i to newVal 
    void decreaseKey(int i, int newVal) {
        // Remove below line after your implementation
        arr[i] = newVal;
        bool done = false;
        int count = 0;
        int p = parent(i);
        while (p >= 0 && !done && count < 2){
            if (p == 0){
                count += 1;
            }
            if (arr[parent(i)] < arr[i]){
                done = true;
                cout << arr[parent(i)] << " " << arr[i] << endl;
            }
            else{
                swap(arr[p], arr[i]);
                i = p;
                p = parent(i);
            }
        }
    }
  
    // Deletes a key stored at index i 
    void deleteKey(int i) {
        // Remove below line after your implementation
        for (int a = i; a < heap_size - 1; a++){
            arr[a] = arr[a+1];
        }
        heap_size -= 1;
        int result = 1;
        while (left(i) < heap_size && result != 0){
            result = swapMin(arr, i);
            if (result == 1){
                i = left(i);
            }
            else if (result == 2){
                i = right(i);
            }
        }
    }
};

#endif
