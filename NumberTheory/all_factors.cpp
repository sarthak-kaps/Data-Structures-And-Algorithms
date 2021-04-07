#include <bits/stdc++.h>

using namespace std;

/* [Description] : Simple function to find all factors of a number n
 * Running Time : O(sqrt(n))
 */

template <class T>
vector<T> all_factors(T n) {
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
