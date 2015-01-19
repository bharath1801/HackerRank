#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}


int main() {
    int n,m;
    cin >> n;
    vector<int> missing;
    map<int, int> A;
    for (int i = 0; i < n; ++i) {
        int val;
        cin >> val;
        if (A.count(val) == 0) A[val] = 1;
        else A[val] += 1;
    }
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int val;
        cin >> val;
        if (A.count(val) == 0) missing.push_back(val);
        else if (A[val] > 0) A[val] -= 1;
        else missing.push_back(val);
    }
    if (missing.size() > 0) {
        qsort(&missing[0], missing.size(), sizeof(int), compare);
        cout << missing[0] << " ";
        for (int i = 1; i < missing.size(); ++i) {
            if (missing[i-1] != missing[i]) cout << missing[i] << " ";
        }
    }   
    return 0;
}
