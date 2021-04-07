#include <bits/stdc++.h>

using namespace std;

template <class T>
T extended_gcd(T a, T b, T& x, T& y) {
    if(b == 0) {
        x = 1, y = 0;
        return a;
    }
    auto g = extended_gcd(b, a % b, x, y);
    auto new_x = y;
    auto new_y = (x - (a / b) * y);
    x = new_x;
    y = new_y;
    return g;
}

template <class T>
array<T, 3> extended_gcd(T a, T b) {
    T x, y;
    auto g = extended_gcd(a, b, x, y); // use g or return it as well if required
    return {g, x, y};
}

/*
 * [Description] : Chinese Remainder Theorem Special Case
 *                 Input (a, b, m, n), finds x such that -
 *                 x  \equiv a (mod m)
 *                 x  \equiv b (mod n)
 *                 Still not properly understood
 *
 * Running Time : O(log n)
 */

int64_t crt(int64_t a, int64_t b, int64_t n, int64_t m) {
    if(n > m) {
        swap(n, m);
        swap(a, b);
    }
    auto s = extended_gcd(m, n);
    auto g = s[0];
    auto x = s[1];
    assert((a - b) % g == 0); // else we have no solution
    auto res = (b - a) % n * x % n / g * m + a;
    if(res < 0) {
        res += m * n / g;
    }
    return res;
}
