#include <bits/stdc++.h>

using namespace std;

unordered_map<int, int> leader, Rank, sz;

void Make(int x)
{
    if(leader[x] == 0) {
        leader[x] = x;
        Rank[x] = 1;
        sz[x] = 1;
    }
}

int Find(int x)
{
    if(leader[x] == x) {
        return x;
    }
    return leader[x] = Find(leader[x]);
}

int Union(int x, int y)
{
    x = Find(x);
    y = Find(y);
    
    if(x == y) {
        return sz[x];
    }
    
    if(x < y) {
        swap(x, y);
    }
    
    leader[y] = x;
    sz[x] += sz[y];
    Rank[x] += Rank[x] == Rank[y];
    
    return sz[x];
}

// Complete the maxCircle function below.
vector<int> maxCircle(vector<vector<int>> queries) {
    leader.clear();
    Rank.clear();
    
    vector<int> ans;
    for(auto & v : queries) {
        int x = v[0], y = v[1];
        Make(x);
        Make(y);
        ans.emplace_back(Union(x, y));
        if(ans.size() >= 2) {
            ans.back() = max(ans.back(), ans[ans.size()-2]);
        }
    }
    
    return ans;
}