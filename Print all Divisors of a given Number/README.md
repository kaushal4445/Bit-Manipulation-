# Find All Divisors of a Number

A C++ solution that returns **all divisors of a number `n`**, sorted in ascending order — computed efficiently in **O(√n)** time instead of the naive O(n) approach.

---

## 📌 Problem

Given an integer `n`, return a list of all its divisors (numbers that divide `n` with no remainder), sorted in increasing order.

**Example:**
```
Input:  n = 36
Output: [1, 2, 3, 4, 6, 9, 12, 18, 36]
```

---

## 🧠 Core Idea

The naive approach checks every number from `1` to `n` — that's O(n) time.

The trick: **divisors always come in pairs**. If `i` divides `n`, then `n / i` also divides `n`.

```
n = 36

i = 1  →  36 / 1 = 36   →  pair (1, 36)
i = 2  →  36 / 2 = 18   →  pair (2, 18)
i = 3  →  36 / 3 = 12   →  pair (3, 12)
i = 4  →  36 / 4 = 9    →  pair (4, 9)
i = 6  →  36 / 6 = 6    →  pair (6, 6)  ← same number! (√36 = 6)
```

Notice that once `i` passes `√n` (which is 6 here), the pairs start **repeating in reverse**:
```
i = 9  → 36 / 9 = 4   (already found as pair of i=4)
i = 12 → 36 / 12 = 3  (already found as pair of i=3)
```

So we only need to loop `i` from `1` up to `√n`, and for each valid `i` we record **both** `i` and `n / i`.

### Visual: divisor pairs mirrored around √n

```
        1 ───────────────────────────── 36
          2 ───────────────────── 18
            3 ─────────────── 12
              4 ─────────── 9
                6 ─── 6   ← center point (√36)
        └──────────────┬──────────────┘
              loop only checks
              this half (i ≤ √n)
```

Every divisor less than `√n` is mirrored by a divisor greater than `√n`. That's why checking only up to `√n` is enough to find *all* of them.

---

## 🔍 Code Walkthrough

```cpp
vector<int> getDivisors(int n) {
    vector<int> res;

    for (int i = 1; i * i <= n; i++) {      // loop only up to √n
        if (n % i == 0) {                   // i divides n
            res.push_back(i);               // add smaller divisor
            if (i != n / i) {               // avoid duplicate when i == √n
                res.push_back(n / i);       // add its paired divisor
            }
        }
    }

    sort(res.begin(), res.end());           // arrange in increasing order
    return res;
}
```

| Line | What it does |
|---|---|
| `for (int i = 1; i * i <= n; i++)` | Loops `i` only while `i² ≤ n`, i.e. `i ≤ √n`. This is the key optimization. |
| `if (n % i == 0)` | Checks whether `i` is a divisor of `n`. |
| `res.push_back(i)` | `i` is a divisor — store it. |
| `if (i != n / i)` | Guards against adding the same number twice when `i` equals `n / i` (happens when `n` is a perfect square). |
| `res.push_back(n / i)` | Stores the "partner" divisor `n / i`. |
| `sort(res.begin(), res.end())` | Divisors are found out of order (small ones and large ones interleaved), so we sort at the end. |

---

## 🪜 Step-by-Step Trace (n = 36)

| `i` | `i*i ≤ 36`? | `36 % i == 0`? | Pushed to `res` |
|---|---|---|---|
| 1 | ✅ | ✅ | 1, 36 |
| 2 | ✅ | ✅ | 2, 18 |
| 3 | ✅ | ✅ | 3, 12 |
| 4 | ✅ | ✅ | 4, 9 |
| 5 | ✅ | ❌ | — |
| 6 | ✅ (6×6=36) | ✅ | 6 (only once, since 6 == 36/6) |
| 7 | ❌ (49 > 36) | — | loop stops |

**`res` before sorting:** `[1, 36, 2, 18, 3, 12, 4, 9, 6]`
**`res` after sorting:** `[1, 2, 3, 4, 6, 9, 12, 18, 36]` ✅

---

## 🧪 More Examples

```
n = 1    →  [1]
n = 7    →  [1, 7]                      (prime number → only 2 divisors)
n = 12   →  [1, 2, 3, 4, 6, 12]
n = 100  →  [1, 2, 4, 5, 10, 20, 25, 50, 100]
```

For `n = 100` (a perfect square, √100 = 10 exactly):
```
i = 10 → 100 / 10 = 10 → i == n/i → pushed only ONCE
```
This is exactly the case the `if (i != n / i)` check protects against.

---

## ⏱️ Complexity

| | Complexity | Why |
|---|---|---|
| **Time** | `O(√n log(√n))` ≈ `O(√n)` dominant, plus `O(d log d)` for sorting `d` divisors | Loop runs `√n` times; sorting the final (small) result list adds a minor overhead |
| **Space** | `O(d)` | where `d` = number of divisors of `n`, used to store the result |

Compare this to the brute-force approach of checking every number `1` to `n`, which is `O(n)` — for large `n` (e.g. 10⁹), `O(√n)` is dramatically faster (≈31,623 iterations vs 1,000,000,000).

---

## ✅ Summary

- Divisors come in **pairs** `(i, n/i)`.
- You only need to search up to `√n` to find every pair.
- Watch out for the special case where `i == n/i` (perfect squares) — don't double-count.
- Sort at the end since divisors are discovered out of order.
