void DeltaP3(int nstep, double *err)
{
	double xmax, xmin, dx, xi;
	double t, tfin, dtime;
	int i;
	double CFL,temp,temp2;
	char *s=(char*)malloc(20);
	char *name= (char*)malloc(200);
	char *nametime=(char*)malloc(200); 
	Zap(&xmin, &xmax, &CFL, &tfin,&s);
	int const n = 2561;
	double sol[n], sol2[n];
	double der[n],der2[n];
	sprintf(name, "%s%s%s%d%s" ,"C:\\Users\\vsolo\\Dropbox\\Schemes\\_dat\\DeltaP3\\",s, "DeltaP3_" , nstep-1 , ".dat");
	FILE* output=fopen(name, "w");
	sprintf(nametime, "%s%s%s" ,"C:\\Users\\vsolo\\Dropbox\\Schemes\\Time\\",s, "TimeDeltaP3.dat");
	FILE* Time=fopen(nametime, "a+");
	unsigned int start_time = clock();
	dx = (xmax - xmin) / (nstep - 1);
	dtime = CFL*dx;//0.00001;
	xi = xmin;
	for (i = 1; i < nstep; i++)
	{
	    sol[i] = U(xi, i, dx);
	    sol2[i]=U(xi, i, dx);
		der[i] = (U(xi, i - 1, dx) - U(xi, i + 1, dx)) / 2 ;
		der2[i] = (U(xi, i - 1, dx) - U(xi, i + 1, dx)) / 2 ;
	
	}
for (t = 0; t < tfin; t += dtime)
{
	sol2[0]=sol2[nstep-1];
	sol[0] = sol[nstep - 1];
	der[0] = der[nstep - 1];
	der2[0]=der2[nstep-1];
	for (i = 1; i < nstep; i++)
	{
		sol2[i]=(CFL-1)*(CFL-1)*(2*CFL+1)*sol[i]+CFL*CFL*(3-2*CFL)*sol[i-1]+CFL*CFL*(1-CFL)*der[i-1]-CFL*(CFL-1)*(CFL-1)*der[i];
		der2[i]=6*CFL*(1-CFL)*(sol[i]-sol[i-1])+(CFL-1)*(3*CFL-1)*der[i]+CFL*(3*CFL-2)*der[i-1];	
	}
		for (i = 1; i < nstep; i++)
	{
		sol[i]=sol2[i];
		der[i]=der2[i];
	}
	
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
