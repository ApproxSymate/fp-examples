/* From Botella et al.: Symbolic Execution of Floating-Point
 * Computations
 */


float foo1(float x)
{
  float y = 1.0e12, z ;
  
  if (x > 0.0)
    /* A */
    z = x + y;
  
  if (z == y)
    /* If the execution visited A, then
       here there is no solution over real
       of rational, but there is over
       floating point */
    return x;

  return y;
}

