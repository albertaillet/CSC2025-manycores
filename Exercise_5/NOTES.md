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


# 5.1.2

```sh
[alsundai@lxplus9108 Exercise_5]$ gdb ./example2
GNU gdb (Red Hat Enterprise Linux) 14.2-4.1.el9_6
Copyright (C) 2023 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-redhat-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<https://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word"...
tbreak example2.cpp:21Reading symbols from ./example2...
(gdb) tbreak example2.cpp:21
Temporary breakpoint 1 at 0x401255: file example2.cpp, line 21.
(gdb) run
Starting program: /eos/home-a/alsundai/Code/CSC2025-manycores/Exercise_5/example2
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib64/libthread_db.so.1".

Temporary breakpoint 1, main () at example2.cpp:21
21        int counter{0};
Missing separate debuginfos, use: dnf debuginfo-install glibc-2.34-168.el9_6.20.x86_64 libgcc-11.5.0-5.el9_5.x86_64 libstdc++-11.5.0-5.el9_5.x86_64
(gdb) watch -l counter
Hardware watchpoint 2: -location counter
(gdb) run
The program being debugged has been started already.
Start it from the beginning? (y or n) Quit
(gdb) continue
Continuing.

Hardware watchpoint 2: -location counter

Old value = 32767
New value = 0
main () at example2.cpp:23
23        std::thread increment1{incrementCounter, &counter, 100000};
(gdb) c
Continuing.
[New Thread 0x7ffff77ff640 (LWP 186498)]
[New Thread 0x7ffff6ffe640 (LWP 186499)]
[Switching to Thread 0x7ffff77ff640 (LWP 186498)]

Thread 2 "example2" hit Hardware watchpoint 2: -location counter

Old value = 0
New value = 2
incrementCounter (counter=0x7fffffffd74c, times=100000) at example2.cpp:9
9         for (unsigned int i = 0; i < times; ++i) {
(gdb) c
Continuing.
[Switching to Thread 0x7ffff6ffe640 (LWP 186499)]

Thread 3 "example2" hit Hardware watchpoint 2: -location counter

Old value = 2
New value = 3
anotherIncrementCounter (c=0x7fffffffd74c, times=1000000000) at example2.cpp:15
15        for (unsigned int i = 0; i < times; ++i) {
(gdb) c
Continuing.

Thread 3 "example2" hit Hardware watchpoint 2: -location counter

Old value = 3
New value = 5
anotherIncrementCounter (c=0x7fffffffd74c, times=1000000000) at example2.cpp:15
15        for (unsigned int i = 0; i < times; ++i) {
(gdb) c
Continuing.

Thread 3 "example2" hit Hardware watchpoint 2: -location counter

Old value = 5
New value = 7
```


# 5.1.3

```sh
[alsundai@lxplus9108 Exercise_5]$ gdb ./example3
GNU gdb (Red Hat Enterprise Linux) 14.2-4.1.el9_6
Copyright (C) 2023 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-redhat-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<https://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from ./example3...
(reverse-i-search)`': Quit
(gdb) set mi-async on
(gdb) set non-stop on
(gdb) tbreak 16
Temporary breakpoint 1 at 0x40121f: file example3.cpp, line 16.
(gdb) run
Starting program: /eos/home-a/alsundai/Code/CSC2025-manycores/Exercise_5/example3
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib64/libthread_db.so.1".
[New Thread 0x7ffff77ff640 (LWP 220385)]
[New Thread 0x7ffff6ffe640 (LWP 220386)]

Thread 2 "example3" hit Temporary breakpoint 1, operator() (__closure=0x416ec0,
    nTimes=100000) at example3.cpp:16
16            ++counter;
Missing separate debuginfos, use: dnf debuginfo-install glibc-2.34-168.el9_6.20.x86_64 libgcc-11.5.0-5.el9_5.x86_64 libstdc++-11.5.0-5.el9_5.x86_64
(gdb) info thr
  Id   Target Id                                     Frame
* 1    Thread 0x7ffff7ea91c0 (LWP 220382) "example3" (running)
  2    Thread 0x7ffff77ff640 (LWP 220385) "example3" operator() (__closure=0x416ec0,
    nTimes=100000) at example3.cpp:16
  3    Thread 0x7ffff6ffe640 (LWP 220386) "example3" (running)
(gdb) thread 2
[Switching to thread 2 (Thread 0x7ffff77ff640 (LWP 220385))]
#0  operator() (__closure=0x416ec0, nTimes=100000) at example3.cpp:16
16            ++counter;
(gdb) p counter
$1 = (std::atomic_uint &) @0x7fffffffd764: {<std::__atomic_base<unsigned int>> = {
    static _S_alignment = 4, _M_i = 146305}, static is_always_lock_free = true}
