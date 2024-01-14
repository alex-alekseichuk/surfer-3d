#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<bios.h>
#include<string.h>
#include<alloc.h>
#include<stdarg.h>
#include<dos.h>
#include<graphics.h>
#include<math.h>

#include"mouse.h"
#include"windows.h"
#include"analysis.h"
#include"simpl_3d.h"

void Exitor()
{
  closegraph();exit(0);
}

char sFun[83]="x*y";

#include"lo_sa.c"  /* Load & Save ======================================= */


void Loader(), Saver() ;



struct Image *i_b_Ok,*i_b_Canc;

void New_Function();
void Img_Pars();
void Do_Basis();
void Do_Full_Screen();


void OurMW(int x,int y);




void InitMainMenu()
{struct MenuPopup *p,*p2;
  MainCount = 4;
  MainMenu  = calloc(MainCount,sizeof(struct MenuItem));
  MainMenuX = calloc(MainCount,sizeof(int));

  MainMenuX[0]    = 5;
  DefineMenuItem(MainMenu,"File",0,33,NULL,DefineMenuPopup(5,12,94,59,4));
    DefineMenuItem(&(MainMenu[0].p->itms[0]),"Load    F3",0,38,&Loader,NULL);
    DefineMenuItem(&(MainMenu[0].p->itms[1]),"Save    F2",0,31,&Saver,NULL);
    DefineMenuItem(&(MainMenu[0].p->itms[2]),NULL,-1,10,NULL,NULL);
    DefineMenuItem(&(MainMenu[0].p->itms[3]),"Exit Alt-x",0,18,&Exitor,NULL);

  MainMenuX[1]    = 50;
  DefineMenuItem(MainMenu+1,"Function",1,22,&New_Function,NULL);


  MainMenuX[2]    = 125;
  DefineMenuItem(MainMenu+2,"Tools",0,20,NULL,DefineMenuPopup(125,12,246,37,2));
    DefineMenuItem(&(MainMenu[2].p->itms[0]),"Basis       F7",0,48,&Do_Basis,NULL);
    DefineMenuItem(&(MainMenu[2].p->itms[1]),"Full Screen F5",0,33,&Do_Full_Screen,NULL);

  MainMenuX[3]    = 180;
  DefineMenuItem(MainMenu+3,"Options",0,24,NULL,DefineMenuPopup(180,12,270,26,1));
    DefineMenuItem(&(MainMenu[3].p->itms[0]),"Parameters",0,25,&Img_Pars,NULL);

}





struct Control *cMain = NULL;      /* Main of Main Control ------------- */


float TA=10.0;                       /*  This is the Angle of Rotation */
char fBasisOnly = 0;



struct Rect   /* --------------------------------  Some of Main Rects  */
  rInf={2,350,525,438},
  rBut={527,15,636,144};

/* ----------------------------------- This Function Init. 4 screen area */
void InitMainRects()
{
  rImg.x1=0;rImg.x2=rBut.x1-4;rImg.y1=rBut.y1;rImg.y2=getmaxy()-50;
  rInf.x2=rImg.x2;rInf.y1=rImg.y2+4;rInf.y2=getmaxy()-3;
  rBas.x1=rBut.x1;rBas.x2=rBut.x2;
  rBas.y2=getmaxy()-3;rBas.y1=rBas.y2-(rBas.x2-rBas.x1)*getmaxy()/getmaxx();
}








void ShowButtonsRect() /* ============-=-=-=-=-=-=-======================= */
{
  DrawRect(&rBut,7,PUSH);
  ShowControl(GC);
}


void ShowInfoRect()
{
auto char s[15];
  DrawRect(&rInf,7,PUSH);
  setviewport(rInf.x1,rInf.y1,rInf.x2,rInf.y2,1);
  setcolor(0);

    if(sFun[0]!='~') outtextxy(5,2,"z=");

    outtextxy(5,12,"Xmin=");outtextxy(155,12,"Ymin=");outtextxy(305,12,"Zmin=");
    outtextxy(5,22,"Xmax=");outtextxy(155,22,"Ymax=");outtextxy(305,22,"Zmax=");
    outtextxy(455,12,"NX=");outtextxy(455,22,"NY=");
    outtextxy(5+16,32,"dX=");outtextxy(155+16,32,"dY=");outtextxy(305+16,32,"dZ=");
  setcolor(sFun[0]=='~'?11:10);
    outtextxy(23,2,sFun[0]=='~'?sFun+1:sFun);
    gcvt(X1,4,s);outtextxy(5+43,12,s);
    gcvt(Y1,4,s);outtextxy(155+43,12,s);
    gcvt(Z1,4,s);outtextxy(305+43,12,s);
    gcvt(X2,4,s);outtextxy(5+43,22,s);
    gcvt(Y2,4,s);outtextxy(155+43,22,s);
    gcvt(Z2,4,s);outtextxy(305+43,22,s);
    itoa(NX,s,10);outtextxy(455+27,12,s);
    itoa(NY,s,10);outtextxy(455+27,22,s);
    gcvt((X2-X1)/NX,4,s);outtextxy(5+43,32,s);
    gcvt((Y2-Y1)/NY,4,s);outtextxy(155+43,32,s);
    gcvt((Z2-Z1)/10,4,s);outtextxy(305+43,32,s);
  setviewport(0,0,getmaxx(),getmaxy(),1);
}

#include"turn.c"


/* Отрисовка всего экрана ---------------------------------------------- */
void DrawScreen()
{
  InitBasis(&B);
  /* SetRect(&rImg,PUSH); */  ShowImage();
  ShowInfoRect();
  ShowButtonsRect();
  SetRect(&rBas,PUSH);ShowBasis();
}




