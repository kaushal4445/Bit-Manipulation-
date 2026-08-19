#include <bits/stdc++.h>
using namespace std;

// Function to swap using XOR bit manipulation
void swapXOR(int &a, int &b) {
    
    a = a ^ b;

   
    b = a ^ b;

    
    a = a ^ b;
}

int main() {
    int a = 5, b = 10;

    // Call the swap function
    swapXOR(a, b);

    // Print the result after swapping
    cout << "a = " << a << ", b = " << b << endl;

    return 0;
}