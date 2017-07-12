void FDM(int nstep, double *err)
{
	double xmin, xmax, dx, xi;
	int const n = 2561;
	double t, tfin, dtime;
	int i;
	double CFL;
	char *s=(char*)malloc(20);
	char *name= (char*)malloc(100);
	char *exact= (char*)malloc(100);
	char *nametime= (char*)malloc(100);
	double sol[n], first[n], second[n];
	Zap(&xmin, &xmax, &CFL, &tfin,&s);
	sprintf(name, "%s%s%s%d%s" ,"C:\\Users\\vsolo\\Dropbox\\Schemes\\_dat\\FDM\\",s, "FDM" , nstep-1 , ".dat");
	FILE* output = fopen(name, "w");
	sprintf(exact, "%s%s%s%d%s" ,"C:\\Users\\vsolo\\Dropbox\\Schemes\\_dat\\Exact Solution\\",s, "Exact" , nstep-1 , ".dat");
	FILE* Exact = fopen(exact, "w");
	sprintf(nametime, "%s%s%s" ,"C:\\Users\\vsolo\\Dropbox\\Schemes\\Time\\",s, "TimeFDM.dat");
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
	}
	for (t = 0; t < tfin; t += dtime)
	{
		sol[0] = sol[nstep - 1];
		first[0] = first[nstep - 1];
		second[0] = second[nstep - 1];
		for (i = 0; i < nstep; i++)
		{

			if (i == 1)
			{
				first[i] = sol[i] + 0.5*(4 * sol[i - 1] - sol[nstep - 1] - 3 * sol[i])*CFL;
				second[i] = first[i] + 0.5*(4 * first[i - 1] - first[nstep - 1] - 3 * first[i])*CFL;
			}
			else

			{
				if (i != 0)
				{
					first[i] = sol[i] + 0.5*(4 * sol[i - 1] - sol[i - 2] - 3 *sol[i])*CFL;
					second[i] = first[i] + 0.5*(4 * first[i - 1] - first[i - 2] - 3 * first[i])*CFL;
				}
			}

		}

		for (i = 0; i < nstep; i++)
		{
			sol[i] = (sol[i] + second[i]) / 2;
		}
	}
	for (i = 0; i < nstep; i++)
	{
		fprintf(output, "%f %f\n",(float)(xi + i*dx), (float)(sol[i]));
	}
	unsigned int end_time = clock();
	unsigned int search_time = end_time - start_time;
	fprintf(Time, "%d\n", (int)(search_time));
	*err = 0;
	for (i = 0; i < nstep; i++)
	{
		*err = *err + dx*fabs(U(xi, i, dx) - sol[i]);
	}
	for (i = 0; i < nstep; i++)
	{
		fprintf(Exact, "%f %f\n", (float)(xi + i*dx), (float)U(xi, i, dx));
	}
	fclose(Exact);
	fclose(output);
	fclose(Time);
}
