#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the luckBalance function below.
int luckBalance(int k, vector<vector<int>> contests) {
    sort(contests.begin(), contests.end(), [](const vector<int> & lhs, const vector<int> & rhs) {
        return lhs[1] != rhs[1] ? lhs[1] > rhs[1] : lhs[0] > rhs[0];
    });
    
    int ans = 0;
    for(int i=0; i<contests.size(); ++i) {
        if(k >= contests[i][1]) {
            ans += contests[i][0];
            k -= contests[i][1];
        }else {
            ans -= contests[i][0];
        }
    }
    return ans;
}