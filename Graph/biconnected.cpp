#include <bits/stdc++.h>

using namespace std;

/* [Description] : Implementation to find biconnected components in an undirected graph,
 *                 using Tarjan's algorithm
 *                 The biconnected components are essentially a partition of the edges of the graph
 *
 *                 The implementation below is for general use only, special requirements could effectively require a new implementation.
 *                 But this can always be used as a guideline.
 *                 
 * Running Time : O(m + n), linear in the graph                 
 */

/* Returns the edges in each of the biconnected components.
 * Return type is vector<vector<edge>>
 */

template <class T>
vector<typename undigraph<T>::edge> cut_vertices_and_bridges(undigraph<T>& g) {
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
    vector<typename undigraph<T>::edge> st; // stack to hold the edges in the current component
    int c_id = 0; // current component id
    vector<vector<typename undigraph<T>::edge>> components;

    function<void(int)> tarjan_dfs = [&](int u) {
        visited[u] = true;
        in[u] = TIME; TIME++;
        low[u] = in[u];
        int num_child = 0; // keeps track of the number of children of a node

        for(auto& e : g.g[u]) {
            int v = e.to;
            if(!visited[v]) {
                par[v] = u;
                st.push_back(e);  // add edge to current component
                tarjan_dfs(v);
                low[u] = min(low[u], low[v]);
                if((par[u] == u and num_child > 1) or (low[v] >= in[u])) {  // we have a cut vertex
                    components.push_back({});  // we have a new biconnected component
                    while(st.back() != e) {   // keep removing edges until the first edge pushed in the current biconnected component is reached
                        components[c_id].push_back(st.back());  
                        st.pop_back();
                    }
                    components.push_back(st.back()); st.pop_back();
                    c_id++; // increment the component id
                }
            }
            else if (v != par[u]) {
                low[u] = min(low[u], in[v]);  // we have a back edge here
            }
        }
        out[u] = TIME; TIME++;
    };
    for(int i = 0; i < g.n; i++) {
        if(!visited[i]) {
            tarjan_dfs(i);
            if(!st.empty()) {
                components.push_back({}); // we have a biconnected component left
            }
            while(!st.empty()) {  // remove all edges still left in current biconnected component
                components[c_id].push_back(st.back()); st.pop();
            }
            c_id++; // increment the component id
        }
    }
    return components;
}
