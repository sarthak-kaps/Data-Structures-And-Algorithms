#include <bits/stdc++.h>

using namespace std;


/*
 * [Description] -
        gcd(a, b) : return greatest common divisor of a and b
        Running Time : log_{phi}(max(a, b))
        
        lcm(a, b) : returns the least common multiple of a and b
        Running Time : log_{phi}(max(a, b))
*/

template <class T>
inline T gcd(T a, T b) {
    while(b > 0) {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}

template <class T>
inline int64_t lcm(T a, T b) {
    return ((int64_t) a * b) / gcd(a, b);
}
