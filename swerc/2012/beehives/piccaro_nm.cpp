/**
    l'idea di base è che dobbiamo cercare la lunghezza del ciclo più corto presente nel grafo (facile da dimostrare:
    un albero non basta chiaramente perché un arco lo sconnette, se ho più di un albero per minimalità prenderò il ciclo
    più piccolo presente). Per ogni coppia di nodi (a,b) memorizzo un vector nel quale registro le lunghezze minime dei percorsi
    per andare da a a b, limitando pero' a 2 il numero di lunghezze registrate.
    IMPORTANTE: è proibito per un percorso fare l'arco (u,v) subito dopo aver fatto (v,u).
    Questo perché voglio che il minimo delle somme delle 2 lunghezze (ove presenti) al variare della coppia di nodi (escluse
    quelle del tipo (u,u)) sia uguale al ciclo minimo. Questo accade se la condizione di prima è rispettata. E' infatti
    facile notare che, sotto questa ipotesi, la lunghezza del ciclo minimo corrisponderà al minimo tra le sommme di prima.
    (basta ragionare per assurdo per verificarlo)

    dall'implementazione di seguito abbiamo una complessità O(N(N+M))
**/

#include<bits/stdc++.h>
using namespace std;
int n, m;
#define MAXN 500
vector<int>children[MAXN];      //children[node] = {figli di n}
vector<int> d[MAXN][MAXN];      //dist[from][to] = {migliore e seconda migliore distanza percorribile per andare da from a to
typedef pair<int,int> ii;
typedef pair<ii, int> II;

int main(){
    cin>>n>>m;

    int a, b;

    for(int i=0; i<m; i++){
        scanf("%d%d",&a,&b);
        children[a].push_back(b);
        children[b].push_back(a);
    }

    int sol = 2*MAXN;

    for(int root = 0; root < n; root++){        //per ogni root possibile calcolo d[root][..]
        //il ciclo mi costa O(N+M) essendo che ogni nodo entra nella coda al più 2 volte
        queue<II> Q;        //queue with <<node, parent>, distance>

        Q.push(II(ii(root, -1), 0));
        d[root][root].push_back(0);

        while(!Q.empty()){
            II x = Q.front();
            Q.pop();

            for(int child : children[x.first.first])
                if(child != x.first.second && d[root][child].size() < 2){
                    Q.push(II(ii(child, x.first.first), x.second+1));
                    d[root][child].push_back(x.second+1);
                }
        }

        for(int i = 0; i < n; i++){
            if(i != root && d[root][i].size() == 2){
                sol = min(sol, d[root][i][0] + d[root][i][1]);
            }
        }
    }

    if(sol != 2*MAXN)
        cout<<sol<<endl;
    else
        cout<<"impossible"<<endl;

    return 0;
}
