/*
Testo: https://open.kattis.com/problems/shuffles
Tecnica: Maths, Osservazioni
Complessità: O(N)

Idea:
 - Se l'array e' ordinato, allora abbiamo bisogno di 0 mosse
 - Supponiamo che l'array A non sia ordinato, e definiamo "inversione"
   ogni coppia (i, j) tale che i<j e a[i]=a[j]+1, ovvero a[i] e a[j] sono
   di valore consecutivo ma in ordine relativo sbagliato.
 - Il claim e' il seguente: partendo dall'array ordinato, dopo k mosse vi saranno al piu' 2^k inversioni.
   Sketch: dim per induzione su k, considerate quante inversioni al piu' puo' generare una mossa rispetto
            alla precedente. Una mossa deve prima spezzare il mazzo in due parti A_1, A_2. Considerare
            le inversioni che coinvolgono un elemento di A_2 con uno di A_1.
 - Il claim dimostra che se l'array ha 1 <= t <= 2^k inversioni, allora sono necessarie almeno k mosse per ordinarlo
 - Bisogna mostrare che sono anche sufficienti
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    
    int N;
    cin >> N;
    vector<int> where_is(N);
    for(int i=0, x; i<N; ++i) {
        cin >> x;
        where_is[ x-1 ] = i;
    }
    
    int ans = 0;
    for(int i=0; i<N-1; ++i)
        ans += where_is[i] > where_is[i+1];
    
    // __builtin_clz(n) e' una funzione standard di gcc che calcola
    // il numero di 'leading zeros' di n in binario, quindi 
    // 32 - __builtin_clz(n) e' come un log2 arrotondato in eccesso
    cout << (ans == 0 ? 0 : (32 - __builtin_clz(ans))) << endl;
}