(gdb) p counter
$2 = (std::atomic_uint &) @0x7fffffffd764: {<std::__atomic_base<unsigned int>> = {
    static _S_alignment = 4, _M_i = 175145}, static is_always_lock_free = true}
(gdb) p counter
$3 = (std::atomic_uint &) @0x7fffffffd764: {<std::__atomic_base<unsigned int>> = {
    static _S_alignment = 4, _M_i = 204020}, static is_always_lock_free = true}
(gdb) p counter
$4 = (std::atomic_uint &) @0x7fffffffd764: {<std::__atomic_base<unsigned int>> = {
    static _S_alignment = 4, _M_i = 222725}, static is_always_lock_free = true}
(gdb) p counter
$5 = (std::atomic_uint &) @0x7fffffffd764: {<std::__atomic_base<unsigned int>> = {
    static _S_alignment = 4, _M_i = 230328}, static is_always_lock_free = true}
(gdb) p counter
$6 = (std::atomic_uint &) @0x7fffffffd764: {<std::__atomic_base<unsigned int>> = {
    static _S_alignment = 4, _M_i = 239482}, static is_always_lock_free = true}
(gdb) p counter
$7 = (std::atomic_uint &) @0x7fffffffd764: {<std::__atomic_base<unsigned int>> = {
    static _S_alignment = 4, _M_i = 245229}, static is_always_lock_free = true}
(gdb) p coun
```


# 5.2
difference between with `-g` and without:

```sh
diff --git a/tmp.txt b/tmp_with_g.txt
index 9732241..8745449 100644
--- a/tmp.txt
+++ b/tmp_with_g.txt
@@ -1,74 +1,74 @@
 ==================
-WARNING: ThreadSanitizer: data race (pid=227758)
-  Read of size 4 at 0x7ffd015b6bfc by thread T2:
-    #0 anotherIncrementCounter(int*, unsigned int) <null> (example2+0x4012ca) (BuildId: 1339b4ce7e1658b4e5515e5fa8dfef740334bf7e)
-    #1 void std::__invoke_impl<void, void (*)(int*, unsigned int), int*, int>(std::__invoke_other, void (*&&)(int*, unsigned int), int*&&, int&&) <null> (example2+0x4023f1) (BuildId: 1339b4ce7e1658b4e5515e5fa8dfef740334bf7e)
-    #2 std::__invoke_result<void (*)(int*, unsigned int), int*, int>::type std::__invoke<void (*)(int*, unsigned int), int*, int>(void (*&&)(int*, unsigned int), int*&&, int&&) <null> (example2+0x40229c) (BuildId: 1339b4ce7e1658b4e5515e5fa8dfef740334bf7e)
-    #3 void std::thread::_Invoker<std::tuple<void (*)(int*, unsigned int), int*, int> >::_M_invoke<0ul, 1ul, 2ul>(std::_Index_tuple<0ul, 1ul, 2ul>) <null> (example2+0x402152) (BuildId: 1339b4ce7e1658b4e5515e5fa8dfef740334bf7e)
-    #4 std::thread::_Invoker<std::tuple<void (*)(int*, unsigned int), int*, int> >::operator()() <null> (example2+0x4020c6) (BuildId: 1339b4ce7e1658b4e5515e5fa8dfef740334bf7e)
-    #5 std::thread::_State_impl<std::thread::_Invoker<std::tuple<void (*)(int*, unsigned int), int*, int> > >::_M_run() <null> (example2+0x402080) (BuildId: 1339b4ce7e1658b4e5515e5fa8dfef740334bf7e)
+WARNING: ThreadSanitizer: data race (pid=228077)
+  Read of size 4 at 0x7ffdb70d03bc by thread T2:
+    #0 anotherIncrementCounter(int*, unsigned int) /eos/user/a/alsundai/Code/CSC2025-manycores/Exercise_5/example2.cpp:16 (example2+0x4012ca) (BuildId: 63ed59f82c0e3abb59e80f25d27da9dc9b11db1f)
+    #1 void std::__invoke_impl<void, void (*)(int*, unsigned int), int*, int>(std::__invoke_other, void (*&&)(int*, unsigned int), int*&&, int&&) /cvmfs/sft.cern.ch/lcg/releases/gcc/13.1.0-b3d18/x86_64-el9/include/c++/13.1.0/bits/invoke.h:61 (example2+0x4023f1) (BuildId: 63ed59f82c0e3abb59e80f25d27da9dc9b11db1f)
+    #2 std::__invoke_result<void (*)(int*, unsigned int), int*, int>::type std::__invoke<void (*)(int*, unsigned int), int*, int>(void (*&&)(int*, unsigned int), int*&&, int&&) /cvmfs/sft.cern.ch/lcg/releases/gcc/13.1.0-b3d18/x86_64-el9/include/c++/13.1.0/bits/invoke.h:96 (example2+0x40229c) (BuildId: 63ed59f82c0e3abb59e80f25d27da9dc9b11db1f)
+    #3 void std::thread::_Invoker<std::tuple<void (*)(int*, unsigned int), int*, int> >::_M_invoke<0ul, 1ul, 2ul>(std::_Index_tuple<0ul, 1ul, 2ul>) /cvmfs/sft.cern.ch/lcg/releases/gcc/13.1.0-b3d18/x86_64-el9/include/c++/13.1.0/bits/std_thread.h:292 (example2+0x402152) (BuildId: 63ed59f82c0e3abb59e80f25d27da9dc9b11db1f)
+    #4 std::thread::_Invoker<std::tuple<void (*)(int*, unsigned int), int*, int> >::operator()() /cvmfs/sft.cern.ch/lcg/releases/gcc/13.1.0-b3d18/x86_64-el9/include/c++/13.1.0/bits/std_thread.h:299 (example2+0x4020c6) (BuildId: 63ed59f82c0e3abb59e80f25d27da9dc9b11db1f)
+    #5 std::thread::_State_impl<std::thread::_Invoker<std::tuple<void (*)(int*, unsigned int), int*, int> > >::_M_run() /cvmfs/sft.cern.ch/lcg/releases/gcc/13.1.0-b3d18/x86_64-el9/include/c++/13.1.0/bits/std_thread.h:244 (example2+0x402080) (BuildId: 63ed59f82c0e3abb59e80f25d27da9dc9b11db1f)
     #6 <null> <null> (libstdc++.so.6+0xe04d2) (BuildId: cec3ea60bea5515189d28bd120331f3320aeda73)

