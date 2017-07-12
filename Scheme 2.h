void Scheme2(int nstep, double *err)
{
	double ksi;
	double xmin, xmax, dx, xi;
	int const n = 2561;
	double t, tfin, dtime;
	int i;
	char *S= (char*)malloc(20);
	char *name= (char*)malloc(200);
	char *nametime=(char*)malloc(200); 	
	double CFL;
	double sol[n],div[n], s[n];
	Zap(&xmin, &xmax, &CFL, &tfin,&S);
	sprintf(name, "%s%s%s%d%s" ,"C:\\Users\\vsolo\\Dropbox\\Schemes\\_dat\\Scheme 2\\",S, "Scheme2_" , nstep-1 , ".dat");
	FILE* output=fopen( name, "w");
	sprintf(nametime, "%s%s%s" ,"C:\\Users\\vsolo\\Dropbox\\Schemes\\Time\\",S, "TimeScheme2.dat");
	FILE* Time=fopen(nametime, "a+");
	unsigned int start_time = clock();
	dx = (xmax - xmin) / (nstep - 1);
	dtime =  0.002;
	xi = xmin;
	ksi = 0.5 - 0.5*CFL;
	for (i = 0; i < nstep; i++)
	{
		sol[i] = U(xi, i, dx);
		div[i] = 0;
		s[i] = 0;
	}
	for (t = 0; t < tfin; t += dtime)
	{
		sol[0] = sol[nstep - 1];
		div[0]=div[nstep-1];
		for (i = 1; i < nstep; i++)
		{
            sol[i] = sol[i] - CFL*(div[i] - div[i - 1]);
		}
				for (i = 1; i < nstep; i++)
		{
			div[i] = sol[i] + s[i] * ksi;
		}
				for (i = 1; i < nstep; i++)
		{
			s[i] = (sol[i] - sol[i - 1]) + 0.5*(s[i] - s[i - 1]) - CFL*(s[i] - s[i - 1]);
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
