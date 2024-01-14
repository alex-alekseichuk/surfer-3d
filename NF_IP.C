/* NEW FUNCTION ------------------------------ - - - - - - - - - -
======================================================================*/



void New_Function()
{
 char retkod,Coing;
 struct Win wFun;
 struct Control *cFun;

  DefineWin(&wFun,100,100,400,220,"Function",7,1);

  cFun=DefineControl(10,NULL,NULL,NULL,0);  GC=cFun;
  cFun->p[0]=DefineInputLine(10,28,NULL,80,35,"~Function",0,33,NULL);
    strcpy(((struct InputLine *)cFun->p[0])->p,sFun[0]=='~'?"":sFun);
  cFun->p[1]=DefineInputLine(45,48,NULL,15,5,"Xmin",-1,33,NULL);
    gcvt( X1 , 8 , ((struct InputLine *)cFun->p[1])->p);
  cFun->p[2]=DefineInputLine(45,65,NULL,15,5,"Ymin",-1,33,NULL);
    gcvt( Y1 , 8 , ((struct InputLine *)cFun->p[2])->p);
  cFun->p[3]=DefineInputLine(135,48,NULL,15,5,"Xmax",-1,33,NULL);
    gcvt( X2 , 8 , ((struct InputLine *)cFun->p[3])->p);
  cFun->p[4]=DefineInputLine(135,65,NULL,15,5,"Ymax",-1,33,NULL);
   gcvt( Y2 , 8 , ((struct InputLine *)cFun->p[4])->p);
  cFun->p[5]=DefineInputLine(215,48,NULL,2,2,"NX",-1,33,NULL);
    gcvt( NX , 2 , ((struct InputLine *)cFun->p[5])->p);
  cFun->p[6]=DefineInputLine(215,65,NULL,2,2,"NY",-1,33,NULL);
    gcvt( NY , 2 , ((struct InputLine *)cFun->p[6])->p);
  cFun->p[7]=DefineCheckBox(20,90,"Verify",0,47,&fVerify);
  cFun->p[8]=DefineButtom(100,85," Ok  ",1,24,NULL,7181,0,i_b_Ok,&Message_Ok);
  cFun->p[9]=DefineButtom(190,85,"Cancel",0,46,NULL,283,0,i_b_Canc,&Message_Cancel);

  MMAccess=0;
  ShowWin(&wFun);  ClipWin(&wFun);
  ShowControl(GC);Process=CONTROLPROCESS;GC->c=0;

  retkod=Serviser();

  MMAccess=1; GC=cMain;  UnClipWin();

  if(retkod==1) {  /* if <--Ok-->  ===================================== */
   unsigned int i;
   float xx;
   struct POSTFIX *pf;
   char *s=((struct InputLine *)cFun->p[0])->p;

    for(i=0;i<strlen(s);i++) {
      if(s[i]=='X') s[i]='x';if(s[i]=='Y') s[i]='y';
    }
    pf=MathAnal(s,2,"x","y");
    if(!MAErr) {
      strcpy(sFun,s);
      X1=atof(((struct InputLine *)cFun->p[1])->p);
      Y1=atof(((struct InputLine *)cFun->p[2])->p);
      X2=atof(((struct InputLine *)cFun->p[3])->p);
      Y2=atof(((struct InputLine *)cFun->p[4])->p);
      xx=atoi(((struct InputLine *)cFun->p[5])->p);  NX = xx<1?1:(xx>50?50:xx);
      xx=atoi(((struct InputLine *)cFun->p[6])->p);  NY = xx<1?1:(xx>50?50:xx);

      DestroyPostFix(pFun);
      pFun=pf;
      if(!(Coing=Counting()))
	Message(wFun.r.x1+30,wFun.r.y1+30,"Bad Function or Parameters","Error",3,0);
      else {
	ShowInfoRect();
      }
    }
  }  /*  End of  --- Ok ---     ==================================== */

  ReleaseControl(cFun);
  if(retkod==2 && wFun.back) HideWin(&wFun); else ShowImage();
}


/* ======================================================================
		      Image  Parameters
 =========================================================================
 =======================================================================*/


void Img_Pars()
{
 char retkod;
 struct Win wFun;

 DefineWin(&wFun,100,100,400,220,"Image Parameters",7,1);

 GC=DefineControl(10,NULL,NULL,NULL,0);

 GC->p[0]=DefineCheckBox(10,20,"Axises",0,30,NULL);
    *(((struct CheckBox *)GC->p[0])->f)=fAxis;
 GC->p[1]=DefineCheckBox(10,35,"Limits",0,38,NULL);
    *(((struct CheckBox *)GC->p[1])->f)=fNums;
 GC->p[2]=DefineCheckBox(10,50,"Bar",0,48,NULL);
    *(((struct CheckBox *)GC->p[2])->f)=fBox;
 GC->p[3]=DefineCheckBox(10,65,"Lines",1,23,NULL);
    *(((struct CheckBox *)GC->p[3])->f)=fLevelLines;
 GC->p[4]=DefineCheckBox(100,20,"Colors",4,19,NULL);
    *(((struct CheckBox *)GC->p[4])->f)=fTwoCol;

 GC->p[5]=DefineInputLine(200,30,NULL,5,5,"x",0,45,NULL);
   strcpy(((struct InputLine *)GC->p[5])->p,AxisNames[0]);
 GC->p[6]=DefineInputLine(200,45,NULL,5,5,"y",0,21,NULL);
   strcpy(((struct InputLine *)GC->p[6])->p,AxisNames[1]);
 GC->p[7]=DefineInputLine(200,60,NULL,5,5,"z",0,44,NULL);
   strcpy(((struct InputLine *)GC->p[7])->p,AxisNames[2]);

 GC->p[8]=DefineButtom(50,85," Ok   ",1,24,NULL,7181,0,i_b_Ok,&Message_Ok);
 GC->p[9]=DefineButtom(160,85,"Cancel",0,46,NULL,283,0,i_b_Canc,&Message_Cancel);

 MMAccess=0;
 ShowWin(&wFun);  ClipWin(&wFun);
 ShowControl(GC);Process=CONTROLPROCESS;GC->c=0;

 retkod=Serviser();

 UnClipWin(&wFun);  MMAccess=1;

 if(retkod==1) {
   fAxis=*(((struct CheckBox *)GC->p[0])->f);
   fNums=*(((struct CheckBox *)GC->p[1])->f);
   fBox=*(((struct CheckBox *)GC->p[2])->f);
   fLevelLines=*(((struct CheckBox *)GC->p[3])->f);
   fTwoCol=*(((struct CheckBox *)GC->p[4])->f);

   strcpy(AxisNames[0],((struct InputLine *)GC->p[5])->p);
   strcpy(AxisNames[1],((struct InputLine *)GC->p[6])->p);
   strcpy(AxisNames[2],((struct InputLine *)GC->p[7])->p);

 }

 ReleaseControl(GC); GC=cMain;
 if(wFun.back && retkod==2) HideWin(&wFun); else ShowImage();

}