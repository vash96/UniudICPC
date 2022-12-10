/*
Testo: https://open.kattis.com/problems/euclidsgame
Tecnica: Game theory, Osservazione
Complessità: O(log(n))

Idea:
 - Per semplicita' si consideri lo stato del gioco (a, b) con a >= b
 - Sia k=floor(a/b), quindi k*b e' il massimo multiplo di b che posso giocare
 - Se k=1, allora sono costretto a giocare b e l'avversario si trova nello stato (b, a-b)
    (e la partita viene giocata ricorsivamente)
 - Se k>1, allora posso sempre vincere:
   -- Se k*b mi fa vincere, allora non c'e' altro da dimostrare
   -- Se k*b mi fa perdere, allora lo stato (b, a-kb) e' vincente (per l'avversario),
      ma allora mi basta giocare (k-1)*b, inducendo l'avversario in (a - (k-1)b, b) e costringendolo
      a giocare b (unica mossa a disposizione), inducendo me nello stato (b, a-kb) che abbiamo stabilito essere vincente.
*/

#include <bits/stdc++.h>
using namespace std;

int Wins(int a, int b, bool me)
{
    if(a < b)
        swap(a, b);
    if(b == 0)
    	return not me;
    int k = a/b;
    return k > 1 ? me : Wins(a - k*b, b, not me);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    const array<string, 2> who = {{"Stan wins\n", "Ollie wins\n"}};
    
    while(true) {
        int a, b;
        cin >> a >> b;
        if(a < b)
            swap(a, b);
        if(a == 0)
            return 0;
        cout << who[Wins(a, b, 0)];
    }
}