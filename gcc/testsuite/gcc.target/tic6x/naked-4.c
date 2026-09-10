/* { dg-do compile } */
/* { dg-options "-O2" } */

/* A pure-assembly naked wrapper calling a normal C function that uses
   the stack.  The wrapper saves its own return address (B3) on the
   stack, keeping B15 8-byte aligned, calls the helper, restores B3 and
   returns.  The compiler must emit nothing for the wrapper beyond the
   asm body, while the helper gets its normal prologue and epilogue.  */

int
helper (int x)
{
  volatile int buf[4];
  buf[0] = x;
  buf[1] = buf[0] + 1;
  return buf[1] * 2;
}

int __attribute__ ((naked))
naked_wrapper (int x)
{
  __asm__ (
    "\tSTW\t.D2T2\tB3, *B15--(8)\n"
    "\tCALLP\t.S2\thelper, B3\n"
    "\tLDW\t.D2T2\t*++B15(8), B3\n"
    "\tNOP\t4\n"
    "\tB\t.S2\tB3\n"
    "\tNOP\t5");
}

/* Nothing between the wrapper's label and the asm: no prologue.  */
/* { dg-final { scan-assembler "naked_wrapper:\n\t; #APP" } } */
/* Nothing between the end of the asm and the size directive: no
   epilogue and no compiler-generated return.  */
/* { dg-final { scan-assembler "NOP\t5\n\t; #NO_APP \n\t\\.size\tnaked_wrapper" } } */
/* The only compiler-generated return and frame belong to the helper.  */
/* { dg-final { scan-assembler-times "\tret\t" 1 } } */
/* { dg-final { scan-assembler-times "\tsub\t\\.d2\tB15" 1 } } */
