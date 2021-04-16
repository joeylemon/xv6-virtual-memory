# xv6-virtual-memory

This is a copy of the [xv6 repository](https://github.com/mit-pdos/xv6-public) which implements new virtual memory features: a new exception when a program dereferences a null pointer and new syscalls to change the protection levels of pages in a process's address space

This project was assigned in COSC361 Operating Systems taught by Dr. Micah Beck, as an assignment from the [OSTEP](https://github.com/remzi-arpacidusseau/ostep-projects) textbook.

## Changes to implement feature

### Makefile
The makefile had to be edited to add the new user programs to test the null pointer dereference exceptions and mprotect and munprotect functions. Additionally, the start address for user programs had to be changed to the start of the second page, or the address 0x1000.

### exec.c
This file contained code to load a program into memory. Since we changed user programs to start at 0x1000, this file needed to reflect that within the loop that performs the actual loading of the program.

### vm.c
This file sets up a page table for a process when it is copied from another process (i.e. forked). Therefore, the loop that performs the setup needed to be changed to start at address 0x1000 instead of 0x0.

Additionally, the true definitions for the mprotect() and munprotect() functions were added to this file. These functions check the arguments for correctness (page alignment and length correctness) and then loop through the page directory to either set or unset the write bits of the page table entry. It also updates the CR3 register so the hardware is aware of the change to the page table entry.

### nulltest.c
This user program provides a means to test the new null pointer dereferencing changes. If a process causes a trap when it tries to dereference a null pointer, the test passes. Otherwise, it fails.

### protecttest.c
This user program provides a means to test the new mprotect() and munprotect() functions. First, it tests that a program doesn’t cause a trap when a protected region of memory is unprotected and then overwritten. If it does cause a trap, the test fails. Then, it tests that a program causes a trap when a protected region of memory is overwritten. If it doesn’t cause a trap, the test fails.

### defs.h
The declarations for the new functions mprotect() and munprotect() were added to this file.

### user.h
The declarations for the new functions mprotect() and munprotect() were added to this file.

### usys.S
The declarations for the new functions mprotect() and munprotect() were added to this file.

### syscall.c
The declarations for the new functions sys_mprotect() and sys_munprotect() were added to this file.

### syscall.h
This system call numbers were assigned to the new functions sys_mprotect() and sys_munprotect().

### sysproc.c
This file contains the definitions of the sys_mprotect() and sys_munprotect() functions which call the definitions in vm.c.
