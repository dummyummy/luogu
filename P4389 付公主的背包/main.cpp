#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define N 100000
#define MOD 998244353

int n, m, v[N+5], cnt[N+5];
int f[4 * N + 5], g[4 * N + 5], f1[4 * N + 5], g1[4 * N + 5], h[4 * N + 5];

int fpow(int x, int p)
{
  int ret = 1;
  while (p)
  {
    if (p & 1)
      ret = 1LL * ret * x % MOD;
    x = 1LL * x * x % MOD;
    p >>= 1;
  }
  return ret;
}

void bitReverse(int *s, int len, int bit)
{
  for (int i = 0; i < len; ++i)
  {
    int t = 0;
    for (int j = 0; j < bit; ++j)
      if ((i >> j) & 1)
        t |= 1 << (bit - 1 - j);
    if (i < t)
      swap(s[i], s[t]);
  }
}

void DFT(int *s, int flag, int len, int bit)
{
  bitReverse(s, len, bit);
  for (int l = 2; l <= len; l <<= 1)
  {
    int mid = l >> 1, t = fpow(3, (MOD - 1) / l);
    if (flag)
      t = fpow(t, MOD - 2);
    for (int *p = s; p != s + len; p += l)
    {
      int w = 1;
      for (int i = 0; i < mid; ++i)
      {
        int x = p[i], y = 1LL * w * p[i + mid] % MOD;
        p[i] = (x + y) % MOD, p[i + mid] = (x - y) % MOD;
        w = 1LL * w * t % MOD;
      }
    }
  }
  if (flag)
  {
    int inv = fpow(len, MOD - 2);
    for (int i = 0; i < len; ++i)
      s[i] = 1LL * s[i] * inv % MOD;
  }
}

void polyInv(int *f, int *g, int c)
{
  if (c == 0)
  {
    g[0] = fpow(f[0], MOD - 2);
    return;
  }
  int len = 1 << c;
  polyInv(f, g, c - 1);
  for (int i = 0; i < len; ++i)
    f1[i] = f[i];
  DFT(f1, 0, len << 1, c + 1), DFT(g, 0, len << 1, c + 1);
  for (int i = 0; i < (len << 1); ++i)
    g[i] = g[i] * (2 - 1LL * f1[i] * g[i] % MOD) % MOD;
  DFT(g, 1, len << 1, c + 1);
  for (int i = len; i < (len << 1); ++i)
    g[i] = 0;
}

void d(int *f, int *g, int c)
{
  g[c - 1] = 0;
  for (int i = 0; i < c - 1; ++i)
    g[i] = 1LL * f[i + 1] * (i + 1) % MOD;
}

void d_(int *f, int *g, int c)
{
  g[0] = 0;
  for (int i = 1; i < c; ++i)
    g[i] = 1LL * f[i - 1] * fpow(i, MOD - 2) % MOD;
}

void polyLn(int *f, int *g, int c)
{
  int len = 1 << c;
  polyInv(f, g, c);
  d(f, g1, len);
  DFT(g, 0, len << 1, c + 1), DFT(g1, 0, len << 1, c + 1);
  for (int i = 0; i < (len << 1); ++i)
    g1[i] = 1LL * g[i] * g1[i] % MOD;
  DFT(g1, 1, len << 1, c + 1);
  d_(g1, g, len);
  for (int i = 0; i < (len << 1); ++i)
    f1[i] = g1[i] = 0;
  for (int i = len; i < (len << 1); ++i)
    g[i] = 0;
}

void polyExp(int *f, int *g, int c)
{
  if (c == 0)
  {
    g[0] = 1;
    return;
  }
  int len = 1 << c;
  polyExp(f, g, c - 1);
  polyLn(g, h, c);
  h[0] = (1 - h[0] + f[0]) % MOD;
  for (int i = 1; i < len; ++i)
    h[i] = (f[i] - h[i]) % MOD;
  DFT(g, 0, len << 1, c + 1), DFT(h, 0, len << 1, c + 1);
  for (int i = 0; i < (len << 1); ++i)
    g[i] = 1LL * g[i] * h[i] % MOD, h[i] = 0;
  DFT(g, 1, len << 1, c + 1);
  for (int i = len; i < (len << 1); ++i)
    g[i] = 0;
}

int main()
{
  scanf("%d%d", &n, &m);
  int bit = 0;
  while((1<<bit) < m+1) bit++;
  for(int i = 1; i <= n; ++i) {
    scanf("%d", &v[i]);
    cnt[v[i]]++;
  }
  for(int i = 1; i <= m; ++i) {
    if(!cnt[i]) continue;
    for(int j = 1; j*i <= m; ++j)
      f[i*j] = (f[i*j]+1LL*cnt[i]*fpow(j, MOD-2))%MOD;
  }
  polyExp(f, g, bit);
  for(int i = 1; i <= m; ++i) printf("%d\n", (g[i]+MOD)%MOD);
  return 0;
}