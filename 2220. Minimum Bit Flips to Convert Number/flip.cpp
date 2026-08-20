#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minBitFlips(int start, int goal) {
        int ans = start^goal;
        int cnt =0;
        for(int i = 0; i<31; i++){
            if(ans & (1<<i)){
                cnt = cnt +1;
            }
        }
        return cnt;
    }
};

int main(){
  
    int start, goal;
    cout << "Enter the start number: ";
    cin >> start;
    cout << "Enter the goal number: ";
    cin >> goal;

    Solution sol;
    int result = sol.minBitFlips(start, goal);
    cout << "The minimum number of bit flips required to convert " << start << " to " << goal << " is: " << result << endl;

    return 0;
}