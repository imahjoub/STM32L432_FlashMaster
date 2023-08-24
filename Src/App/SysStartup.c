#include <stdint.h>

/* ----------------------------------------------------------------------------------- */
/*  Function prototype                                                                 */
/* ----------------------------------------------------------------------------------- */
void crt_init_ram(void);
void crt_init_ctors(void);
void __my_startup() __attribute__((used, noinline));


/* ----------------------------------------------------------------------------------- */
/*  Types defintion                                                                    */
/* ----------------------------------------------------------------------------------- */
typedef void(*function_type)(void);


/* ----------------------------------------------------------------------------------- */
/*  Extern data                                                                        */
/* ----------------------------------------------------------------------------------- */
extern int main(void);

extern uintptr_t     _sdata;  /* Start address for the .data section. */
extern uintptr_t     _edata;  /* End address for the .data section.   */
extern uintptr_t     _sbss;   /* Start address for the .bss section.  */
extern uintptr_t     _ebss;   /* End address for the .bss section.    */
extern uintptr_t     _ldata;  /* Load address for the init. values
                                 of the rom-to-ram section.           */

extern function_type _ctors_end;
extern function_type _ctors_begin;


/* ----------------------------------------------------------------------------------- */
/*  Functions implementation                                                           */
/* ----------------------------------------------------------------------------------- */
void __my_startup(void)
{
  /* Load the stack pointer.                          */
  /* The stack pointer is automatically loaded from   */
  /* the base position of the interrupt vector table  */
  /* So we do nothing here.                           */

  /* Initialize statics from ROM to RAM               */
  /* Zero-clear default-initialized static RAM        */
  crt_init_ram();

  /* Call all ctor initializations                    */
  crt_init_ctors();

  /* Jump to main (and never return)                  */
  (void) main();

  /* Catch an unexpected return from main.            */
  for(;;)
  {
    /* Replace with a loud error if desired.          */
  }
}

void crt_init_ram(void)
{
  /* Copy the data segment initializers from ROM to RAM.*/
  /* Note that all data segments are aligned by 4.      */
  const unsigned size_data = (unsigned) ((uint8_t*) (&_edata) - (uint8_t*) &_sdata);

  for(unsigned i = 0U; i < size_data; ++i)
  {
    ((uint8_t*) &_sdata)[i] = ((const uint8_t*) &_ldata)[i];
  }

  const unsigned size_bss = (unsigned) ((uint8_t*) (&_ebss) - (uint8_t*) &_sbss);

  /* Clear the bss segment.*/
  for(unsigned i = 0U; i < size_bss; ++i)
  {
    ((uint8_t*) &_sbss)[i] = (uint8_t) 0U;
  }
}

void crt_init_ctors(void)
{
  for(function_type* pfn = (function_type*) &_ctors_begin; pfn != (function_type*) &_ctors_end; ++pfn)
  {
    (*pfn)();
  }
}
