#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the riddle function below.
vector<long> riddle(vector<long> arr) {
    int n = arr.size();
    vector<long> ans(n, -1);
    stack<pair<long, long>> st;
    
    arr.push_back(0);
    for(int i=0; i<=n; ++i) {
        long ii = i;
        while(not st.empty() and st.top().first > arr[i]) {
            auto [h, j] = st.top();
            st.pop();
            ans[i-j-1] = max(ans[i-j-1], h);
            ii = j;
        }
        st.emplace(arr[i], ii);
    }
    
    ans[n-1] = *min_element(arr.begin(), arr.end()-1);
    for(int i=n-2; i>=0; --i) {
        ans[i] = max(ans[i], ans[i+1]);
    }
    
    return ans;
}