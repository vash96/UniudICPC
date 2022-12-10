/*
Testo: https://open.kattis.com/problems/longincsubseq
Tecnica: Programmazione Dinamica (classico problema LIS)
Complessità: O(n*log(n))

Idea:
 - Si consideri il classico algoritmo per la LIS: si mantengono in un array 'ans'
   i valori ans[i] = il minimo elemento che puo' essere utilizzato per "chiudere" una subseq
   lunga i.
 - L'algoritmo opera scorrendo da sx a dx la sequenza, e al passo i si chiede che subseq puo'
   chiudere s[i]. Detto L l'indice piu' grande "popolato" di ans, si nota che ans[1..L] e'
   ordinato in senso crescente, quindi basta cercare (tramite ricerca binaria) il primo j
   tale che ans[j] >= s[i] (oppure j=L+1 quando questi non esiste) e assegnare ans[j] = s[i].
 - Per questo problema, manteniamo anche un puntatore che collega s[i] con ans[j-1] (il precedente
   della sottosequenza). Piu' precisamente si mantiene un puntatore da i alla posizione del prec.
 - Nel codice, ans mantiene la posizione del minimo elemento invece del minimo in se'.
 - Al termine si scorre la catena dei puntatori da ans[L] in giu'.
*/


#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    
    int N;
    while(cin >> N) {
        vector<long long> s(N);
        for(auto & x : s)
            cin >> x;
        vector<int> ans(N+1, -1), par(N+1, -1);
        int L = 1;
        ans[1] = 0;
        for(int i=1; i<N; ++i) {
            auto iter = lower_bound(ans.begin()+1, ans.begin()+L+1, i, [&s](int x, int y) {
                return s[x] < s[y];
            });
            int j = iter - ans.begin();
            par[i] = ans[j-1];
            ans[j] = i;
            L = max(L, j);
        }
        cout << L << endl;
        vector<int> aa;
        aa.emplace_back(ans[L]);
        for(int i=1; i<L; ++i)
        	aa.emplace_back(par[aa.back()]);
        reverse(aa.begin(), aa.end());
        for(auto x : aa)
        	cout << x << " ";
        cout << endl;
    }
}
