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