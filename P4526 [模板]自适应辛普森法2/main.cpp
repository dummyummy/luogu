#include <bits/stdc++.h>

using namespace std;

const double eps = 1e-10;

double a;

double f(double x) {
  return pow(x, a/x-x);
}

double simpson(double l, double r) {
  return (f(l)+4*f((l+r)/2)+f(r))*(r-l)/6;
}

double ars(double l, double r, double A) {
  double mid = (l+r)/2;
  double L = simpson(l, mid), R = simpson(mid, r);
  if(fabs(L+R-A) <= eps) return (L+R+A)/2;
  return ars(l, mid, L)+ars(mid, r, R);
}

int main() {
  cin >> a;
  if(a < 0) printf("orz\n");
  else printf("%.5lf\n", ars(eps, 20, simpson(eps, 20)));
  return 0;
}