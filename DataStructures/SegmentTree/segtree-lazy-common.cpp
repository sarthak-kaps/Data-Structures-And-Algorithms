#include <bits/stdc++.h>

using namespace std;

constexpr int __inf = 1e9;

class segtree_node {
public :
    /* Class Data Members */

    /* This node is a class implementing the following methods: 
    * constructor: identity element of monoid (you should have the neutral values)
    * constructor: element created by combining 2 elements
    */
    typedef int dtype; // change this to long long if required
    int l, r;
    dtype mn, mx, sum, gap;
    segtree_node() {
       mn =  __inf, mx = -__inf,  sum = 0, gap = 0;
       l = -1, r = -1;
    }
    segtree_node(const segtree_node& one, const segtree_node& two) {
        l = one.l;
        r = two.r;
        if(l == -1) {
            l = two.l;
        }
        else if(r == -1) {
            r =  one.r;
        }
        mn = min(one.mn, two.mn);
        mx = max(one.mx, two.mx);
        sum = one.sum + two.sum;
        gap = one.gap + two.gap;
    }  
};

class Function {
public :
    /* Function Data Members */

    /* A Function is a class implementing the following methods: 
    * constructor: identity function
    * constructor : to construct arbitrary function
    * constructor: function composition (f1.f2)
    * whether this function is the identity function
    * function definition (action on segTreeNode)
    */
    int a, b;
    Function() {
        a = 1, b = 0;
    }  
    Function(int a, int b) : a(a), b(b) {}
    Function(const Function& f1, const Function& f2) {
        a = f1.a * f2.a;
        b = f1.a * f2.b + f1.b;
    }  
    bool is_identity() const {
        return (a == 1 and b == 0);
    }  
    segtree_node operator()(const segtree_node& node) {
        segtree_node ans = node;
        ans.mx = a * node.mx + b;
        ans.mn = a * node.mn + b;
        ans.sum = a * node.sum + b * node.gap;  
        return ans;
    }  
};

template <class M, class F>
class segtree {
// M is a node
// F is a function
// remember to set leaf nodes from calling function
public:
    static void identity_check() {
        if(!F().is_identity()) {
            cout << "Default Constructor is not identity !!!" << endl;
        }
    }

private:
    int n;
    vector<M> values;  // the segment tree
    vector<F> pends;   // stores pending updates for lazy propogation

    inline int segtree_size(int _n) {
        _n -= 1;
        _n |= _n >> 1;
        _n |= _n >> 2;
        _n |= _n >> 4;
        _n |= _n >> 8;
        _n |= _n >> 16;
        return 2 * _n + 1;
    }

public:
    explicit segtree(std::vector<M>& v):
        n(v.size()), values(segtree_size(v.size())), pends(values.size()) {identity_check(); assign(v);}

private:
    // build function with vector of leaves 
    void assign_values(int root, int first, int last, vector<M> &a) {
        // root has the node number, first and last have the array indices.
        if(first == last) {
            values[root] = a[first];
        }
        else {
            int left = 2 * root + 1;
            int mid = (first + last) / 2;
            assign_values(left, first, mid, a);
            assign_values(left + 1, mid + 1, last, a);
            values[root] = M(values[left], values[left + 1]);
        }
    }

public:
    // assign every leaf corresponding vector entry
    void assign(vector<M>& v) {
        assert(v.size() == n); 
        assign_values(0, 0, n - 1, v);
    }

private:
    // lazy propagation
    void propagate(int root, int first, int last) {
        if(!pends[root].is_identity()) {
            values[root] = pends[root](values[root]);
            if(first != last) {
                int left = 2 * root + 1;
                pends[left] = F(pends[root], pends[left]);
                pends[left + 1] = F(pends[root], pends[left + 1]);
            }
            pends[root] = F();
        }
    }
    // query from range l to r (zero indexing)
    M query(int root, int first, int last, int l, int r) {
        if(l > last or r < first) {
            return M();
        }
        propagate(root, first, last);
        if(l <= first and last <= r) {
            return values[root];
        }
        else {
            int left = 2 * root + 1;
            int mid = (first + last) / 2;
            return M(query(left, first, mid, l, r), query(left + 1, mid + 1, last, l, r));
        }
    }

public:
    // query from range l to r (zero indexing)
    M query(int l, int r) {
        return query(0, 0, n - 1, l, r);
    }

private:
    // update from range l to r by giving update function (zero indexing)
    void update(int root, int first, int last, int l, int r, const F& f) {
        if(l > last or r < first) {
            propagate(root, first, last);
        }
        else if(l <= first and last <= r) {
            pends[root] = F(f, pends[root]);
            propagate(root, first, last);
        }
        else {
            propagate(root, first, last);
            int left = 2 * root + 1;
            int mid = (first + last) / 2;
            update(left, first, mid, l, r, f);
            update(left + 1, mid + 1, last, l, r, f);
            values[root] = M(values[left], values[left + 1]);
        }
    }

public:
    // update from range l to r by giving update function (zero indexing)
    void update(int l, int r, const F& f) {
        update(0, 0, n - 1, l, r, f);
    }
};


// test code

int main(void) {
    int n;
    cin >> n;
    vector<int> v(n);
    for(int i = 0; i < n; i++) {
       cin >> v[i];
    }
    vector<segtree_node> leaves(n);
    for(int i = 0; i < n; i++) {
       leaves[i].mn = leaves[i].mx = leaves[i].sum = v[i];
       leaves[i].l = leaves[i].r = i;
       leaves[i].gap = 1;
    }
    segtree<segtree_node, Function> s(leaves);
    int q;
    cin >> q;
    while(q --> 0) {
        int op;
        cin >> op;
        if(op == 0) {
            int x, y;
            cin >> x >> y;
            x--, y--;
            auto res = s.query(x, y);
            cout << res.mn << ' ' << res.mx << ' ' << res.sum << endl;
        }
        else {
            int x, y;
            cin >> x >> y;
            int up;
            cin >> up;
            x--, y--;
            s.update(x, y, Function(1, up));
        }
    }
}
