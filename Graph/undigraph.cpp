
#include <bits/stdc++.h>

using namespace std;

/* [Description] : Generic Undirected Graph class
 *                 Not for regular use, prefer vector<vector<..>> in general
 *                 This interface is implemented to unify implementation of various different graph algorithms 
 */

template <class T>
class graph {
public :
    struct edge {
        int from;
        int to;
        T cost;
    };

    vector<vector<edge>> g;
    int n;

    graph(int _n) : n(_n) {
        g.resize(n);   
    }
    virtual void add(int from, int to, T cost);
};

template <class T>
class undigraph : public graph<T> {
public :
    using graph<T>::g;
    using graph<T>::n;

    undigraph(int _n) : graph<T>(_n) {}
    
    void add(int from, int to, T cost) {
        g[from].push_back({from, to , cost});
        g[to].push_back({to, from, cost});
    }
};