-  Previous write of size 4 at 0x7ffd015b6bfc by thread T1:
-    #0 incrementCounter(int*, unsigned int) <null> (example2+0x40127b) (BuildId: 1339b4ce7e1658b4e5515e5fa8dfef740334bf7e)
-    #1 void std::__invoke_impl<void, void (*)(int*, unsigned int), int*, int>(std::__invoke_other, void (*&&)(int*, unsigned int), int*&&, int&&) <null> (example2+0x4023f1) (BuildId: 1339b4ce7e1658b4e5515e5fa8dfef740334bf7e)
-    #2 std::__invoke_result<void (*)(int*, unsigned int), int*, int>::type std::__invoke<void (*)(int*, unsigned int), int*, int>(void (*&&)(int*, unsigned int), int*&&, int&&) <null> (example2+0x40229c) (BuildId: 1339b4ce7e1658b4e5515e5fa8dfef740334bf7e)
-    #3 void std::thread::_Invoker<std::tuple<void (*)(int*, unsigned int), int*, int> >::_M_invoke<0ul, 1ul, 2ul>(std::_Index_tuple<0ul, 1ul, 2ul>) <null> (example2+0x402152) (BuildId: 1339b4ce7e1658b4e5515e5fa8dfef740334bf7e)
-    #4 std::thread::_Invoker<std::tuple<void (*)(int*, unsigned int), int*, int> >::operator()() <null> (example2+0x4020c6) (BuildId: 1339b4ce7e1658b4e5515e5fa8dfef740334bf7e)
-    #5 std::thread::_State_impl<std::thread::_Invoker<std::tuple<void (*)(int*, unsigned int), int*, int> > >::_M_run() <null> (example2+0x402080) (BuildId: 1339b4ce7e1658b4e5515e5fa8dfef740334bf7e)
+  Previous write of size 4 at 0x7ffdb70d03bc by thread T1:
+    #0 incrementCounter(int*, unsigned int) /eos/user/a/alsundai/Code/CSC2025-manycores/Exercise_5/example2.cpp:10 (example2+0x40127b) (BuildId: 63ed59f82c0e3abb59e80f25d27da9dc9b11db1f)
+    #1 void std::__invoke_impl<void, void (*)(int*, unsigned int), int*, int>(std::__invoke_other, void (*&&)(int*, unsigned int), int*&&, int&&) /cvmfs/sft.cern.ch/lcg/releases/gcc/13.1.0-b3d18/x86_64-el9/i
```

