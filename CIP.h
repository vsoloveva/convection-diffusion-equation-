#include "input.h"
#include <iostream>
#include <cmath>	
#include <ctime>
#include <cstdlib>
double r (int i, double IL, double IR,double alpha)
{
	return (i >= IL && i <= IR) ? alpha : 1.0;
}

void CIP(int nstep, double *err)
{
	double xmax, xmin, dx, xi;
	double t, tfin, dtime;
	int i;
	double CFL;
	char *s=(char*)malloc(20);
	char *name= (char*)malloc(100);
	char *nametime= (char*)malloc(100);
	Zap(&xmin, &xmax, &CFL, &tfin, &s);
	int const n = 2561;
	double sol[n];
	double der[n];
	sprintf(name, "%s%s%s%d%s" ,"C:\\Users\\vsolo\\Dropbox\\Schemes\\_dat\\CIP\\",s, "CIP" , nstep-1 , ".dat");
	FILE* output=fopen(name, "w");
	sprintf(nametime, "%s%s%s" ,"C:\\Users\\vsolo\\Dropbox\\Schemes\\Time\\",s, "TimeCIP.dat");
	FILE*Time=fopen(nametime, "a+");
	unsigned int start_time = clock();
	dx = (xmax - xmin) / (nstep - 1);
	dtime =0.00025;//CFL*dx;
	xi = xmin;
	//IL=(nstep-1)/4;
	//NM=(nstep-1)/100;
	//IR=IL+20*NM-1;
	//alpha=1.0;	
	//}
	for (i = 1; i < nstep; i++)
	{
	    sol[i] = U(xi, i, dx);
		der[i] =(U(xi, i + 1, dx) - U(xi, i - 1, dx)) / 2 / dx;
	}
double A[n], B[n], C[n], D[n];
for (t = 0; t < tfin; t += dtime)
{
	xi = dtime;
	sol[0] = sol[nstep - 1];
	der[0] = der[nstep - 1];
	for (i = 1; i < nstep; i++)
	{
		A[i] = 2 / (dx*dx*dx)*(sol[i - 1] - sol[i]) + 1 / (dx * dx)*(der[i - 1] + der[i]);
		B[i] = 3 / (dx * dx) *(sol[i] - sol[i - 1]) - 1 / dx*(2 * der[i - 1] + der[i]);
		C[i] = der[i - 1];
		D[i] = sol[i - 1];
	}	
	for (i = 1; i < nstep; i++)
	{
		sol[i] = A[i]*xi*xi*xi + B[i]*xi*xi + C[i]*xi + D[i];
		der[i] = 3 * A[i]*xi*xi + 2 * B[i]*xi + C[i];
	}
	xi = xmin;
}
for (i = 0; i < nstep; i++)
{
	fprintf(output, "%f %f\n", (float)(xi + i*dx), (float)sol[i]);
}

unsigned int end_time = clock();
unsigned int search_time = end_time - start_time;
fprintf(Time, "%d\n", (int)search_time);
*err = 0;
for (i = 0; i < nstep; i++)
{
	*err = *err + dx*fabs(sol[i] - U(xi, i, dx));
}
fclose(output);
fclose(Time);
}

