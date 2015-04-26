/* aliasing: global & formal */

int a[10];

int f(int x[])
{
  int i, j;

  for (i = 0; i < 10; i = i+2) {
    a[i] = i;
    x[i] = i+1;
    a[i+1] = i+1;
    x[i+1] = i+2;
  }

  j = 0;
  for (i = 0; i < 10; i = i+1) 
    j = j + a[i];

  return j;
}

extern void print_int(int x);
extern void print_string(char str[]);

void main(void)
{
  int x;

  x = f(a);

  print_int(x);
  print_string("\n");
}
