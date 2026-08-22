# Pow(x, n) — Fast Power using Binary Exponentiation

A C++ solution that computes **x raised to the power n** (`xⁿ`) in **O(log n)** time instead of the naive O(n) approach of multiplying `x` by itself `n` times.

---

## 📌 Problem

Implement `pow(x, n)`, which calculates `x` raised to the power `n` (i.e., `xⁿ`).

**Example:**
```
Input:  x = 2.0, n = 10
Output: 1024.0

Input:  x = 2.0, n = -2
Output: 0.25   (= 1 / 2²)
```

---

## 🧠 Core Idea — Binary Exponentiation

The naive way multiplies `x` by itself `n` times:
```
x^10 = x * x * x * x * x * x * x * x * x * x     → 10 multiplications
```

The smart way: **halve the exponent every step**, and square `x` instead.

```
x^10 = (x²)^5
x^5  = x * (x²)^2
```

Every time `n` is **even**, we can just square `x` and halve `n` — the answer doesn't change:
```
x^n = (x²)^(n/2)        when n is even
```

Every time `n` is **odd**, we pull out one extra factor of `x`, then treat the rest as even:
```
x^n = x * (x²)^((n-1)/2)   when n is odd
```

This is exactly what recursion does, cutting `n` in half at every call → only `log₂(n)` steps.

### Visual: computing x^10

```
x^10
 └── n=10 is even → square x, halve n
     (x²)^5
      └── n=5 is odd → pull out one x
          x * (x²)^2
                └── n=2 is even → square (x²), halve n
                    x * ((x²)²)^1
                          └── n=1 is odd → pull out one x
                              x * x⁴ * ((x²)²)^0
                                            └── n=0 → base case, return 1
```

```
Step-by-step values:
n=10 ──(square, halve)──▶ n=5 ──(odd: extract x)──▶ n=2 ──(square, halve)──▶ n=1 ──(odd: extract x)──▶ n=0 (base case = 1)

Only 4 recursive calls instead of 10 multiplications!
```

Each level either **halves n (even case)** or **halves (n-1) (odd case)**, so the recursion depth is `O(log n)`.

---

## 🔍 Code Walkthrough

```cpp
double solve(double x, long long n) {

    if (n == 0)
        return 1;                          // base case: anything^0 = 1

    if (n < 0) {
        return solve(1 / x, -n);           // negative exponent → invert x, flip sign of n
    }

    if (n % 2 == 0) {
        return solve(x * x, n / 2);        // even exponent: square x, halve n
    }
    else {
        return x * solve(x * x, (n - 1) / 2);  // odd exponent: pull out one x, then recurse on even part
    }
}

double myPow(double x, int n) {
    return solve(x, (long long)n);         // cast n to long long BEFORE negating (see below)
}
```

| Part | Purpose |
|---|---|
| `if (n == 0) return 1;` | Base case — recursion must stop somewhere. `x⁰ = 1` always. |
| `if (n < 0) return solve(1/x, -n);` | Handles negative exponents: `x⁻ⁿ = (1/x)ⁿ`. Converts the problem into a positive-exponent one. |
| `if (n % 2 == 0)` | **Even case** — `xⁿ = (x²)^(n/2)`. No extra `x` needed. |
| `else` | **Odd case** — `xⁿ = x · (x²)^((n-1)/2)`. One factor of `x` is set aside since `n` can't be evenly halved. |
| `(long long)n` in `myPow` | **Critical detail** — see the "Why `long long`?" section below. |

---

## ⚠️ Why cast to `long long`?

`n` is an `int`, and `int` in C++ typically ranges from `-2,147,483,648` to `2,147,483,647`.

If `n = -2,147,483,648` (`INT_MIN`), then `-n` would try to become `2,147,483,648`, which **overflows** a 32-bit `int` (since the positive range only goes up to `2,147,483,647`). This is undefined behavior / a bug.

```
int n = INT_MIN;     // -2147483648
-n                    // ❌ overflow! max int is 2147483647

long long n = INT_MIN;
-n                    // ✅ fine, long long range is much bigger
```

That's why `myPow` casts `n` to `long long` **before** it's ever negated inside `solve`. This is a classic edge case in "power" problems.

---

## 🪜 Step-by-Step Trace (x = 2.0, n = 10)

| Call | n | n even/odd? | Action | Returns |
|---|---|---|---|---|
| `solve(2, 10)` | 10 | even | `solve(4, 5)` | `1024` |
| `solve(4, 5)` | 5 | odd | `4 * solve(16, 2)` | `4 * 256 = 1024` |
| `solve(16, 2)` | 2 | even | `solve(256, 1)` | `256` |
| `solve(256, 1)` | 1 | odd | `256 * solve(65536, 0)` | `256 * 1 = 256` |
| `solve(65536, 0)` | 0 | base case | `return 1` | `1` |

**Unwinding back up:**
```
solve(65536, 0)  = 1
solve(256, 1)    = 256 * 1        = 256
solve(16, 2)     = 256
solve(4, 5)      = 4 * 256        = 1024
solve(2, 10)     = 1024   ✅
```

---

## 🧪 More Examples

```
x = 2.0,  n = 10   →  1024.0
x = 2.1,  n = 3    →  9.261
x = 2.0,  n = -2   →  0.25         (negative exponent)
x = 0.0,  n = 5    →  0.0
x = 5.0,  n = 0    →  1.0          (base case)
```

**Negative exponent trace (x = 2.0, n = -2):**
```
solve(2, -2)
  n < 0 → solve(1/2, 2)
             n even → solve(0.25, 1)
                        n odd → 0.5 * solve(0.0625, 0)
                                            n==0 → return 1
                        = 0.5 * 1 = 0.5
             = 0.5
solve(2, -2) = 0.5 ... 

Wait — let's verify: 2^-2 = 1/4 = 0.25
```
```
Actual trace:
solve(2, -2)
  → solve(0.5, 2)                 [1/x, -n]
      → solve(0.25, 1)            [x*x, n/2]  since 2 is even
          → 0.25 * solve(0.0625, 0)   [x*x, (n-1)/2] since 1 is odd
              → 0.0625's call returns 1 (base case)
          → 0.25 * 1 = 0.25
      → 0.25
  → 0.25   ✅ matches 2^-2 = 0.25
```

---

## ⏱️ Complexity

| | Complexity | Why |
|---|---|---|
| **Time** | `O(log n)` | The exponent is halved at every recursive call |
| **Space** | `O(log n)` | Due to the recursion call stack (each call adds a stack frame) |

Compare to the brute-force loop `result *= x` repeated `n` times, which is `O(n)`. For `n = 2³¹`, that's the difference between ~31 steps and over 2 billion steps.

---

## ✅ Summary

- **Even exponent:** square `x`, halve `n` → `xⁿ = (x²)^(n/2)`
- **Odd exponent:** pull out one `x`, then treat the rest as even → `xⁿ = x · (x²)^((n-1)/2)`
- **Negative exponent:** invert `x`, flip the sign of `n` → `xⁿ = (1/x)⁻ⁿ`
- **Base case:** `x⁰ = 1`
- Always cast `n` to a wider type (`long long`) before negating, to avoid `INT_MIN` overflow.
- This technique is called **binary exponentiation** (or "fast power") and runs in `O(log n)` instead of `O(n)`.