#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'countingValleys' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER steps
 *  2. STRING path
 */

int countingValleys(int steps, string path) {
    int ans = 0;
    int level = 0;
    for(auto c : path) {
        if(level == 0 and c == 'D') {
            ++ans;
        }
        level += c == 'D' ? -1 : +1;
    }
    
    return ans;
}