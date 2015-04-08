/* Test case for uncolorable graph. */

extern void print_int (int n);
extern void print_string (char s[]);

void main(void)
{
  int x1,x2,x3,x4,x5,x6,x7,x8,x9,x10;
  int y1,y2,y3,y4,y5,y6,y7,y8,y9,y10;

  x1 = 1;
  x2 = 2 * x1;
  x3 = 2 * x2;
  x4 = 2 * x3;
  x5 = 2 * x4;
  x6 = 2 * x5;
  x7 = 2 * x6;
  x8 = 2 * x7;
  x9 = 2 * x8;
  x10 = 2 * x9;

  y1 = x1 + x2;
  y2 = x2 + x3;
  y3 = x3 + x4;
  y4 = x4 + x5;
  y5 = x5 + x6;
  y6 = x6 + x7;
  y7 = x7 + x8;
  y8 = x8 + x9;
  y9 = x9 + x10;
  y10 = y1 + y2 + y3 + y4 + y5 + y6 + y7 + y8 + y9;

  print_int(x1);
  print_string("\n");
  print_int(y1);
  print_string("\n");
  
  print_int(x2);
  print_string("\n");
  print_int(y2);
  print_string("\n");

  print_int(x3);
  print_string("\n");
  print_int(y3);
  print_string("\n");

  print_int(x4);
  print_string("\n");
  print_int(y4);
  print_string("\n");

  print_int(x5);
  print_string("\n");
  print_int(y5);
  print_string("\n");

  print_int(x6);
  print_string("\n");
  print_int(y6);
  print_string("\n");

  print_int(x7);
  print_string("\n");
  print_int(y7);
  print_string("\n");

  print_int(x8);
  print_string("\n");
  print_int(y8);
  print_string("\n");

  print_int(x9);
  print_string("\n");
  print_int(y9);
  print_string("\n");

  print_int(x10);
  print_string("\n");
  print_int(y10);
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
}
