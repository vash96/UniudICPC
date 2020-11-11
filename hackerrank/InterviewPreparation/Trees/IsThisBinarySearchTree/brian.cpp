/* Hidden stub code will pass a root argument to the function below. Complete the function to solve the challenge. Hint: you may want to write one or more helper functions.  

The Node struct is defined as follows:
   struct Node {
      int data;
      Node* left;
      Node* right;
   }
*/
   bool helper(Node* root, int left, int right) {
       if(root == nullptr)
           return true;
       else if(root->data<left or root->data>right)
           return false;
       else
           return helper(root->left, left, root->data-1) and helper(root->right, root->data+1, right);
   }
    
   bool checkBST(Node* root) {
      return helper(root, 0, 10000);
   }
