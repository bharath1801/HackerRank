#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>
using namespace std;

class Node {
    private:
    int id;
    int sum;
    int cost;
    bool is_visited;
    vector<Node*> childs;
   
    public:
    Node (int x, int y) : id(x), sum(0), cost(y), is_visited(false) {
        childs.clear();
    }
    
    vector<Node*>& get_childs() { return childs; }
    int   get_sum() { return sum; }
    void  add_child(Node *node) { childs.push_back(node); }
    void  set_sum(int val) { sum = val; }
    int   get_cost() { return cost; }
    int   get_id() { return id; }
    void  set_visited() { is_visited = true; }
    bool  visited() { return is_visited; }
};

inline int abs_diff(int a, int b) {
    if (a > b) return a-b;
    return b-a;
}

int calculate_sums(Node* node) {
    if (node == NULL) return 0;    
    node->set_visited();
    vector<Node*> childs = node->get_childs();
    int sum = 0;
    for (int i = 0; i < childs.size(); ++i) {
        if (!childs[i]->visited())
            sum += calculate_sums(childs[i]);
    }
    sum += node->get_cost();
    node->set_sum(sum);
    //cout << node->get_id() << ":" << sum << endl;
    return sum;
}

void findMin(Node* node, int &min, int total_cost) {
    if (node == NULL) return;
    vector<Node*> childs = node->get_childs();
    for (int i = 0; i < childs.size(); ++i) {
        Node* child = childs[i];
        if (child->get_id() == node->get_id()) continue;
        int diff =  abs_diff(child->get_sum(), total_cost - child->get_sum());
        min = (min > diff) ? diff : min;
    }
    return;
}

int main() {
    int num_vertices;
    cin >> num_vertices;
    Node* Tree[num_vertices];
    int total_cost = 0;
    for (int i = 0; i < num_vertices; ++i) {
        int cost;
        cin >> cost;
        Node *node = new Node(i+1, cost);
        Tree[i] = node;
        total_cost += cost;
    }
    //cout << total_cost << endl;
    
    for (int i = 0; i < num_vertices - 1; ++i) {
        int x, y;
        cin >> x >> y;
        Tree[x-1]->add_child(Tree[y-1]);
        Tree[y-1]->add_child(Tree[x-1]);
        //cout << x << ":" << y << endl;
    }
    
    int min_cost = calculate_sums(Tree[0]);
    //cout << min_cost << endl;
    assert(min_cost == total_cost);
    for (int i = 0; i < num_vertices; ++i)
        findMin(Tree[i], min_cost, total_cost);
    cout << min_cost << endl;
    for (int i = 0; i < num_vertices; ++i) delete Tree[i];
    return 0;
}
