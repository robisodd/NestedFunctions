#include <pebble.h>
int total = 100;

// Global DEF function
int def(int a) {
  a=a*3;
  return a;
}

int abc() {
  // total variable is local to ABC and the nested DEF function
  static int total = 1;
  
  // Nested DEF function
  //   It doesn't have an argument, showing how it differs from the Global DEF function
  //   CloudPebble's linter flags this line since it thinks functions aren't allowed here (which is normally right)
  int def() {
    total = total * 2;  // this is the total which is local to ABC
    return total;
  }
  
  total = total + def();  // <-- calls local DEF
  total = total + def();  // Same, but for some reason CloudPebble's linter flags this line
  
  return total;
}

int main(void) {
  printf("function1: %d", abc());      // function1: 9
  printf("function1: %d", abc());      // function1: 81
  printf("function1: %d", abc());      // function1: 729
  printf("function2: %d", def(total)); // function2: 300   <-- calls Global DEF Function (notice it has an argument)
  printf("Total: %d", total);          //     Total: 100
}