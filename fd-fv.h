void fd_fv(int nstep, double *err, double *errint)
{
	double xmin, xmax, dx, xi;
	int const n = 2561;
	double t, tfin, dtime;
	int i;
	char *s=(char*)malloc(20);
	double CFL;
	char *name= (char*)malloc(200);
	char*nametime=(char*)malloc(200);
	char *nameint= (char*)malloc(200);
	double sol[n], first[n], second[n], integ[n], firstint[n], secondint[n];
	Zap(&xmin, &xmax, &CFL, &tfin,&s);
	sprintf(name, "%s%s%s%d%s" ,"C:\\Users\\vsolo\\Dropbox\\Schemes\\_dat\\fd-fv\\",s, "fd-fv" , nstep-1 , ".dat");
	sprintf(nameint, "%s%d%s" , "fd-fvint" , nstep-1 , ".dat");
	FILE* outputint=fopen( nameint, "w");
	FILE* output=fopen( name, "w");
	sprintf(nametime, "%s%s%s" ,"C:\\Users\\vsolo\\Dropbox\\Schemes\\Time\\",s, "Timefd-fv.dat");
	FILE* Time=fopen(nametime, "a+");
	unsigned int start_time = clock();
	dx = (xmax - xmin) / (nstep - 1);
	dtime = CFL*dx;
	xi = xmin;

	for (i = 0; i < nstep; i++)
	{
		sol[i] = U(xi, i, dx);
		first[i] = 0;
		second[i] = 0;
		if (i != 0)
		{
			integ[i] = (U(xi, i, dx) + U(xi, i - 1, dx)) / 2;
			firstint[i] = 0;
			secondint[i] = 0;
		}

	}

	for (t = 0; t < tfin; t += dtime)
	{
		sol[0] = sol[nstep - 1];
		first[0] = first[nstep - 1];
		second[0] = second[nstep - 1];
		firstint[1] = firstint[nstep - 1];
		secondint[1] = secondint[nstep - 1];
		for (i = 1; i < nstep; i++)
		{

			firstint[i] = integ[i] + (sol[i - 1] - sol[i])*CFL;
			first[i] = sol[i] + (integ[i] - sol[i]) * 2 * CFL;
			secondint[i] = firstint[i] + (first[i - 1] - first[i])*CFL;
			second[i] = first[i] + (firstint[i] - first[i]) * 2 * CFL;
		}
		for (i = 1; i < nstep; i++)
		{
			integ[i] = (integ[i] + secondint[i]) / 2;
			sol[i] = (sol[i] + second[i]) / 2;
		}
	}

	for (i = 0; i < nstep; i++)
	{
		fprintf(output, "%f %f\n", (float)(xi + i*dx), (float)sol[i]);
	}
	for (i = 1; i < nstep; i++)
	{
		fprintf(outputint, "%f %f\n", (float)(xi + (i - 0.5)*dx), (float)integ[i]);
	}
	unsigned int end_time = clock();
	unsigned int search_time = end_time - start_time;
	fprintf(Time, "%d\n", (int)search_time);
	*err = 0;
	for (i = 0; i < nstep; i++)
	{
		*err = *err + dx*fabs(U(xi, i, dx) - sol[i]);
	}
	*errint = 0;
	for (i = 1; i < nstep; i++)
	{
		*errint = *errint + dx*fabs((U(xi, i, dx) + U(xi, i - 1, dx) / 2) - integ[i]);
	}
	fclose(outputint);
	fclose(output);
	fclose(Time);

}
