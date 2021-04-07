#include <bits/stdc++.h>

using namespace std;


/*
 * [Description] : Returns all primes numbers <= n
 * Time Complexity = O(n*log(log(n)))
 */

vector<int> sieve(int n) {
    vector<int> primes;
    vector<bool> sieve(n + 1, true);
    for(int i = 2; i <= n; i++) {
        if(sieve[i]) {
            primes.push_back(i);
            for(int j = i + i; j <= n; j += i) {
                sieve[j] = false;
            }
        }
    }
    return primes;
}
