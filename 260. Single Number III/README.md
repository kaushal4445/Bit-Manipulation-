# 🔢 Single Number III — XOR Partitioning Solution

> **LeetCode 260** — Given an integer array `nums` where **exactly two elements** appear only **once** and all other elements appear **exactly twice**, find the two elements that appear once.
>
> Must run in **O(n) time** and **O(1) extra space**.

```cpp
class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        int n = nums.size();
        long XOR = 0;
        for (int i = 0; i < n; i++) {
            XOR = XOR ^ nums[i];
        }
        int rightmost = XOR & (XOR - 1) ^ XOR;
        int bucket1 = 0;
        int bucket2 = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i] & rightmost) {
                bucket1 = bucket1 ^ nums[i];
            } else {
                bucket2 = bucket2 ^ nums[i];
            }
        }
        if (bucket1 > bucket2)
            return {bucket2, bucket1};
        else
            return {bucket1, bucket2};
    }
};
```

---

## 💡 The Core Idea

We already know the classic trick: `x ^ x = 0`, so XOR-ing an array where **everything appears twice except one number** leaves you with that one number.

Here we have **two** unique numbers, `a` and `b`, mixed in with pairs. If we XOR the whole array, all the pairs vanish and we're left with:

```
XOR_total = a ^ b
```

The problem: `a` and `b` are tangled together in a single value. We need a way to **split the array into two buckets** — one containing `a` (and all pairs that share a certain bit), the other containing `b` — so that XOR-ing each bucket separately isolates them.

---

## 🧩 Step-by-Step Pipeline

```
 ┌───────────────┐     ┌────────────────────┐     ┌───────────────────┐     ┌───────────────────┐
 │  XOR everything │ →  │ Isolate rightmost   │ →  │ Split nums into    │ →  │ XOR each bucket    │
 │  → get a ^ b    │    │ set bit of (a^b)    │    │ two buckets by     │    │ separately → a, b  │
 │                │     │ (a bit where a,b    │    │ that bit           │    │                    │
 │                │     │ differ)             │    │                    │    │                    │
 └───────────────┘     └────────────────────┘     └───────────────────┘     └───────────────────┘
```

---

## 🔍 Why This Works — Bit-Level Intuition

Since `a ≠ b`, `a ^ b` is **not zero**, meaning at least one bit differs between them:

```
   a  =  0 1 1          (example: 3)
   b  =  1 0 1          (example: 5)
 a^b  =  1 1 0          (differs at bit 2 and bit 1)
```

Any bit that is `1` in `a ^ b` is a bit where **exactly one** of `a`/`b` has a `1` and the other has a `0`. We only need **one** such bit — the code picks the **rightmost set bit**:

```cpp
rightmost = XOR & (XOR - 1) ^ XOR;
```

### How `rightmost` isolates one bit

```
        XOR        =  0 1 1 0
      XOR - 1       =  0 1 0 1     (flips everything after & including rightmost set bit)
 XOR & (XOR - 1)     =  0 1 0 0     (clears the rightmost set bit only)
      ^ XOR          =  0 0 1 0     (XOR with original → leaves ONLY that cleared bit set)
                    -----------
              rightmost = 0 0 1 0   ✅ single isolated bit
```

---

## 🗂️ Splitting Into Two Buckets

Now walk through the array again. For each number, check whether the `rightmost` bit is set:

```
                    rightmost bit set?
                   ┌───────────┴───────────┐
                  YES                       NO
                   │                         │
             ┌─────▼─────┐            ┌─────▼─────┐
             │  bucket1   │            │  bucket2   │
             │  (has a    │            │  (has the  │
             │  or b)     │            │  other)    │
             └────────────┘            └────────────┘
```

Because duplicate pairs always have **identical bits**, both copies of any repeated number land in the **same bucket** and cancel out via XOR. But `a` and `b` differ at this bit, so they're **guaranteed to land in different buckets** — never together!

```
 Duplicate pair "2, 2":  both have same bit → both in bucket1 (or both bucket2) → cancel to 0
 Unique "a":              bit = 1 → bucket1
 Unique "b":              bit = 0 → bucket2
```

---

## 🧪 Full Walkthrough Example

`nums = [1, 2, 1, 3, 2, 5]`  (unique numbers are `3` and `5`)

**Step 1 — XOR everything:**

```
 1 ^ 2 ^ 1 ^ 3 ^ 2 ^ 5
 = (1^1) ^ (2^2) ^ 3 ^ 5      ← pairs cancel
 =    0  ^    0  ^ 3 ^ 5
 = 3 ^ 5
 = 011 ^ 101
 = 110   →  XOR_total = 6
```

**Step 2 — isolate rightmost set bit of `110`:**

```
 XOR      = 1 1 0
 XOR - 1  = 1 0 1
 AND      = 1 0 0
 XOR orig = 0 1 0   → rightmost = 2 (binary 010)
```

**Step 3 — split every number using bit `010`:**

| num | binary | `num & 010` | bucket |
|:---:|:---:|:---:|:---:|
| 1 | 001 | 0 | bucket2 |
| 2 | 010 | 2 | bucket1 |
| 1 | 001 | 0 | bucket2 |
| 3 | 011 | 2 | bucket1 |
| 2 | 010 | 2 | bucket1 |
| 5 | 101 | 0 | bucket2 |

```
 bucket1 = 2 ^ 3 ^ 2 = 3     ✅
 bucket2 = 1 ^ 1 ^ 5 = 5     ✅
```

**Result → `[3, 5]`** 🎯 — the two duplicate 1's and 2's cancelled out perfectly inside their buckets, leaving each unique number isolated.

---

## 📊 Visual Summary

```
   nums: [1, 2, 1, 3, 2, 5]
             │
             ▼
     XOR all → 6 (110)
             │
             ▼
   isolate rightmost bit → 2 (010)
             │
      ┌──────┴──────┐
      ▼             ▼
  bit set?        bit clear?
  {2, 3, 2}        {1, 1, 5}
      │             │
   XOR → 3        XOR → 5
      │             │
      └──────┬──────┘
             ▼
        return [3, 5]
```

---

## ⚙️ Complexity

| Metric | Value |
|---|:---:|
| Time | **O(n)** — two linear passes |
| Space | **O(1)** — constant number of variables |

---

## 📌 Key Takeaways

- XOR cancels pairs, so the whole-array XOR gives you `a ^ b`.
- Any **set bit** in `a ^ b` marks a position where `a` and `b` differ — perfect for splitting them apart.
- Isolating the **rightmost set bit** with `x & (x - 1) ^ x` is a classic bit trick worth memorizing.
- Splitting by that bit guarantees duplicates stay together (and cancel) while `a` and `b` land in separate buckets.