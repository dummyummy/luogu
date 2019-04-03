#include <bits/stdc++.h>

using namespace std;

#define ll long long

int n;

ll gcd(ll x, ll y) {
  return !y ? x : gcd(y, x%y);
}

int Len(ll x) {
  return (int)log10(x)+1;
}

void solve() {
  ll p = 1, q = 1, d;
  for(int i = 2; i <= n; ++i) {
    ll lcm = q/gcd(i, q)*i;
    p = lcm/q*p+lcm/i, q = lcm;
    d = gcd(p, q);
    p /= d, q /= d;
  }
  p *= n;
  d = gcd(p, q);
  p /= d, q /= d;
  if(p%q == 0) printf("%lld\n", p/q);
  else {
    d = p/q;
    p %= q;
    int len1, len2 = Len(q);
    if(!d) len1 = 1;
    else len1 = Len(d);
    for(int i = 1; i <= len1; ++i) printf(" ");
    printf("%lld", p);
    for(int i = Len(p)+1; i <= len2; ++i) printf(" ");
    printf("\n");
    printf("%lld", d);
    for(int i = 1; i <= len2; ++i) printf("-");
    printf("\n");
    for(int i = 1; i <= len1; ++i) printf(" ");
    printf("%lld\n", q);
  }
}

int main() {
  scanf("%d", &n);
  solve();
  return 0;
}