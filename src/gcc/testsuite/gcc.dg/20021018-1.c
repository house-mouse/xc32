/* { dg-do run } */
/* { dg-options "-O2 -fpic" } */
/* { dg-xfail-if "PIC not supported for MIPS16" "mips*-*-*" { "-mips16" "-mips16e" } "" } */
/* { dg-xfail-if "PIC not supported" "mips*-*-elf" "*" "" } */

extern void abort (void);
extern void exit (int);

#if __INT_MAX__ >= 2147483647L
static const long foo [10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

long __attribute__((noinline))
bar (int x)
{
  return foo [x - 0x6ffffffa];
}

int
main (void)
{
  if (bar (0x6ffffffc) != 2)
    abort ();
  exit (0);
}
#else
int
main (void)
{
  exit (0);
}
#endif