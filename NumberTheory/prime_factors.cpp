#include <bits/stdc++.h>

using namespace std;

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
