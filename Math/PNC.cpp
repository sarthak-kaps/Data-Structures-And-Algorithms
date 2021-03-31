#include <bits/stdc++.h>

using namespace std;

class PNC {
private :
    int n;
    const int mod = 1000000007; // 988353244
    vector<int64_t> fact;
public :
    PNC(int _n = (int) 1e6) : n(_n + 1) {
        fact.reserve(n);
        fact[0] = 1;
        for(int i = 1; i < n; i++) {
            fact[i] = (fact[i - 1] * i) % mod; 
        }
    }
    int64_t factorial(int k) {
        return fact[k];
    }
    int64_t power(int64_t a, int b) {
        int64_t res = 1;
        while(b) {
            if(b & 1) {
                res = (res * a) % mod;
            }
            a = (a * a) % mod;
            b >>= 1;
        }
        return res;
    }
    int64_t mod_inverse(int64_t a) {
        return power(a, mod - 2) % mod;
    }
    int64_t nPr(int n, int r) {
        return fact[n] * mod_inverse(fact[n - r]) % mod;
    }
    int64_t nCr(int n, int r) {
        return fact[n] * mod_inverse(fact[r]) % mod * mod_inverse(fact[n - r]) % mod;
    }
};
