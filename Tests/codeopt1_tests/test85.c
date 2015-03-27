/* liveness analysis: more complicated control flow */

extern void print_int(int x);
extern void print_string(char str[]);

void main(void)
{
  int i, j, k;

  k = 0;
  for (i = 0; i < 100; i = i+1) {
    j = (2*i-1)/3;          /* this statement is dead! */
    j = (i+1)*i - 3;        /* this statement is dead! */
    if (i-2*(i/2) == 0) { 
      k = k+i+1;
      j = 1;                /* this statement is dead! */
    }
    else {
      j = 0;
    }
  };
  if (i > 0) {
    print_int(k);
    print_string("\n");
    return;
  }
  else {
    print_int(i);
    print_string("\n");
    return;
  }
}
