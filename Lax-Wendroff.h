void LW(int nstep, double *err)
{
	double xmin, xmax, dx, xi;
	int const n = 2565;
	double t, tfin, dtime;
	int i;
	char *s=(char*)malloc(20);
	char *name= (char*)malloc(300);
	char *nametime=(char*)malloc(300); 	
	double  CFL;
	double sol[n],solnow[n];
	Zap(&xmin, &xmax, &CFL, &tfin,&s);
	sprintf(name, "%s%s%s%d%s" ,"C:\\Users\\vsolo\\Dropbox\\Schemes\\_dat\\Lax-Wendroff\\",s, "Lax-Wendroff_" , nstep-1 , ".dat");
	FILE* output=fopen(name, "w");
	sprintf(nametime, "%s%s%s" ,"C:\\Users\\vsolo\\Dropbox\\Schemes\\Time\\",s, "TimeLax-Wendroff.dat");
	FILE* Time=fopen(nametime, "a+");
	unsigned int start_time = clock();
	dx = (xmax - xmin) / (nstep - 1);
	dtime = CFL*dx;
	xi = xmin;
	for (i = 0; i < nstep+2; i++)
	{
		sol[i] = U(xi, i-1, dx);
	}
	for (t = 0; t < tfin; t += dtime)
	{
		for (i = 0; i < nstep+2; i++)
		{
			solnow[i]=sol[i];
		}
		for (i = 1; i < nstep+1; i++)
		{
				sol[i] = solnow[i] - 0.5*CFL*(solnow[i+1] - solnow[i - 1])+pow(CFL,2)*0.5*(solnow[i+1]-2*solnow[i]+solnow[i-1]);
        	
		}
		sol[0] = sol[nstep];
		sol[nstep+1]=sol[1];
	}
	for (i = 1; i < nstep+1; i++)
	{
		fprintf(output, "%f %f\n",(float) (xi + (i-1)*dx),(float) sol[i]);
	}
	unsigned int end_time = clock();
	unsigned int search_time = end_time - start_time;
	fprintf(Time, "%d\n", (int)search_time);
	*err = 0;
	for (i = 1; i < nstep+1; i++)
	{
		*err = *err + dx*fabs(sol[i] - U(xi, i-1, dx));
	}
	fclose(output);
	fclose(Time);
}
