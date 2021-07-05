#include <bits/stdc++.h>

using namespace std;

/* [Description] : Implementation to find a topological ordering of vertices in a Directed Acyclic Graph (DAG)
 *                 Can be run on any directed graph, it checks whether the graph is a DAG or not
 *                 
 *                 The implementation below is for general use only, special requirements could effectively require a new implementation.
 *                 But this can always be used as a guideline.
 *                 
 * Running Time : O(m + n), linear in the graph                 
 */


template <class T>
vector<int> topsort(const digraph<T>& g) {
    vector<int> indegree(g.n);
    queue<int> to_remove;
    vector<int> top_sorted;
    for(int i = 0; i < g.n; i++) {
        for(auto& [from, to, cost] : g.g[i]) {
            // assert(from == i);
            indegree[to]++;     
        }
    }
    for(int i = 0; i < g.n; i++) {
        if(indegree[i] == 0) {
            to_remove.push(i);
        }
    }
    while(true) {
        if(top_sorted.size() != g.n and to_remove.empty()) {
            cout << "[Error] : Graph is not a DAG" << '\n';
            return {};
        } 
        if(to_remove.empty()) {
            return top_sorted;
        }
        int top = to_remove.front();
        to_remove.pop();
        top_sorted.push_back(top);
        for(auto& [from, to, cost] : g.g[top]) {
            indegree[to]--;
            if(indegree[to] == 0) {
                to_remove.push(to);
            }
        }
    }
}
