/*
Testo: https://open.kattis.com/problems/binarytree
Tecnica: Ad-hoc
Complessità: O(|S| + |T|)

Idea:
  - Definiamo r la radice, s il nodo raggiunto da S
  - L'idea è quella di simulare una camminata "parallela" su tutti i nodi raggiungibili da s leggendo T
  - Ad ogni passo avrò a disposizione openL nuovi nodi raggiungibili andando a sinistra, openR nuovi
    nodi raggiungibili andando a destra
  - Se leggo L allora posso andare a sinistra su tutti gli openL nodi e andrò a scoprire un nuovo figlio
    destro su ognuno (mentre i nuovi figli sinistri aperti saranno sempre in numero uguale)
    Per R stessa cosa ma invertito
  - Se leggo U salgo di un livello:
        * Se ero in radice non faccio niente
        * Se sono in un altro nodo, allora l'unico nodo nuovo che posso scoprire è un antenato di s,
          quindi aggiorno la risposta e aggiorno openL ed openR se salgo da R o da L rispettivamente
  - Lo stack si usa per mantenere il cammino r -> s

*/

#include <bits/stdc++.h>
using namespace std;

const int MOD = 21092013;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    for(int t=1; t<=n; ++t) {
        string S;
        string T;
        cin >> S >> T;

        stack<char> st;
        for(auto c : S) {
            if(c == 'U') {
                if(not st.empty()) {
                    st.pop();
                }
            }else {
                st.push(c);
            }
        }

        int ans = 1, openL = 1, openR = 1;        
        for(auto c : T) {
            if(c == 'L') {
                ans = (ans + openL) % MOD;
                openR = (openR + openL) % MOD;
            }else if(c == 'R') {
                ans = (ans + openR) % MOD;
                openL = (openL + openR) % MOD;
            }else if(not st.empty()) {
                ans = (ans + 1) % MOD;
                if(st.top() == 'L') {
                    openR = (openR + 1) % MOD;
                }else {
                    openL = (openL + 1) % MOD;
                }
                st.pop();
            }
        }

        cout << "Case " << t << ": " << ans << "\n";
    }

    return 0;
}