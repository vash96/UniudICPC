#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

class Graph {
    private:
        int N;
        vector<vector<int>> graph;
    public:
        Graph(int n) : N(n) {
            graph.resize(n);
        }
    
        void add_edge(int u, int v) {
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
    
        vector<int> shortest_reach(int start) {
            queue<pair<int, int>> q;
            vector<int> distance(N, -1);
            q.push({start, 0});
            
            while(!q.empty()) {
                auto head = q.front();
                q.pop();
                
                if(distance[head.first] == -1) {
                    distance[head.first] = head.second;
                    
                    for(auto& e: graph[head.first])
                        if(distance[e] == -1)
                            q.push({e, head.second+1});
                }
            }
            
            for(auto& d: distance)
                if(d != -1)
                    d *= 6;
                
            return distance;
        }
};

int main() {
    int queries;
    cin >> queries;
        
    for (int t = 0; t < queries; t++) {
      
      int n, m;
        cin >> n;
        // Create a graph of size n where each edge weight is 6: 
        Graph graph(n);
        cin >> m;
        // read and set edges
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            // add each edge to the graph
            graph.add_edge(u, v);
        }
      int startId;
        cin >> startId;
        startId--;
        // Find shortest reach from node s
        vector<int> distances = graph.shortest_reach(startId);

        for (int i = 0; i < distances.size(); i++) {
            if (i != startId) {
                cout << distances[i] << " ";
            }
        }
        cout << endl;
    }
    
    return 0;
}
