#include <bits/stdc++.h>

using namespace std;

/* [Description] : Simple function to find all factors of a number n
 * Running Time : O(sqrt(n))
*/

template <class T>
vector<T> all_factors_simple(T n) {
    vector<T> f;
    for(T i = (T)1; i * i <= n; i++) {
        if(n % i == 0) {
            f.push_back(i);
            if(i != n / i) {
                f.push_back(n / i);
            }
        }
    }
    return f;
}

/* [Description] : Function to find all prime factors of a number
 *                 Returns prime factors along with their powers
 * Running Time : O(sqrt(n))
*/

template <class T>
vector<pair<T, T>> prime_factors(T _n) {
    auto n = _n;
    vector<pair<T, T>> p_f;
    for(T i = (T)2; i * i <= n; i++) {
        int cnt = 0;
        while(n % i == 0) {
            n /= i;
            cnt++;
        }
        if(cnt) {
            p_f.push_back({i, cnt});
        }
    }
    if(n > 1) {
        p_f.push_back({n, 1});
    }
    return p_f;
}

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

