#include <bits/stdc++.h>

using namespace std;

const double eps = 1e-10;

double a, b, c, d, L, R;

double f(double x) {
  return (c*x+d)/(a*x+b);
}

double simpson(double l, double r) {
  return (f(l)+4*f((l+r)/2)+f(r))*(r-l)/6;
}

double asr(double l, double r, double A) {
  double mid = (l+r)/2;
  double L = simpson(l, mid), R = simpson(mid, r);
  if(fabs(L+R-A) <= eps) return (L+R+A)/2;
  return asr(l, mid, L)+asr(mid, r, R);
}

int main() {
  cin >> a >> b >> c >> d >> L >> R;
  printf("%.6lf\n", asr(L, R, simpson(L, R)));
  return 0;
}