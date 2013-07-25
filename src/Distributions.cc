#include "Queue.h"

#define RAND_DOUBLE (double)random()/(double)RAND_MAX
//---------------------------------------------------------------------------
///  RANDOM VALS
//---------------------------------------------------------------------------

rvCnst::rvCnst (double avg) : avg(avg)
{
}
int rvCnst::Val (void)
{
  //stała wartość:
  return avg;
}

rvBin::rvBin (double newavg)
{  
  ipp = newavg * RAND_MAX+0.5;
}

int rvBin::Val (void)
{
  
  //rozkład binarny, a tak naprawdę najzwyklejszy
  rnd = rand();
  
  rnd++;
  
  return isTrue();
}

int rvBin::isTrue(void){
  // std::cout << rnd << " \n" << ipp << "\n";
  return rnd<=ipp;
}



rvExp::rvExp (double avg) : avg(avg)
{
}

int rvExp::Val (void)
{
  //rozkład wykładniczy:
  double v;
  v = double(rand())/RAND_MAX;
  v = v>0.99999? 0: (-log(1-v))*avg;
  

  return int (v+0.5);
}

rvNormal::rvNormal (double avg, double variance) : 
avg(avg), variance(variance)
{
}

int rvNormal::Val (void)
{
double u1=RAND_DOUBLE;
double u2=RAND_DOUBLE;
double z=sqrt(-2.0*log(u1))*cos(2*M_PI*u2);
return avg+variance*z;
}

rvPoisson::rvPoisson (double avg) : avg(avg)
{
}

int rvPoisson::Val (void)
{
double p=exp(-avg);
double g=p;
double u=RAND_DOUBLE;
unsigned long k=0;
while (u>g)  {
    p*=(avg/(double)(++k));
    g+=p;
 };
 return k;
}

rvBinominal::rvBinominal (unsigned long n, double p) : n(n), p(p)
{
}

int rvBinominal::Val (void)
{
double t=p/(1-p);
double u=RAND_DOUBLE;
double p0=pow((1-p),n);
double g=p0;
 unsigned int k=0;
 while (u>g)
   {
     p0*=t*(n-k)/(k+1);
     g+=p0;
     k++;
   };
 return k;
}

rvErlang::rvErlang(int order, double loc)
{
  if (order < 1){
    std::cout << "Order shouldn't be less 1\n";
    throw;
  }
  else if (loc == 0){

    std::cout << "Loc cannot be 0\n";
    throw;
  }
  else {
    scale  = 1.0 / RAND_MAX;		// scale long to [0,1]
    scale2 = 2.0 / RAND_MAX;		// auxilliary
    A = order;			// order of Erlang distribution
    a1 = A-1.0;			// auxilliary
    sq = sqrt( 2 * a1 + 1 );	// auxilliary
    B = loc;			// location parmeter
  }
}



int rvErlang::Val()
{
  if (A < 6) {	// direct method
    double x;
    do {
      x = rand() * scale;
      for (int i = 1; i < A; i++) x *= rand() * scale;
    } while (x <= 0.0);
    return ( -log(x)/B );

  } else {		// rejection method
    double x, y, b;
    do {
      do {
	double v1,v2;
	do {
	  v1 = scale2 * rand() - 1;
	  v2 = scale2 * rand() - 1;
	} while ( (v1 == 0.0) || (v1*v1 + v2*v2 > 1.0) );
	y = v2/v1;
	x = sq*y + a1;
      } while (x <= 0.0);
      b = (1.0 + y*y) * exp( a1 * log(x/a1) - sq*y );
    } while ( (scale * rand()) > b );
    return x/B;
  }
}



//---------------------------------------------------------------------------

