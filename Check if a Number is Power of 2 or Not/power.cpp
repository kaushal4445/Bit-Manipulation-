#include<bits/stdc++.h>
using namespace std;
class Solution {
  public:
    bool isPowerOfTwo(int n) {
       
        return (n > 0) && ((n & (n - 1)) == 0);
    }
};

int main() {
    Solution sol;
    int num;
    cout << "Enter a number: ";
    cin >> num;

    if (sol.isPowerOfTwo(num)) {
        cout << num << " is a power of 2." << endl;
    } else {
        cout << num << " is not a power of 2." << endl;
    }

    return 0;
}