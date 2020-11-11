#include <bits/stdc++.h>

using namespace std;

// Complete the isBalanced function below.
string isBalanced(string s) {
    stack<char> st;
    auto Closed = [](const char c) {
        return c == ')' or c == ']' or c == '}';
    };
    auto Corr = [](const char c) {
        return c == ')' ? '(' :
                c == ']' ? '[' : '{';
    };
    for(auto c : s) {
        if(Closed(c)) {
            if(st.empty() or st.top() != Corr(c)) {
                return "NO";
            }else {
                st.pop();
            }
        }else {
            st.push(c);
        }
    }
    
    return st.empty() ? "YES" : "NO";
}