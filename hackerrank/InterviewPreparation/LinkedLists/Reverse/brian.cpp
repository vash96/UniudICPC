

// Complete the reverse function below.

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
DoublyLinkedListNode* reverse(DoublyLinkedListNode* head) {
    if(head == nullptr) {
        return nullptr;
    }
    
    swap(head->next, head->prev);
    auto ret = reverse(head->prev);
    if(ret == nullptr) {
        return head;
    }else {
        return ret;
    }
}

