/*
Testo: https://codeforces.com/contest/1430/problem/E
Tecnica: sqrt-decomposition (consiglio https://training.olinfo.it/#/task/vasi/statement)
Complessità: O(n * sqrt(n))

Idea:
  - Detta target[i] la lettera che dovrà finire in posizione i, si nota come sia sempre conveniente scegliere
    l'occorrenza di target[i] in posizione j più vicina possibile a i, tra quelle ancora da sistemare
    (il costo di tale operazione sarà |i-j|)
  - Osservare come concentrarsi sul "sistemare" una posizione per volta sia sempre conveniente
  - Osservare che la posizione 1 andrà sistemata prima o poi, tantovale farlo subito; successivamente 2, 3, ...
  - Soluzione naive/quadratica: per ogni i, cerco il più vicino target[i] nei j>i e faccio shift circolare di [i..j] -> [j, i, ..., j-1]
  - Miglioro decomponendo l'array [1..N] in sqrt(N) pezzi lunghi sqrt(N) [1..sqrtN] [sqrtN+1 .. 2sqrtN] ...
    le operazioni possono ora essere effettuate in modo quasi naive in O(sqrtN)
    (ricordarsi di tenere un array delle frequenze per capire facilmente se un blocco contiene il target cercato)
*/


#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    string s;
    cin >> s;

    int sqn = sqrt(n)+1; // Arrotondo per evitare problemi per i quadrati non perfetti
    deque<int> deck[sqn];
    int target[n];
    int freq[sqn][26];
    memset(freq, 0, sizeof(freq));
    for(int i=0; i<n; ++i) { // Costruisco i blocchi, i target e le frequenze
        deck[i/sqn].push_back(s[i]-'a');
        target[i] = s[n-1-i]-'a';
        freq[i/sqn][s[i]-'a']++;
    }

    long long cost = 0;
    for(int i=0; i<n; ++i) { // Per ogni posizione
        int x = i/sqn, y = i%sqn; // Coordinate della posizione nel blocco
        if(deck[x][y] == target[i]) { // Se è già ok salta l'iterazione
            continue;
        }

        for(int j=x; j*sqn<n; ++j) { // Per ogni blocco successivo
            if(freq[j][target[i]] > 0) { // Cerca il primo che contenga target
                int q=0;
                while(q<deck[j].size() and (deck[j][q] != target[i] or (j==x and q<=y))) // Attenzione se il blocco è quello di partenza
                    q++;
                if(q>=deck[j].size()) continue;
                
                cost += j*sqn+q-i; // Aggiorno il costo

                while(q>0) { // Shift dell'ultimo blocco
                    deck[j][q] = deck[j][q-1];
                    q--;
                }
                
                // Sposto l'ultimo di un blocco come primo del successivo, così da mantenere ogni blocco grande sqrtN
                // Aggiorno le frequenze
                int tmp = target[i];
                deck[j].pop_front();
                freq[j][tmp]--;
                int s = j-1;
                while(s >= x) {
                    int tt = deck[s].back();
                    freq[s][tt]--;
                    freq[s+1][tt]++;
                    deck[s].pop_back();
                    deck[s+1].push_front(tt);
                    s--;
                }

                // Push dell'elemento in testa al blocco interessato e shifto per metterlo nella pos giusta
                deck[x].push_front(tmp);
                freq[x][tmp]++;
                for(int z=1; z<=y; ++z) {
                    swap(deck[x][z], deck[x][z-1]);
                }
                break;
            }
        }
    }

    cout << cost << "\n";

    return 0;
}