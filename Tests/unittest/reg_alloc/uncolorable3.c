/* Test case for uncolorable graph. */

extern void print_int (int n);
extern void print_string (char s[]);

void main(void)
{
  int x1,x2,x3,x4,x5,x6,x7,x8,x9,x10;
  int y1,y2,y3,y4,y5,y6,y7,y8,y9,y10;
  int A[10];
  int B[10];
  int a, b, i;

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

  for (i = 0; i < 10; i = i+1) {
    A[i] = a + 2;
    B[i] = b + 2;
    print_int(A[i]);
    print_string("\n");
    print_int(B[i]);
    print_string("\n");
  }
}
