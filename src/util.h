#ifndef UTIL_H
#define UTIL_H

#include <math.h>

void vis_force(int N,double *f, double *vis, double *vel);
void add_norm(int N,double *r, double *delta);
double force(double W, double delta, double r);
void wind_force(int N,double *f, double *vis, double vel);

#endif
