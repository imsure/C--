/* Test case for uncolorable graph. */

extern void print_int (int n);
extern void print_string (char s[]);

void func( int x1, int x2, int x3, int x4, int x5,
	   int x6, int x7, int x8, int x9, int x10 )
{
  int y1,y2,y3,y4,y5,y6,y7,y8,y9,y10;
  int z1,z2,z3,z4,z5,z6,z7,z8,z9,z10;

  y1 = x1 + 2;
  y2 = x2 + 2;
  y3 = x3 + 2;
  y4 = x4 + 2;
  y5 = x5 + 2;
  y6 = x6 + 2;
  y7 = x7 + 2;
  y8 = x8 + 2;
  y9 = x9 + 2;
  y10 = x10 + 2;

  print_int(y1);
  print_string("\n");
  print_int(y2);
  print_string("\n");
  print_int(y3);
  print_string("\n");
  print_int(y4);
  print_string("\n");
  print_int(y5);
  print_string("\n");
  print_int(y6);
  print_string("\n");
  print_int(y7);
  print_string("\n");
  print_int(y8);
  print_string("\n");
  print_int(y9);
  print_string("\n");
  print_int(y10);
  print_string("\n");

  z1 = x1 + 3;
  z2 = x2 + 3;
  z3 = x3 + 3;
  z4 = x4 + 3;
  z5 = x5 + 3;
  z6 = x6 + 3;
  z7 = x7 + 3;
  z8 = x8 + 3;
  z9 = x9 + 3;
  z10 = x10 + 3;

  print_int(z1);
  print_string("\n");
  print_int(z2);
  print_string("\n");
  print_int(z3);
  print_string("\n");
  print_int(z4);
  print_string("\n");
  print_int(z5);
  print_string("\n");
  print_int(z6);
  print_string("\n");
  print_int(z7);
  print_string("\n");
  print_int(z8);
  print_string("\n");
  print_int(z9);
  print_string("\n");
  print_int(z10);
  print_string("\n");
}

void main(void)
{
  int x1,x2,x3,x4,x5,x6,x7,x8,x9,x10;
  int y1,y2,y3,y4,y5,y6,y7,y8,y9,y10;
  int a, b;

  a = 'a';
  b = 'b';

  x1 = a;
  x2 = a;
  x3 = a;
  x4 = a;
  x5 = a;
  x6 = a;
  x7 = a;
  x8 = a;
  x9 = a;
  x10 = a;

  y1 = b;
  y2 = b;
  y3 = b;
  y4 = b;
  y5 = b;
  y6 = b;
  y7 = b;
  y8 = b;
  y9 = b;
  y10 = b;

  print_int(x1);
  print_string("\n");
  print_int(x2);
  print_string("\n");
  print_int(x3);
  print_string("\n");
  print_int(x4);
  print_string("\n");
  print_int(x5);
  print_string("\n");
  print_int(x6);
  print_string("\n");
  print_int(x7);
  print_string("\n");
  print_int(x8);
  print_string("\n");
  print_int(x9);
  print_string("\n");
  print_int(x10);
  print_string("\n");

  print_int(y1);
  print_string("\n");
  print_int(y2);
  print_string("\n");
  print_int(y3);
  print_string("\n");
  print_int(y4);
  print_string("\n");
  print_int(y5);
  print_string("\n");
  print_int(y6);
  print_string("\n");
  print_int(y7);
  print_string("\n");
  print_int(y8);
  print_string("\n");
  print_int(y9);
  print_string("\n");
  print_int(y10);
  print_string("\n");

  func(x1,x2,x3,x4,x5,x6,x7,x8,x9,x10);
}
