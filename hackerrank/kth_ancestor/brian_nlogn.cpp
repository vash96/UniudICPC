#include <bits/stdc++.h>
using namespace std;
const int MAX = 1e5+1;

void solve()
{
    int P, Q;
    int kparent[MAX][17]; memset(kparent, 0, sizeof(kparent));
    vector<bool> isin(MAX, false);
    cin >> P;
    
    for(int i=0, x, y; i<P; ++i) {
        cin >> x >> y;
        isin[x] = true;
        kparent[x][0] = y;
    }

    for(int j=1; j<17; ++j) {
        for(int i=0; i<MAX; ++i) {
            kparent[i][j] = kparent[kparent[i][j-1]][j-1];
        }
    }

    cin >> Q;
    for(int q=0, x, y, k, t; q<Q; ++q) {
        cin >> t;
        if(t == 0) {
            cin >> y >> x;
            kparent[x][0] = y;
            for(int j=1; j<17; ++j) {
                kparent[x][j] = kparent[kparent[x][j-1]][j-1];
            }
            isin[x] = true;
        }else if(t == 1) {
            cin >> x;
            isin[x] = false;
        }else{
            cin >> x >> k;
            if(not isin[x]) {
                cout << "0\n";
                continue;
            }
            int ans = x;
            while(ans != 0 and k > 0) {
                int j=0;
                while((1<<(j+1)) <= k) {
                    ++j;
                }
                ans = kparent[ans][j];
                k -= (1<<j);
            }
            cout << ans << "\n";
        }
    }
}


int main() {
    ios_base::sync_with_stdio(false);

    int T;
    cin >> T;
    for(int t=0; t<T; ++t) {
        solve();
    }

    return 0;
}
