#include <iostream>

class Node {
public:
    int data;
    Node* next;

    // Constructor to initialize a Node with a given value
    Node(int val) {
        data = val;
        next = nullptr;
    }
};

class CustomQueue {
private:
    Node* frontPtr; // Pointer to the front of the queue
    Node* rearPtr;  // Pointer to the rear of the queue

public:
    // Constructor to initialize the queue
    CustomQueue() {
        frontPtr = nullptr;
        rearPtr = nullptr;
    }

    // Function to enqueue an element into the queue
    void enqueue(int value) {
        Node* newNode = new Node(value);
        if (isEmpty()) {
            frontPtr = newNode;
            rearPtr = newNode;
        } else {
            rearPtr->next = newNode;
            rearPtr = newNode;
        }
    }

    // Function to dequeue and return the front element from the queue
    int dequeue() {
        if (isEmpty()) {
            return -1; // Return -1 if the queue is empty
        }
        Node* temp = frontPtr;
        frontPtr = frontPtr->next;
        int dequeuedValue = temp->data;
        delete temp;
        return dequeuedValue;
    }

    // Function to return the front element of the queue without removing it
    int front() {
        if (isEmpty()) {
            return -1; // Return -1 if the queue is empty
        }
        return frontPtr->data;
    }

    // Function to check if the queue is empty
    bool isEmpty() {
        return frontPtr == nullptr;
    }

    // Function to print the elements of the queue
    // Useful for testing and debugging
    void printQueue() {
        Node* current = frontPtr;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

int main() {
    // Create an instance of the CustomQueue class
    CustomQueue myQueue;

    // Perform various queue operations and print the queue at each stage
    myQueue.enqueue(2);
    myQueue.enqueue(4);
    myQueue.enqueue(6);
    myQueue.printQueue(); // Output: 2 4 6

    int frontValue = myQueue.front();
    std::cout << "The front element is: " << frontValue << std::endl; // Output: Front element is: 2

    int dequeuedValue = myQueue.dequeue();
    std::cout << "The dequeued element is: " << dequeuedValue << std::endl; // Output: Dequeued element is: 2

    myQueue.printQueue(); // Output: 2 4

    bool empty = myQueue.isEmpty();
    std::cout << "Is the queue empty? " << (empty ? "Yes" : "No") << std::endl; // Output: Is the queue empty? No

    return 0;
}
