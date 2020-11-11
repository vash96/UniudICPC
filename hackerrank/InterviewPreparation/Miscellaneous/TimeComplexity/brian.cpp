#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    int P;
    cin >> P;
    
    for(int p=0; p<P; ++p) {
        int N;
        cin >> N;
        
        bool flag = true;
        for(int i=2; i*i<=N and flag; ++i) {
            flag = N % i != 0;
        }
        
        if(flag and N!=1)
            cout << "Prime\n";
        else
            cout << "Not prime\n";
    }
    return 0;
}
