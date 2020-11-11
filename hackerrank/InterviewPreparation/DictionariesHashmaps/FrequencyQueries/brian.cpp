#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

// Complete the freqQuery function below.
vector<int> freqQuery(vector<vector<int>> queries) {
    unordered_map<int, int> freq, freq_freq;
    vector<int> ans;
    for(auto &q : queries) {
        switch (q[0]) {
            case 1: // Insert
                --freq_freq[freq[q[1]]];
                ++freq[q[1]];
                ++freq_freq[freq[q[1]]];
                break;
            case 2: // Delete
                if(freq[q[1]] > 0) {
                    --freq_freq[freq[q[1]]];
                    --freq[q[1]];
                    ++freq_freq[freq[q[1]]];
                }
                break;
            case 3: // Check
                ans.emplace_back(freq_freq[q[1]] > 0);
                break;
        }
    }
    return ans;
}