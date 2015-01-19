#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <map>
using namespace std;

class Node {
    private:
        int id;
        bool is_visited;
        vector<Node*> childs;
   
    public:
        int indegree;
        int outdegree;
        Node (int x) : id(x), is_visited(false), indegree(0), outdegree(0) { childs.clear(); }
        vector<Node*>& get_childs() { return childs; }
        void  add_child(Node *node) { childs.push_back(node); }
        int   get_id() { return id; }
        void  set_visited() { is_visited = true; }
        bool  visited() { return is_visited; }
};

inline int abs_diff(int a, int b) {
    if (a>b) return a-b;
    return b-a;
}

int num_pairs(Node *node, map<int, bool>& ancestors, int T) {
    int res = 0;
    vector<Node*> childs = node->get_childs();
    for (int i = 0; i < childs.size(); ++i) {
        Node* child = childs[i];
        int childid = child->get_id();
        for (map<int,bool>::iterator it=ancestors.begin(); it!=ancestors.end(); ++it) {
            if (abs_diff(it->first, childid) <= T) res++;
        }
        /*for (int id = childid-T; id <= childid+T; id++) {
            if (ancestors.count(id) != 0) res++;
        }*/
        ancestors[childid] = true;
        res += num_pairs(child, ancestors, T);
        ancestors.erase(childid);
    }
    return res;
}

int main() {
    int num_vertices, T;
    cin >> num_vertices >> T;
    Node* Tree[num_vertices];
    for (int i = 0; i < num_vertices; ++i) Tree[i] = NULL;
    for (int i = 0; i < num_vertices-1; ++i) {
        int from, to;
        cin >> from >> to;
        if (Tree[from-1] == NULL) Tree[from-1] = new Node(from);
        if (Tree[to-1] == NULL) Tree[to-1] = new Node(to);
        Tree[from-1]->add_child(Tree[to-1]);
        Tree[from-1]->outdegree++;
        Tree[to-1]->indegree++;
    }
    Node* root = NULL;
    for (int i = 0; i < num_vertices; ++i) {
        if (Tree[i]->indegree == 0) {
            root = Tree[i];
            break;
        }
    }
    assert(root != NULL);
    map<int,bool> ancestors;
    ancestors[root->get_id()] = true;
    cout << num_pairs(root, ancestors, T) << endl;
    //cleanup
    for (int i = 0; i < num_vertices; ++i) delete Tree[i];
    return 0;
}
