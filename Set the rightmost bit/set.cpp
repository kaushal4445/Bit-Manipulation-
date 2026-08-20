#include<bits/stdc++.h>
using namespace std;
class Solution {
  public:
  int setrightbit(int n){
    return n |(n +1);
  }

};
int main(){
  int n ;
  cout<<"Enter a number: ";
  cin>>n;
 Solution sol;
  int result = sol.setrightbit(n);
  cout <<"The number after setting the rightmost unset bit of " <<n<<" is: "<<result<<endl;
  return 0;
}
