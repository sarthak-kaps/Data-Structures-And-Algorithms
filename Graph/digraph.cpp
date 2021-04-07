#include <bits/stdc++.h>

using namespace std;

/* [Description] : Generic Directed Graph class
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
    virtual void add(int u, int v, T cost);
};

template <class T>
class digraph : public graph<T> {
public :
    using graph<T>::g;
    using graph<T>::n;

    digraph(int _n) : graph<T>(_n) {}

    void add(int from, int to, T cost) {
        assert(0 <= from and from < n and 0 <= to and to < n);
        g[from].push_back({from, to, cost});
    }
    
    digraph<T> reverse() {
        digraph<T> rev_graph(n);
        for(auto& e : g) {
            rev_graph.add(e.to, e.from, e.cost);
        }
        return rev_graph;
    }
};
