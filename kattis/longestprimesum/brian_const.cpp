/*
Testo: https://open.kattis.com/problems/longestprimesum
Tecnica: Osservazioni
Complessità: O(1)

Idea:
 - Non viene richiesto che i primi siano distinti, quindi basta usare solo '2'
   per quanto possibile (N pari) e al piu' un '3' (N dispari)
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    long long N; 
    cin >> N;
    long long ans = -1;
    if(N <= 3)
        ans = 1;
    else if((N%2LL) == 0LL)
        ans = N/2LL;
    else
        ans = (N-3LL)/2LL + 1LL;
    cout << ans << endl;
}
