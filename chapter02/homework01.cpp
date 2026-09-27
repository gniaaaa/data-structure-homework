#include<iostream>
using namespace std;
struct node
{
	int data;  
	struct node *next;
};

node* linklist(node*& a, node*& b){
    node *head = new node;
    head->next = NULL;
    node* current = head;
    while(a != nullptr && b !=nullptr){
        if(a->data > b->data){
            current->next = b;
            current = b;
            b = b->next;
        }
        else{
            current->next = a;
            current = a;
            a = a->next;
        }
    }
    while(a != nullptr){
        current->next = a;
        current = a;
        a = a->next;
    }
    while(b != nullptr){
        current->next = b;
        current = b;
        b = b->next;
    }

    node* fast = nullptr;
    node* slow = nullptr;
    if(head->next != nullptr){
        fast = head->next;
        slow = head->next;
    }
    else{
        return nullptr;
        delete head;
    }

    node* bottom = nullptr;
    while(fast != nullptr){
        fast = fast->next;
        slow->next = bottom;
        bottom = slow;
        slow = fast;
    }
    delete head;
    return bottom;
}
