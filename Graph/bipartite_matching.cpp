#include <bits/stdc++.h>

using namespace std;

/*
 * [Description] : Bipartite Matching using Dinitz Max Flow algorithm
 *                 Can be used as a standard subroutine for any graph.
 * Running Time : O(m \sqrt(n)) [as all capacities are unit]
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

class bipartite_matching {
public :
    vector<int> A; // partition A's matched neighbour
    vector<int> B; // partition B's matched neighbour
    int n, m;      // size of the partitions
   
    flow_graph<int> g = flow_graph<int>(0);
    int s, t;
    
    vector<bool> A_set;  // have we added s->u ?
    vector<bool> B_set;  // have we added v->t ?

    bipartite_matching(int n, int m) : n(n), m(m) {
        A.assign(n, -1);
        B.assign(m, -1);
        A_set.assign(n, false);
        B_set.assign(m, false);
        g = flow_graph<int>(n + m + 2);
        s = n + m, t = n + m + 1; // added source and sink
    }

    void add(int u, int v) {
        assert(0 <= u and u < n and 0 <= v and v < m);
        v += n;
        g.add(u, v, 1);
        if (!A_set[u]) {
            g.add(s, u, 1);
            A_set[u] = true;
        }
        if (!B_set[v - n]) {
            g.add(v, t, 1);
            B_set[v - n] = true;
        }
    }
   
    // set given matching, assuming AA is valid representation of A partition
    // [NOTE] : set -1 if vertex is not matched
    void set_matching(vector<int>& AA) {
        assert(n == (int) AA.size());
        A = AA;
        B.assign(m, -1);
        for (int i = 0; i < n; i++) {
            if (A[i] == -1) { 
                continue;
            }
            B[A[i]] = i;
            for (int id : g.g[i]) {
                auto& e = g.edges[id];
                if (e.to - n == A[i]) {
                    // this will happen only once
                    e.flow = 1;
                    auto& rev_e = g.edges[id ^ 1];
                    rev_e.flow = -1;
                }
            }
        }
        // set flow on s->u
        for (int id : g.g[s]) {
            auto& e = g.edges[id];
            int u = e.to;
            if (A[u] != -1) {
                e.flow = 1;
                auto& rev_e = g.edges[id ^ 1];
                rev_e.flow = -1;
            }
        }
        // set flow on v->t
        for (int id : g.g[t]) {
            auto& rev_e = g.edges[id];
            int v = rev_e.to;
            if (B[v - n] != -1) {
                rev_e.flow = -1;
                auto& e = g.edges[id ^ 1];
                e.flow = 1;
            }
        }
    }

    int max_matching() {
        int sz = g.max_flow(s, t);
        for (int i = 0; i < n; i++) {
            A[i] = -1;
        }
        for (int i = 0; i < m; i++) {
            B[i] = -1;
        }
        for (int i = 0; i < (int) g.edges.size(); i += 2) {
            auto& e = g.edges[i];
            int u = e.from, v = e.to;
            if (e.cap == e.flow) {
                if (u != s and v != t) {
                    v -= n;
                    A[u] = v, B[v] = u;
                }
            }
        } 
        return sz;
    }
};
 
