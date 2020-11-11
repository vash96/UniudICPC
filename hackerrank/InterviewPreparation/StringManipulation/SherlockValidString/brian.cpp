#include <bits/stdc++.h>

using namespace std;

// Complete the isValid function below.
string isValid(string s) {
    
    vector<int> freq(26, 0);
    for(auto c : s) {
        ++freq[c-'a'];
    }
    
    vector<int> freq_freq(s.length()+1, 0);
    for(auto f : freq) {
        if(f > 0) {
            ++freq_freq[f];
        }
    }
    
    int ans = count_if(freq_freq.begin(), freq_freq.end(), [](int v){ return v>0; });
    if(ans > 2) {
        cerr << ">2";
        return "NO";
    }else if(ans == 1) {
        cerr << "==1";
        return "YES";
    }else {
        cerr << "Else " << ans;
        int pos = find_if(freq_freq.begin(), freq_freq.end(), [](int v){ return v>0; })
                    - freq_freq.begin();
        if(freq_freq[pos] == 1 and pos == 1) {
            return "YES";
        }else if(freq_freq[pos+1] == 0) {
            return "NO";
        }else if(freq_freq[pos+1] == 1) {
            return "YES";
        }else {
            return "NO";
        }
    }        
}