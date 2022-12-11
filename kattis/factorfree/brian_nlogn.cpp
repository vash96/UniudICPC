/*
Testo: https://open.kattis.com/problems/factorfree
Tecnica: Divide and Conquer, Osservazioni
Complessità: O(NlogN)

Idea:
 - La prima cosa da osservare e' che la radice dell'albero deve essere coprima
   con tutto il resto dell'array
 - Supponiamo che la radice sia a[i], allora il sotto-albero sinistro avra' i nodi
   in a[1..i-1] e il sotto-albero destro avra' i nodi in a[i+1..N] e a loro volta
   saranno factor-free
 - L'idea quindi e' quella di costruire un factor-free tree sul sottoarray a[l..r]
   ricorsivamente:
   -- Se l>r, allora l'albero e' vuoto
   -- Se l=r, allora il factor-free tree ha solo il nodo a[l]
   -- Se l<r, allora cerco l<=i<=r tale che a[i] e' coprimo con tutto a[l..r] (tolto a[i]),
      lo metto come radice, e ricorro nei sottoproblemi a[l..i-1] e a[i+1..r]
   -- Se l<r ma non trovo un tale i, allora il factor-free tree non esiste
 - Come stare nei tempi:
   -- Vogliamo un modo rapido per rispondere al test Coprime(l, i, r) = "a[i] e' coprimo con il resto di a[l..r]?":
      --- Ci precalcoliamo per ogni intero i fattori primi distinti (si puo' fare con una modifica del crivello)
          Il costo di questo e' O(nlogn)
      --- Per ogni elemento a[i], ci calcoliamo gli indici 'j' e 'k' piu' vicini tali che j < i < k e a[j] e a[k]
          condividono un fattore primo in comune con a[i] (si puo' fare con una sorta di programmazione dinamica)
          Il costo e' O(nlogn)
      --- Una volta svolto il pre-compute, si puo' rispondere al test in O(1)
   -- Vogliamo anche una ricorsione 'equa':
      --- Quando trovo la radice l<i<r, spezzo il problema a[l..r] nei problemi a[l..i-1] e a[i+1..r],
          quindi se 'i' si trova a meta', la ricorsione spacca il problema in due e la scansione mi costa n/2,
          mentre se 'i' si trova vicino a un bordo, la ricorsione spacca il problema in modo sbilanciato ma la scansione
          puo' essere fermata prima
      --- Percio' scansiono un passo vicino al bordo sx e un passo vicino al bordo dx (fermandomi a meta'):
          se sono fortunato, trovo la radice vicino al bordo e ricorro subito
          se sono sfortunato, trovo la radice a meta' e spacco il problema in modo equo
      --- Non ho un argomento rigoroso per dire che la complessita' e' O(nlogn), ma dovrebbe essere cosi'
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    
    // Crivello di eratostene
    const int MAX = 1e7;
    vector<vector<int>> factors(MAX+1);
    for(int i=2; i<=MAX; ++i) {
        if(factors[i].empty()) {
            for(int j=1; i*j<=MAX; ++j)
                factors[i*j].emplace_back(i);
        }
    }
    
    // Input
    int N;
    cin >> N;
    vector<int> a(N);
    for(auto & x : a)
        cin >> x;
    
    // Pre-computo i 'j' dell'idea sopra
    vector<int> lft(N);
    vector<int> last(MAX+1, -1); // last[f] e' la posizione della piu' recente occorrenza vista di 'f' 
    for(int i=0; i<N; ++i) {
        int curr = -1;
        for(auto f : factors[ a[i] ]) {
            curr = max(curr, last[f]);
            last[f] = i;
        }
        lft[i] = curr;
    }
    last.clear();

    // Pre-computo i 'k' dell'idea sopra
    vector<int> rgt(N);
    last.resize(MAX+1, N);
    for(int i=N-1; i>=0; --i) {
        int curr = N;
        for(auto f : factors[ a[i] ]) {
            curr = min(curr, last[f]);
            last[f] = i;
        }
        rgt[i] = curr;
    }

    // Test Coprime(l, i, r) dell'idea sopra
    const auto Coprime = [&lft, &rgt](int l, int i, int r) {
        return lft[i] < l and r < rgt[i];
    };
    
    // Risolvo ricorsivamente: -1 indica che la soluzione non esiste, -2 indica il sottoalbero vuoto
    function<int(int, int)> solve;
    vector<int> par(N, 0);
    solve = [&par, &Coprime, &solve](int l, int r) -> int {
        int n = r-l+1;
        if(n <= 0) // Albero vuoto
            return -2;
        if(n == 1) // Albero con un solo nodo
            return l;
        for(int i=0; i<n; ++i) { // Scansiono
            if(l+i > r-i) // Se non ho trovato la radice prima della meta', allora non esiste
                return -1;
            // left
            int root = l+i;
            if(not Coprime(l, root, r)) // Se vicino al bordo sinistro non trovo...
                root = r-i;             // ...provo vicino al bordo destro
            
            if(Coprime(l, root, r)) { // Se la radice (qualunque essa sia) e' buona, ricorro
                int L = solve(l, root-1); // Ricorro a sx
                int R = solve(root+1, r); // Ricorro a dx
                if(L == -1 or R == -1) // Se la sol non esiste in uno dei due rami, allora non esiste
                    return -1;
                if(L >= 0) // Se a sx l'albero non e' vuoto, L rappresenta l'indice della radice
                    par[L] = root+1; // Radice 1-based
                if(R >= 0) // Stessa cosa del caso sx
                    par[R] = root+1;
                return root;
            }
        }
        
        return -1;
    };
    
    auto ans = solve(0, N-1);
    if(ans == -1)
        cout << "impossible\n";
    else {
        for(auto x : par)
            cout << x << " ";
        cout << endl;
    }
}