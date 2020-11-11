#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

long dfs(int u, const vector<vector<int>> & graph, vector<bool> & vis)
{
    long ans = 0;
    if(not vis[u]) {
        ans = 1;
        vis[u] = true;
        for(auto v : graph[u]) {
            ans += dfs(v, graph, vis);
        }
    }
    
    return ans;
}

// Complete the roadsAndLibraries function below.
long roadsAndLibraries(int n, int c_lib, int c_road, vector<vector<int>> cities) {
    if(c_lib <= c_road) {
        return long(n) * long(c_lib);
    }
    
    // c_lib > c_road
    vector<vector<int>> graph;
    graph.resize(n);
    for(auto & e : cities) {
        int u = e[0]-1, v = e[1]-1;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    
    vector<long> compSize;
    vector<bool> vis(n, false);
    for(int i=0; i<n; ++i) {
        if(not vis[i]) {
            compSize.emplace_back( dfs(i, graph, vis) );
        }
    }
    
    return accumulate(compSize.begin(), compSize.end(), long(0), [&](const long acc, const long x) {
        return acc + long(c_lib) + (x-1) * long(c_road);
    });
}