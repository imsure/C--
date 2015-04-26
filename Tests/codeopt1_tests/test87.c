/* register allocation 1 */

extern void print_int(int n);
extern void print_string(char s[]);

void main(void)
{
  int i, j;
  
  j = 0;
  for (i = 0; i < 100; i = i+1) {
    j = j+1;     /* will j be kept in a register? */
    j = j-1;
    j = j+2;
    j = j-2;
    j = j+3;
    j = j-3;
    j = j+4;
    j = j-4;
    j = j+5;
    j = j-5;
    j = j+6;
    j = j-5;
  };
  print_int(j);
  print_string("\n");
}
