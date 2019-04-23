#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define N 100000
#define MOD 998244353

int n;
int f[4*N+5], g[4*N+5], h[4*N+5], f1[4*N+5], g1[4*N+5], h1[4*N+5];

int fpow(int x, int p) {
  int ret = 1;
  while(p) {
    if(p&1) ret = 1LL*ret*x%MOD;
    x = 1LL*x*x%MOD;
    p >>= 1;
  }
  return ret;
}

void bitReverse(int *s, int len, int bit) {
  static int rev[4*N+5];
  for(int i = 1; i < len; ++i) {
    rev[i] = (rev[i>>1]>>1)|((i&1)<<(bit-1));
    if(i < rev[i]) swap(s[i], s[rev[i]]);
  }
}

void NTT(int *s, int len, int bit, int flag) {
  bitReverse(s, len, bit);
  for(int l = 2; l <= len; l <<= 1) {
    int mid = l>>1, t = fpow(3, (MOD-1)/l);
    if(flag == -1) t = fpow(t, MOD-2);
    for(int *p = s; p != s+len; p += l) {
      int w = 1;
      for(int i = 0; i < mid; ++i) {
        int x = 1LL*w*p[i+mid]%MOD;
        p[i+mid] = (p[i]-x)%MOD, p[i] = (p[i]+x)%MOD;
        w = 1LL*w*t%MOD;
      }
    }
  }
  if(flag == -1) {
    int inv = fpow(len, MOD-2);
    for(int i = 0; i < len; ++i) s[i] = 1LL*s[i]*inv%MOD;
  }
}

void polyInv(int *f, int *g, int bit) {
  if(bit == 0) { g[0] = fpow(f[0], MOD-2); return ; }
  polyInv(f, g, bit-1);
  int len = 1<<bit, lim = len<<1;
  for(int i = 0; i < len; ++i) f1[i] = f[i];
  NTT(f1, lim, bit+1, 1), NTT(g, lim, bit+1, 1);
  for(int i = 0; i < lim; ++i) g[i] = 1LL*g[i]*(2-1LL*f1[i]*g[i]%MOD)%MOD;
  NTT(g, lim, bit+1, -1);
  for(int i = len; i < lim; ++i) g[i] = 0;
}

void d(int *f, int *g, int len) {
  g[len-1] = 0;
  for(int i = 1; i < len-1; ++i) g[i-1] = 1LL*i*f[i]%MOD;
}

void d_(int *f, int *g, int len) {
  g[0] = 0;
  for(int i = 1; i < len; ++i) g[i] = 1LL*fpow(i, MOD-2)*f[i-1]%MOD;
}

void polyLn(int *f, int *g, int bit) {
  int len = 1<<bit, lim = len<<1;
  polyInv(f, g, bit); d(f, g1, len);
  NTT(g, lim, bit+1, 1), NTT(g1, lim, bit+1, 1);
  for(int i = 0; i < lim; ++i) g1[i] = 1LL*g[i]*g1[i]%MOD;
  NTT(g1, lim, bit+1, -1);
  d_(g1, g, len);
}

int main() {
  scanf("%d", &n);
  for(int i = 0; i < n; ++i) scanf("%d", &f[i]);
  int bit = 0;
  while((1<<bit) <= n) bit++;
  polyLn(f, g, bit);
  for(int i = 0; i < n; ++i) printf("%d ", (g[i]+MOD)%MOD);
  puts("");
  return 0;
}