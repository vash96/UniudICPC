/*
Testo: https://www.hackerrank.com/challenges/kth-ancestor/problem
Tecnica: Binary lifting/jump pointers, Programmazione dinamica
            (consiglio https://training.olinfo.it/#/task/trasporti/statement)
Complessità: O((Q+N) * logN)

Idea:
 - Algoritmo naive: mantenere per ogni vertice la lista (ordinata) di tutti i suoi ancestor.
    In questo modo si hanno potenzialmente un numero quadratico di elementi salvati.
 - Per migliorare, possiamo mantenere solo gli ancestor che sono distanti una potenza di 2:
    * Tabella kparent[i][j] = antenato di i che si trova a distanza 2^j
    * Il calcolo di kparent può essere svolto in programmazione dinamica:
        L'ancestor a distanza 2^0 da i è il padre
        L'ancestor a distanza 2^k da i è l'ancestor a distanza 2^(k-1) da quello a distanza 2^(k-1) da i
    * Dimensione della tabella e costo per riempirla O(N * logN)
 - Una query di K ancestor è facile scomponendo K in potenze di due e "saltando" sui rispettivi antenati in O(logN)
 - Eliminare un vertice ha costo O(1)
 - Aggiungere un vertice costa come riempire una colonna della tabella, quindi O(logN)
*/

#include <bits/stdc++.h>
using namespace std;
const int MAX = 1e5+1;

void solve()
{
    int P, Q;
    int kparent[MAX][17]; memset(kparent, 0, sizeof(kparent));
    vector<bool> isin(MAX, false);
    cin >> P;
    
    for(int i=0, x, y; i<P; ++i) {
        cin >> x >> y;
        isin[x] = true;
        kparent[x][0] = y;
    }

    // Popolare la tabella per potenze di 2 crescenti
    for(int j=1; j<17; ++j) {
        for(int i=0; i<MAX; ++i) {
            kparent[i][j] = kparent[kparent[i][j-1]][j-1];
        }
    }

    cin >> Q;
    for(int q=0, x, y, k, t; q<Q; ++q) {
        cin >> t;
        if(t == 0) { // Inserisco un nodo e popolo la colonna
            cin >> y >> x;
            kparent[x][0] = y;
            for(int j=1; j<17; ++j) {
                kparent[x][j] = kparent[kparent[x][j-1]][j-1];
            }
            isin[x] = true;
        }else if(t == 1) { // Elimino il nodo
            cin >> x;
            isin[x] = false;
        }else{ // Ricerca del K ancestor
            cin >> x >> k;
            if(not isin[x]) {
                cout << "0\n";
                continue;
            }
            int ans = x;
            while(ans != 0 and k > 0) { // Finché non sono fuori dall'albero e devo ancora percorrere strada
                int j=0;
                while((1<<(j+1)) <= k) { // Cerco il salto più lungo <= k
                    ++j;
                }
                ans = kparent[ans][j]; // Salto
                k -= (1<<j); // Aggiorno la nuova distanza
            }
            cout << ans << "\n";
        }
    }
}


int main() {
    ios_base::sync_with_stdio(false);

    int T;
    cin >> T;
    for(int t=0; t<T; ++t) {
        solve();
    }

    return 0;
}
