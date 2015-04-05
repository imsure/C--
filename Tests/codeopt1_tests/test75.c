/* short circuit evaluation */

int flag;
int val;

extern void print_int (int n);
extern void print_string (char s[]);

int side_effect(int x)
{
  flag = -1;
  print_int("x");
  print_string("side_effect");
  print_string("\n");
  return x;
}

void main(void)
{
  int x, y, z;

  x = 3; y = 4; z = 5;
  flag = 1;
  val = 1234;

  if (x < y && y > z && side_effect(x) < z) {
    x = x-1;
  }
  if (flag < 0)
    val = 4321;
  if (x < y || y > z || side_effect(x) < z) {
    x = x-1;
  }
  if (flag < 0)
    val = 4321;
  val = x*val;

  print_int(val);
  print_string("\n");
}
