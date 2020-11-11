#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the largestRectangle function below.
long largestRectangle(vector<int> h) {
    long ans = 0;
    stack<pair<int, long>> st;
    
    h.emplace_back(0);
    for(int i=0; i<h.size(); ++i) {
        int ii = i;
        while(not st.empty() and st.top().second > h[i]) {
            auto [j, hh] = st.top();
            st.pop();
            ii = j;
            ans = max(ans, (i-j)*hh);
        }
        st.emplace(ii, h[i]);
    }
    
    return ans;
}