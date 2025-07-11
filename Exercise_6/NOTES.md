# Exercise 6


## 1.

$A, B, C = 1$

and 

$D = 0$


## 2.

Prerequisites:

- n depends on n-1: this is the case after the rewrite.
- the sucessor function is associative (yes it is associative, not commutative) also it is integers and not floating points.

## 3.


From Fibonacci.cxx
```c++
class FiboMatrix {
    using Int_t = uint64_t;
    // Task 3: Fill in the matrix that computes the two next Fibonacci numbers:
    Int_t matrix[2][2] = {{1,1},
                          {1,0}};
  ...
};
```
