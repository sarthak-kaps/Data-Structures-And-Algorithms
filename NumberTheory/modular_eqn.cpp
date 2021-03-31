#include <bits/stdc++.h>

using namespace std;

/****************************************  
    always call this with a >= b
    we want to find at each stage x, y such that - 
    ax + by = gcd(a, b)
    
    At the base case, gcd(a, b) = a, as b = 0
    Thus a * x + b * y = a can be satisfied by setting
    x = 1, y = arbitrary

    Suppose we know the result for gcd(b, a % b)
    Let it be x_1, y_1, then

    b * x_1 + (a % b) * y_1 = gcd(a, b) ---- (1)
    Now (a % b) = a - |_a / b_| * b,   |_a / b_| = floor(a / b)
    
    Therefore (1) becomes, 
    b * x_1 + (a - |_a / b_| * b) * y_1 = gcd(a, b)
    a * y_1 + b * (x_1 - |_a / b_| * y_1) = gcd(a, b)

    On comparing this with a * x + b * y = gcd(a, b)
    we get
    x = y_1
    y = (x_1 - |_a / b_| * y_1)

    NOTE - There can be multiple solutions to this
                        
***************************************/
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
