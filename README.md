# Comparing Left Shift By One Vs Multiplication By Two

A best effort empirical comparison of using left shift verses multiplication by two.

This repository contains two programs. One is for testing on X86-64 platforms. The other is for
testing on ARM64 platforms. The code uses inline assembly to force usage of specific instructions
so that the compiler doesn't "cheat" by substituting different code. That is, a compiler may
decide that it will use a right shift by one operation instead of a multiplication by two. That
would spoil the point of this test.

## Compilation

Using Clang, I used the following compile instructions:

```bash
c++ -std=c++20 -o ShiftVMul_arm64 ShiftVMul_arm64.cpp
```

This is for the ARM64 version. The x86-64 version should be compiled the same way. The use of the asm
keyword requires compiling the appropriate program on your architecture. If you are using GCC for your compiler,
simply use gcc instead of c++.

## My Results

On my hardware, the difference is small. However, the multiply by two is generally a tiny bit faster.
This means you can write your code in a more natural, readable fashion without worrying about that
last bit of performance.

Use:

```
x = y * 2;
```

Instead of:

```
x = y << 1;
```

When you mean multiplication.



