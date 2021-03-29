#include <bits/stdc++.h>

using namespace std;

/*
 * [Description] : Generic Sparse Segment Tree
 * By sparse we mean that the nodes are not stored contiguously and are allocated dynamically when required
 * Use cases can be when the ranges are huge e.g [0, 1e18] etc.
 * Can also be used as a normal generic segment tree - The interface is the same - expected to be faster
 * Again we have segtree_node and Function classes, we expect same functionalities as before
    [Note] : We have one extra requirement, that the l, r, gap fields are always implemented in segtree_node
             This is not a big requirement and is necessary.
             l = start of the range handled by the segtree_node
             r = end of the range handled by the segtree_node
             gap = r - l + 1
 * All functions are the same as in Generic Segment Tree with same time complexity
 * An example code is put for understanding
*/

constexpr int __inf = 1e9;


class segtree_node {
public :
    /* Class Data Members */

    /* This node is a class implementing the following methods: 
    * constructor: identity element of monoid (you should have the neutral values)
    * constructor: element created by combining 2 elements
    */
    typedef int data_type;
    int l, r, gap;
    data_type mn, mx, sum;
 
    segtree_node() {
        l = -1, r = -1;
        gap = 0;
        mx = -__inf, mn = __inf, sum = 0;
    }

    segtree_node(const segtree_node& one, const segtree_node& two) {
        l = one.l;
        r = two.r;
        gap = one.gap + two.gap;
        mn = min(one.mn, two.mn);
        mx = max(one.mx, two.mx);
        sum = one.sum + two.sum;
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
    * function definition (action on segtree_node)
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
        ans.mn = a * node.mn + b;
        ans.mx = a * node.mx + b;
        ans.sum = a * ans.sum + b * node.gap;
        return ans;
    }  
};

template <class M, class F>
class segtree_sparse {
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

    class node {
    public :
        M values;
        F pends;
        node* left;
        node* right;
        node(M values, F pends) : values(values), pends(pends) {}        
    };
    
    node* root;
    M value_init;
    F func_init;
public:
    explicit segtree_sparse(M value, F func) {
        root = new node(value, func);
        value_init = value;
        func_init = func;
        root->left = nullptr;
        root->right = nullptr;
    }

private:
    // lazy propagation
    void propagate(node* root) {
        if(!root->pends.is_identity()) {
            root->values = root->pends(root->values);
            int mid = (root->values.l + root->values.r) / 2;
           
            if(root->left == nullptr) {
                root->left = new node(value_init, func_init);
                root->left->values.l = root->values.l;
                root->left->values.r = mid;
                root->left->values.gap = (mid - root->left->values.l + 1);
            }
            if(root->right == nullptr) {
                root->right = new node(value_init, func_init);
                root->right->values.l = mid + 1;
                root->right->values.r = root->values.r;
                root->right->values.gap = (root->right->values.r - mid);
            }
            root->left->pends =  F(root->pends, root->left->pends);
            root->right->pends  = F(root->pends, root->right->pends);
            
            root->pends = F();
        }
    }
    // query from range l to r (zero indexing)
    M query(node* root, int l, int r) {
        propagate(root);
        if(l <= root->values.l and root->values.r <= r) {
            return root->values;
        }
        else {
            int mid = (root->values.l + root->values.r) / 2;
            if(root->left == nullptr) {
                root->left = new node(value_init, func_init);
                root->left->values.l = root->values.l;
                root->left->values.r = mid;
                root->left->values.gap = (mid - root->left->values.l + 1);
            }
            if(root->right == nullptr) {
                root->right = new node(value_init, func_init);
                root->right->values.l = mid + 1;
                root->right->values.r = root->values.r;
                root->right->values.gap = (root->right->values.r - mid);
            }
            if(l > mid) {
                return query(root->right, l, r);
            }
            else if(r <= mid) {
                return query(root->left, l, r);
            }
            else {
                return M(query(root->left, l, mid), query(root->right, mid + 1, r));
            }
        }
    }

public:
    // query from range l to r (zero indexing)
    M query(int l, int r) {
        return query(root, l, r);
    }

private:
    // update from range l to r by giving update function (zero indexing)
    void update(node* root, int l, int r, const F& f) {
        propagate(root);
        if(l <= root->values.l and root->values.r <= r) {
            root->pends = F(f, root->pends);
            propagate(root);
        }
        else {
            propagate(root); 
            int mid = (root->values.l + root->values.r) / 2;
            if(root->left == nullptr) {
                root->left = new node(value_init, func_init);
                root->left->values.l = root->values.l;
                root->left->values.r = mid;
                root->left->values.gap = (mid - root->left->values.l + 1);
            }
            if(root->right == nullptr) {
                root->right = new node(value_init, func_init);
                root->right->values.l = mid + 1;
                root->right->values.r = root->values.r;
                root->right->values.gap = (root->right->values.r - mid);
            }
            if(l > mid) {
                update(root->right, l, r, f);
            }
            else if(r <=  mid) {
                update(root->left, l, r, f);
            }   
            else {
                update(root->left, l, mid, f);
                update(root->right, mid + 1, r, f);
            }
            propagate(root->left);
            propagate(root->right);
            root->values = M(root->left->values, root->right->values);
        }
    }

public:
    // update from range l to r by giving update function (zero indexing)
    void update(int l, int r, const F& f) {
        update(root, l, r, f);
    }
};


// test code

int main(void) {
    segtree_node s_node;
    s_node.l = 0, s_node.r = 1e9;
    s_node.gap = s_node.r - s_node.l + 1;
    s_node.mn = 0, s_node.mx = 0, s_node.sum = 0;
    segtree_sparse<segtree_node, Function> s(s_node, Function());
    int q;
    cin >> q;
    while(q --> 0) {
        int op;
        cin >> op;
        if(op == 0) {
            int x, y;
            cin >> x >> y;
            --x, --y;
            auto res = s.query(x, y);
            cout << res.mn << ' ' << res.mx << ' ' << res.sum << endl;
        }
        else {
            int x, y;
            cin >> x >> y;
            --x, --y;
            int upd;
            cin >> upd;
            s.update(x, y, Function(1, upd));
        }
    }
}
