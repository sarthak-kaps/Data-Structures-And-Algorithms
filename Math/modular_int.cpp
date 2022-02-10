#include <bits/stdc++.h>

using namespace std;

const int mod = (int) 1e9 + 7;

class Mint {
public :
    int64_t x;
    Mint(int64_t x) : x((x + mod) % mod) {}
};

Mint operator *(Mint a, Mint b) {
    return a.x * b.x % mod;
}

Mint operator +(Mint a, Mint b) {
    return (a.x + b.x) % mod;
}

void operator ++(Mint& a) {
    a = a + 1;
}

void operator ++(Mint& a, int inc) {
    ++a;
}

bool operator ==(Mint a, Mint b) {
    return a.x == b.x;
} 

