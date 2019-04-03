#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define N 100000
#define MOD 998244353

int n;
int f0[4*N+5], f[4*N+5], g[4*N+5], h[4*N+5], f1[4*N+5];

int fpow(int x, int p) {
  int ret = 1;
  while(p) {
    if(p&1) ret = 1LL*x*ret%MOD;
    x = 1LL*x*x%MOD;
    p >>= 1;
  }
  return ret;
}

void bitReverse(int *s, int len, int bit) {
  for(int i = 0; i < len; ++i) {
    int t = 0;
    for(int j = 0; j < bit; ++j) if((i>>j)&1) t |= 1<<(bit-1-j);
    if(i < t) swap(s[i], s[t]);
  }
}

void DFT(int *s, int flag, int len, int bit) {
  bitReverse(s, len, bit);
  for(int l = 2; l <= len; l <<= 1) {
    int mid = l>>1, t = fpow(3, (MOD-1)/l);
    if(flag) t = fpow(t, MOD-2);
    for(int *p = s; p != s+len; p += l) {
      int w = 1;
      for(int i = 0; i < mid; ++i) {
        int x = p[i], y = 1LL*w*p[i+mid]%MOD;
        p[i] = (x+y)%MOD, p[i+mid] = (x-y)%MOD;
        w = 1LL*w*t%MOD;
      }
    }
  }
}

void inv(int *f, int *g, int c) {
  if(c == 1) {
    g[0] = fpow(f[0], MOD-2);
    return ;
  }
  inv(f, g, (c+1)/2);
  int bit = 0, len, invlen, lim = c+(c+1)/2-1;
  while((1<<bit) < lim) bit++;
  len = (1<<bit), invlen = fpow(len, MOD-2);
  memset(f0, 0, sizeof(int)*len), memcpy(f0, f, sizeof(int)*c);
  DFT(f0, 0, len, bit), DFT(g, 0, len, bit);
  for(int i = 0; i < len; ++i) f0[i] = 1LL*f0[i]*g[i]%MOD;
  DFT(f0, 1, len, bit);
  f0[0] = 2-1LL*f0[0]*invlen%MOD;
  for(int i = 1; i < lim; ++i) f0[i] = i < c ? -1LL*f0[i]*invlen%MOD : 0;
  DFT(f0, 0, len, bit);
  for(int i = 0; i < len; ++i) g[i] = 1LL*g[i]*f0[i]%MOD;
  DFT(g, 1, len, bit);
  for(int i = 0; i < lim; ++i) g[i] = i < c ? 1LL*g[i]*invlen%MOD : 0;
}

void d(int *f, int *g, int c) {
  g[c-1] = 0;
  for(int i = 1; i < c; ++i) g[i-1] = 1LL*i*f[i]%MOD;
}

void _d(int *f, int *g, int c) {
  g[0] = 0;
  for(int i = 1; i <= c; ++i) g[i] = 1LL*f[i-1]*fpow(i, MOD-2)%MOD;
}

void ln(int *f, int *g, int c) {
  int bit = 0, len, invlen;
  while((1<<bit) < 2*c-1) bit++;
  len = (1<<bit), invlen = fpow(len, MOD-2);
  inv(f, h, c);
  d(f, f1, c);
  DFT(h, 0, len, bit), DFT(f1, 0, len, bit);
  for(int i = 0; i < len; ++i) h[i] = 1LL*h[i]*f1[i]%MOD;
  DFT(h, 1, len, bit);
  for(int i = 0; i < len; ++i) h[i] = i < c ? 1LL*h[i]*invlen%MOD : 0;
  _d(h, g, c);
  g[c] = 0;
}

int main() {
  scanf("%d", &n);
  for(int i = 0; i <= n-1; ++i) scanf("%d", &f[i]);
  ln(f, g, n);
  for(int i = 0; i <= n-1; ++i) printf("%d ", (g[i]+MOD)%MOD);
  puts("");
  return 0;
}
