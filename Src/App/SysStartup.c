#include <stdint.h>

extern int main(void);
void __my_startup(void) __attribute__((used, noinline));

// *****************************************************************************
// * This is the first function that is executed after a reset.                *
// * 1. It selects the debug interface (TBD)                                   *
// * 2. It sets the stack alignment.(TBD)                                      *
// * 3. It copies the initialized variables data from flash to RAM.(TBD)       *
// * 4. It clears the uninitialized variables. (TBD)                           *
// * 5. It calls main.                                                         *
// *****************************************************************************
__attribute__ ((noreturn)) void __my_startup(void){
  extern char _sdata;    // .data section start
  extern char _edata;    // .data section end
  extern char _sbss;     // .bss  section start
  extern char _ebss;     // .bss  section end
  extern char _ldata;    // .data load address

  char *dst = &_sdata;
  char *src = &_ldata;

 (void)*src;
 (void)*dst;
 (void)_ebss;
 (void)_sbss;
 (void)_edata;

  // call main
  main();

  // halt
  for(;;)
  {
  }
}

