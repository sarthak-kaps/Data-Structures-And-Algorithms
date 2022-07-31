#include <bits/stdc++.h>

/*
 * [Description] : Basic 2D Segment Tree.
 *                 Allows you to query over submatrices in a matrix. 
 *                 Imagine it as a segment tree of a segment trees !
 *                 It basically does to a matrix what segment tree does to an array.
 * Note : This is just a basic implementation and not general enough
 *        Better to view this as a guide. The current implementation is a max 2D segment tree.
 * [Running Time] :
 *      Build : O(n^2)
 *      Query : O(log^2 n)
 *      Update : O(log^2 n)
*/

using namespace std;

vector<vector<int>> segtree_2d;
vector<vector<int>> a;


void build(vector<int>& segtree, int index, int first, int last, int pos) {
    if(first == last) {
        segtree[index] = a[pos][first];
        return;
    }
    int mid = (first + last) / 2;
    build(segtree, 2 * index + 1, first, mid, pos);
    build(segtree, 2 * index + 2, mid + 1, last, pos);
    segtree[index] = max(segtree[2 * index + 1], segtree[2 * index + 2]);
}

int query(int index, int first, int last, int l, int r, int pos) {
    if(l <= first and r >= last) {
        return segtree_2d[pos][index];
    }
    int mid = (first + last) / 2;
    if(l > mid) {
        return query(2 * index + 2, mid + 1, last, l, r, pos);
    }
    else if(r <= mid) {
        return query(2 * index + 1, first, mid, l, r, pos);
    }
    else {
        return max(query(2 * index + 1, first, mid, l, r, pos), query(2 * index + 2, mid + 1, last, l, r, pos));
    }
}

void build_2d(int index, int first_x, int last_x, int first_y, int last_y) {
    if(first_x == last_x) {
       build(segtree_2d[index], 0, first_y, last_y, first_x);
       return;
    } 
    int mid_x = (first_x + last_x) / 2;
    build_2d(2 * index + 1, first_x, mid_x, first_y, last_y);
    build_2d(2 * index + 2, mid_x + 1, last_x, first_y, last_y);

    for(int i = 0; i < segtree_2d[2 * index + 1].size(); i++) {
        segtree_2d[index][i] = max(segtree_2d[2 * index + 1][i], segtree_2d[2 * index + 2][i]);
    }
}

int query_2d(int index, int first_x, int last_x, int first_y ,int last_y, int l_x, int r_x, int l_y, int r_y) {
    if(l_x <= first_x and r_x >= last_x) {
        return query(0, first_y, last_y, l_y, r_y, index);
    }
    int mid_x = (first_x + last_x) / 2;
    if(l_x > mid_x) {
        return query_2d(2 * index + 2, mid_x + 1, last_x, first_y, last_y, l_x, r_x, l_y, r_y);
    }
    else if(r_x <= mid_x) {
        return query_2d(2 * index + 1, first_x, mid_x, first_y, last_y, l_x, r_x, l_y, r_y);
    }
    else {
        return max(query_2d(2 * index + 2, mid_x + 1, last_x, first_y, last_y, l_x, r_x, l_y, r_y), query_2d(2 * index + 1, first_x, mid_x, first_y, last_y, l_x, r_x, l_y, r_y)); 
    }
}

// test code

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    a.resize(n);
    for(auto& x : a) {
        x.resize(n);
    }
    segtree_2d.resize(4 * n);
    for(auto& segtree : segtree_2d) {
        segtree.assign(4 * n, -1e8);
    }
    int k;
    cin >> k;
    for(auto& x : a) {
        for(auto& e : x) {
            cin >> e;
        }
    }
    build_2d(0, 0, n - 1, 0, n - 1);

    for(int i = 0; i <= n - k; i++) {
        for(int j = 0; j <= n - k; j++) {
            int ans = query_2d(0, 0, n - 1, 0, n - 1, i, i + k - 1, j, j + k - 1); 
            cout << ans << endl;
        }
    }
}
