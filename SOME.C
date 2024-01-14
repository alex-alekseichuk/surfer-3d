void Do_Basis()
{
 unsigned char i,ReturnKod;
 struct Rect rOld=rBas;
 Basis OldBasis=B;
 struct Win wFun;

  DefineWin(&wFun,120,100,280,265,"Basis",7,1);

  MMAccess=0;
  ShowWin(&wFun);
  setcolor(0);line(wFun.x1+3,wFun.y2-30,wFun.x2-4,wFun.y2-30);
  setcolor(15);line(wFun.x1+4,wFun.y2-29,wFun.x2-3,wFun.y2-29);
  rBas.x1=wFun.r.x1;rBas.y1=wFun.r.y1+12;rBas.x2=wFun.r.x2;rBas.y2=wFun.r.y1+135;
  ShowBasis();


  GC=DefineControl(cMain->n+2,NULL,NULL,NULL,0);
  for(i=0;i<cMain->n;i++) GC->p[i]=cMain->p[i];

    GC->p[i]=DefineButtom(135,243,"  Ok  ",2,24,NULL,7181,0,NULL,&Message_Ok);
    GC->p[i+1]=DefineButtom(210,243,"Cancel",0,46,NULL,283,0,NULL,&Message_Cancel);

  ShowControl(GC);GC->c=i;


  fBasisOnly=1; ReturnKod=Serviser(); fBasisOnly=0;

  free(GC->p[i]);free(GC->p[i+1]);free(GC->p);free(GC);


  GC=cMain;  rBas=rOld;


  if(ReturnKod==1) {
    ShowBasis();InitBasis(&B);ShowImage();
  } else { B=OldBasis; if(wFun.back) HideWin(&wFun); else ShowImage(); }


  MMAccess=1;
} /* ------------------- End of DO_BASIS ----------------- */

void Do_Full_Screen()
{
  int x,y; struct Rect rOld=rImg;
  rImg.x1=0;rImg.y1=0;rImg.x2=getmaxx();rImg.y2=getmaxy();
  InitImageArea();Desktop(0,0,getmaxx(),getmaxy());
  ShowImage();

  while(kbhit())getch();
  while(!kbhit() && !(GET_MOUSE(&x,&y)&&MOUSE_FLAG));
  while(kbhit())getch();
  rImg=rOld;InitImageArea();
  Desktop(0,0,getmaxx(),getmaxy());ShowMainMenu();DrawScreen();
}


void Do_About()
{
 char MMAccessOld=MMAccess;
 struct Win wFun;
 struct Control *cOld=GC;

  DefineWin(&wFun,170,125,170+200,95+190,"About",3,1);
  GC=DefineControl(1,NULL,NULL,NULL,0);
  GC->p[0]=DefineButtom(245,255,"  Ok  ",2,24,NULL,7181,0,NULL,&Message_Ok);

  MMAccess=0;  ShowWin(&wFun);
  setcolor(0);outtextxy(250,165,"Surfer");
  outtextxy(190,225,"Alexander Alexeychuk");
  outtextxy(198,210,"Copyright (c) 1997");
  ShowControl(GC);Process=CONTROLPROCESS;GC->c=0;

  Serviser();

  MMAccess=MMAccessOld;
  ReleaseControl(GC);  GC=cOld;
  if(wFun.back) HideWin(&wFun); else ShowImage();
}