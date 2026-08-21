#include<bits/stdc++.h>
#include<vector>
using namespace std;
class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
      int n = nums.size();
      long XOR = 0;
      for (int i =0; i < n; i++){
        XOR = XOR ^ nums[i];

      }
      int rightmost = XOR  & (XOR - 1) ^ XOR;
      int bucket1 = 0;
      int bucket2 = 0;
      for(int i  = 0; i< n; i++){
        if(nums[i] & rightmost){
            bucket1  = bucket1^nums[i];
            }

        else {
        bucket2 = bucket2^nums[i];
        }
      }
      if(bucket1 > bucket2)
      return {bucket2, bucket1};
      else
      return {bucket1, bucket2};
    }
};

int main() {
    vector<int> nums = {1, 2, 1, 3, 5, 2};
    
 
    Solution sol; 
    
   
    vector<int> ans = sol.singleNumber(nums);
    
    cout << "The single numbers in given array are: " << ans[0] << " , " << ans[1];
    
    return 0;
}



