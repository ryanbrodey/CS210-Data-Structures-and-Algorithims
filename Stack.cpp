#include <iostream>

// Definition of a Node class for singly linked list
class Node {
public:
    int data;       // Data stored in the node
    Node* next;     // Pointer to the next node in the list

    // Constructor to initialize a Node with a given value
    Node(int val) {
        data = val;
        next = nullptr;
    }
};

// Definition of a custom stack class using singly linked list
class MyCustomStack {
private:
    Node* top;  // Pointer to the top of the stack

public:
    // Constructor to initialize the stack
    MyCustomStack() {
        top = nullptr;
    }

    // Function to push an element onto the stack
    void push(int value) {
        Node* newNode = new Node(value);
        newNode->next = top;
        top = newNode;
    }

    // Function to pop and return the top element from the stack
    int pop() {
        if (isEmpty()) {
            return -1; // Return -1 if the stack is empty
        }
        Node* temp = top;
        top = top->next;
        int poppedValue = temp->data;
        delete temp;
        return poppedValue;
    }

    // Function to peek and return the top element without removing it
    int peek() {
        if (isEmpty()) {
            return -1; // Return -1 if the stack is empty
        }
        return top->data;
    }

    // Function to check if the stack is empty
    bool isEmpty() {
        return top == nullptr;
    }

    // Function to print the elements of the stack
    // Useful for testing and debugging
    void printStack() {
        Node* current = top;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

int main() {
    MyCustomStack myStack;

    // Pushing elements onto the stack
    myStack.push(8);
    myStack.push(16);
    myStack.push(24);
    myStack.printStack(); // Output: 8 16 24

    // Peeking at the top element
    int topValue = myStack.peek();
    std::cout << "Top element is: " << topValue << std::endl; // Output: Top element is: 24

    // Popping an element from the stack
    int poppedValue = myStack.pop();
    std::cout << "Popped element is: " << poppedValue << std::endl; // Output: Popped element is: 24

    myStack.printStack(); // Output: 16 8

    // Checking if the stack is empty
    bool empty = myStack.isEmpty();
    std::cout << "Is the stack empty? " << (empty ? "Yes" : "No") << std::endl; // Output: Is the stack empty? No

    return 0;
}

