/* more elaborate dead code elimination */

extern void print_int(int x);
extern void print_string(char str[]);

void main(void)
{
  int i, j;
  
  for (i = 0; i < 100; i = i+1) {
    if (i/2 == 0) 
      j = 3*i+1;
    else 
      j = i/2;
  };
  print_int(i);
  print_string("\n");
}
