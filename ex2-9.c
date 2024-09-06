/* In the two's complement number system, the bitwise operation `x &= (x - 1)` has a useful property: it removes the rightmost 1-bit from the integer `x`. Let's break down why this happens and then use this observation to write a more efficient version of the `bitcount` function.

### Why `x &= (x - 1)` Removes the Rightmost 1-Bit

Consider an integer `x` in its binary representation. When you subtract 1 from `x`, the rightmost 1-bit and all the 0-bits to its right flip:

- **Original value of x**: Suppose `x` has a rightmost 1-bit at position `k`, and all bits to the right are 0. The bits to the left of position `k` (including `k`) are unaffected by the subtraction.

  ```
  x:      ... 0001 0000
  x - 1:  ... 0000 1111
  ```

  In this example, the subtraction flips the rightmost 1-bit and all the bits to its right from 0 to 1.

- **Bitwise AND operation**: Now, if you perform `x &= (x - 1)`, the result is a bit pattern where the rightmost 1-bit is removed:

  ```
  x:      ... 0001 0000
  x - 1:  ... 0000 1111
  x & (x - 1): ... 0000 0000
  ```

  The rightmost 1-bit and all the bits to its right have been set to 0, effectively removing the rightmost 1-bit.

### Faster Version of `bitcount`

The provided `bitcount` function counts the number of 1-bits in an integer using a loop that checks each bit individually. This can be optimized by using the property discussed above. Here's a faster version of `bitcount`:

```
*/
/* bitcount: count 1 bits in x */
int bitcount(unsigned x) {
    int b = 0;
    while (x) {
        x &= (x - 1);  // Remove the rightmost 1-bit
        b++;
    }
    return b;
}


//

//### Explanation

//- **Initialization**: `b` is initialized to 0. It will keep track of the number of 1-bits.
//- **Loop**: The loop continues until `x` becomes 0.
//  - Inside the loop, `x &= (x - 1)` removes the rightmost 1-bit from `x`.
//  - Each time a rightmost 1-bit is removed, the count `b` is incremented.
//- **Termination**: When `x` becomes 0, all 1-bits have been counted, and the function returns the count.

//### Efficiency

//This version of `bitcount` is more efficient than the original version because it performs a constant-time operation inside the loop (`x &= (x - 1)`) rather than shifting and masking every bit of the integer. The number of iterations of the loop is proportional to the number of 1-bits in `x`, making it faster in practice for large numbers.
