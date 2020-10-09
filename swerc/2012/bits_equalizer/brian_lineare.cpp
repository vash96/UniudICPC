/*
Testo: https://open.kattis.com/problems/bitsequalizer
Tecnica: Ad hoc, osservazione
Complessità: O(|S|)

Idea:
 - Si osserva che le posizioni "giuste" (00, 11) non ha senso toccarle.
    Le posizioni 10 possono essere scambiate con le 01.
    Se dovessero avanzare posizioni 10 possono essere scambiate con ?0.
    Se dovessero avanzare posizioni 01 possono essere scambiate con ?1.
    Se dovessero ancora avanzare posizioni 10 la soluzione non esiste.
    Se dovessero ancora avanzare 01, ?0, ?1 possono essere trasformate in 11, 00, 11.
 - Si contano quante mosse ricadono nei casi sopra

*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    int C;
    cin >> C;
    for(int c=1; c<=C; ++c) {
        string S, T;
        cin >> S >> T;
        
        cout << "Case " << c << ": ";
        int n = S.size();
        int zu=0, uz=0, qz=0, qu=0;
        for(int i=0; i<n; ++i) {
            if(S[i]=='0' and T[i]=='1') ++zu;
            if(S[i]=='1' and T[i]=='0') ++uz;
            if(S[i]=='?' and T[i]=='0') ++qz;
            if(S[i]=='?' and T[i]=='1') ++qu;
        }
        
        int ans = min(zu, uz);
        zu -= ans;
        uz -= ans;
        if(uz > qu) {
            cout << "-1\n";
        }else if(uz > 0) {
            ans += uz+qu+qz;
            cout << ans << "\n";
        }else {
            ans += zu+qz+qu;
            cout << ans << "\n";
        }
    }
    
    return 0;
}