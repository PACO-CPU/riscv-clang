#include <inttypes.h>
//Check if marko works
//#ifndef __paco
//#define approx(...) macro does not work;
//#else
//#define approx(...) macro works;
//#endif

//legal combine modes
#pragma paco combine most_precise
//#pragma paco combine least_precise
//#pragma paco combine error

//legal intermediate_literal modes
#pragma paco intermediate_literal precise
//#pragma paco intermediate_literal mimic

//Check if typedef works
void checkTypeDef() {
  typedef int64_t approx(mask = 1111000 inject = 1 relax = 1)  approx_int_1;
  approx_int_1 typeCheckInt_1 = 1;
  approx_int_1 typeCheckInt_2 = 100000;
  approx_int_1 typeCheckInt_Result = 0;
  typeCheckInt_Result = typeCheckInt_1 + typeCheckInt_2;
  typeCheckInt_Result = typeCheckInt_1 - typeCheckInt_2;
  typeCheckInt_Result = typeCheckInt_1 * typeCheckInt_2;
}

//Check if basic ALU functions work
int64_t approx(mask = 1111000 inject = 1 relax = 1) checkBasicALU() {
  int64_t approx(mask = 1111000 inject = 1 relax = 1) typeCheckInt_1 = 1;
  int64_t approx(mask = 1111000 inject = 1 relax = 1) typeCheckInt_2 = 100000;
  int64_t approx(mask = 1111000 inject = 1 relax = 1) typeCheckInt_Result = 0;
  typeCheckInt_Result = typeCheckInt_1 + typeCheckInt_2;
  typeCheckInt_Result = typeCheckInt_1 - typeCheckInt_2;
  typeCheckInt_Result = typeCheckInt_1 * typeCheckInt_2;
  return typeCheckInt_Result;
}

//Check if all approx Decls works
int64_t approx(mask = 0000000 inject = 1 relax = 1) checkApproxDecls() {
  //Not all are tested, because it is too much to test, but basic usage is tested
  int64_t approx(mask = 0000000 inject = 1 relax = 1) result = 0;
  int64_t approx(mask = 1000000 inject = 1 relax = 1) APD1 = 1;
  int64_t approx(mask = 1100000 inject = 1 relax = 1) APD2 = 1;
  int64_t approx(mask = 1110000 inject = 1 relax = 1) APD3 = 1;
  int64_t approx(mask = 1111000 inject = 1 relax = 1) APD4 = 1;
  int64_t approx(mask = 1111100 inject = 1 relax = 1) APD5 = 1;
  int64_t approx(mask = 1111110 inject = 1 relax = 1) APD6 = 1;
  int64_t approx(mask = 1111111 inject = 1 relax = 1) APD7 = 1;
  int64_t approx(mask = 0100000 inject = 1 relax = 1) APD8 = 1;
  int64_t approx(mask = 0010000 inject = 1 relax = 1) APD9 = 1;
  int64_t approx(mask = 0001000 inject = 1 relax = 1) APD10 = 1;
  int64_t approx(mask = 0000100 inject = 1 relax = 1) APD11 = 1;
  int64_t approx(mask = 0000010 inject = 1 relax = 1) APD12 = 1;
  int64_t approx(mask = 0000001 inject = 1 relax = 1) APD13 = 1;
  int64_t approx(neglect_amount = 2 inject = 1 relax = 1) APD14 = 1;
  int64_t approx(neglect_amount = 4 inject = 1 relax = 1) APD15 = 1;
  int64_t approx(neglect_amount = 7 inject = 1 relax = 1) APD16 = 1;
  int64_t approx(neglect_amount = 10 inject = 1 relax = 1) APD17 = 1;
  int64_t approx(neglect_amount = 15 inject = 1 relax = 1) APD18 = 1;
  int64_t approx(neglect_amount = 20 inject = 1 relax = 1) APD19 = 1;
  int64_t approx(neglect_amount = 27 inject = 1 relax = 1) APD20 = 1;
  //Should cause an error
  //int64_t approx(neglect_amount = 19 inject = 1 relax = 1) APD20 = 1;
#pragma paco combine most_precise
  result += APD1 + APD2;
  result += APD1 + APD3;
  result += APD1 + APD4;
  result += APD1 + APD5;
  result += APD1 + APD6;
  result += APD1 + APD7;
  result += APD1 + APD8;
  result += APD1 + APD9;
  result += APD1 + APD10;
  result += APD1 + APD11;
  result += APD1 + APD12;
  result += APD1 + APD13;
  result += APD1 + APD14;
  result += APD1 + APD15;
  result += APD1 + APD16;
  result += APD1 + APD17;
  result += APD1 + APD18;
  result += APD1 + APD19;
  result += APD1 + APD20;
#pragma paco combine least_precise
  result += APD1 + APD2;
  result += APD1 + APD3;
  result += APD1 + APD4;
  result += APD1 + APD5;
  result += APD1 + APD6;
  result += APD1 + APD7;
  result += APD1 + APD8;
  result += APD1 + APD9;
  result += APD1 + APD10;
  result += APD1 + APD11;
  result += APD1 + APD12;
  result += APD1 + APD13;
  result += APD1 + APD14;
  result += APD1 + APD15;
  result += APD1 + APD16;
  result += APD1 + APD17;
  result += APD1 + APD18;
  result += APD1 + APD19;
  result += APD1 + APD20;
#pragma paco combine most_precise
  //Should cause a error
  //APD1 = APD2 + APD12;
  return result;
}

