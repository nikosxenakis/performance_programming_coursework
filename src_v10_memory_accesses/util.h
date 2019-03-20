#ifndef UTIL_H
#define UTIL_H

#include <math.h>

// inline void visc_force(int N,double * restrict f, double vis, double * restrict velo) {
//   int l;
//   for(l=0; l<N; l++) {
//     f[l] = -vis * velo[l];
//   }
// }

// inline void wind_force(int N,double * restrict f, double vis, double * restrict wind) {
//   int l;
//   for(l=0; l<N; l++){
//     f[l] += -vis * wind[l];
//   }
// }

inline double visc_wind_force(double vis, double velo, double wind) {
  return -vis * (velo + wind);
}

inline double add_norm(int N, double * restrict delta) {
  int k;
  double r = 0.0;
  for(k=0;k<N;k++){
    r += (delta[k] * delta[k]);
  }

  return sqrt(r);
}

inline double force(double W, double delta, double r) {
  return W*delta/(pow(r,3.0));
}

#endif
