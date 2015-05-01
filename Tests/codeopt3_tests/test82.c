/* simple dead code elimination 2 */

extern void print_int(int x);
extern void print_string(char str[]);

void main(void)
{
  int i, j;

  for (i = 0; i < 100; i = i+1) {
    j = (2*i-1)/3;          /* this statement is dead! */
    j = (i+1)*i - 3;        /* this statement is dead! */
    j = 1;                  /* this statement is dead! */
  };
  print_int(i);
  print_string("\n");
}
