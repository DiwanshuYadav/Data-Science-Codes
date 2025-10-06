#include <iostream>
using namespace std;

struct Node{
    int data;
    Node* next;
};

int main(){
    //Step 1: Create 3 Nodes
    Node* first = new Node(); //first node
    Node* second = new Node(); //second node
    Node* third = new Node(); //third node
    Node* fourth = new Node(); //fourth node

    //Step 2: Initialize the nodes
    first -> data = 10; //first node    
    second -> data = 20; //second node
    third -> data = 30; //third node
    fourth -> data = 40; //fourth node

    //Step 3: Connect Nodes
    first -> next = second;   //first -> second   // To delete any, write third directly instead of second
    second -> next = third;   // second -> third
    third -> next = fourth;   // third -> fourth
    fourth -> next = nullptr; // end of list 

    //Step 4: Print the linked list
    Node* temp = first;  // Starts from first node
    while(temp != nullptr){
        cout<<temp->data<<"->";
        temp = temp->next;  // Move to next node
    }
    cout << "NULL" << endl;
    return 0;
}