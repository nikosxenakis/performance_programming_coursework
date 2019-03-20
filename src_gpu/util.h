#ifndef UTIL
#define UTIL

#include <math.h>

// #pragma omp declare simd
inline double visc_wind_force(double vis, double velo, double wind) {
  return -vis * (velo + wind);
}

// #pragma omp declare simd
inline double add_norm(int N, double * restrict delta) {
  int k;
  double r = 0.0;

  for(k=0; k<N; k++) {
    r += delta[k]*delta[k];
  }
  return sqrt(r);
}

// #pragma omp declare simd inbranch
inline double force (double W, double delta, double r)
{
  return W * delta / (pow (r, 3.0));
}

#endif
