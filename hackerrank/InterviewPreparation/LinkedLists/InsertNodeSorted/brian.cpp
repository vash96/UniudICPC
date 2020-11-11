

// Complete the sortedInsert function below.

/*
 * For your reference:
 *
 * DoublyLinkedListNode {
 *     int data;
 *     DoublyLinkedListNode* next;
 *     DoublyLinkedListNode* prev;
 * };
 *
 */
DoublyLinkedListNode* sortedInsert(DoublyLinkedListNode* head, int data) {
    auto newNode = new DoublyLinkedListNode(data);
    auto ans = newNode;
    
    newNode->next = head;
    if(head) {
        head->prev = newNode;
    }
    
    while(newNode->next and newNode->data > newNode->next->data) {
        swap(newNode->data, newNode->next->data);
        newNode = newNode->next;
    }
    
    return ans;
}

