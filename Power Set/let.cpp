#include<bits/stdc++.h>
using namespace std;
class Solution {
public:


    vector<vector<int>> subsets(vector<int>& nums) {
           int n = nums.size();
   int subsets = 1<<n;
   vector<vector<int>> ans;

  

   for(int num =0; num < subsets ; num++){
     vector<int> list;
    for(int i =0; i<n; i++){
        if(num &( 1 << i)){
            list.push_back(nums[i]);
        }
    }
    ans.push_back(list);
   }
   return ans;
    }
};

int main() {
    // Input array
    vector<int> nums = {5, 7, 8};

    // Create object of Solution
    Solution obj;

    // Call function to generate subsets
    vector<vector<int>> subsets = obj.subsets(nums);

    // Print original input array
    cout << "Initial Input Array: ";
    for (auto num : nums) {
        cout << num << " ";
    }
    cout << endl;

    // Print all subsets
    cout << "Subsets: " << endl;
    for (auto subset : subsets) {
        cout << "[ ";
        for (auto num : subset) {
            cout << num << " ";
        }
        cout << "]" << endl;
    }

    return 0;
}