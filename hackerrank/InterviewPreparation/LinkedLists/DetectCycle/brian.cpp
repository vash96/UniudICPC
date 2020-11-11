/*
Detect a cycle in a linked list. Note that the head pointer may be 'NULL' if the list is empty.

A Node is defined as: 
    struct Node {
        int data;
        struct Node* next;
    }
*/
#include <unordered_set>

bool has_cycle(Node* head) {
    // Complete this function
    // Do not write the main method
    unordered_set<Node*> vis;
    
    while(head != NULL) {
        if(vis.find(head) != vis.end())
            return true;
        else {
            vis.insert(head);
            head = head->next;
        }
    }
    
    return false;
}
