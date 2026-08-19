# 🧮 Introduction to Bit Manipulation

> A clean, interview-ready guide to bitwise operators, number representation, and the core bit-manipulation tricks every programmer should know.

Based on the concepts covered in [takeUforward — Introduction to Bit Manipulation (Theory)](https://takeuforward.org/data-structure/introduction-to-bit-manipulation-theory)

![Topic](https://img.shields.io/badge/Topic-DSA-blue)
![Level](https://img.shields.io/badge/Level-Beginner--Friendly-brightgreen)
![Language](https://img.shields.io/badge/Language-C%2B%2B%20%2F%20Java%20%2F%20Python-orange)

---

## 📖 Table of Contents

- [Why Learn Bit Manipulation?](#-why-learn-bit-manipulation)
- [Number Representation](#-number-representation)
- [Bitwise Operators](#-bitwise-operators)
  - [AND (&)](#and-)
  - [OR (|)](#or-)
  - [XOR (^)](#xor-)
  - [NOT (~)](#not-)
- [Shift Operators](#-shift-operators)
  - [Left Shift (`<<`)](#left-shift-)
  - [Right Shift (`>>`)](#right-shift-)
- [Signed vs Unsigned Numbers](#-signed-vs-unsigned-numbers)
- [Common Bit Tricks](#-common-bit-tricks)
- [Why Bit Manipulation Is Fast](#-why-bit-manipulation-is-fast)
- [Practice Problems](#-practice-problems)
- [Reference](#-reference)

---

## 🤔 Why Learn Bit Manipulation?

Every value stored in a computer is ultimately represented as a sequence of **bits** (0s and 1s). Bit manipulation lets you operate directly on these bits, which unlocks:

- ⚡ **Speed** — bitwise operations run in O(1) at the hardware level, much faster than loops or arithmetic in many cases.
- 💾 **Memory efficiency** — a single integer can store up to 32/64 boolean flags.
- 🎯 **Elegant solutions** — many DSA problems (subsets, unique elements, parity, power-of-two checks) collapse into a single line using bit tricks.
- 💼 **Interview relevance** — a recurring category in coding interviews (FAANG-style rounds especially).

---

## 🔢 Number Representation

A computer stores integers in **binary (base-2)** form. Each digit position represents a power of 2, counted from the right starting at index 0.

```
Decimal:  13
Binary:   1  1  0  1
Position: 3  2  1  0

13 = (1×2³) + (1×2²) + (0×2¹) + (1×2⁰)
   =   8    +   4    +   0    +   1
   =  13
```

| Term | Meaning |
|------|---------|
| **Bit** | A single binary digit (0 or 1) |
| **MSB** | Most Significant Bit — leftmost bit |
| **LSB** | Least Significant Bit — rightmost bit |
| **Set bit** | A bit with value 1 |
| **Unset/Clear bit** | A bit with value 0 |

---

## ⚙️ Bitwise Operators

These operators compare numbers **bit by bit**.

### AND (`&`)

Returns `1` only when **both** bits are `1`.

| A | B | A & B |
|---|---|-------|
| 0 | 0 | 0 |
| 0 | 1 | 0 |
| 1 | 0 | 0 |
| 1 | 1 | 1 |

```text
  1010   (10)
& 0110   (6)
------
  0010   (2)
```

**Use cases:** checking if a bit is set, clearing bits with a mask, checking if a number is even (`n & 1 == 0`).

### OR (`|`)

Returns `1` when **at least one** bit is `1`.

| A | B | A \| B |
|---|---|--------|
| 0 | 0 | 0 |
| 0 | 1 | 1 |
| 1 | 0 | 1 |
| 1 | 1 | 1 |

```text
  1010   (10)
| 0110   (6)
------
  1110   (14)
```

**Use cases:** setting a specific bit to 1, combining flags.

### XOR (`^`)

Returns `1` when the bits are **different**.

| A | B | A ^ B |
|---|---|-------|
| 0 | 0 | 0 |
| 0 | 1 | 1 |
| 1 | 0 | 1 |
| 1 | 1 | 0 |

```text
  1010   (10)
^ 0110   (6)
------
  1100   (12)
```

**Key properties:**
- `x ^ x = 0`
- `x ^ 0 = x`
- XOR is commutative & associative

**Use cases:** finding the unique element among duplicates, swapping two numbers without a temp variable, toggling bits.

### NOT (`~`)

A **unary** operator — flips every bit (0 → 1, 1 → 0). Also called **one's complement**.

```text
~ 0000 0101   (5)
------------
  1111 1010   (-6, in two's complement)
```

---

## ↔️ Shift Operators

### Left Shift (`<<`)

Shifts bits to the left, filling with `0`s on the right. Equivalent to **multiplying by 2ᵏ**.

```text
1 << 0 = 1
1 << 1 = 2
1 << 2 = 4
1 << 3 = 8
1 << n = 2ⁿ
```

```text
0101 << 1  →  1010    (5 → 10)
```

### Right Shift (`>>`)

Shifts bits to the right, discarding bits that fall off. Equivalent to **integer division by 2ᵏ**.

```text
0101 >> 1  →  0010    (5 → 2)
```

> ⚠️ For **negative/signed** numbers, right shift behavior depends on whether it's an *arithmetic* shift (preserves the sign bit) or a *logical* shift (fills with 0s). Most languages use arithmetic right shift (`>>`) for signed integers by default.

---

## 🔐 Signed vs Unsigned Numbers

Negative numbers are typically stored using **two's complement**:

```
-x  =  ~x + 1
```

```text
x  =  0000 0101   (5)
~x =  1111 1010
+1 =  1111 1011   (-5 in two's complement)
```

This representation makes addition/subtraction hardware simpler and ensures only one representation for zero.

---

## 🧠 Common Bit Tricks

| Goal | Expression | Explanation |
|------|-----------|-------------|
| Check if `i`-th bit is set | `(n >> i) & 1` | Shift target bit to LSB, mask with 1 |
| Set the `i`-th bit | `n \| (1 << i)` | OR with a mask having only bit `i` set |
| Clear the `i`-th bit | `n & ~(1 << i)` | AND with everything except bit `i` |
| Toggle the `i`-th bit | `n ^ (1 << i)` | XOR flips exactly that bit |
| Check even/odd | `n & 1` | `0` → even, `1` → odd |
| Check power of 2 | `n & (n - 1) == 0` | Powers of 2 have exactly one set bit |
| Clear lowest set bit | `n & (n - 1)` | Removes the rightmost `1` |
| Get lowest set bit | `n & (-n)` | Isolates the rightmost `1` |
| Count set bits | Brian Kernighan's algorithm | Repeatedly apply `n = n & (n - 1)` |
| Find the unique element | XOR all elements | Duplicate pairs cancel out to `0` |

**Example — Brian Kernighan's Algorithm (count set bits):**

```python
def count_set_bits(n):
    count = 0
    while n:
        n = n & (n - 1)   # clears the lowest set bit
        count += 1
    return count
```

---

## 🚀 Why Bit Manipulation Is Fast

Bitwise operations map directly to a **single CPU instruction**, unlike loops, conditionals, or arithmetic operations that may require multiple cycles. This is why:

- `n * 2` can be replaced with `n << 1`
- `n / 2` can be replaced with `n >> 1`
- Checking parity avoids the `%` (modulo) operator entirely

---

## 📝 Practice Problems

- Single Number (find the element that appears once)
- Number of 1 Bits (Hamming Weight)
- Power of Two / Power of Four
- Counting Bits (0 to n)
- Missing Number using XOR
- Subsets using bitmasking
- Swap two numbers without a temporary variable
- Reverse bits of a number

---

## 📚 Reference

- Original tutorial: [takeUforward — Introduction to Bit Manipulation (Theory)](https://takeuforward.org/data-structure/introduction-to-bit-manipulation-theory)

---

<p align="center">Made with ⚡ for anyone learning DSA & bit manipulation</p>