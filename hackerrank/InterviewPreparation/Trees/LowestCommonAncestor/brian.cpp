

/*The tree node has data, left child and right child 
class Node {
    int data;
    Node* left;
    Node* right;
};

*/
  
    Node *lca(Node *root, int v1,int v2) {
		// Write your code here.
        if(root == nullptr) {
            return nullptr;
        }
        if(v1 > v2) {
            swap(v1, v2);
        }
        
        if(root->data == v1 or root->data == v2) {
            return root;
        }
        
        if(root->data > v2) {
            return lca(root->left, v1, v2);
        }
        if(root->data < v1) {
            return lca(root->right, v1, v2);
        }
        
        return root;
    }

