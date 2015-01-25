#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

typedef int ull;

inline ull max(ull x, ull y) { return (x > y)? x : y; }

ull lps(string str) {
   int n = str.size();
   int i, j, cl;
   map<ull,ull> L[n]; 
 
    for (i = 0; i < n; i++)
      L[i][i] = 1;
    
    for (cl=2; cl<=n; cl++)
    {
        for (i=0; i<n-cl+1; i++)
        {
            j = i+cl-1;
            if (str[i] == str[j] && cl == 2)
               L[i][j] = 2;
            else if (str[i] == str[j])
               L[i][j] = L[i+1][j-1] + 2;
            else
               L[i][j] = max(L[i][j-1], L[i+1][j]);
        }
    }
 
    ull maxp = L[0][0]*L[1][n-1];
    
    for (int i = 1; i < n-1; ++i) {
        maxp = max(maxp, L[0][i]*L[i+1][n-1]);
    }
    
    return maxp;
}

int main() {
    string input;
    cin >> input;
    cout << lps(input) << endl;
    return 0;
}


