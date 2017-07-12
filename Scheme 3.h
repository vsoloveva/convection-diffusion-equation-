void Scheme3(int nstep, double *err)
{
	double ksi;
	double xmin, xmax, dx, xi;
	int const n = 2561;
	double t, tfin, dtime;
	double temp, tempint;
	int i;
	double CFL;
	char *s=(char*)malloc(20);
	char *name= (char*)malloc(200);
	char *nametime=(char*)malloc(200); 		
	double sol[n],solnow[n], integ[n],integnow[n], divtim[n], div[n];
	Zap(&xmin, &xmax, &CFL, &tfin,&s);
	sprintf(name, "%s%s%s%d%s" ,"C:\\Users\\vsolo\\Dropbox\\Schemes\\_dat\\Scheme 3\\",s, "Scheme3_" , nstep-1 , ".dat");
	FILE* output=fopen( name, "w");
	sprintf(nametime, "%s%s%s" ,"C:\\Users\\vsolo\\Dropbox\\Schemes\\Time\\",s, "TimeScheme3.dat");
	FILE* Time=fopen(nametime, "a+");
	FILE* outerr=fopen("out.dat", "w");
	Zap(&xmin, &xmax, &CFL, &tfin,&s);
	unsigned int start_time = clock();
	dx = (xmax - xmin) / (nstep - 1);
	dtime = CFL*dx;
	xi = xmin;
	ksi = 0.5 - 0.5*CFL;

	for (i = 1; i < nstep; i++)
	{
		sol[i] = U(xi, i, dx);
		divtim[i] = 0;
		div[i] = 0;
		integ[i] = (U(xi, i, dx) + U(xi, i - 1, dx)) / 2 * dx;
	}
	for (t = 0; t < tfin; t += dtime)
	{
		sol[0] = sol[nstep - 1];
		div[0] = div[nstep - 1];
		for (i = 1; i < nstep; i++)
		{
			solnow[i]=sol[i];
			sol[i] = sol[i] - CFL*(div[i] - div[i - 1]);
		}
		for (i = 1; i < nstep; i++)
		{
			integnow[i]=integ[i];
			integ[i] = integ[i] - 0.5*CFL*(div[i] + div[i - 1]) + 1 / 6 * (solnow[i] + 4 * divtim[i] + sol[i]);
		}
		for (i = 1; i < nstep; i++)
		{		
			div[i] = sol[i] + integ[i] * ksi;			
		}		
		for (i = 1; i < nstep; i++)
		{		
			divtim[i] = sol[i] - 0.5*CFL*(div[i] - div[i - 1]);		
		}	
	}
	for (i = 0; i < nstep; i++)
	{
		fprintf(output, "%f %f\n", (float)(xi + i*dx), (float)sol[i]);

	}
	unsigned int end_time = clock();
	unsigned int search_time = end_time - start_time;
	fprintf(Time, "%d\n", int(search_time));
	*err = 0;
	for (i = 0; i < nstep; i++)
	{
		*err = *err + dx*fabs(sol[i] - U(xi, i, dx));
		fprintf(outerr, "%f %f\n",(float)(xi + i*dx), fabs(sol[i] - U(xi, i, dx)));
	}
	fclose(output);
	fclose(Time);
	fclose(outerr);
}
