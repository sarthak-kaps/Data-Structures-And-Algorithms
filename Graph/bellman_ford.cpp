#include <bits/stdc++.h>

using namespace std;

/*
 * [Description] : Standard implementation of Bellman Ford Single Source Shortest Path algorithm
 *                 Can be used as a standard subroutine for any graph
 *                 Need to provide implementation for (+) operator in special cases
 *                 [Note] : Single soure shortest path for novel situations may have to be implemented completely from scratch
 *                          This can always be taken as a guideline
 *
 * Running Time : O(mn)
 */

template<class T> 
vector<T> bellman_ford(const graph<T>& g, int start) {
    vector<T> d(g.n, numeric_limits<T>::max()); // distance vector from the vertex start
    d[start] = 0;
    for (int i = 0; i < g.n; i++) {  // at the ith iteration we are finding shortest paths from start using i edges, i = 0... n - 1
        for (int u = 0; u < g.n; u++) {
            if (d[u] == numeric_limits<T>::max()) {
                continue;
            }
            for (auto& e : g.g[u]) {
                int v = e.to;
                if (d[v] > d[u] + e.cost) { // condition to relax edge e
                    d[v] = d[u] + e.cost;
                }
            }
        }
    }
    // we will now check for negative weight cycle
    for (int u = 0; u < g.n; u++) {
        if (d[u] == numeric_limits<T>::max()) {
            continue;
        }
        for (auto& e : g.g[u])  {
            int v = e.to;
            if (d[v] > d[u] + e.cost) {  // if the edge e still relaxes then there is a negative weight cycle
                cout << "[Bellman-Ford] : Found a negative weight cycle\n";
            }
        }
    }
    return d;
}
