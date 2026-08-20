# Minimum Bit Flips

Count the minimum number of bit flips required to convert an integer `start` into an integer `goal`.

## Problem

A **bit flip** of a number `x` is choosing a bit in the binary representation of `x` and flipping it (0 → 1 or 1 → 0).

Given two integers `start` and `goal`, return the minimum number of bit flips to convert `start` to `goal`.

## Code

```cpp
class Solution {
public:
    int minBitFlips(int start, int goal) {
        int ans = start ^ goal;
        int cnt = 0;
        for (int i = 0; i < 31; i++) {
            if (ans & (1 << i)) {
                cnt = cnt + 1;
            }
        }
        return cnt;
    }
};
```

## Key Idea

Two numbers differ in exactly the bit positions where their binary representations disagree.

The **XOR (`^`)** operator gives a `1` in every position where `start` and `goal` differ, and a `0` where they are the same:

```
start = 10 (bit 1, matches)
goal  = 20 (bit 0, differs)
------------------------
XOR   = 1  (bit set → flip needed)
```

So the answer to "how many bits must I flip?" is simply:

**count the number of `1` bits in `(start ^ goal)`**

## Step-by-step Diagram

Example: `start = 10`, `goal = 7`

```
start = 10  →  0 1 0 1 0
goal  =  7  →  0 0 1 1 1
                -----------
XOR result  →  0 1 1 0 1     (start ^ goal)
```

Reading the bits (from bit 4 down to bit 0):

```
Bit position :   4   3   2   1   0
start        :   0   1   0   1   0
goal         :   0   0   1   1   1
                 --- --- --- --- ---
XOR (differs):   0   1   1   0   1
                     ↑   ↑       ↑
                  differ differ differ
```

There are **3 positions** where the bits differ → `minBitFlips = 3`.

### Visual Flip Trace

```
   start:  0 1 0 1 0
             │       (bit 3: 1→0)  flip
             ▼
            0 0 0 1 0
                 │   (bit 2: 0→1)  flip
                 ▼
            0 0 1 1 0
                     │ (bit 0: 0→1)  flip
                     ▼
            0 0 1 1 1  =  goal (7)
```

3 flips transform `start` into `goal`, matching the XOR bit-count.

## How the Code Works

| Step | Code | Purpose |
|------|------|---------|
| 1 | `int ans = start ^ goal;` | Marks every differing bit position with a `1` |
| 2 | `for (int i = 0; i < 31; i++)` | Scans all 31 possible bit positions of an `int` |
| 3 | `if (ans & (1 << i))` | Checks whether bit `i` of `ans` is set |
| 4 | `cnt = cnt + 1;` | Counts each set bit — i.e., each required flip |
| 5 | `return cnt;` | Total number of bit flips needed |

## Complexity

| Metric | Value |
|--------|-------|
| Time   | O(1) — fixed 31 iterations, independent of input size |
| Space  | O(1) — only a few integer variables used |

## Example Runs

```
Input:  start = 10, goal = 7
Output: 3

Input:  start = 3, goal = 4
        start = 011
        goal  = 100
        XOR   = 111  → 3 bits differ
Output: 3
```
