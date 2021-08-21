#include <bits/stdc++.h>

using namespace std;

/* [Description] : Implementation to find strong components in a directed graph,
 *                 using Tarjan's algorithm
 *                 The strong components are essentially a partition of the vertices of the graph, in which every vertex
 *                 in a strong component can reach another vertex in the strong component along a directed path.
 *
 *                 The implementation below is for general use only, special requirements could effectively require a new implementation.
 *                 But this can always be used as a guideline.
 *                 
 * Running Time : O(m + n), linear in the graph                 
 */

/* Returns the vertices in each of the strong components.
 * Return type is vector<vector<int>>
 * root of each of the strong components is the first vertex in the vector
 */

template <class T>
vector<vector<int>> strong_components(digraph<T>& g) {
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
    vector<int> st; // stack to hold the vertices in the current strong component
    int c_id = 0; // current component id
    vector<vector<int>> components;
    
    function<void(int)> tarjan_dfs = [&] (int u) {
        visited[u] = true;
        in[u] = TIME; TIME++;
        low[u] = in[u];
        st.push_back(u);

        for(auto& e : g.g[u]) {
            int v = e.to;
            if(!visited[v]) {
                par[v] = u;
                tarjan_dfs(v);
                low[u] = min(low[u], low[v]);
            }
            else {
                low[u] = min(low[u], in[v]); // we have a back/cross edge here, u assuredly cannot be
                                             // the root of a strong component
            }
        }

        if(low[u] == in[u]) {   // vertex u is the root of its strong component
            while(st.back() != u)  {
                components[c_id].push_back(st.back());
                st.pop_back();
            }
            components[c_id].push_back(st.back()); st.pop_back();
            swap(st.front(), st.back()); // make the root the first node in the strong component
            c_id++;  // we are done with this component
        }   
        out[u] = TIME; TIME++;
    };

    for(int i = 0; i < g.n; i++) {
        if(!visited[i]) {
            tarjan_dfs(i);
        }
    }
    return components;
}
