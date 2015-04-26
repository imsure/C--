/* register allocation 3: dealing with procedure calls */

int f(int x)
{
  int y, z;
  
  y = x+2;
  z = y-1;
  x = z+3;
  return x;
}

extern void print_int(int n);
extern void print_string(char s[]);

void main(void)
{
  int i, j0, j1, j2, j3, j4, j5, j6, j7, j8, j9, j10, j11, j12;
  
  j0 = 0;
  for (i = 0; i < 100; i = i+1) {
    j1 = j0+1;
    j2 = j1-1;
    j3 = j2+2;
    j4 = j3-2;
    j5 = j4+3;
    j6 = j5-3;
    j7 = f(j6);
    j8 = j7-4;
    j9 = j8+5;
    j10 = j9-5;
    j11 = j10+6;
    j12 = j11-5;
  };
  print_int(j12);
  print_string("\n");
}
