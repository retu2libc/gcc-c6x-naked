/* { dg-do compile } */
/* { dg-options "-O2 -Wall" } */

/* A naked function must get no prologue, epilogue or return sequence:
   only the assembly body may appear.  */

void __attribute__ ((naked))
naked_fn (void)
{
  __asm__ ("\tB\t.S2\tB3\n\tNOP\t5");
}

/* A naked function with a non-void return type must not trigger
   -Wreturn-type, since the assembly is responsible for returning.  */

int __attribute__ ((naked))
naked_ret (int a, int b)
{
  __asm__ ("\tADD\t.L1\tA4, B4, A4\n\tB\t.S2\tB3\n\tNOP\t5");
}

/* The asm bodies are present.  */
/* { dg-final { scan-assembler-times "B\t\\.S2\tB3" 2 } } */
/* No compiler-generated return.  */
/* { dg-final { scan-assembler-not "\tret\t" } } */
/* No compiler-generated delay slot nops (the asm ones are uppercase).  */
/* { dg-final { scan-assembler-not "\tnop\t" } } */
/* No stack pointer adjustment or register saves/restores.  */
/* { dg-final { scan-assembler-not "B15" } } */
/* { dg-final { scan-assembler-not "\tstw\t" } } */
/* { dg-final { scan-assembler-not "\tldw\t" } } */
