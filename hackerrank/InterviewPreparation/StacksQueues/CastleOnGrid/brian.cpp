#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the minimumMoves function below.
int minimumMoves(vector<string> grid, int startX, int startY, int goalX, int goalY) {
    int n = grid.size(), m = grid[0].size();
    vector<vector<bool>> graph(n+2, vector<bool>(m+2, false));
    for(int i=0; i<n; ++i) {
        for(int j=0; j<m; ++j) {
            graph[i+1][j+1] = grid[i][j] == '.';
        }
    }
    
    ++startX; ++startY;
    ++goalX; ++goalY;
    vector<vector<long>> dist(n+2, vector<long>(m+2, 1e9));
    queue<pair<int, int>> q;
    q.emplace(startX, startY);
    
    dist[startX][startY] = 0;
    while(not q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        
        // go up
        int xx = x, yy = y;
        while(graph[xx-1][yy]) {
            --xx;
            if(dist[xx][yy] > 1+dist[x][y]) {
                dist[xx][yy] = 1+dist[x][y];
                q.emplace(xx, yy);
            }
        }
        
        // go down
        xx = x; yy = y;
        while(graph[xx+1][yy]) {
            ++xx;
            if(dist[xx][yy] > 1+dist[x][y]) {
                dist[xx][yy] = 1+dist[x][y];
                q.emplace(xx, yy);
            }
        }

        
        // go left
        xx = x; yy = y;
        while(graph[xx][yy-1]) {
            --yy;
            if(dist[xx][yy] > 1+dist[x][y]) {
                dist[xx][yy] = 1+dist[x][y];
                q.emplace(xx, yy);
            }
        }
        
        // right
        xx = x; yy = y;
        while(graph[xx][yy+1]) {
            ++yy;
            if(dist[xx][yy] > 1+dist[x][y]) {
                dist[xx][yy] = 1+dist[x][y];
                q.emplace(xx, yy);
            }
        }
    }
    
    return dist[goalX][goalY];
}