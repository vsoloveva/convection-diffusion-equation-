void Upwind(int nstep, double *err)
{
	double xmin, xmax, dx, xi;
	int const n = 2561;
	double t, tfin, dtime;
	int i;
	char *s=(char*)malloc(20);
	char *name= (char*)malloc(100);
	char *nametime= (char*)malloc(100);
	double  CFL;
	double sol[n],solnow[n];
	Zap(&xmin, &xmax, &CFL, &tfin, &s);
	sprintf(name,"%s%s%s%d%s" ,"C:\\Users\\Dropbox\\Schemes\\_dat\\Upwind\\",s,"Upwind" , nstep-1 , ".dat");
	FILE* output=fopen(name, "w");
	sprintf(nametime, "%s%s%s" ,"C:\\Users\\vsolo\\Dropbox\\Schemes\\Time\\",s, "TimeUpwind.dat");
	FILE* Time=fopen(nametime, "a+");
	unsigned int start_time = clock();
	dx = (xmax - xmin) / (nstep - 1);
	dtime = CFL*dx;
	xi = xmin;
	for (i = 0; i < nstep; i++)
	{
		sol[i] = U(xi, i, dx);
	}
	for (t = 0; t < tfin; t += dtime)
	{
		sol[0] = sol[nstep - 1];
		solnow[0]=sol[nstep-1];
		for (i = 1; i < nstep; i++)
		{
			solnow[i]=sol[i];
			sol[i] = solnow[i] - CFL*(solnow[i] - solnow[i - 1]);
		}
	}
	for (i = 0; i < nstep; i++)
	{
		fprintf(output, "%f %f\n",(float) (xi + i*dx),(float) sol[i]);
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
