#include <bits/stdc++.h>

using namespace std;

/*
 * [Description] : Generic implementation of Dinitz Max Flow algorithm
 *                 Can be used as a standard subroutine for any graph.
 *                 TODO - In case flows are floating point, we need to be more careful about <, >, =
 *                 Max Flow can be used to find minimum cuts and matchings as well with minimal extra effort
 * Running Time : O(n^2 m)
 */


template <class T>
class flow_graph {
public :
    class flow_edge {
    public :
        int from, to;
        T cap, flow;
    };
    vector<flow_edge> edges; // edges in the graph
    vector<vector<int>> g; // adjacency list
    int s, t; // source and terminal vertex
    vector<int> level; // level of the vertex in the level graph built by bfs

    flow_graph(int n) {
        g.resize(n);
        level.assign(n, -1);
    }

    void add(int u, int v, T cap) {
        const int n = (int) g.size();
        assert(0 <= u and u < n and 0 <= v and v < n);
        g[u].push_back(edges.size());
        edges.push_back({u, v, cap, 0});
        g[v].push_back(edges.size());
        edges.push_back({v, u, 0, 0});
    }

    bool flow_bfs() {  // check if t is reachable from s in the residual graph
        queue<int> q;
        q.push(s);
        level.assign(level.size(), -1);
        level[s] = 0;
        while (!q.empty()) {
            int top = q.front();
            q.pop();
            for (auto& i : g[top]) {
                flow_edge& e = edges[i];
                if (e.cap - e.flow > 0 and level[e.to] == -1) {  // use only those edges where there is scope to push flow
                    level[e.to] = level[e.from] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[t] >= 0;
    }

    T flow_dfs(int u, T push) {  // push is the maximum amount of flow we wish to push, function returns maximum flow it could push
        if (push == T(0)) {
            return T(0); // if we want to push nothing then no point continuing
        }
        if (u == t) {
            return push; // we have reached the sink/terminal successfully and hence we managed a flow = push
        }
        for (auto& i : g[u]) {
            flow_edge& e = edges[i];
            flow_edge& rev_e = edges[i ^ 1]; // reverse edge corresponding to e
            int v = e.to;
            if (e.cap - e.flow > 0 and level[v] == level[u] + 1) {  
                // if there is scope to for some flow to be pushed and v is below u in the level graph
                T bottleneck = flow_dfs(v, min(push, e.cap - e.flow));
                if (bottleneck > T(0)) {
                    // we were succesful in pushing some flow
                    e.flow += bottleneck;
                    rev_e.flow -= bottleneck;
                    return bottleneck; // we found a flow, return
                }
            }
        }
        return T(0); // we are unsuccesful in pushing any flow, return empty flow
    }

    T max_flow(int source, int sink) { // returns the maximum flow in the graph between source and sink
        s = source, t = sink;
        level.assign(level.size(), -1);
        T flow = T(0);
        for (auto& i : g[s]) {
            flow += edges[i].flow;
        }
        T max_flow = numeric_limits<T>::max(); // maximum flow
        while (true) {
            bool res = flow_bfs(); // check reachability
            if (!res) {
                return flow; 
            }
            while (true) {
                T extra_flow = flow_dfs(s, max_flow);
                if (extra_flow == 0) { // we have saturated an edge in every s-t path
                    break;
                }
                flow += extra_flow; 
            }
        }
        return flow;
    }
};
