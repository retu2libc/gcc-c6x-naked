/* { dg-do compile } */
/* { dg-options "-O0" } */

/* Check that function arguments aren't assigned and copied to stack slots
   in naked functions.  This usually happens at -O0 (for better debugging),
   but is highly undesirable if we haven't created a stack frame.  */

void __attribute__ ((naked))
foo (int n, int m)
{
  __asm__ ("\tFROB\tA4, B4");
}

/* { dg-final { scan-assembler "\tFROB\tA4, B4" } } */
/* No argument spills, stack pointer adjustment or return sequence.  */
/* { dg-final { scan-assembler-not "\tstw\t" } } */
/* { dg-final { scan-assembler-not "B15" } } */
/* { dg-final { scan-assembler-not "\tret\t" } } */
