# ➗ Divide Two Integers — Without `*`, `/`, or `%`

A clean C++ solution to the classic **LeetCode 29: Divide Two Integers** problem, solved using **bit manipulation (exponential search)**.

---

## 📌 Problem Statement

Given two integers `dividend` and `divisor`, divide them **without using** multiplication (`*`), division (`/`), or modulus (`%`) operators.

- Return the quotient after dividing `dividend` by `divisor`.
- The result must be **truncated toward zero** (i.e., `8.5 → 8`, `-8.5 → -8`).
- The result is bounded within the **32-bit signed integer range**: `[-2³¹, 2³¹ - 1]`.
  If the result overflows this range, return `INT_MAX` or `INT_MIN`.

**Example:**

```
Input:  dividend = 10, divisor = 3
Output: 3          (10 / 3 = 3.33 → truncated to 3)

Input:  dividend = 7, divisor = -3
Output: -2          (7 / -3 = -2.33 → truncated to -2)
```

---

## 🧠 The Core Idea

Since we can't use `/`, we simulate division the way **binary long division** works — by repeatedly subtracting the **largest possible multiple** of the divisor (found by left-shifting, i.e., multiplying by powers of 2) from the dividend.

> **Key trick:** `d << cnt` is the same as `d × 2^cnt`, but uses only bit shifting — no `*` or `/` needed!

### 🔍 Visual Diagram

Let's divide **43 ÷ 5**:

```
n = 43, d = 5

Step 1: Find the largest (d << cnt) that still fits in n
        5<<0=5   5<<1=10   5<<2=20   5<<3=40   5<<4=80(too big)
                                         ↑
                                  fits! cnt = 3

        quotient += (1 << 3) = 8
        n = 43 - 40 = 3

Step 2: n = 3, d = 5
        5<<0 = 5  → already bigger than n=3
        cnt = 0, but 5 > 3, so loop "while(n >= d)" stops here

Final:  quotient = 8, remainder = 3
        43 ÷ 5 = 8  ✅  (since 8×5=40, 9×5=45 > 43)
```

```
        43
       ────  →  subtract 40 (5 × 8)  →  remainder 3
        5              ↑
                 quotient so far = 8
                 (3 < 5, so we stop)
```

This is much faster than subtracting `5` one at a time (43 times) — instead we "leap" by powers of two, making it **O(log n × log n)** instead of **O(n)**.

---

## 🧩 Line-by-Line Code Explanation

```cpp
class Solution {
public:
    int divide(int dividend, int divisor) {
```
> Standard LeetCode function signature — takes two `int`s, returns an `int` quotient.

```cpp
       if(dividend == divisor) return 1;
```
> **Shortcut:** if both numbers are equal (e.g., `5 / 5` or `-7 / -7`), the answer is always `1`. Handles this instantly without running the main loop.

```cpp
       bool sign = true;
       if(dividend >= 0 && divisor < 0) 
         sign =  false;
         else if (dividend <= 0 && divisor > 0) 
         sign = false;
```
> Determines the **sign of the final answer**.
> - `sign = true` → result should be **positive**.
> - `sign = false` → result should be **negative**.
>
> Logic: if exactly one of `dividend`/`divisor` is negative (and the other non-negative), the quotient must be negative — so `sign` flips to `false`. All the math below works with **absolute values**, and this flag re-applies the correct sign at the end.

```cpp
        // Convert to long long BEFORE abs()
        long long n = abs((long long)dividend);
        long long d = abs((long long)divisor);
```
> **Critical overflow guard.** `INT_MIN` is `-2147483648`, but `INT_MAX` is only `2147483647`. So `abs(INT_MIN)` as an `int` would overflow!
> By casting to `long long` **first**, then taking `abs()`, we safely get `2147483648` without wraparound. `n` and `d` are now positive `long long` copies of the dividend/divisor.

```cpp
        long  long quotient  =0;
```
> Accumulator for the final answer, built up piece by piece.

```cpp
         while(n >= d){
```
> Main loop — keep subtracting chunks of `d` from `n` as long as `n` is still big enough to contain at least one more `d`.

```cpp
            int cnt =0;
            while(n >= (d << (cnt + 1))){
                cnt++;
            }
```
> **The "exponential leap" step.** Instead of finding just one `d`, we find the **largest power-of-2 multiple** of `d` that still fits inside `n`.
> - `d << (cnt+1)` means `d × 2^(cnt+1)`.
> - We keep incrementing `cnt` while doubling `d` still fits under `n`.
> - This is exactly what happened in the diagram above: `5, 10, 20, 40` all fit under `43`, but `80` doesn't — so `cnt` stops at `3`.

```cpp
            quotient += 1<<cnt;
```
> We just accounted for `2^cnt` copies of `d` inside `n`, so add `2^cnt` to the quotient. (In our example: `quotient += 8`.)

```cpp
            n  = n-(d << cnt);
```
> Subtract that large chunk (`d × 2^cnt`) from `n` in one shot, instead of subtracting `d` one at a time. (In our example: `43 - 40 = 3`.)

```cpp
         }
```
> End of the outer `while` loop. It repeats until `n < d`, meaning no more full copies of `d` remain — division is complete.

```cpp
         if(quotient == (1<<31) && sign){
         return INT_MAX;
         }
         if(quotient == (1<<31) && !sign){
            return INT_MIN;
         }
```
> **Overflow check.** The only case where the true quotient can exceed the 32-bit range is `INT_MIN / -1 = 2147483648`, which equals `1 << 31` here.
> - If the answer *should* be positive → clamp to `INT_MAX` (`2147483647`).
> - If the answer *should* be negative → it's exactly `INT_MIN` (`-2147483648`), which is valid, so return it directly.

```cpp
         return sign ? quotient : -quotient;
    }
};
```
> Finally, re-apply the sign we determined earlier:
> - `sign == true` → return `quotient` as-is (positive).
> - `sign == false` → return `-quotient` (negative).

---

## ⏱️ Complexity Analysis

| Metric | Complexity | Why |
|---|---|---|
| **Time** | `O(log n × log n)` | Outer loop runs ~`log(n/d)` times; inner loop doubles `d` each time, also `O(log n)` |
| **Space** | `O(1)` | Only a few extra variables (`n`, `d`, `quotient`, `cnt`) |

---

## ✅ Why This Approach Works Well

- 🚫 **No `*`, `/`, or `%`** — fully compliant with the problem's constraints.
- ⚡ **Fast** — uses bit-shifting to "jump" through large chunks instead of subtracting one at a time.
- 🛡️ **Overflow-safe** — carefully handles the `INT_MIN` edge case using `long long`.
- 🎯 **Correct sign & truncation** — sign tracked separately, and integer subtraction naturally truncates toward zero.

---

## 🧪 Sample Trace

| dividend | divisor | Output |
|---|---|---|
| 10 | 3 | 3 |
| 7 | -3 | -2 |
| 0 | 1 | 0 |
| -2147483648 | -1 | 2147483647 (`INT_MAX`, clamped) |
| -2147483648 | 1 | -2147483648 (`INT_MIN`) |