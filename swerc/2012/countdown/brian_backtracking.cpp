/*
Testo: https://open.kattis.com/problems/countdown
Tecnica: complete search, backtracking
Complessità: O((n!)^2) con n=6 numeri nel set

Idea:
  - Da notare che il numero di set costruibili è maggiorato da 3^4 * (6!)^2 ≈ 42 milioni
    quindi una soluzione che enumera ogni possibile set è sufficiente
  - Per implementare efficientemente la costruzione usiamo il backtracking; ad ogni passo
    abbiamo un insieme di elementi salvato in s[0..i] e, scelti "a" e "b" tra tutte le possibili coppie,
    calcoliamo res = "a" op "b" (op in {+,-,*,/}) e ricorriamo su s[0..i-1].
  - Per simulare l'eliminazione di a e b in favore di res, sistemiamo a e b in [i-1, i] e sovrascriviamo [i-1] con res.
    Al ritorno della ricorsione invertiamo le suddette mosse.
  - La funzione di backtracking ritorna TRUE se il ramo ricorsivo ha scovato una soluzione migliorativa, così da sapere
    quando salvare la mossa appena effettuata.
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Move {
    char op;
    ll a, b, res;
    
    Move() {}
    Move(char op, ll a, ll b, ll res)
    : op(op), a(a), b(b), res(res) { }
};

ll s[6], t, best;
int nmov;
Move moves[6];
function<ll(ll, ll)> fs[4];

inline void applyOp(char, function<ll (ll, ll)>, int, int, int);
bool backtrack(int);

inline void applyOp(char op, int f, int x, int y, int i)
{
    long long a, b, res;
    a = s[x];
    b = s[y];
    res = fs[f](max(a,b), min(a,b));
    swap(s[y], s[i]);
    swap(s[x], s[i-1]);
    s[i-1] = res;
    if(backtrack(i-1)) {
        moves[i] = {op, max(a, b), min(a, b), res};
    }
    s[i-1] = a;
    s[i] = b;
    swap(s[x], s[i-1]);
    swap(s[y], s[i]);
}

bool backtrack(int i)
{
    long long bestBefore = best;

    if(abs(s[i]-t) < abs(best-t)) { // Se il numero prodotto dall'operazione precedente è migliorativo salvo il best
        best = s[i];
        nmov = i;
    }

    if(i > 0) {
        for(int x=0; x<i; ++x) { // Per ogni coppia di elementi del set applico un operazione e ricorro (attenzione per il /)
            for(int y=x+1; y<=i; ++y) {
                // +
                applyOp('+', 0, x, y, i);
                
                // -
                applyOp('-', 1, x, y, i);
                
                // *
                applyOp('*', 2, x, y, i);
                
                // /
                if(s[x]*s[y] != 0 and max(s[x], s[y]) % min(s[x], s[y]) == 0) {
                    applyOp('/', 3, x, y, i);
                }
            }
        }
    }
    
    return best != bestBefore; // Ritorno true SSE ho migliorato la soluzione
}
    
void solve()
{
    best = 1e13;
    nmov = 5;
    for(int i=0; i<6; ++i) {
        cin >> s[i];
    }
    cin >> t;
    for(int i=0; i<6; ++i) {
        if(abs(s[i]-t) < abs(best-t)) {
            best = s[i];
        }
    }
    
    backtrack(5);
    cout << "Target: " << t << "\n";
    for(int i=5; i>nmov; --i) {
        cout << moves[i].a << " " << moves[i].op << " " << moves[i].b << " = " << moves[i].res << "\n";
    }
    cout << "Best approx: " << best << "\n\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    fs[0] = [](ll a, ll b){ return a+b; };
    fs[1] = [](ll a, ll b){ return a-b; };
    fs[2] = [](ll a, ll b){ return a*b; };
    fs[3] = [](ll a, ll b){ return a/b; };
    
    int C;
    cin >> C;
    
    for(int i=0; i<C; ++i) {
        solve();
    }
    
    return 0;
}