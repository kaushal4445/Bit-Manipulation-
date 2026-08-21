#include<bits/stdc++.h>
#include<vector>
using namespace std;
class Solution {
public:
    int singleNumber(vector<int>& nums) {
      int ones =0;
      int twos = 0;
      int n = nums.size();
      for (int i =0; i< n ; i++){
        ones = (ones ^ nums[i] & ~ twos);
         twos = (twos ^ nums[i] & ~ ones);

      }
      return ones;
    }
};
int main() {

    int n;
    Solution sol;
    cout << "Enter the size of array: ";
    cin >> n;

    vector<int> nums(n);

    cout << "Enter " << n << " elements: ";

    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    int answer = sol.singleNumber(nums);

    cout << "The single number is: " << answer << endl;

    return 0;
}


//Another appoarch 
// class Solution {
// public:
//     int singleNumber(vector<int>& nums) {
//       sort(nums.begin(), nums.end());
//       int n = nums.size();
//       for(int i = 1; i< n; i = i +3){
//         if(nums[i] != nums[i -1])
//         return nums[i - 1];
//       }
//       return nums[n - 1];
//     }
// };





//Another approach
// class Solution {
// public:
//     int singleNumber(vector<int>& nums) {
//         int n = nums.size();

//         unordered_map<int, int> mpp;

//         // Count frequency of every number
//         for (int i = 0; i < n; i++) {
//             mpp[nums[i]]++;
//         }

//         // Find the number appearing once
//         for (auto it : mpp) {
//             if (it.second == 1) {
//                 return it.first;
//             }
//         }

//         return -1;
//     }
// };