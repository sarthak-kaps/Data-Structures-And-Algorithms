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
