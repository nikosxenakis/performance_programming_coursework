#ifndef UTIL
#define UTIL

#include <math.h>

// inline void
// visc_force (int N, double *f, double *vis, double *velo)
// {
//   int i;
//   for (i = 0; i < N; i++)
//   {
//     f[i] = -vis[i] * velo[i];
//   }
// }

// inline void
// wind_force (int N, double *f, double *vis, double velo)
// {
//   int i;
//   for (i = 0; i < N; i++)
//   {
//     f[i] = f[i] - vis[i] * velo;
//   }
// }

#pragma omp declare simd
inline void wind_visc_force(int N, double * restrict f, double vis, double * restrict velo, const double * restrict wind) {
  int i;
  for (i = 0; i < N; i++) {
    f[i] = - vis * (velo[i] + wind[i]);
  }
}

// inline void add_norm(int N, double * restrict r, double * restrict delta)
// {
//   int k;
//   for(k=0;k<N;k++){
//     *r += pow(delta[k],2.0);
//   }
// }

#pragma omp declare simd
inline double add_norm(int N, double * restrict delta) {
  int k;
  double r = 0.0;

  for(k=0; k<N; k++) {
    r += pow(delta[k], 2.0);
  }
  return r;
}

#pragma omp declare simd inbranch
inline double force (double W, double delta, double r)
{
  return W * delta / (pow (r, 3.0));
}

#endif
