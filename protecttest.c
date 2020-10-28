#include "types.h"
#include "stat.h"
#include "user.h"
#include "mmu.h"

int
main(int argc, char *argv[])
{
  int parent = getpid();

  // Create an address to protect
  int *val = sbrk(0);

  // Make sure the process memory size is at least a page
  sbrk(PGSIZE);

  // Protect the address
  mprotect(val, 1);

  // Child 1: test that munprotect works properly by 
  // making sure it doesn't cause a trap
  if(fork() == 0) {
    int child1 = getpid();

    // Child 1.1
    if (fork() == 0) {
      munprotect(val, 1);  
      *val = 5;
      printf(1, "\033[0;32m✔\033[0m unprotected value did not cause trap\n");
      kill(child1);
      exit();

    // Child 1.0
    } else {
      wait();
      
      // If child 1 hasn't been killed, child 1.1 was killed, meaning test failed
      printf(1, "\033[0;31m✗\033[0m unprotected value caused trap\n");
      exit();
    }

  // Child 2: test that mprotect works properly by 
  // making sure it causes a trap
  } else if(fork() == 0) {
    sleep(5);
    *val = 5;
    printf(1, "\033[0;31m✗\033[0m protected value did not cause trap\n");
    kill(parent);
    exit();

  // Parent: wait for children
  } else {
    wait();
    wait();
  }

  // If parent hasn't been killed, child 2 was killed, meaning test worked
  printf(1, "\033[0;32m✔\033[0m protected value caused trap\n");
  exit();
}