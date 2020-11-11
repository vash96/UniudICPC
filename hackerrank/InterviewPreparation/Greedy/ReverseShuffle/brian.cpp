#include <bits/stdc++.h>
using namespace std;

string S;
int freq[26];
queue<int> pos[26];

bool ok(int i, int& last)
{
    while(pos[i].front() < last)
        pos[i].pop();
    
    int nextfreq[26];
    for(int j=0; j<26; ++j)
        nextfreq[j] = -freq[j];
    for(size_t j=pos[i].front(); j<S.length(); ++j)
        ++nextfreq[S[j]-'a'];
    
    for(int j=0; j<26; ++j) {
        if(nextfreq[j] < 0)
            return false;
    }
    
    last = pos[i].front();
    pos[i].pop();
    return true;
}

string solve(size_t len)
{
    for(auto& x: freq)
        x /= 2;
    
    string ans(len, ' ');
    int last = -1;
    for(auto& c: ans) {
        for(int i=0; i<26; ++i) {
            if(freq[i]>0 and ok(i, last)) {
                c = 'a'+i;
                --freq[i];
                break;
            }
        }
    }
    
    return ans;
}

int main()
{
    cin >> S;
    auto len = S.length()/2;
    for(size_t i=0; i<len; ++i)
        swap(S[i], S[2*len-1-i]);
    for(size_t i=0; i<2*len; ++i) {
        int c = S[i]-'a';
        ++freq[c];
        pos[c].push(i);
    }
    
    cout << solve(len) << "\n";
    
    return 0;
}
