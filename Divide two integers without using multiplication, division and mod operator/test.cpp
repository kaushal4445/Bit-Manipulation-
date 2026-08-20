#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int divide(int dividend, int divisor) {
       if(dividend == divisor) return 1;

       bool sign = true;
       if(dividend >= 0 && divisor < 0) 
         sign =  false;
         else if (dividend <= 0 && divisor > 0) 
         sign = false;

          // Convert to long long BEFORE abs()
        long long n = abs((long long)dividend);
        long long d = abs((long long)divisor);
        long  long quotient  =0;
         while(n >= d){
            int cnt =0;
            while(n >= (d << (cnt + 1))){
                cnt++;
            }
            quotient += 1<<cnt;
            n  = n-(d << cnt);

         }
         if(quotient == (1<<31) && sign){
         return INT_MAX;
         }
         if(quotient == (1<<31) && !sign){
            return INT_MIN;
         }
         return sign ? quotient : -quotient;
    }
};

int main() {

  //  int dividend = 10, divisor = 3;


    int dividend ;
    int divisor ;
    cout << "Enter the dividend: ";
    cin >> dividend;
    cout << "Enter the divisor: ";
    cin >> divisor;

    /* Creating an instance of 
    Solution class */
    Solution sol; 
    
    /* Function call to divide two numbers
    without multiplication and division */
    int ans = sol.divide(dividend, divisor);
    
    cout << "The result of dividing " << dividend << " and " << divisor << " is " << ans;
    
    return 0;
}




//Another Appoarch 

// class Solution {
// public:
//      int divide(int dividend, int divisor) {
        
       
//         if(dividend == divisor) return 1;
//         if(dividend == INT_MIN && divisor == -1) return INT_MAX;
//         if(divisor == 1) return dividend;
        
       
//         bool isPositive = true;
        
//         if(dividend >= 0 && divisor < 0) 
//             isPositive = false;
//         else if(dividend < 0 && divisor > 0)
//             isPositive = false;
            
      
//         long long n = dividend;
//         long long d = divisor;

//         n = abs(n);
//         d = abs(d);
     
//         long long ans = 0, sum = 0;
        
  
//         while(sum + d <= n) {
            
//             // Increment the count
//            ans++;
//            // Update the sum
//            sum += d;
//         }
        
       
//         if(ans > INT_MAX && isPositive) 
//             return INT_MAX;
//         if(ans > INT_MAX && !isPositive)
//             return INT_MIN;
        
        
//         return isPositive ? ans : -ans;
//     }
// };