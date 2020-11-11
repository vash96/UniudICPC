#include <bits/stdc++.h>

using namespace std;

/*
 * Complete the swapNodes function below.
 */

void Depths(int u, int d, vector<vector<int>> & atDepth, const vector<vector<int>> & tree)
{
    if(u >= 0) {
        atDepth[d].emplace_back(u);
        Depths(tree[u][0], d+1, atDepth, tree);
        Depths(tree[u][1], d+1, atDepth, tree);
    }
}

void Swap(int k, const vector<vector<int>> & atDepth, vector<vector<int>> & tree)
{
    for(int d=k; d<=tree.size(); d += k) {
        for(auto u : atDepth[d]) {
            swap(tree[u][0], tree[u][1]);
        }
    }
}

void InOrder(int u, vector<int> & vis, const vector<vector<int>> & tree)
{
    if(u >= 0) {
        InOrder(tree[u][0], vis, tree);
        vis.emplace_back(u+1);
        InOrder(tree[u][1], vis, tree);
    }
}
 
vector<vector<int>> swapNodes(vector<vector<int>> indexes, vector<int> queries) {
    for(auto & v : indexes) {
        --v[0];
        --v[1];
    }
    
    vector<vector<int>> depth(indexes.size()+1);
    Depths(0, 1, depth, indexes);
    
    cerr << "Depths ok!\n";
    vector<vector<int>> ans;
    for(auto k : queries) {
        Swap(k, depth, indexes);
        ans.emplace_back();
        InOrder(0, ans.back(), indexes);
    }
    
    return ans;
}