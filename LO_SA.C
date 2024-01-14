int LoadSurf(char *fn)
{
 FILE *f;    char retkod=0;
 unsigned int xi,yi;

  if( !(f=fopen(fn,"rt")) ) {return(0);}
    if(!fgets(sFun,80,f)) goto Exi;    sFun[strlen(sFun)-1]='\0';
    if(11 != fscanf(f,"%2d %2d %e %e %e %e %e %e %6s %6s %6s",
       &NX,&NY,&X1,&Y1,&Z1,&X2,&Y2,&Z2,AxisNames[0],AxisNames[1],AxisNames[2]))
      goto Exi;

    for(xi=0;xi<=NX;xi++)
      for(yi=0;yi<=NY;yi++)
	if(1!=fscanf(f," %e",&(Surf[xi][yi]))) goto Exi;
    retkod=1;
Exi:  fclose(f);

  DX=2.0/((float)NX);  DY=2.0/((float)NY);               /*  Глобальные */
  gcvt(X1,4,sX1);gcvt(X2,4,sX2); gcvt(Y1,4,sY1);gcvt(Y2,4,sY2);
  gcvt(Z1,4,sZ1);gcvt(Z2,4,sZ2);

  return(retkod);
}


int SaveSurf(char *fn)
{
 FILE *f;
 unsigned int xi,yi;

  if( !(f=fopen(fn,"wt")) ) {return(0);}
  /* fprintf(f,"%s\n%5s %e %5s",sFun,"Alex",k,"Slon"); */

  fputs(sFun,f);fputc('\n',f);   /* sFun --------------------------------- */

  fprintf(f,"%2d %2d %e %e %e %e %e %e %6s %6s %6s",
	      NX,NY, X1,Y1,Z1,X2,Y2,Z2,AxisNames[0],AxisNames[1],AxisNames[2]);

  for(xi=0;xi<=NX;xi++)
    for(yi=0;yi<=NY;yi++)
      if(fprintf(f," %e",Surf[xi][yi])==EOF) {fclose(f);return(0);};

  fclose(f); return(1);
}