int64_t approx(mask = 0000000 inject = 1 relax = 1) checkApproxComputations() {
  int64_t approx(inject=1 mask=1000000) a = 41171108;
  int64_t approx(mask=1110000) b = 632399;
  int64_t c = 728943616;
  int64_t d = 225573392;
  int64_t e = 12433592;
  int64_t f = 154851952;
  int64_t g = 304389568;
  int64_t approx(mask=1110000) h = 24112200;
  int64_t approx(mask=1100000) i = 84241280;
  int64_t j = 41508804;
  int64_t k = 531786112;
  int64_t approx(mask=1110000) l = 227842288;
  int64_t approx(mask=1000000) m = 216787968;
  int64_t n = 62215564;
  int64_t approx(mask=1111110) o = 17832148;
  int64_t approx(mask=1000000) p = 248603664;
  int64_t approx(mask=1111111) q = 574434880;
  int64_t r = 114368240;
  int64_t s = 238866912;
  int64_t t = 33042176;
  int64_t approx(mask=1000000) u = 217104176;
  int64_t approx(inject=1 mask=1000000) v = 427679200;
  int64_t w = 97322464;
  int64_t approx(mask=1111100) x = 905182464;
  int64_t y = 807648448;
  int64_t approx(mask=1111111) z = 113479568;
  b = l-x+d+b+o/p-(g/c)*(o*d)-l/a*d;
  k = (j/r)*g/m*(s+p*f*w-r/l)/x-k-j;
  z = e/x/j/e+(d-(c-g*q-m/j*n));
  p = t+x+o/(i/h)-g+v/y/j-v-u-n;
  v = a/r/c-(s-a*k)/w-u*f*l/p+t;
  u = (e+(i-p-u-n+t+i-b+(e-u-k)));
  v = u+m+w+(w-h)-(l-(q*u-u+m-h-t));
  return p+v+u;
}

int64_t callTest(int64_t approx(mask=1111100 inject = 1) input) {
  return (input + input) * input - input;
}

int64_t approx(mask = 1111100 inject = 1 relax = 1) checkApproxFunctionCalls() {
  int64_t approx(mask=1111100) result = 0;
  int64_t approx(mask=1111100 inject = 1) input = 20;
  result = callTest(input);
  return result;
}

int main() {
  int64_t approx(mask = 0000000 inject = 1 relax = 1) value = 0;
  value = checkApproxFunctionCalls();
  checkTypeDef();
  value = checkBasicALU();
  value = checkApproxDecls();
  value = checkApproxComputations();
  
  return 0;
}






