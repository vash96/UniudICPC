/*
Testo: https://open.kattis.com/problems/spidersonwater
Tecnica: math
Complessità: O(D) per testcase

Idea:
  - Se S in input ha meno di D+1 elementi, allora soddisfa S[i] = alpha*S[i-1] + beta*S[i-2] per
    qualche alpha e beta: vogliamo trovarli.
  - Sistema lineare di due equazioni in due incognite
        S[2] = alpha*S[1] + beta*S[0]
        S[3] = alpha*S[2] + beta*S[1]
  - In input abbiamo almeno 4 valori di S, quindi il sistema ha sempre soluzione.
    Doppiamo fare attenzione nel caso di S[1]=0 ed S[1]^2 = S[0]*S[2] (perché si annullano i denominatori)
    Basta porre a zero i rispettivi parametri.

*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    while(true) {
        ll D, P;
        cin >> D >> P;
        if(cin.eof()) break;

        vector<ll> S;
        char seq[1<<17];
        cin.getline(seq, 1<<17);

        stringstream ss(seq); // Stringstream per leggere da stringa come se fosse cin
        while(not ss.eof()) {
            ll x;
            ss >> x;
            S.push_back(x);
        }
        
        if(S.size() < D+1) { // Se così allora posso determinare il resto della sequenza
            ll beta = (S[1]==0 or S[1]*S[1]==S[0]*S[2]) ? 0 : (S[1]*S[3] - S[2]*S[2]) / (S[1]*S[1] - S[0]*S[2]);
            ll alpha = (S[1]==0) ? 0 : (S[2] - beta*S[0]) / S[1];
            for(int i=S.size(); i<=D and S[i-1]<=P; ++i) {
                S.push_back(alpha*S[i-1] + beta*S[i-2]);
            }
        }

        // Trovo il punto di non ritorno
        int ans = 0;
        while(ans <= D and S[ans] <= P) {
            ++ans;
        }

        if(ans == 0) {
            cout << "The spider is going to fall!\n";
        }else if(ans > D) {
            cout << "The spider may fall!\n";
        }else {
            cout << (D-ans+1) << "\n";
        }
    }

    return 0;
}