/*
Testo: https://codeforces.com/contest/748/problem/E
Tecnica: two pointers (consiglio https://training.olinfo.it/#/task/spiedini/statement)
Complessità: O(V) dove V è il numero di fette del mandarino più grande

Idea:
  - Manteniamo tue posizioni (i, j) sul vettore delle frequenze a[x] = quanti mandarini con x fette
  - Le posizioni indicano il fatto che il mandarino con più fette ne ha j e il numero di mandarini con
    fette in [i..j] è >=k
  - L'obbiettivo è trovare il massimo i, quindi ad ogni passo divido a metà tutti i mandarini con j fette
    (incrementando il numeri di mandarini in [i..j-1] di a[j]) e incremento i fintanto che la somma è >= k
  - Al passo successivo ripeto con j-1 e così via
  - Mi fermo quando 2*i > j in quanto dividendo i mandarini di j fette non aumenta il totale
*/

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int v = 1e7+1;

ll n, k;
ll a[v];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    cin >> n >> k;
    ll tot=0;
    for(int i=0, x; i<n; ++i) {
        cin >> x;
        a[x]++;
        tot += x;
    }
    
    if(tot < k) {
        cout << "-1\n";
        return 0;
    }
    
    int i=0, j=v-1;
    tot = n;
    while(i<j and tot<k) { // Divido finché non ho abbastanza mandarini
        int x = j/2;
        a[x] += a[j];
        a[j-x] += a[j];
        tot += a[j];
        a[j] = 0;
        --j;
    }
    while(i<j and tot-a[i]>=k) { // Incremento finché ho troppi mandarini
        tot -= a[i++];
    }

    while(2*i<=j) { // Main loop: divido mandarini di j fette e incremento i mantenendo tot>=k
        int x = j/2;
        a[x] += a[j];
        a[j-x] += a[j];
        tot += a[j];
        a[j] = 0;
        while(i<j and tot-a[i]>=k) {
            tot -= a[i++];
        }
        j--;
    }

    cout << i << "\n";
    
    return 0;
}
