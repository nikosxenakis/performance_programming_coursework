#ifndef UTIL_H
#define UTIL_H

#include <math.h>

// #pragma omp declare simd
inline void visc_wind_force(int N,double * restrict f, double vis, double * restrict velo, double * restrict wind) {
  int l;
  for(l=0; l<N; l++){
    f[l] = -vis * (velo[l] + wind[l]);
  }
}

// #pragma omp declare simd
inline double add_norm(int N, double * restrict delta) {
  int k;
  double r = 0.0;
  for(k=0;k<N;k++){
    r += (delta[k] * delta[k]);
  }

  return sqrt(r);
}

// #pragma omp declare simd inbranch
inline double force(double W, double delta, double r) {
  return W*delta/(pow(r,3.0));
}

#endif
