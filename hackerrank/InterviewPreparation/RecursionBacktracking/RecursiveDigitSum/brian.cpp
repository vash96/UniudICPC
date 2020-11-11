#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

long digitSum(long n)
{
    if(n % 10LL == n) {
        return n;
    }
    long digsum = 0;
    while(n > 0) {
        digsum += n % 10LL;
        n /= 10LL;
    }
    
    return digitSum(digsum);
}

// Complete the superDigit function below.
int superDigit(string n, int k) {
    return digitSum(long(k) * digitSum(accumulate(n.begin(), n.end(), long(0), [](const long acc, const char c) {
        return acc + (c-'0');
    })));
}