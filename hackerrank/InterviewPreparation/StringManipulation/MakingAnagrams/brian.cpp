#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

int number_needed(string a, string b) {
    vector<int> freq_a(26, 0), freq_b(26, 0);
    for(auto& c: a)
        ++freq_a[c - 'a'];
    for(auto& c: b)
        ++freq_b[c - 'a'];
    
    int ans = 0;
    for(size_t i=0; i<freq_a.size(); ++i)
        ans += abs(freq_a[i] - freq_b[i]);
    
    return ans;
}

int main(){
    string a;
    cin >> a;
    string b;
    cin >> b;
    cout << number_needed(a, b) << endl;
    return 0;
}
