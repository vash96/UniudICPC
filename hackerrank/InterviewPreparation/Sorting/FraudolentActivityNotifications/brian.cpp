#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the activityNotifications function below.
int activityNotifications(vector<int> expenditure, int d) {
    int n = expenditure.size();
    
    vector<int> freq(201, 0);
    for(int i=0; i<d; ++i) {
        ++freq[expenditure[i]];
    }
    
    int s = 0;
    int med = 0;
    while(2*(s + freq[med]) < d) {
        s += freq[med];
        ++med;
    }
    
    auto Help = [&](int val) -> int {
        if((d & 1) or 2*(s+freq[val])>d) return val;
        return find_if(freq.begin()+val+1, freq.end(), [](int x) { return x > 0; })-freq.begin();
    };
    int ans = 0;
    cerr << "Med = " << med << "\n";
    for(int i=d; i<n; ++i) {
        
        ans += expenditure[i] >= med + Help(med);
        --freq[expenditure[i-d]];
        ++freq[expenditure[i]];
        
        s -= expenditure[i-d] < med;
        s += expenditure[i] < med;
        
        while(2*(s + freq[med]) < d) {
            s += freq[med++];
        }
        while(2*s >= d) {
            s -= freq[--med];
        }
        cerr << "Med = " << med << "\n";
    }
    
    return ans;
}