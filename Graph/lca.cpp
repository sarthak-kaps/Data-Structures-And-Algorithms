#include <bits/stdc++.h>

using namespace std;


/* [Description] : Implementation of Least Common Ancestor of a pair of vertices in a tree
 *                 Works only for undirected trees/forests
 *                 Initialize object of the class lca_forest with a given forest
 *                 Call lca(u, v) to find lca of vertices u and v (function works if they are in the same component)
 *                 Need to do an outside check for this (future work is to do it here).
 *
 * [Running Time] : O(log(n)) for finding lca(u, v)
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
        assert(m <= n - 1);
    }
};

template <class T>
class lca_forest : public forest<T> {
public :
    
    using forest<T>::g;
    using forest<T>::n;

    int log_n;
    vector<vector<int>> up; // up[u][i] tells the 2 ^ i th ancestor of vertex u
    vector<int> in, out;    // in[u] tells the in time of vertex u during dfs
                            // out[u] tells the out time of vertex u during dfs

    lca_forest(forest<T>& input_forest) : forest<T>(g.n) {
        g = copy(input_forest.g);
        lca_set();
    }

    void lca_set() {
        log_n = 2; // start from 2 for safety
        while(true) {
            if(n <= (1 << log_n)) {
                break;
            }
            log_n++;
        }

        up.resize(n, vector<int>(log_n + 1)); // up is of dimension (n, log(n) + 1)
        in.resize(n); out.resize(n);
        vector<int> par(n); 
        for(int i = 0; i < n; i++) {
            par[i] = i; // set parent of every vertex itself, think about the disconnected tree case
        }
        vector<bool> visited(n);
        int TIME = 0; 

        function<void(int)> dfs = [&] (int u) {
            visited[u] = true;
            up[u][0] = par[u];
            for(int i = 1; i <= log_n; i++) {
                up[u][i] = up[up[u][i - 1]][i - 1]; // 2 ^ i th ancestor of u is the 2 ^ (i - 1) th ancestor of the 
                                                    // 2 ^ (i - 1) th ancestor of u
            }
            in[u] = TIME; TIME++;

            for(auto& e : g[u]) {
                int v = e.to;
                if(par[u] != v) {
                    par[v] = u;
                    dfs(v);
                }
            }    
            out[u] = TIME; TIME++;
        };
        for(int i = 0; i < n; i++) {
            if(!visited[i]) {
                dfs(i);
            }
        }
    }

    bool is_ancestor(int u, int v) { // is u the ancestor of v
        if(in[u] <= in[v] and out[u] >= out[v]) {  // standard dfs concept
            return true;
        }
        return false;
    }

    int lca(int u, int v) {  // does not check if u and v are in different components
        if(is_ancestor(u, v)) {
            return u;
        }
        if(is_ancestor(v, u)) {
            return v;
        }
        for(int i = log_n; i >= 0; i--) {
            if(!is_ancestor(up[u][i], v)) {
                u = up[u][i];
            }
        }
        return up[u][0];
    }
};
