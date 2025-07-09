# 5.1.1

```sh
(gdb) run
The program being debugged has been started already.
Start it from the beginning? (y or n) y
Starting program: /eos/home-a/alsundai/Code/CSC2025-manycores/Exercise_5/example1
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib64/libthread_db.so.1".

Breakpoint 1, main () at example1.cpp:10
10        std::atomic<int> counter{0};
(gdb) watch -l counter
Hardware watchpoint 5: -location counter
(gdb) continue
Continuing.

Hardware watchpoint 5: -location counter

Old value = {<std::__atomic_base<int>> = {static _S_alignment = 4, _M_i = 32767}, static is_always_lock_free = true}
New value = {<std::__atomic_base<int>> = {static _S_alignment = 4, _M_i = 0}, static is_always_lock_free = true}
main () at example1.cpp:16
16        };
(gdb) continue
Continuing.
[New Thread 0x7ffff77ff640 (LWP 4106986)]
[New Thread 0x7ffff6ffe640 (LWP 4106987)]
[Switching to Thread 0x7ffff77ff640 (LWP 4106986)]

Thread 2 "example1" hit Hardware watchpoint 5: -location counter

Old value = {<std::__atomic_base<int>> = {static _S_alignment = 4, _M_i = 0}, static is_always_lock_free = true}
New value = {<std::__atomic_base<int>> = {static _S_alignment = 4, _M_i = 1}, static is_always_lock_free = true}
0x00000000004018b5 in std::__atomic_base<int>::operator++ (this=0x7fffffffd764)
    at /usr/include/c++/11/bits/atomic_base.h:385
385           { return __atomic_add_fetch(&_M_i, 1, int(memory_order_seq_cst)); }
(gdb) disass /m
Dump of assembler code for function _ZNSt13__atomic_baseIiEppEv:
384           operator++() noexcept
   0x00000000004018a0 <+0>:     push   %rbp
   0x00000000004018a1 <+1>:     mov    %rsp,%rbp
   0x00000000004018a4 <+4>:     mov    %rdi,-0x8(%rbp)

385           { return __atomic_add_fetch(&_M_i, 1, int(memory_order_seq_cst)); }
   0x00000000004018a8 <+8>:     mov    -0x8(%rbp),%rdx
   0x00000000004018ac <+12>:    mov    $0x1,%eax
   0x00000000004018b1 <+17>:    lock xadd %eax,(%rdx)
=> 0x00000000004018b5 <+21>:    add    $0x1,%eax
   0x00000000004018b8 <+24>:    pop    %rbp
   0x00000000004018b9 <+25>:    ret

End of assembler dump.
(gdb)
```