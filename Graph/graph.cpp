#include <bits/stdc++.h>

using namespace std;

/* [Description] : Generic Graph class
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
