

// Complete the insertNodeAtPosition function below.

/*
 * For your reference:
 *
 * SinglyLinkedListNode {
 *     int data;
 *     SinglyLinkedListNode* next;
 * };
 *
 */
SinglyLinkedListNode* insertNodeAtPosition(SinglyLinkedListNode* head, int data, int position) {
    auto old = head;
    int pos = 0;
    while(pos+1 < position) {
        ++pos;
        head = head->next;
    }
    auto newNode = new SinglyLinkedListNode(data);
    newNode->next = head->next;
    head->next = newNode;
    
    return old;
}

