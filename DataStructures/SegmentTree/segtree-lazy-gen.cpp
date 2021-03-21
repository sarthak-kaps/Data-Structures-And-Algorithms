#include <bits/stdc++.h>

using namespace std;

/*
 * [Description] : Generic Lazy Segment Tree Implementation
 * Requires filling the segtree_node and Function classes before usage
 * segtree_node and Function need to guarantee some functionalities (The template for that is given)
 * Functions in segtree -
    1) assign(v) : a.k.a build function, v is a vector of segtree_node, build can also be automatically done by passing v in constructor
        Runnng Time : O(n)
    2) query(l, r) : 0 indexed queries, returns a segtree_node
        Running Time : O(log(n))
    3) update(l, r, F) : F is an object of Function we want to apply from l to r (0 indexed)
        Running Time : O(log(n))
*/

class segtree_node {
public :
    /* Class Data Members */

    /* This node is a class implementing the following methods: 
    * constructor: identity element of monoid (you should have the neutral values)
    * constructor: element created by combining 2 elements
    */
    segtree_node() {}
    segtree_node(const segtree_node& one, const segtree_node& two) {}  
};

class Function {
public :
    /* Function Data Members */

    /* A Function is a class implementing the following methods: 
    * constructor: identity function
    * constructor : to construct arbitrary function
    * constructor: function composition (f1.f2)
    * whether this function is the identity function
    * function definition (action on segtree_node)
    */

    Function() {}  
    Function(/**/) {}
    Function(const Function& f1, const Function& f2) {}  
    bool is_identity() const {}  
    segtree_node operator()(const segtree_node& node) {}  

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

    explicit segtree(int _n):
        n(_n), values(segtree_size(_n)), pends(values.size()) {identity_check();}
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
        assert(l <= last and r >= first);
        propagate(root, first, last);
        if(l <= first and last <= r) {
            return values[root];
        }
        else {
            int left = 2 * root + 1;
            int mid = (first + last) / 2;
            if(l > mid or r < first) {
                return query(left + 1, mid + 1, last, l, r);
            }
            else if(l > last or r < mid + 1) {
                return query(left, first, mid, l, r);
            }
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

