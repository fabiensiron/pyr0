
double pow(double x, double y)
{
  if (y <= 0) return 1.0;
  if (y == 1) return x;
  
  double r = x;

  while(y > 1)
    {
      r *= x;
      y--;
    }

  return r;
}


double fabs(double x)
{
  double __value = x;
  __value = (double)((int)x);
  
  return __value;       
}
