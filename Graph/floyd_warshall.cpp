#include <bits/stdc++.h>

using namespace std;

/*
 * [Description] : Standard implementation of Floyd Warshall All Pair Shortest Path algorithm
 *                 Can be used as a standard subroutine for any graph
 *                 Need to provide implementation for (+) operator in special cases
 *                 [Note] : All Pair shortest path for novel situations may have to be implemented completely from scratch
 *                          This can always be taken as a guideline
 *
 * Running Time : O(n^3)
 */

template <class T>
vector<vector<T>> all_pair_shortest_paths(const graph<T>& g) {
    vector<vector<T>> d(g.n, vector<T>(g.n, T(1e18))); // we can modify the max dist as per use and cost function
    for(int i = 0; i < g.n; i++) {
        d[i][i] = T(0);
    }
    for(auto& e : g.g) {
        d[e.from][e.to] = e.cost;
    }
    for(int k = 0; k < g.n; k++) {
        for(int i = 0; i < g.n; i++) {
            for(int j = 0; j < g.n; j++) {
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
            if(d[i][i] < 0) {
                cout << "Negative cost cycle detected" << '\n';
            }
        }
    }
    return d;
}
