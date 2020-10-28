#include <bits/stdc++.h>
using namespace std;
#define M 1000
bool conn[M+1][M+1];
vector<int> children[M+1];
int cant[M+1][5];
int colored[M+1];
int cantCnt[M+1];
typedef pair<int,int> ii; //available colors, node
priority_queue<ii, vector<ii>, greater<ii>> pq;
vector<int> sol;
int N;

inline void color(int node, int col){
    colored[node] = col;

    for(int child : children[node]){
        cant[child][col]++;
        if(cant[child][col] == 1)
            cantCnt[child]++;

        //cout<<"   coloring "<<node<<" of "<<colored[node]<<" effects on "<<child<<" : "<<cant[child][col]<<" "<<cantCnt[child]<<endl;

        pq.push(ii(4-cantCnt[child], child));
    }
}

inline void decolor(int node, int col){
    colored[node] = 0;

    for(int child : children[node]){
        cant[child][col]--;
        if(cant[child][col] == 0)
            cantCnt[child]--;

        pq.push(ii(4-cantCnt[child], child));
    }
}

void explore(int node){
    //cout<<node<<" -> "<<colored[node]<<endl;
    while(!pq.empty()){
        ii t = pq.top();
        pq.pop();

        if(colored[t.second] == 0 && t.first + cantCnt[t.second] == 4){
            for(int i = 1; i <= 4; i++)
                if(cant[t.second][i] == 0){
                    color(t.second, i);

                    //cout<<"exploring from "<<node<<" to "<<t.second<<endl;

                    explore(t.second);

                    if(!sol.empty())
                        return;

                    decolor(t.second, i);
                }
        }
    }

    for(int i=1; i<=N; i++){
        sol.push_back(colored[i]);
    }
}

int main(){
    scanf("%d\n", &N);

    int a, b;

    while(scanf("%d-%d\n",&a,&b) != EOF){
        conn[a][b] = conn[b][a] = 1;
    }

    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++)
            if(conn[i][j])
                children[i].push_back(j);
    }

    for(int i=2; i<=N; i++)
        pq.push(ii(4, i));

    color(1, 1);

    explore(1);

    for(int i=1; i<=N; i++)
        cout<<i<<" "<<sol[i-1]<<endl;

    return 0;
}
