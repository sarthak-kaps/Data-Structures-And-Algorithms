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
 * [Description] : The following algorithm finds roots of the equation
 *                 ax = b (mod n), here equality denotes congruency relation
 *                 The algorithm has been referred from CLRS - Chapter 31, Section 4
 *
 * Running Time : O(log(n))
 */

template <class T>
vector<T> modular_equation_solver(T a, T b, T n) {
    array<T, 3> s = extended_gcd(a, n);
    T d = s[0];
    T x = s[1];
    // we have a solution iff d divides b 
    if(b % d == 0) {
        // if b divides d, then we have d solutions, the first of which is x_0
        vector<T> solutions;
        T x_0 = x * (b / d) % n; // x_0 = x(b/d) mod n
        if(x_0 < 0) {
            x_0 += n;
        }
        for(int i = 0; i < d; i++) {
            solutions.push_back((x_0 + i * n / d) % n); // x_0 + i * (n / d) is a solution
        }
        return solutions;
    }
    return {};
}