/* ====================================================================
	       New Function   &  Image Parameters
====================================================================*/
#include"nf_ip.c"



void ShowBasisBox(char c){char i,j;  setcolor(c);

  for(i=-1;i<=1;i+=2)
    for(j=-1;j<=1;j+=2) {
	Line3D(i,j,-1,i,j,1);Line3D(-1,i,j,1,i,j);Line3D(i,-1,j,i,1,j);
    }
}

void OurMW(int x,int y)
{
 /*  Basis ========================================================== */
  if(InSide(&rBas,x,y)){ Process=PROCPROCESS;MegaFun=&Do_Basis;  return; }
 /* Mouse-Visual-Turn ================================================ */
  if(InSide(&rImg,x,y)){int x,y,k,x0,y0,xx,yy; char c=1;
    if(1==GET_MOUSE(&x0,&y0)) { Basis OldB=B;float OldA=TurnAngle;
      setfillstyle(1,Colors[ColBacImg]);bar(rImg.x1+1,rImg.y1+1,rImg.x2-1,rImg.y2-1);
      ShowBasisBox(10);
      k=GET_MOUSE(&xx,&yy);
      while(1==k) {
	k=GET_MOUSE(&x,&y);
	if( y!=yy || x!=xx ) { xx=x;yy=y;
	  ShowBasisBox(Colors[ColBacImg]);
	  B=OldB;
	  TurnAngle=(float)(y0-y)/2; Turn3DTop();
	  TurnAngle=(float)(x0-x)/2; Turn3DLef();
	  ShowBasisBox(10);
	}
      }
      SET_MOUSE(300,170);
      if(!k) {ShowBasis();InitBasis(&B);ShowImage();}
      else {B=OldB;ShowImage();}
      TurnAngle=OldA;
    }
  return; }

  MWControl(x,y);
}

void OurKW(int k)
{
  switch(k) {
    case 11520 : Process=PROCPROCESS;MegaFun=&Exitor;break;  /*  Alt-X  */
    case 15360 : Process=PROCPROCESS;MegaFun=&Saver;break;  /*  F2  */
    case 15616 : Process=PROCPROCESS;MegaFun=&Loader;break;  /*  F3  */
    case 15872 : Process=PROCPROCESS;MegaFun=&New_Function;break;  /*  F3  */
    case 16128 : Process=PROCPROCESS;MegaFun=&Do_Full_Screen;break;  /*  F5  */
    case 16640 : Process=PROCPROCESS;MegaFun=&Do_Basis;break;  /*  F7  */
    case 283   : Process=PROCPROCESS;MegaFun=NULL;break;

    default : KWControl(k);
  }
}


void Loader()
{
 char s[85]="*.sur";
  if(Filer(150,100,"Load Surface",LOAD_MODE,s)) {
    if(LoadSurf(s)) {ShowImage();ShowInfoRect();}
    else Message(150,100,"Bad Data","Error",3,0);
  }
}

void Saver()
{
 char s[85]="*.sur";
  if(Filer(150,100,"Save Surface",SAVE_MODE,s))
    if(!SaveSurf(s)) Message(150,100,"Write Error","Error",3,0);
}

#include"some.c"

void main(void)
{int gd=0,gm=1;

/* =====================================  INITIALIZATION ================= */
InitMainMenu();                     /* MainMenu      */
initgraph(&gd,&gm,"");              /* BGI           */
INIT_MOUSE();                       /* MOUSE         */
InitMathAn();                       /* Math Analysis */
InitMainRects();
InitImageArea();

pFun=MathAnal(sFun,2,"x","y");
PushCS();GCS->t=CS_NUM;PushCS();GCS->t=CS_NUM;

TA=5;
i_b_Ok=LoadImage("but_ok.img");i_b_Canc=LoadImage("but_canc.img");


Desktop(0,0,getmaxx(),getmaxy());
ShowMainMenu();

cMain=DefineControl(7,NULL,&OurMW,&OurKW,1);
GC=cMain;

/* Main Contolr's Definitions ----------=-=-=-=-=-=-=-=-----------------
-----------------------=-=-=-=-=-------------------------=-=-=-=-=-=-=- */
cMain->p[0]=DefineButtom(rBut.x1+5,rBut.y1+15,NULL,0,71,NULL,15360,0,LoadImage("standart.img"),&pStandart);
cMain->p[1]=DefineButtom(rBut.x1+40,rBut.y1+15,NULL,0,72,NULL,15360,0,LoadImage("kolotop.img"),&pKoloTop);
cMain->p[2]=DefineButtom(rBut.x1+75,rBut.y1+15,NULL,0,73,NULL,15360,0,LoadImage("kolosudi.img"),&pKoloSudi);
cMain->p[3]=DefineButtom(rBut.x1+5,rBut.y1+50,NULL,0,75,NULL,15360,8,LoadImage("kololef.img"),&pKoloLef);
cMain->p[4]=DefineButtom(rBut.x1+75,rBut.y1+50,NULL,0,77,NULL,15360,0,LoadImage("kolorig.img"),&pKoloRig);
cMain->p[5]=DefineButtom(rBut.x1+40,rBut.y1+85,NULL,0,80,NULL,15360,0,LoadImage("kolobot.img"),&pKoloBut);
cMain->p[6]=DefineButtom(rBut.x1+75,rBut.y1+85,NULL,0,81,NULL,15360,0,LoadImage("kolotudi.img"),&pKoloTudi);

Counting();

DrawScreen();

Do_About();

Serviser();
}

