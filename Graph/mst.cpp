#include <bits/stdc++.h>

using namespace std;

/*
 * [Description] : Standard Implementation of Prim's Minimum Spanning Tree Algorithm
 *                 Note that we can easily transform this to Maximum Spanning Tree 
 *                 Places where changes need to be done are indicated with a comment
 *
 * Running Time : O((m + n)logn)
 */

template <class T>
forest<T> mst(const graph<T>& g) {
    
    const T max_dist = T(1e18);
    vector<T> d(g.n, max_dist); // we can modify the max_dist as per use and cost function
                                // set max_dist as T(-1e18) for maximum spanning tree 
    vector<int> p(g.n, -1); 
    set<pair<T, int>> s;
    for(int i = 0; i < g.n; i++) {
        s.insert({d[i], i});
    }
    while(!s.empty()) {
        int u = s.begin()->first;
        s.erase(s.begin());
        if(d[u] == max_dist) {
            d[u] = 0; // start of new component
        }
        for(auto& e : g.g[u]) {
            int v = e.to;
            if(d[u] + e.cost < d[v]) {   // change (<) to (>) for maximum spanning tree 
                s.erase({d[v], v});
                d[v] = d[u] + e.cost;
                s.insert({d[v], v});
                p[v] = u;
            } 
        }
    }
    forest<T> f(g.n); // f is the minimum spanning forest
    for(int i = 0; i < g.n; i++) {
        for(auto& e : g.g[i]) {
            if(i == p[e.to]) {
                f.add(i, e.to, e.cost);
            }
        }
    }
    return f;
}
