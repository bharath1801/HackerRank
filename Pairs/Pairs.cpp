#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <cstdlib>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;

bool binary_search(vector<int>& a, int low, int high, int x) {
    if (low>high) return false;
    int mid = (low+high)/2;
    if (a[mid] == x) return true;
    else if (a[mid] > x) return binary_search(a, low, mid-1, x);
    return binary_search(a, mid+1, high, x);
}

int pairs(vector<int>& a, int k) {
   int ans = 0;
   for (int i = 0; i < a.size(); ++i) {
       ans = (binary_search(a, i+1, a.size()-1, a[i]+k)) ? ans + 1 : ans;
   }
   return ans;
}

int compare(const void* a, const void* b) {
    return ( *(int*)a - *(int*)b );
}

int main() {
    int res;
    
    int _a_size,_k;
    cin >> _a_size>>_k;
    cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n'); 
    vector<int> _a;
    int _a_item;
    for(int _a_i=0; _a_i<_a_size; _a_i++) {
        cin >> _a_item;
        _a.push_back(_a_item);
    }
    qsort(&_a[0], _a.size(), sizeof(int), compare);
    res = pairs(_a,_k);
    cout << res;
    
    return 0;
}
