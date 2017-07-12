void Scheme4(int nstep, double *err)
{
	double ksi;
	double xmin, xmax, dx, xi;
	int const n = 2561;
	double t, tfin, dtime;
	int i;
	char *s=(char*)malloc(20);
	char *name= (char*)malloc(200);
	char *nametime=(char*)malloc(200); 		
	double CFL;
	double sol[n],integ[n], P0[n],P1[n],P2[n];
	Zap(&xmin, &xmax, &CFL, &tfin,&s);
	sprintf(name, "%s%s%s%d%s" ,"C:\\Users\\vsolo\\Dropbox\\Schemes\\_dat\\Scheme 4\\",s, "Scheme4_" , nstep-1 , ".dat");
	FILE* output=fopen( name, "w");
	sprintf(nametime, "%s%s%s" ,"C:\\Users\\vsolo\\Dropbox\\Schemes\\Time\\",s, "TimeScheme4.dat");
	FILE* Time=fopen(nametime, "a+");
	unsigned int start_time = clock();
	dx = (xmax - xmin) / (nstep - 1);
	dtime = CFL*dx;
	xi = xmin;
	ksi = 0.5 - 0.5*CFL;
	for (i = 1; i < nstep; i++)
	{
		sol[i] = U(xi, i, dx);
		integ[i] = (U(xi, i, dx)+U(xi, i-1, dx))/2*dx;
		P0[i]=U(xi, i, dx);
		P1[i]=0;
		P2[i]=0;
	}
	for (t = 0; t < tfin; t += dtime)
	{
		sol[0] = sol[nstep - 1];
		integ[0]=integ[nstep-1];
		P0[0]=P0[nstep-1];
	    P1[0]=P1[nstep-1];
		P2[0]=P2[nstep-1];
		for (i = 1; i < nstep; i++)
		{
            P0[i]=sol[i];
            if (i==nstep-1)
            {
			    P1[i]=0.5*(sol[i]-sol[i-1]);
            	P2[i]=0.5*(sol[i]-2*sol[i]+sol[i-1]);            	
			}
            else
            {
			    P1[i]=0.5*(sol[i+1]-sol[i-1]);
            	P2[i]=0.5*(sol[i+1]-2*sol[i]+sol[i-1]);
        	}	
		}

		for (i = 1; i < nstep; i++)
		{
			integ[i]=P0[i]+P1[i]*(0.5-0.5*CFL)+P2[i]*(0.5-0.5*CFL+pow(CFL,2)/3);
		}
		for (i = 1; i < nstep; i++)
		{
			sol[i] = sol[i] - CFL* (integ[i]-integ[i-1]);
		}
	}
		
	for (i = 0; i < nstep; i++)
	{
		fprintf(output, "%f %f\n", (float)(xi + i*dx),(float)sol[i]);
	}
	unsigned int end_time = clock();
	unsigned int search_time = end_time - start_time;
	fprintf(Time, "%d\n", search_time);
	*err = 0;
	for (i = 0; i < nstep; i++)
	{
		*err = *err + dx*fabs(sol[i] - U(xi, i, dx));
	}
}
