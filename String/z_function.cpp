#include <bits/stdc++.h>

using namespace std;

/* [Description] : Computation of Z Function for string matching
 *                 For a string s[0 .... n - 1], define z for i > 0 :
 *                 z[i] = length of longest substring starting from i that matches a prefix of s
 *                 z[0] can be defined to be 0.
 *                 
 *                 The function returns the Z table for the input string
 *
 *                 To do pattern matching pass the string as pattern + # + text, then for each
 *                 position i in the text if z[i] = len(pattern) then we have a match.
 * [Running Time] : O(n)
 */

vector<int> z_function(string& s) {
    int n = (int) s.length();
    vector<int> z(n);
    int L = 0, R = 0; // [L, R] is the segment with the maximum possible R such that s[0.....L - R] = s[L....R]
                      // i.e it is the rightmost match we have found so far

    for (int i = 1; i < n; i++) {
        if (i <= R) {
            z[i] = min(R - i + 1, z[i - L]);  // we know that s[i...R] matches with s[i-L...R-L]
                                              // therefore z[i - L] is a good estimate
        }
        while (i + z[i] < n and s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] - 1 > R) {
            L = i;
            R = i + z[i] - 1;
        }
    }
    return z;
}
