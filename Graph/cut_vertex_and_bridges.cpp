#include <bits/stdc++.h>

using namespace std;

/* [Description] : Implementation to find cut vertices and bridges in an undirected graph,
 *                 using Tarjan's algorithm
 *
 *                 The implementation below is for general use only, special requirements could effectively require a new implementation.
 *                 But this can always be used as a guideline.
 *                 
 * Running Time : O(m + n), linear in the graph                 
 */


/* Returns the bridges of the graph as a vector of edges
 * Need to pass an empty vector of cut vertices, will be filled after the algorithm terminates
 */

template <class T>
vector<typename undigraph<T>::edge> cut_vertices_and_bridges(undigraph<T>& g, vector<int>& cut_vertices) {
    vector<int> par(g.n);  // par[u] is the parent of vertex u
    vector<int> in(g.n);   // in[u] is the time at which vertex u is first traversed during dfs
    vector<int> out(g.n);  // out[u] is the time at which vertex u exits after completing the dfs under its subtree
    vector<int> low(g.n);  // low[u] is the vertex v with minimum in[v] reachable by 0 or 1 back edges from the dfs subtree rooted at u 
                           // this is quite a mouthful but is the main concept behind the entire algorithm
    vector<bool> visited(g.n);
    for(int i = 0; i < g.n; i++) {
        par[i] = i; // think about the disconnected graph case
    }

    int TIME = 0;
    vector<bool> is_cut_vertex(g.n); // stores if the vertex is a cut vertex or not
    vector<typename undigraph<T>::edge> bridges; // stores the bridges found in the graph

    function<void(int)> tarjan_dfs = [&](int u) {
        visited[u] = true;
        in[u] = TIME; TIME++;
        low[u] = in[u];
        int num_child = 0;
        
        for(auto& e : g.g[u]) {
            int v = e.to;
            if(!visited[v]) {
                par[v] = u;
                tarjan_dfs(v);
                low[u] = min(low[u], low[v]);  // low[u] can also be determined by low[v] for v in dfs subtree of u
                if(par[u] != u and in[u] <= low[v]) {  // u is not a root and satisfies the condition to be the cut vertex
                    is_cut_vertex[u] = true;
                    if(in[u] < low[v]) {  // condition for e to be a bridge
                        bridges.push_back(e);
                    }
                }
                num_child++;  // increment the number of children
            }
            else if (v != par[u]) {
                low[u] = min(low[u], in[v]);   // we have a back edge here, which is not to the parent
            }
        }
        if(par[u] == u) { // this is the root of the dfs tree
            if(num_child > 1) {
                is_cut_vertex[u] = true;
                for(auto& e: g.g[u]) {
                    int v = e.to;
                    if(is_cut_vertex[v]) {
                        bridges.push_back(e);
                    }
                }
            }    
        }
        out[u] = TIME; TIME++;
    };

    for(int i = 0; i < g.n; i++) {
        if(!visited[i]) {
            tarjan_dfs(i);
        }
        if(is_cut_vertex[i]) {
            cut_vertices.push_back(i);
        }
    }
    return bridges;
}
