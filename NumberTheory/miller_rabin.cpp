#include <bits/stdc++.h>

using namespace std;

/*
 * [Description] : Modular Exponentiation, compute (a ^ b) % n
 * Running Time : O(log(b))
 */

// width of a should be enough to prevent overflows, to be safe pass higher widths (like int64_t for example)
template <class T, class V, class W>
T modular_exp(T a, V b, W n) {
   T res = T(1);
   while(b) {
       if(b & 1) {
           res = ((res % n) * (a % n)) % n;
       }
       a = (a % n) * (a % n) % n;
       b >>= 1;
   }
   return res;
}

/*
 * [Description] : Miller Rabin Primality Test
 *                 Tells with very low probabilty of error whether the given number is prime
 *                 Refer CLRS : Chapter 31, Section 8
 *  Running Time : O(log_2(n))
 */

// n must be odd here, returns true if n is composite
bool witness(int64_t a, int64_t n) {
   assert(n & 1);
   int64_t t = 0, u;
   auto temp = n - 1;
   while(temp % 2 == 0) {
      temp /= 2;
      t++;
   }
   u = temp;
   int64_t x_0 = modular_exp(a, u, n);
   for(int i = 1; i <= t; i++) {
      int64_t new_x = (x_0 * x_0) % n;
      if(new_x == 1 and x_0 != 1 and x_0 != n - 1) {
         return true;
      }
      x_0 = new_x;
   }
   if(x_0 != 1) {
      return true;
   }
   return false;
}

// return true if n is prime
bool miller_rabin(int64_t n, int s = 10) {
   if(n == 2) {
      return true;
   }
   if(n % 2 == 0) {
      return false;
   }
   mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
   for(int i = 0; i < s; i++)  {
      int64_t a = rng() % (n - 2) + 1;
      if(witness(a, n)) {
         return false;
      }
   }
   return true;
}

int main() {
   int n;
   cin >> n;
   cout << (miller_rabin(n) ? "Yes" : "No")  << endl;
}
