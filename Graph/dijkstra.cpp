#include <bits/stdc++.h>

using namespace std;

/*
 * [Description] : Standard implementation of Dijkstra's Single Source Shortest Path algorithm
 *                 Can be used as a standard subroutine for any graph
 *                 Need to provide implementation for (+) operator in special cases
 *                 [Note] : Single soure shortest path for novel situations may have to be implemented completely from scratch
 *                          This can always be taken as a guideline
 *
 * Running Time : O((m + n)log(n))
 */

template <class T>
vector<T> dijkstra(const graph<T>& g, int start) {
    assert(0 <= start < g.n);
    vector<T> d(g.n, numeric_limits<T>::max());
    d[start] = T(0); // need to customize this depending on the cost
    set<pair<T, int>> s;
    for(int i = 0; i < g.n; i++) {
      s.insert({d[i], i});  
    }
    while(!s.empty()) {
        auto u = s.begin()->second;
        s.erase(s.begin());
        for(auto& e : g.g[u]) {
            int v = e.to;
            if(d[u] + e.cost < d[v]) {
                s.erase({d[v], v});
                d[v] = d[u] + e.cost; 
                s.insert({d[v], v});
            }
        }
    }
    return d;
}
