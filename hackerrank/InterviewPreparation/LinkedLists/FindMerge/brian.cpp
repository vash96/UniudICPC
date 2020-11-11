

// Complete the findMergeNode function below.

/*
 * For your reference:
 *
 * SinglyLinkedListNode {
 *     int data;
 *     SinglyLinkedListNode* next;
 * };
 *
 */
int findMergeNode(SinglyLinkedListNode* head1, SinglyLinkedListNode* head2) {
    unordered_set<SinglyLinkedListNode*> vis;
    
    while(head1) {
        vis.insert(head1);
        head1 = head1->next;
    }
    
    while(head2) {
        if(vis.find(head2) != vis.end()) {
            return head2->data;
        }
        head2 = head2->next;
    }
    return -1;
}

