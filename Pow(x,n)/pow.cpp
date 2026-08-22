#include<bits/stdc++.h>
using namespace std;
class Solution {
public:

    double solve(double x, long long n) {

        if (n == 0)
            return 1;

        if (n < 0) {
            return solve(1 / x, -n);
        }

        if (n % 2 == 0) {
            return solve(x * x, n / 2);
        }
        else {
            return x * solve(x * x, (n - 1) / 2);
        }
    }

    double myPow(double x, int n) {
        return solve(x, (long long)n);
    }
};
int main() {
    double x;
    int n;
    cout << "Enter the base (x): ";
    cin >> x;
    cout << "Enter the exponent (n): ";
    cin >> n;

    Solution sol;
    double result = sol.myPow(x, n);

    cout << x << " raised to the power of " << n << " is: " << result << endl;

    return 0;
}