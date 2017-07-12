#include <iostream>
#include <cmath>
#include "CIP.h"
#include "DeltaP3.h"
#include "Upwind.h"
#include "fd-fv.h"
#include "FDM.h" 
#include "Scheme 1.h"
#include "Scheme 2.h"
#include "Scheme 3.h"
#include "Scheme 4.h"
#include "Scheme 5.h"
#include "Lax-Wendroff.h"

int main()
{
	int i;
	char *s=(char*)malloc(20);
	double a,b,c,d;
	char *nLW= (char*)malloc(100);
	char *nCIP= (char*)malloc(100);
	char *nScheme1= (char*)malloc(100);
	char *nScheme2= (char*)malloc(100);
	char *nScheme3= (char*)malloc(100);
	char *nScheme4= (char*)malloc(100);
	char *nScheme5= (char*)malloc(100);
	//char *nScheme6= (char*)malloc(100);
	//char *nScheme7= (char*)malloc(100);
	//char *nScheme8= (char*)malloc(100);
	char *nUpwind= (char*)malloc(100);
	char *nFDM= (char*)malloc(100);
	char *nfd_fv= (char*)malloc(100);
	char *nDeltaP3= (char*)malloc(100);
	Zap(&a,&b,&c,&d,&s);
	sprintf(nScheme1, "%s%s%s" ,"C:\\Users\\vsolo\\Dropbox\\Schemes\\Errors\\",s, "errorScheme1.dat");			
	sprintf(nScheme2, "%s%s%s" ,"C:\\Users\\vsolo\\Dropbox\\Schemes\\Errors\\",s, "errorScheme2.dat");
	sprintf(nScheme3, "%s%s%s" ,"C:\\Users\\vsolo\\Dropbox\\Schemes\\Errors\\",s, "errorScheme3.dat");
	sprintf(nScheme4, "%s%s%s" ,"C:\\Users\\vsolo\\Dropbox\\Schemes\\Errors\\",s, "errorScheme4.dat");
	sprintf(nScheme5, "%s%s%s\n" ,"C:\\Users\\vsolo\\Dropbox\\Schemes\\Errors\\",s, "errorScheme5.dat");
	//sprintf(nScheme6, "%s%s%s\n" ,"C:\\Dropbox\\Schemes\\Errors\\",s, "errorScheme6.dat");
	//sprintf(nScheme7, "%s%s%s\n" ,"C:\\Dropbox\\Schemes\\Errors\\",s, "errorScheme7.dat");
	//sprintf(nScheme8, "%s%s%s\n" ,"C:\\Dropbox\\Schemes\\Errors\\",s, "errorScheme8.dat");
	sprintf(nLW, "%s%s%s" ,"C:\\Users\\vsolo\\Dropbox\\Schemes\\Errors\\",s, "errorLax-Wendroff.dat");
	sprintf(nFDM, "%s%s%s" ,"C:\\Users\\vsolo\\Dropbox\\Schemes\\Errors\\",s, "errorFDM.dat");
	sprintf(nfd_fv, "%s%s%s" ,"C:\\Users\\vsolo\\Dropbox\\Schemes\\Errors\\",s, "errorfd-fv.dat");
	sprintf(nCIP, "%s%s%s" ,"C:\\Users\\vsolo\\Dropbox\\Schemes\\Errors\\",s, "errorCIP.dat");
	sprintf(nUpwind, "%s%s%s" ,"C:\\Users\\vsolo\\Dropbox\\Schemes\\Errors\\",s, "errorUpwind.dat");
	sprintf(nDeltaP3, "%s%s%s" ,"C:\\Users\\vsolo\\Dropbox\\Schemes\\Errors\\",s, "errorDeltaP3.dat");
	double  helpCIP,helpDeltaP3,  helpUpwind, helpfd_fv, helpfd_fvint,helpFDM, helpScheme1, helpScheme2, helpScheme3,
	helpScheme4, helpScheme5, helpLW;
	double  erCIP,erDeltaP3, erUpwind, erfd_fv, erfd_fvint,erFDM,erScheme1, erScheme2,  erScheme3,
	erScheme4, erScheme5,erLW;
	FILE* ErrLW= fopen(nLW, "w");
	FILE* ErrFDM= fopen(nFDM, "w");
	FILE* ErrCIP=fopen( nCIP, "w");
	FILE* ErrScheme1=fopen( nScheme1, "w");
	FILE* ErrScheme2=fopen( nScheme2, "w");
	FILE* ErrScheme3=fopen(nScheme3, "w");
	FILE* ErrScheme4=fopen(nScheme4, "w");
	FILE* ErrScheme5=fopen(nScheme5, "w");
	FILE* ErrUpwind=fopen(nUpwind, "w");
	FILE* Errfd_fv=fopen(nfd_fv, "w");
	FILE* Errfd_fvint=fopen("errorfd_fvint.dat", "w");
	FILE* ErrDeltaP3=fopen(nDeltaP3, "w");
	helpFDM = 1;
	helpCIP = 1;
	helpLW=1;
	helpScheme1 = 1;
	helpScheme2 = 1;
	helpScheme3 = 1;	
	helpScheme4 = 1;
	helpScheme5 = 1;
	helpUpwind = 1;
	helpfd_fv = 1;
	helpfd_fvint = 1;
	helpDeltaP3=1;
	for (i = 0; i < 5; i++)
	{
		FDM((int)(pow(2, i) * 10+1), &erFDM);
		CIP((int)(pow(2, i)*10+1), &erCIP);
		Scheme1((int)(pow(2, i) * 10+1), &erScheme1);
        Scheme2((int)(pow(2, i)*10), &erScheme2);
		Scheme3((int)(pow(2, i) * 100+1 ), &erScheme3);
		Scheme4((int)(pow(2, i) * 100+ 1), &erScheme4);
		//Scheme5((int)(pow(2, i) * 100 + 1), &erScheme5);
		Upwind((int)(pow(2, i) * 100 + 1), &erUpwind);
		fd_fv((int)(pow(2, i) * 100 + 1), &erfd_fv, &erfd_fvint);
	    DeltaP3((int)(pow(2, i) * 100 + 1), &erDeltaP3);
	    LW((int)(pow(2, i) * 100 + 1), &erLW);
		fprintf(ErrCIP, "%e %f\n", erCIP, log(helpCIP / erCIP) / log(2));		
		fprintf(ErrDeltaP3, "%f %f\n", erDeltaP3, log(helpDeltaP3 / erDeltaP3) / log(2));
		fprintf(ErrUpwind, "%f %f\n", erUpwind, log(helpUpwind / erUpwind) / log(2));	
		fprintf(Errfd_fv, "%f %f\n", erfd_fv, log(helpfd_fv / erfd_fv) / log(2));
		fprintf(Errfd_fvint, "%f %f\n", erfd_fvint, log(helpfd_fvint / erfd_fvint) / log(2));	
		fprintf(ErrFDM, "%f %f\n", erFDM, log(helpFDM / erFDM) / log(2));		
		fprintf(ErrScheme1, "%e %f\n", erScheme1, log(helpScheme1 / erScheme1) / log(2));
		fprintf(ErrScheme2, "%e %f\n", erScheme2, log(helpScheme2 / erScheme2) / log(2));
		fprintf(ErrScheme3, "%f %f\n", erScheme3, log(helpScheme3 / erScheme3) / log(2));
		fprintf(ErrScheme4, "%f %f\n", erScheme4, log(helpScheme4 / erScheme4) / log(2));
		//fprintf(ErrScheme5, "%f %f\n", erScheme5, log(helpScheme5 / erScheme5) / log(2));
		fprintf(ErrLW, "%f %f\n", erLW, log(helpLW / erLW) / log(2));
		helpFDM = erFDM;
		helpCIP = erCIP;
		helpLW=erLW;
		helpScheme1 = erScheme1;
		helpScheme2 = erScheme2;
		helpScheme3 = erScheme3;
		helpScheme4 = erScheme4;
		//helpScheme5 = erScheme5;
		helpUpwind = erUpwind;
		helpfd_fv = erfd_fv;
		helpfd_fvint = erfd_fvint;
		helpDeltaP3 = erDeltaP3;
	}
	fclose(ErrCIP);
	fclose(ErrDeltaP3);
	fclose(ErrUpwind);	
	fclose(Errfd_fv);
	fclose(Errfd_fvint);
	fclose(ErrFDM);	
	fclose(ErrScheme1);
	fclose(ErrScheme2);
	fclose(ErrScheme3);
	fclose(ErrScheme4);
	//fclose(ErrScheme5);
	fclose(ErrLW);
	return 0;
}
