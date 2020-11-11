#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

int bfs(int i, int j, vector<vector<int>> & grid, vector<vector<bool>> & vis)
{
    int N = grid.size();
    int M = grid[0].size();
    int sizeComp = 0;
    
    queue<pair<int, int>> Queue;
    Queue.push({i, j});
    
    while(not Queue.empty()) {
        int x = Queue.front().first;
        int y = Queue.front().second;
        Queue.pop();
        
        if(not vis[x][y]) {
            ++sizeComp;
            vis[x][y] = true;
            
            for(int xx=max(x-1, 0); xx<=min(x+1, N-1); ++xx) {
                for(int yy=max(y-1, 0); yy<=min(y+1, M-1); ++yy) {
                    if(not vis[xx][yy] and grid[xx][yy]==1)
                        Queue.push({xx, yy});
                }
            }
        }
    }
    
    return sizeComp;
}

int get_biggest_region(vector< vector<int> > & grid) {
    vector<vector<bool>> vis(grid.size());
    for(auto & row: vis)
        row.resize(grid[0].size(), false);
    
    int bestComp = 0;
    for(int i=0; i<(int)grid.size(); ++i) {
        for(int j=0; j<(int)grid[0].size(); ++j) {
            if(not vis[i][j] and grid[i][j]==1)
                bestComp = max(bestComp, bfs(i, j, grid, vis));
        }
    }
    
    return bestComp;
}

int main(){
    int n;
    cin >> n;
    int m;
    cin >> m;
    vector< vector<int> > grid(n,vector<int>(m));
    for(int grid_i = 0;grid_i < n;grid_i++){
       for(int grid_j = 0;grid_j < m;grid_j++){
          cin >> grid[grid_i][grid_j];
       }
    }
    cout << get_biggest_region(grid) << endl;
    return 0;
}
