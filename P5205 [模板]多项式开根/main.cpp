#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define N 100000
#define MOD 998244353

int n;
int f[4*N+5], g[4*N+5], f1[4*N+5], g1[4*N+5], h[4*N+5];

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
    for(int j = 0; j < bit; ++j) if((i>>j)&1) t |= (1<<(bit-1-j));
    if(i < t) swap(s[i], s[t]);
  }
}

void NTT(int *s, int len, int bit, int flag) {
  bitReverse(s, len, bit);
  for(int l = 2; l <= len; l <<= 1) {
    int mid = l>>1;
    int t = fpow(3, (MOD-1)/l);
    if(flag == -1) t = fpow(t, MOD-2);
    for(int *p = s; p != s+len; p += l) {
      int w = 1;
      for(int i = 0; i < mid; ++i) {
        int x = p[i], y = 1LL*w*p[i+mid]%MOD;
        p[i] = (x+y)%MOD, p[i+mid] = (x-y)%MOD;
        w = 1LL*w*t%MOD;
      }
    }
  }
  int inv = fpow(len, MOD-2);
  if(flag == -1) for(int i = 0; i < len; ++i) s[i] = 1LL*s[i]*inv%MOD;
}

void polyInv(int *f, int *g, int bit) {
  if(bit == 0) {
    g[0] = fpow(f[0], MOD-2);
    return ;
  }
  polyInv(f, g, bit-1);
  int len = 1<<bit, lim = len<<1;
  for(int i = 0; i < len; ++i) f1[i] = f[i];
  NTT(f1, lim, bit+1, 1), NTT(g, lim, bit+1, 1);
  for(int i = 0; i < lim; ++i) g[i] = (2*g[i]-1LL*f1[i]*g[i]%MOD*g[i]%MOD)%MOD;
  NTT(g, lim, bit+1, -1);
  for(int i = len; i < lim; ++i) g[i] = 0;
}

void polySqrt(int *f, int *g, int bit) {
  if(bit == 0) {
    g[0] = 1;
    return ;
  }
  polySqrt(f, g, bit-1);
  int len = 1<<bit, lim = len<<1, inv2 = fpow(2, MOD-2);
  for(int i = 0; i < len; ++i) g1[i] = 0, h[i] = f[i], f1[i] = 0;
  polyInv(g, g1, bit);
  NTT(g1, lim, bit+1, 1), NTT(h, lim, bit+1, 1);
  for(int i = 0; i < lim; ++i) h[i] = 1LL*h[i]*g1[i]%MOD;
  NTT(h, lim, bit+1, -1);
  for(int i = 0; i < len; ++i) g[i] = 1LL*(g[i]+h[i])%MOD*inv2%MOD;
}

int main() {
  scanf("%d", &n);
  for(int i = 0; i < n; ++i) scanf("%d", &f[i]);
  int bit = 0;
  while((1<<bit) < n) bit++;
  polySqrt(f, g, bit);
  for(int i = 0; i < n; ++i) printf("%d ", (g[i]%MOD+MOD)%MOD);
  return 0;
}