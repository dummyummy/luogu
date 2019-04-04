#include <bits/stdc++.h>

using namespace std;

#define N 200000
#define MOD 998244353

int n;
int f[4*N+5], g[4*N+5], f0[4*N+5], g0[4*N+5], h[4*N+5];

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
  if(flag) {
    int inv = fpow(len, MOD-2);
    for(int i = 0; i < len; ++i) s[i] = 1LL*s[i]*inv%MOD;
  }
}

void d(int *f, int *g, int c) {
  g[c-1] = 0;
  for(int i = 1; i < c-1; ++i) g[i-1] = 1LL*i*f[i]%MOD;
}

void d_(int *f, int *g, int c) {
  g[0] = 0;
  for(int i = 1; i < c; ++i) g[i] = 1LL*f[i-1]*fpow(i, MOD-2)%MOD;
}

void polyInv(int *f, int *g, int c) {
  if(c == 0) { g[0] = fpow(f[0], MOD-2); return ; }
  polyInv(f, g, c-1);
  int len = 1<<c;
  for(int i = 0; i < len; ++i) f0[i] = f[i];
  DFT(f0, 0, len<<1, c+1), DFT(g, 0, len<<1, c+1);
  for(int i = 0; i < (len<<1); ++i) g[i] = 1LL*g[i]*(2-1LL*f0[i]*g[i]%MOD)%MOD;
  DFT(g, 1, len<<1, c+1);
  for(int i = len; i < (len<<1); ++i) g[i] = 0;
}

void polyLn(int *f, int *g, int c) {
  int len = (1<<c);
  polyInv(f, g, c); d(f, g0, len);
  DFT(g, 0, len<<1, c+1), DFT(g0, 0, len<<1, c+1);
  for(int i = 0; i < (len<<1); ++i) g0[i] = 1LL*g[i]*g0[i]%MOD;
  DFT(g0, 1, len<<1, c+1);
  d_(g0, g, len);
  for(int i = 0; i < (len<<1); ++i) g0[i] = f0[i] = 0;
  for(int i = len; i < (len<<1); ++i) g[i] = 0;
}

void polyExp(int *f, int *g, int c) {
  if(c == 0) { g[0] = 1; return ; }
  polyExp(f, g, c-1);
  int len = 1<<c;
  polyLn(g, h, c);
  h[0] = (1-h[0]+f[0])%MOD;
  for(int i = 1; i < len; ++i) h[i] = (-h[i]+f[i])%MOD;
  DFT(g, 0, len<<1, c+1), DFT(h, 0, len<<1, c+1);
  for(int i = 0; i < (len<<1); ++i) g[i] = 1LL*g[i]*h[i]%MOD, h[i] = 0;
  DFT(g, 1, len<<1, c+1);
  for(int i = len; i < (len<<1); ++i) g[i] = 0;
}

int main() {
  scanf("%d", &n);
  for(int i = 0; i <= n-1; ++i) scanf("%d", &f[i]);
  int n0 = 0;
  while((1<<n0) <= n) n0++;
  polyExp(f, g, n0);
  for(int i = 0; i < n; ++i) printf("%d ", (g[i]+MOD)%MOD);
  return 0;
}