#include <bits/stdc++.h>

using namespace std;


/* [Description] : Generic Forest and Tree class
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
class forest : public graph<T> {
public :
    using graph<T>::g;
    using graph<T>::n;
    int m;

    forest(int _n) : graph<T>(_n) {
        m = 0;
    }

    void add(int from, int to, T cost) {
        assert(0 <= from and from < n and 0 <= to and to < n);
        g[from].push_back({from, to, cost});
        g[to].push_back({to, from, cost});
        m++;
        assert(m < n - 1);
    }
};
