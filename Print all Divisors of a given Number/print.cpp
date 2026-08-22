#include <bits/stdc++.h>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
  public:
    vector<int> getDivisors(int n) {
        // code here
         vector<int> res;
 for (int i = 1; i * i <= n; i++) {
             // Check if i divides N
             if (n % i == 0) {
                 // Add i to the result
                 res.push_back(i);

                 // If N / i is different from i, add N / i too
                 if (i != n/ i) {
                     res.push_back(n / i);
                 }
             }
         }

     
         sort(res.begin(), res.end());
         return res;
     }
 };
int main() {
    int n;
    cout << "Enter a number: ";
    cin >> n;

    Solution sol;
    vector<int> divisors = sol.getDivisors(n);

    cout << "Divisors of " << n << " are: ";
    for (int divisor : divisors) {
        cout << divisor << " ";
    }
    cout << endl;

    return 0;
}