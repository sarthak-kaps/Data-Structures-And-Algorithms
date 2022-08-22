#include <bits/stdc++.h>

using namespace std;

/*
 * [Description] : Function to compute KMP Table for a string 
 *                 Used in Knuth-Morris-Pratt String matching algorithm.
 *
 *                 Call this function on - pattern + # + text  (where # is an extra symbol not present in pattern & text)
 *                 For all i in the text if F[i] = len(pattern) then pattern matches text at index i in the text
 *                 
 *                 This can be used on individual strings as well.
 *
 * Running Time : O(n) where n is the length of the input string.
 */


vector<int> kmp_table(string& s) {
    int n = (int) s.length();
    vector<int> F(n); // F[i] = length of longest proper suffix ending at i which is also a prefix of the string
                      // thus F[0] = 0, and for all i > 0 F[i] <= F[i - 1] + 1
    
    for (int i = 1; i < n; i++) {
        int j = F[i - 1]; 
        while (j > 0 and s[j] != s[i]) {
            j = F[j - 1];  // F[j - 1] is the next best alternative after j
        }
        if (s[i] == s[j]) {
            F[i] = j + 1;
        }
    }

    return F;
}
