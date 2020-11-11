#include <iostream>

using namespace std;

int fibonacci(int n) {
    if(n <= 1)
        return n;
    // Complete the function.
    int fib1 = 1, fib2 = 0;
    for(int fib=2; fib<=n; ++fib) {
        int temp = fib1+fib2;
        fib2 = fib1;
        fib1 = temp;
    }
    
    return fib1;
}

int main() {
    int n;
    cin >> n;
    cout << fibonacci(n);
    return 0;
}
