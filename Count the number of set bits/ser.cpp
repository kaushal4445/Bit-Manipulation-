#include<bits/stdc++.h>
using namespace std;
class Solution {
  public:
    int countSetBits(int n) {
        int count = 0;
        while(n > 0){
          n &= (n -1);
          count++;
        }
        return count;
       }
    
};
int main(){
  int n ;
  cout<<"Enter a number: ";
  cin>>n;
  Solution sol;
  int result = sol.countSetBits(n);
  cout<<"The number of set bits in "<<n<<" is: "<<result<<endl;
  return 0;
}
