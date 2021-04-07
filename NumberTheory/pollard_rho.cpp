#include <bits/stdc++.h>

using namespace std;

/*
 * [Description] : Implementation of standard pollard-rho algorithm to find a factor of a given number
 *                 The factor is not neccessarily prime
 *                 Call function rho(n) to find a factor
 * Running Time : Expected O(n^(1/4))
 */

namespace pollard_rho {
    template <class T>
    inline T mult(T a, T b, T mod) {
        return (a % mod) * (b % mod) % mod;
    }

    template <class T>
    T f(T x, T c, T mod) {
        return (mult(x, x, mod) + c) % mod;
    }

    template <class T>
    T rho(T n, T x_0 = 2, T c = 1) {
        T x = x_0;
        T y = x_0;
        T g = (T) 1;
        while(g == 1) {
            x = f(x, c, n);
            y = f(f(y, c, n), c, n);
            g = __gcd(abs(x - y), n);
        }
        return g;
    }
}
