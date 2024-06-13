#include <iostream>
#include <vector>
/*
 * Ryan Brodey
 * Basil
 * 11/27/23
 */
using namespace std;

template <typename T>
class Heap {
protected:
    vector<T> heapArray; // Dynamic array to store heap elements
    int capacity;        // Maximum capacity of the heap
    int size;            // Current number of elements in the heap

    // Constructor initializes an empty heap with the given capacity
public:
    Heap(int capacity) : capacity(capacity), size(0) {
        heapArray.resize(capacity);
    }

    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }

    // Function to swap elements at two given indices in the heapArray
    void swap(int i, int j) {
        T temp = heapArray[i];
        heapArray[i] = heapArray[j];
        heapArray[j] = temp;
    }

    // Function to perform heapify operation starting from index i
    virtual void heapify(int i) = 0;

    // Function to check if the heap is empty
    bool isEmpty() {
        return size == 0;
    }

    // Function to check if the heap is full
    bool isFull() {
        return size == capacity;
    }
};

template <typename T>
class MaxHeap : public Heap<T> {
public:
    MaxHeap(int capacity) : Heap<T>(capacity) {}

    // Function to perform heapify operation starting from index i in the Max Heap
    void heapify(int i) override {
        int largest = i;
        int left = this->leftChild(i);
        int right = this->rightChild(i);

        if (left < this->size && this->heapArray[left] > this->heapArray[largest])
            largest = left;

        if (right < this->size && this->heapArray[right] > this->heapArray[largest])
            largest = right;

        if (largest != i) {
            this->swap(i, largest);
            this->heapify(largest);
        }
    }

    // Function to insert a key into the Max Heap
    void insert(T key) {
        if (this->isFull()) {
            cout << "Heap is full. Cannot insert more elements." << endl;
            return;
        }

        // Insert the new key at the end
        int i = this->size;
        this->heapArray[i] = key;
        this->size++;

        // Fix the Max Heap property
        while (i != 0 && this->heapArray[this->parent(i)] < this->heapArray[i]) {
            this->swap(i, this->parent(i));
            i = this->parent(i);
        }
    }

    // Function to extract the maximum element from the Max Heap
    T extract() {
        if (this->isEmpty()) {
            cout << "Heap is empty. Cannot extract element." << endl;
            return T(); // Return a default-constructed value for simplicity (assuming T has a default constructor)
        }

        // The root of the heap contains the maximum element
        T maxElement = this->heapArray[0];

        // Replace the root with the last element
        this->heapArray[0] = this->heapArray[this->size - 1];
        this->size--;

        // Fix the Max Heap property
        this->heapify(0);

        return maxElement;
    }
};

template <typename T>
class PriorityQueue : public MaxHeap<pair<T, int> > {
public:
    PriorityQueue(int capacity) : MaxHeap<pair<T, int> >(capacity) {}

    // Function to insert a key and its priority into the Priority Queue
    void insert(T key, int priority) {
        // Create a pair with the key and priority
        pair<T, int> element = make_pair(key, priority);
        MaxHeap<pair<T, int> >::insert(element);
    }

    // Function to extract the key with the highest priority from the Priority Queue
    T extractMax() {
        // Check if the Priority Queue is empty
        if (this->isEmpty()) {
            cout << "Priority Queue is empty. Cannot extract element." << endl;
            return T(); // Return a default-constructed value for simplicity (assuming T has a default constructor)
        }

        // Extract the pair with the maximum priority from the Max Heap
        pair<T, int> maxPair = MaxHeap<pair<T, int> >::extract();

        // Return the key from the extracted pair
        return maxPair.first;
    }

    // Function to decrease the priority of a key in the Priority Queue
    void decreaseKey(T key, int newPriority) {
        // Find the index of the key in the Max Heap
        int index = -1;
        for (int i = 0; i < this->size; ++i) {
            if (this->heapArray[i].first == key) {
                index = i;
                break;
            }
        }

        // Update the priority of the key in the Max Heap
        this->heapArray[index].second = newPriority;

        // Fix the Max Heap property by adjusting the key's position
        while (index != 0 && this->heapArray[this->parent(index)].second < this->heapArray[index].second) {
            this->swap(index, this->parent(index));
            index = this->parent(index);
        }

        // Maintain the heap property
        this->heapify(index);
    }
};

int main() {
    // Instantiate and test MaxHeap
    MaxHeap<int> maxHeap(10);

    cout << "Max Element: " << maxHeap.extract() << endl; // Before this line no elements are inserted so the heap will be empty

    int arr[] = {12, 7, 1, 4, 8, 5, 6, 10};
    int n = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < n; ++i) {
        maxHeap.insert(arr[i]);
    }

    cout << "Heapified array: ";
    while (!maxHeap.isEmpty()) {
        cout << maxHeap.extract() << " ";
    }

    cout << endl;

    // Instantiate and test PriorityQueue
    PriorityQueue<int> priorityQueue(10);

    priorityQueue.insert(4, 2);
    priorityQueue.insert(7, 5);
    priorityQueue.insert(2, 1);
    priorityQueue.insert(5, 4);
    priorityQueue.insert(1, 3);

    cout << "Max Priority Element: " << priorityQueue.extractMax() << endl;

    // Demonstrate decreaseKey()
    priorityQueue.decreaseKey(7, 1);

    cout << "Updated Max Priority Element: " << priorityQueue.extractMax() << endl;

    return 0;
}
