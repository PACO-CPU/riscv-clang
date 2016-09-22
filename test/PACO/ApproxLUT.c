#include <inttypes.h>



int64_t approx( strategy="lut" segments="log-left" approximation="linear" bounds ="(0,65536)") checkLUTE(int64_t input_1) {
  int a = 1;
  int b = 2;
  int c = 3;
  int result = 0;
  
  result = input_1 * b +c/input_1-a+input_1*(input_1+2);
  
  return result;
}

int64_t approx( strategy="lut" segments="log-left" approximation="linear" bounds ="(0,65536)") checkLUTE2(int64_t input_1, int64_t input_2) {
  int a = 1;
  int b = 2;
  int c = 3;
  int result = 0;
  
  result = input_1 * b +c/input_1-a+input_2*(input_2+2);
  
  return result;
}

int64_t approx( strategy="lut" segments="log-left" approximation="linear" bounds ="(0,65536)") checkLUTE3(int64_t input_1, int64_t input_2, int64_t input_3) {
  int a = 1;
  int b = 2;
  int c = 3;
  int result = 0;
  
  result = input_1 * b +c/input_2-a+input_3*(input_1+2);
  
  return result;
}

int main() {
  int64_t approx(mask = 0000000 inject = 1 relax = 1) value = 0;
  int64_t input_1 = 10, input_2 = 20, input_3 = 30;
  value = checkLUTE(input_1);
  //should cause an error
  //value = checkLUTE2(input_1, input_2);
  value = checkLUTE3(input_1, input_2, input_3);
  
  return 0;
}






