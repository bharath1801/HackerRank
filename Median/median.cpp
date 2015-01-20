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
#include <set>
#include <cassert>
#include <climits>
using namespace std;

inline int abs_diff (int a, int b) {
    if (a > b) return a-b;
    return b-a;
}

inline int upperMin (multiset<int>& oset) {
    if (oset.empty()) return INT_MIN;
    multiset<int>::iterator it = oset.begin();
    return *it;
}

inline int lowerMax (multiset<int>& oset) {
    if (oset.empty()) return INT_MAX;
    multiset<int>::reverse_iterator rit = oset.rbegin();
    return *rit;
}

inline bool haselem(multiset<int>& oset, int val) {
    if (oset.find(val) != oset.end()) return true;
    return false;
}

inline void eraseelem(multiset<int>& oset, int val) {
    multiset<int>::iterator it;
    it = oset.find(val);
    assert(it != oset.end());
    oset.erase(it);
    return;
}

inline string dbl2str(double d)
{
    size_t len = std::snprintf(0, 0, "%.10f", d);
    std::string s(len+1, 0);
    // technically non-portable, see below
    std::snprintf(&s[0], len+1, "%.10f", d);
    // remove nul terminator
    s.pop_back();
    // remove trailing zeros
    s.erase(s.find_last_not_of('0') + 1, std::string::npos);
    // remove trailing point
    if(s.back() == '.') {
        s.pop_back();
    }
    return s;
}

class MedianSet {
  private:
    multiset<int> lower;
    multiset<int> upper;
    void reorder();
    
  public:
    MedianSet() {
        lower.clear();
        upper.clear();
    }
    int a_size() { return lower.size() + upper.size(); }
    void insertX(int val);
    bool removeX(int val);
    bool empty() { return lower.empty() && upper.empty(); }
    string getMedian();
    void print();
};

void MedianSet::print() {
    multiset<int>::iterator it;
    cout << "Lower: ";
    for (it=lower.begin(); it!=lower.end(); ++it) cout << *it << ",";
    cout <<  "\nUpper: ";
    for (it=upper.begin(); it!=upper.end(); ++it) cout << *it << ",";
    cout << endl;
}

string MedianSet::getMedian() {
    assert(abs_diff(lower.size(), upper.size()) <= 1);
    if (lower.size() == upper.size()) {
        double val1 = upperMin(upper);
        double val2 = lowerMax(lower);
        return dbl2str((val1+val2)/2.0);
    }
    
    if (lower.size() > upper.size()) {
        return to_string(lowerMax(lower));
    }
    
    return to_string(upperMin(upper));
}

void MedianSet::insertX(int val) {
    
    if(lower.empty() && upper.empty()) {
        lower.insert(val);
        return;
    }
    
    if (lower.empty() || upper.empty()) {
        if (lower.empty()) {
            if (val < upperMin(upper)) lower.insert(val);
            else upper.insert(val);
        } else {
            if (val > lowerMax(lower)) upper.insert(val);
            else lower.insert(val);
        }
    } else {
        int lower_max = lowerMax(lower);
        int upper_min = upperMin(upper);
        if (val < lower_max) lower.insert(val);
        else if (val > upper_min) upper.insert(val);
        else {
            if (lower.size() == upper.size()) lower.insert(val);
            else upper.insert(val);
        }
    }
    reorder();
    return;
}

bool MedianSet::removeX(int val) {
    if (lower.empty() && upper.empty()) {
        return false;
    }
    
    if (lower.empty() || upper.empty()) {
        if(lower.empty()) {
            if(haselem(upper, val)) {
                eraseelem(upper, val);
                reorder();
                return true;
            }
            return false;
        }
        
        if(haselem(lower, val)) {
            eraseelem(lower, val);
            reorder();
            return true;
        }
        
        return false;
    }
    
    if(val <= lowerMax(lower) && haselem(lower, val)) {
        eraseelem(lower, val);
        reorder();
        return true;
    }
    
    if (val >= upperMin(upper) && haselem(upper, val)) {
        eraseelem(upper, val);
        reorder();
        return true;
    }
    
    return false;
    
}

void MedianSet::reorder() {
    
    if(lower.empty() && upper.empty()) {
        return;
    }
    
    while ( abs_diff(lower.size(), upper.size()) > 1) {
        if (lower.size() > upper.size()) {
            int lower_max = lowerMax(lower);
            eraseelem(lower, lower_max);
            upper.insert(lower_max);
         } else {
            int upper_min = upperMin(upper);
            eraseelem(upper, upper_min);
            lower.insert(upper_min);
         }
    }
    
    assert(abs_diff(lower.size(), upper.size()) <= 1);
    
    return;
}

void median(vector<char> s,vector<int> X) {
    MedianSet median_set;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == 'a') {
            median_set.insertX(X[i]);
            //median_set.print();
            cout << median_set.getMedian() << endl;
        } else {
            bool ret = median_set.removeX(X[i]);
            //median_set.print();
            if (ret && !median_set.empty()) cout << median_set.getMedian() << endl;
            else cout << "Wrong!" << endl;
        }
    }
}

int main(void){

   int N;
   cin >> N;
   
   vector<char> s;
   vector<int> X;
   char temp;
   int tempint;
   for(int i = 0; i < N; i++){
      cin >> temp >> tempint;
        s.push_back(temp);
        X.push_back(tempint);
   }
   
   median(s,X);
   return 0;
}
