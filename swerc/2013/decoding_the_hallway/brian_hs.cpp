/*
Testo: https://open.kattis.com/problems/decodingthehallway
Tecnica: Ad-hoc
Complessità: prepocessing della hallway H fino al livello 10
             pattern matching in O(H * S)

Idea:
  - Sviluppando la hallway si nota che H_(n+1) = H_n ++ L ++ H_n*
    dove * indica la stringa complementata e rovesciata
  - La lunghezza di H_n è 2^n -1
  - Osservazione chiave è che se cerco una stringa lunga k, allora
    mi serve almeno H_logk e al più H_(3+logk)
    Ogni hallway successiva  conterrà le stesse stringhe lunghe k di H_(3+logk)
  - Precomputo H_10 (dato che |S|<|H_7|)
  - Cerco in modo naive S in H_k per k che soddisfa il limite su n

*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    string p = "L";
    string q = "";
    auto revcomp = [&](const string & p) {
        string ans;
        for(auto i=p.rbegin(); i!=p.rend(); ++i) {
            ans += *i == 'L' ? 'R' : 'L';
        }
        return ans;
    };
    for(int i=1; i<=10; ++i) {
        q = p;
        p = p + "L" + revcomp(p);
    }

    int t;
    cin >> t;
    for(int tt=1; tt<=t; ++tt) {
        cout << "Case " << tt << ": ";

        int n;
        string S;
        cin >> n >> S;
        
        int s = S.length();
        int m = min(10, n), lenm = (1 << m)-1;        

        bool flag = false;
        for(int i=0; i<=lenm-s and not flag; ++i) {
            flag = true;
            for(int j=0; j<s and flag; ++j) {
                if(q[i+j] != S[j]) {
                    flag = false;
                }
            }
        }
        cout << (flag ? "Yes\n" : "No\n");
    }

    return 0;
}