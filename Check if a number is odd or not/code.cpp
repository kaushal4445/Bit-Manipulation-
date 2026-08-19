#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
  bool isOdd(int n) {
    
    return (n % 2 != 0);  
  }
};
int main() {
   Solution sol;
    int num;
    cout << "Enter a number: ";
    cin >> num;

   
    if (sol.isOdd(num)) {
        cout << num << " is an odd number." << endl;
    } else {
        cout << num << " is an even number." << endl;
    }
  return 0;
}