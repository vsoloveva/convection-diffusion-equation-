#include <iostream>
#include <cmath>

double U(double x, int i, double dx)
{
 //*
		return exp(-100*pow(x+i*dx-0.5,2));
/*/
	/*
	if ((x + i*dx > 1) && (x + i*dx < 3))
	{
		return 1 + cos(3.1415926535*(x + i*dx))	;
	}
	else
	{
		return 0;
	}
	*/
	//*
	//return pow(sin(3.1415926535*(x + i*dx)),4);
	/*/
		
	/*	
	if ((x + i*dx > -0.8) && (x + i*dx < -0.6))
	{
		return exp(-log(2)*pow(x + i*dx + 0.7, 2) / 0.0009);
	}
	else
	{
		if ((x + i*dx > -0.4) && (x + i*dx < -0.2))
		{
			return 1;
		}
		else
		{
			if ((x + i*dx > 0) && (x + i*dx < 0.2))
			{
				return 1 - fabs(10 * (x + i*dx) - 1);
			}
			else
			{
				if ((x + i*dx > 0.4) && (x + i*dx < 0.6))
				{
					return pow(1 - 100 * pow(x + i*dx - 0.5, 2), 0.5);
				}
				else
				{
					return 0;
				}

			}
		}
	}
	*/
	/*
	if ((x + i*dx > -0.25) && (x + i*dx < 0.25))
	{
		return 1;
	}
	else
	{
		return 0;
	}
   /*/
}

void Zap(double *xmin, double *xmax, double *CFL, double *tfin, char  **s)
{
	*xmin = 0;
	*xmax = 1;
	*CFL = 0.5;
	*tfin = 1;
	*s ="exp\\";
}
