# 🔢 Set Rightmost Unset Bit

A tiny, elegant C++ bit-manipulation trick that flips the **rightmost `0` bit** of an integer to `1` — in a single line, without loops.

```cpp
n | (n + 1)
```

---

## 📖 Table of Contents

- [How it works](#-how-it-works)
- [Step-by-step example](#-step-by-step-example-n--10)
- [Code](#-code)
- [Build & run](#-build--run)
- [More examples](#-more-examples)
- [Complexity](#-complexity)
- [Edge cases](#-edge-cases)

---

## ⚙️ How it works

Adding `1` to a binary number always does the same thing:

1. Every **trailing `1`** flips to `0` (the carry propagates through them).
2. The **first `0`** it hits from the right flips to `1` (the carry stops here).

So in `n + 1`, there is now a guaranteed `1` sitting exactly where `n`'s rightmost `0` used to be.

OR-ing `n` with `n + 1` merges the two:
- Bits that were already `1` in `n` **stay `1`**.
- The one bit that flipped in `n + 1` **becomes `1`** in the result.
- Every bit to the left of that point is untouched (both numbers agree there).

That's the whole trick — one bitwise OR, no loops, no branching.

---

## 🧮 Step-by-step example (`n = 10`)

| Step | Binary | Decimal |
|---|:---:|:---:|
| `n` | `1010` | 10 |
| `n + 1` | `1011` | 11 |
| `n \| (n + 1)` | `1011` | **11** |

```
   n        = 1 0 1 0
   n + 1    = 1 0 1 1      <- rightmost 0 became 1
 -------------------------
   n | n+1  = 1 0 1 1      <- result: 11
                     ↑
              rightmost unset bit is now set
```

Bit weights, left to right: `8 4 2 1`. The `1`-weight bit was the rightmost `0` in `n`, and it's the one that flips.

---

## 💻 Code

```cpp
#include <bits/stdc++.h>
using namespace std;

// Function to set the rightmost unset bit (0 -> 1)
int setRightmostUnsetBit(int n) {
    // Use bitwise OR with n+1 to set rightmost 0
    return n | (n + 1);
}

int main() {
    // Sample input
    int n = 10; // binary: 1010

    // Call function
    int result = setRightmostUnsetBit(n);

    // Print output
    cout << "Number after setting rightmost unset bit: " << result << endl; // Output: 11

    return 0;
}
```

---

## 🚀 Build & run

```bash
g++ -std=c++17 -O2 -o set_bit set_bit.cpp
./set_bit
```

**Expected output:**
```
Number after setting rightmost unset bit: 11
```

---

## 🔍 More examples

| `n` | Binary | Result | Binary | Explanation |
|:---:|:---:|:---:|:---:|---|
| `5` | `0101` | `7` | `0111` | Rightmost `0` (weight 2) flips |
| `10` | `1010` | `11` | `1011` | Rightmost `0` (weight 1) flips |
| `7` | `0111` | `15` | `1111` | Rightmost `0` (weight 8) flips |
| `0` | `0000` | `1` | `0001` | First bit gets set |
| `-1` (all bits set) | `...1111` | `-1` | `...1111` | No unset bit exists → unchanged |

---

## ⏱️ Complexity

| | Value |
|---|---|
| Time | `O(1)` — one addition, one OR |
| Space | `O(1)` |

No loops are needed because addition's carry propagation *is* the search for the rightmost `0` — the hardware does the scanning for you.

---

## ⚠️ Edge cases

- **`n = -1`** (all bits set in two's complement): there is no unset bit, so `n + 1` overflows to `0` and `n | (n+1)` just returns `n` unchanged.
- **Very large `n`** near `INT_MAX`: `n + 1` can overflow a 32-bit `int`. Use `unsigned int` or `long long` if you need to handle that safely.

---

<p align="center">Made with 🧠 and a bit of bit-twiddling</p>