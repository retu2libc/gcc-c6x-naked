/* { dg-do compile } */
/* { dg-options "-O2" } */

/* The naked attribute is only valid on functions.  */

int not_a_function __attribute__ ((naked)); /* { dg-warning "'naked' attribute only applies to functions" } */

/* Non-naked functions are unaffected and still get a return sequence.  */

void
normal_fn (void)
{
  __asm__ ("\tNOP");
}

/* { dg-final { scan-assembler "\tret\t" } } */
