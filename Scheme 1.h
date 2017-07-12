void Scheme1(int nstep, double *err)
{
	double ksi;
	double xmin, xmax, dx, xi;
	int const n = 2561;
	double t, tfin, dtime;
	int i;
	double CFL;
	char *s=(char*)malloc(20);
	char *name= (char*)malloc(200);
	char *nametime=(char*)malloc(200); 	
	Zap(&xmin, &xmax, &CFL, &tfin, &s);
	double sol[n], div[n];
	sprintf(name, "%s%s%s%d%s" ,"C:\\Users\\vsolo\\Dropbox\\Schemes\\_dat\\Scheme 1\\",s, "Scheme1_" , nstep-1 , ".dat");
	FILE* output=fopen( name, "w");
	sprintf(nametime, "%s%s%s" ,"C:\\Users\\vsolo\\Dropbox\\Schemes\\Time\\",s, "TimeScheme1.dat");
	FILE* Time=fopen(nametime, "a+");
	unsigned int start_time = clock();
	dx = (xmax - xmin) / (nstep - 1);
	dtime =0.0000005;
	xi = xmin;
	ksi = 0.5 - 0.5*CFL;

	for (i = 0; i < nstep+2; i++)
	{
		sol[i] = (U(xi, i, dx)+U(xi, i-1, dx))/2;
		div[i] = U(xi,i-1,dx);
	}
	for (t = 0; t < tfin; t += dtime)
	{
		sol[nstep]=sol[1];
		sol[0]=sol[nstep+1];
		div[0]= div[nstep+1];
		div[nstep]=div[1];		
		for (i = 1; i < nstep+2; i++)
		{
				sol[i] = sol[i] - CFL*(div[i] - div[i - 1]);
			
		}	
		for (i = 1; i < nstep+1; i++)
		{
			if (i==nstep+1)
		{
			div[i] = sol[i] + 0.5*(sol[i] - sol[i - 1])*ksi;	
		}
		else
		{
				div[i] = sol[i] + 0.5*(sol[i + 1] - sol[i - 1])*ksi;
		}
		}
			

	}
	for (i = 1; i < nstep+1; i++)
	{
		fprintf(output, "%f %f\n", xi + (i-1)*dx, div[i]);
	}
	unsigned int end_time = clock();
	unsigned int search_time = end_time - start_time;
	fprintf(Time, "%d\n", (int)search_time);
	*err = 0;
	for (i = 0; i < nstep; i++)
	{
		*err = *err + dx*fabs(div[i] - U(xi, i, dx));
	}
	fclose(output);
	fclose(Time);
}
