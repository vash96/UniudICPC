#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

struct Trie {
    struct Node {
        vector<Node*> child;
        Node() : child(2, nullptr) {}
    };
    
    Node* root;
    
    Trie() : root(new Node) { }
    
    vector<int> Base2(int n) {
        vector<int> base2(32, 0);
        int i = 31;
        while(n > 0) {
            base2[i--] = n % 2;
            n /= 2;
        }
        return base2;
    }
    
    void AddNum(int n) {
        auto base2 = Base2(n);
        auto curr = root;
        for(auto dig : base2) {
            if(curr->child[dig] == nullptr) {
                curr->child[dig] = new Node;
            }
            curr = curr->child[dig];
        }
    }
    
    int GetMax(int n) {
        auto base2 = Base2(n);
        int ans = 0;
        
        auto curr = root;
        for(auto dig : base2) {
            if(curr->child[1-dig] != nullptr) {
                ans = 2*ans + 1;
                curr = curr->child[1-dig];
            }else {
                ans = 2*ans;
                curr = curr->child[dig];
            }
        }
        
        return ans;
    }
};

// Complete the maxXor function below.
vector<int> maxXor(vector<int> arr, vector<int> queries) {
    // solve here
    Trie trie;
    
    for(auto x : arr) {
        trie.AddNum(x);
    }
    
    vector<int> ans;
    for(auto q : queries) {
        ans.emplace_back(trie.GetMax(q));
    }
    
    return ans;
}