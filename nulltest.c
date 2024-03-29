#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char **argv) {
   int parent = getpid();

   if (fork() == 0) {
      uint* nullp = (uint*) 0;
      printf(1, "%x %x\n", nullp, *nullp);

      // If above code didn't kill this process, the test didn't work
      printf(1, "\033[0;31m✗\033[0m null pointer dereference didn't cause trap\n");
      kill(parent);
      exit();
   } else {
      wait();
   }

   // If parent hasn't been killed, the child was killed, meaning test worked
   printf(1, "\033[0;32m✔\033[0m null pointer dereference caused trap\n");
   exit();
}