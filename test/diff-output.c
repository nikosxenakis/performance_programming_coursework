/*
 *
 * program to diff the output of the MD program
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define  Nbody 4*1024

#define WARN_LEVEL 0.001
#define ERROR_LEVEL 0.05

double error(double v1, double v2){
  double diff = fabs(v1 -v2);
  double sum = fabs(v1+v2);
  if( sum != 0.0 ){
    // normalise
    diff = diff / sum;
  }
  return diff;
}
int main(int argc, char *argv[]){
int i;
double q1,q2,q3,q4,q5,q6,q7,q8;
double t1,t2,t3,t4,t5,t6,t7,t8;
double d1,d2,d3,d4,d5,d6,d7,d8, dt;
double max;
FILE *in, *in2;
int status=0;

  if(argc != 3 ){
    fprintf(stderr,"useage:%s file1 file2\n",argv[0]);
    exit(1);
  }
/* read the initial data from a file */

  in = fopen(argv[1],"r");

  if( ! in ){
    perror(argv[1]);
    exit(1);
  }

  in2 = fopen(argv[2],"r");

  if( ! in2 ){
    perror(argv[2]);
    exit(1);
  }



  max=0.0;
  for(i=0;i<Nbody;i++){
    fscanf(in,"%16le%16le%16le%16le%16le%16le%16le%16le\n",
      &q1,&q2,&q3,&q4,&q5,&q6,&q7,&q8);

    fscanf(in2,"%16le%16le%16le%16le%16le%16le%16le%16le\n",
      &t1,&t2,&t3,&t4,&t5,&t6,&t7,&t8);
      
    d1 = error(t1,q1);
    d2 = error(t2,q2);
    d3 = error(t3,q3);
    d4 = error(t4,q4);
    d5 = error(t5,q5);
    d6 = error(t6,q6);
    d7 = error(t7,q7);
    d8 = error(t8,q8);
    dt = d1+d2+d3+d4+d5+d6+d7+d8;

    if( dt > WARN_LEVEL ){ 
      if( dt > max ){ 
        printf("!!!New max!!!\n");
      }
      printf("%d< %16.8E%16.8E%16.8E%16.8E%16.8E%16.8E%16.8E%16.8E\n",i,
        q1,q2,q3,q4,q5,q6,q7,q8);
      printf("%d> %16.8E%16.8E%16.8E%16.8E%16.8E%16.8E%16.8E%16.8E\n",i,
        t1,t2,t3,t4,t5,t6,t7,t8);
      printf("%d: %16.8E%16.8E%16.8E%16.8E%16.8E%16.8E%16.8E%16.8E\n",i,
        d1,d2,d3,d4,d5,d6,d7,d8);
      printf("\n");
    }
    if( dt > max ){ 
        max = dt; 
    }

	
  }
  fclose(in);
  fclose(in2);

  printf("max=%lf\n",max);
  if( max > ERROR_LEVEL ){
     return 1;
  }else{
    return 0;
  }
}
