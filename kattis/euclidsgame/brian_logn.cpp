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