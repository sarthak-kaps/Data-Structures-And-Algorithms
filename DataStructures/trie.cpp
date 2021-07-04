#include <bits/stdc++.h> 

using namespace std;

/* 
 * [Description] : Generic Trie Data Structure
 *                 This data structure is suitable when we have many strings whose length is relatively small (~100)
 *                 Supported Functionalities -
 *                   1) Adding a string
 *                   2) Removing a string
 *                   3) Searching a string and a prefix
 *                   4) Keeps track of duplicate enteries of the same string efficiently (we can remove all duplicates or only one of them) 
 *
 * Note : currently works if all the characters that can be present in the strings are contiguous in ASCII values
 *        e.g. [a-z] or [0-9] or [A-Z] or [A-Z + a-z] etc.
 *
 * Time Complexity : Searching a string w in the Trie takes time O(len(w))
 *                   Adding a string w in the Trie takes time O(len(w))
 *                   Removing a string w in the S takes time O(len(w))
 *
 *********** NOT TESTED RIGOROUSLY ***********
 */
 

//A trie_node represents a the last character in some running prefix till that node

class trie_node {
public :
    char ch;
    vector<trie_node*> children;
    int dup; // keeps the count of how many times the current prefix is present in all the added strings
    int end; // does a valid string end here, 0 means no  and > 0 means yes and represent how many end here

    trie_node(char ch, int alpha_size = 26) : ch(ch) {
        dup = 0;
        children.assign(alpha_size, NULL);
        end = false;
    }
};

class trie {
public :
    trie_node* root_node; // root node represents the string epsilon (depicted as '$')
    char base; // base is the smallest lexicographic character in the alphabet
    int alpha_size; // size of the alphabet

    trie(char base = 'a', int alpha_size = 26) : base(base), alpha_size(alpha_size) { 
        root_node = new trie_node('$', alpha_size);
        root_node->end = true; // empty string ends here
    }

    void add(trie_node* root, string& s, int pos) {  // we have already added string till index pos - 1 and done all required computations till then 
        if(pos == s.length()) {                       
            return; // we have already added the string (note the empty string case)
        }
        int index = s[pos] - base;
        if(root->children[index] == NULL) {
            root->children[index] = new trie_node(s[pos], alpha_size);
        }
        root->children[index]->dup++;
        if(pos == s.length() - 1) {
            root->children[index]->end = true; // we are adding the last character
        }
        add(root->children[index], s, pos + 1);
    }

    int remove(trie_node* root, string& s, int pos, bool all = true) { // all parameter tells if we want to remove all instances or one duplicate
        if(pos == s.length()) {
            return 0; // we have reached the end of string and hence removed it
        } 
        int index = s[pos] - base;
        if(root->children[index] == NULL or root->children[index]->dup == 0) {
            return 0; // the string is not present in the trie
        }
        if(pos == s.length() - 1) { // we are removing the last character  
            int total = root->children[index]->end;
            if(total > 0) {  // a string does end here and we can remove it
                int to_remove = all ? total : 1;
                root->children[index]->end -= to_remove; 
                root->children[index]->dup -= to_remove;
                return to_remove;
            }
            return 0;  // no string ends here
        }
        int removed = remove(root->children[index], s, pos + 1, all);
        root->children[index]->dup -= removed;
        return removed;
    }

    pair<int, int> search(trie_node* root, string& s, int pos) { // returns the number of strings that match s and the number of prefixes that match s
        if(pos == s.length()) {
            return {0, 0};
        }
        int index = base - s[pos];
        if(root->children[index] == NULL) {
            return {0, 0};
        }
        if(pos == s.length() - 1) {
            return {root->end, root->dup};
        }
        return search(root->children[index], s, pos + 1);
    } 

    void add(string& s) {
        add(root_node, s, 0);
    }

    int remove(string& s, bool all = true) {
        return remove(root_node, s, 0, all);
    }

    pair<int, int> search(string& s) {
        return search(root_node, s, 0);
    }
};
