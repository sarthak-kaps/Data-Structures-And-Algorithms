#include <bits/stdc++.h>

using namespace std;

/* 
 * [Description] : Implementation Of Disjoint Set Union Class
 * Note - This implementation uses Union By Size
 * Running Time - 
    parent(i) - alpha(n)
    size(i) - alpha(n)
    Union(i) - alpha(n)
    get_distinct - O(1)
*/

class DSU {
private :
    vector<int> set;
    int num_sets;
public :
    DSU(int n) {
        set.assign(n, -1);
        num_sets = n;
    }
    int size(int i) {
        i = parent(i);
        return -set[i];
    }
    int parent(int i) {    // find parent and path compression
        if(set[i] <= -1) {
            return i;
        }
        set[i] = parent(set[i]);
        return set[i];
    }
    void Union(int i, int j) {
        i = parent(i);
        j = parent(j);
        if(i == j) {
            return;
        }
        if(size(j) >= size(i)) { 
            swap(i, j);
        }
        set[i] += set[j];
        set[j] = i;
        num_sets--;
    }
    int getDistinct() {
        return num_sets;
    }
};
