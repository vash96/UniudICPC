#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

int Find (const int x, vector<int> & leader) {
    if(leader[x] == x) return x;
    return leader[x] = Find(leader[x], leader);
}

void Union (int x, int y, vector<int> & rank, vector<int> & leader, vector<bool> & hasMachine) {
    x = Find(x, leader);
    y = Find(y, leader);
    
    if(rank[x] < rank[y]) {
        swap(x, y);
    }
    
    leader[y] = x;
    rank[x] += rank[x] == rank[y];
    
    hasMachine[x] = hasMachine[x] or hasMachine[y];
};

// Complete the minTime function below.
int minTime(vector<vector<int>> roads, vector<int> machines) {
    sort(roads.begin(), roads.end(), [](const vector<int> & fst, const vector<int> & snd) {
       return fst[2] > snd[2]; 
    });
    
    vector<int> leader(roads.size()+2);
    vector<int> rank(roads.size()+2, 1);
    vector<bool> hasMachine(roads.size()+2, false);
    for(auto m : machines) {
        hasMachine[m] = true;
    }
    iota(leader.begin(), leader.end(), 0);
    
    
    
    long long cost = 0;
    for(auto & v : roads) {
        int a = v[0], b = v[1], t = v[2];
        int x = Find(a, leader);
        int y = Find(b, leader);
        
        if(hasMachine[x] and hasMachine[y]) {
            cost += t;
        }else {
            Union(x, y, rank, leader, hasMachine);
        }
    }
    
    return cost;
}