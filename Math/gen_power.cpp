#include <bits/stdc++.h>

using namespace std;

/*
 * [Description] : Generic power function
 *                 Computes a ^ b, where -
 *                 a is any mathematical object for which * is defined
 *                 e.g. integers, real numbers, matrices
 *
 *                 For modular exponentiation for integers, refer to NumberTheory/primes.cpp
 *
 * Running Time : O(time(T, *) * log(b))
 *                where time(T, *) is time required to apply * on 2 instances of T.
 */

/* Example on matrices */
template <class T>
vector<vector<T>> operator *(vector<vector<T>>& a, vector<vector<T>>& b) {
    vector<vector<T>> c(a.size(), vector<T>(b[0].size()));
    assert(a[0].size() == b.size());
    for(int i = 0; i < a.size(); i++) {
        for(int j = 0; j < b[0].size(); j++) {
            for(int k = 0; k < b.size(); k++) {
                c[i][j] = c[i][j] + a[i][k] * b[k][j];
            }
        }
    }
    return c;
}

// the T(1) scam actually statically compiles for most practical instances !
template <class T>
T power(T a, int b, T base = T(1)) {
    T res = move(base);
    while(b) {
        if(b & 1) {
            res = res * a;
        }
        a = a * a;
        b >>= 1;
    }
    return res;
}


int main() {
    int n;
    cin >> n;
    vector<vector<int>> A(n, vector<int>(n));
    vector<vector<int>> I(n, vector<int>(n)); // identity matrix, for base
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            A[i][j] = n * i + j;
            cout << A[i][j] << ' ';
        }
        I[i][i] = 1;
        cout << endl;
    }
    int b;
    cin >> b;
    for(auto& r : power(A, b, I)) {
        for(auto& e : r) {
            cout << e << ' ';
        }
        cout << endl;
    } 
}


