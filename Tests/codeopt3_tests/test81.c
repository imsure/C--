/* simple dead code elimination 1 */

extern void print_int(int x);
extern void print_string(char str);

void main(void)
{
  int i, j;

  for (i = 0; i < 1000; i = i+1) 
    j = 1;     /* this statement is dead! */

  print_int(i);
  print_string("\n");
}
