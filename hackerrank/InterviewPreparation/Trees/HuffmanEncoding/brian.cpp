

/* 
The structure of the node is

typedef struct node
{
    int freq;
    char data;
    node * left;
    node * right;
    
}node;

*/


void decode(node * root, string::iterator & it)
{
    char c = *it;
    auto next = c == '0' ? root->left : root->right;
    
    if(next == nullptr) {
        cout << root->data;
    }else {
        decode(next, ++it);
    }
}

void decode_huff(node * root, string s) {
    for(auto it = s.begin(); it != s.end(); ) {
        decode(root, it);
    }
}

