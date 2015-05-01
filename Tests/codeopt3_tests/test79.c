/* aliasing: two formals aliased to global arrays */

int f(int x[], int y[])
{
  int i, j;

  for (i = 0; i < 10; i = i+2) {
    y[i] = i;
    x[i] = i+1;
    y[i+1] = i+1;
    x[i+1] = i+2;
  }

  j = 0;
  for (i = 0; i < 10; i = i+1) 
    j = j + x[i] + y[i];

  return j;
}

int a[10];

extern void print_int(int x);
extern void print_string(char str[]);

void main(void)
{
  int x;

  x = f(a, a);

  print_int(x);
  print_string("\n");
}
