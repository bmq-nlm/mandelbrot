#include <bits/stdc++.h>
#include <complex>
#include <cmath>
#include <math.h> 
using namespace std;

const complex<double> I(0.0, 1.0);
const int MAX_ITER(1000);
const int SIZE(1000);
const double ZOOM(2000);
const double STEP(0.004);
const complex<double> RE_START(-0.77568377);
const complex<double> IM_START(0.13646737);  
const string FILENAME("BITMAP.txt");

double mandelbrot(complex<double> c){
    complex<double> z = 0;
    int n = 0;
    while(abs(z)<=2 and n < MAX_ITER){
        z = z*z+c;
        n+=1;
    }
    if (n==MAX_ITER){
        return MAX_ITER;
    }
    return n + 1 - log(log2(abs(z)));
}

double to_hue(double point_escape, double max_escape){
  return point_escape/max_escape;
}

complex<double> plane(int x, int y){
  return (RE_START + (1/ZOOM)*STEP*(x-SIZE/2)) + (IM_START + (1/ZOOM)*STEP*(SIZE/2-y))*I;
}

int main(){
double bitmap[SIZE][SIZE] ={};
double maxEscape = 0;

for (int i = 0; i < SIZE; i++){
    for (int j = 0; j < SIZE; j++){
      bitmap[i][j] = mandelbrot(plane(i,j));
      if (bitmap[i][j] != MAX_ITER){
          maxEscape = max(maxEscape, bitmap[i][j]);
      }
    }
}

   for (int i = 0; i < SIZE; i++){
    for (int j = 0; j < SIZE; j++){
      if (bitmap[i][j]  == MAX_ITER){
        bitmap[i][j] = to_hue(bitmap[i][j] , MAX_ITER);
      }
      else{
        bitmap[i][j] = to_hue(bitmap[i][j] , maxEscape);
      }

    }
  }

  ofstream bitMat;
  bitMat.open (FILENAME);
  for (int j = 0; j < SIZE; j++){
    for (int i = 0; i < SIZE; i++){
      bitMat << bitmap[i][j] << " ";
    }
    bitMat << '\n';
  }
  bitMat.close();
}