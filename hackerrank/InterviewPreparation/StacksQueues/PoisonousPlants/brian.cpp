#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the poisonousPlants function below.
int poisonousPlants(vector<int> p) {
    int n = p.size();
    stack<pair<int, int>> st;
    int ans = 0;
    
    for(auto poison : p) {
        int days = 0;
        while(not st.empty() and st.top().first >= poison) {
            days = max(days, st.top().second);
            st.pop();
        }
        st.emplace(poison, st.empty() ? 0 : 1+days);
        ans = max(ans, st.top().second);
    }
    
    return ans;
}