#include <bits/stdc++.h>

using namespace std;

/*
 * [Description] : Solves the matrix equation Ax = b
 *                 Simple RREF implementation, but a lot of floating point checks for stability need to be performed
 *                 NOTE : For efficiency A, b and x are passed by reference, but their values will be mutated, save a copy locally if you need A or b later
 *
 *                 Reference - https://github.com/kth-competitive-programming/kactl/blob/master/content/numerical/SolveLinear.h
 *
 * Running Time : O(n^2 * m), n = rows in A = size of b, m = columns in A = size of x
 */

const double eps = 1e-12;

// returns the rank of the matrix A

int solve_linear(vector<vector<double>>& A, vector<double>& b, vector<double>& x) {
    int n = (int) A.size();
    int m = (int) x.size();
    assert((int) A[0].size() == m);
    assert((int) b.size() == n);

    int rank = 0, max_r = 0, max_c = 0;
    vector<int> col(m); // maintains column permutation
    iota(col.begin(), col.end(), 0); // sets col with 0, 1, .... m - 1

    for(int i = 0; i < n; i++) {
        double max_val = 0; // maximum magnitude element in the remaining matrix, i.e A[i...n - 1][i...m - 1]
        for(int r = i; r < n; r++) {
            for(int c = i; c < m; c++) {
                double abs_val = fabs(A[r][c]);
                if(abs_val > max_val) {
                    max_r = r, max_c = c;
                    max_val = abs_val;
                }
            }
        }
        // check the matrix
        if(max_val <= eps) {
            for(int j = i; j < n; j++) {
                if(fabs(b[j]) > eps) {
                    return -1;  // in particular this handles the case when A is singular
                } 
            }
            break;
        }
        // bring the maximum element to the current position to begin elimination of other elements
        swap(A[i], A[max_r]);
        swap(b[i], b[max_r]);
        swap(col[i], col[max_c]);

        for(int j = 0; j < n; j++) {
            swap(A[j][i], A[j][max_c]);
        }
        // now max element is at required position
        
        max_val = 1 / A[i][i];
        // begin elimination
        for(int j = i + 1; j < n; j++) {
            double factor = A[j][i] * max_val;
            b[j] -= factor * b[i];
            // apply on jth row
            for(int k = i + 1; k < m; k++) {
                A[j][k] -= factor * A[i][k];
            }
        }
        rank++;
    }

    x.assign(m, 0);
    for(int i = rank; i >= 0; i--) {
        b[i] /= A[i][i];
        x[col[i]] = b[i]; // here we use the permutation to put answer at right entry for the original problem
        for(int j = 0; j < i; j++) {
            b[j] -= A[j][i] * b[i];
        }
    }
    return rank;
}
