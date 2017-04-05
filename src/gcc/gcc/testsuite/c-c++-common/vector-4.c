/* { dg-do compile } */
/* { dg-options "-fno-common" { target { { hppa*-*-hpux* } && { ! lp64 } } } } */
#define vector __attribute__((vector_size(4*sizeof(int)) ))

vector int a, b, c;


/* Test that remainder works for vectors. */
void f(void)
{
  a = b % c;
}
