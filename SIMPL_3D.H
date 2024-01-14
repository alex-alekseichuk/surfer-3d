
#define ColWeb1     0
#define ColWeb2     1
#define ColWeb2     2
#define ColAxs      3
#define ColAxsNames 4
#define ColAxsNums  5
#define ColMarks    6
#define ColLevLin   7
#define ColBacImg   8

extern char Colors[];

typedef struct
{ float x,y,z; } Vector;

typedef struct
{ Vector Ox,Oy,Oz;            /* Наши вектора репера */
  struct { char x,y,z; } S;  /* вершина единич-го пар-да , кот-я не видна */
  char Xy,Xz,Yx,Yz,Zx,Zy;      /* коор-ты рис-х осей */
  char Xdx,Xdy,Ydx,Ydy,Zdx,Zdy; /* отклонение от оси во внешн. сторону */
} Basis;

extern Basis B ;     /* Наш базис */

#define Pi 3.14159265358

extern float TurnAngle;



void Turn3DTudi();
void Turn3DSudi();
void Turn3DTop();
void Turn3DBut();
void Turn3DRig();
void Turn3DLef();
void InitBasis(Basis *b) ;  /* Инициализация базиса после его изменения */


/********************************************************************
	   Глобальные Параметры и массивы данных
**************************************************************************/


extern
  struct Rect rImg , rBas ;
extern
  int wImg,hImg,     /* Width and Hieght of Image Area */
      WX0,WY0,                /* Реальные координаты Центра Screen Area */
      WKX,WKY;                /* Коеф-ты , зависящие от Screen Area */


void InitImageArea();

/* Attributs of 3D-Image ---------------------------------------------- */
extern char
		   fAxis ,    /* 1 - Draw Axis */
		   fNums ,         /* Draw Nums of Axis */
		    fBox ,    /* 1 - Draw Koord's Box */
	     fLevelLines ,         /* 1 - Draw Level Lines */
		 fTwoCol ,    /* 1 - Two-Colors Filling */
		  fVerify;  /* 1 - Verify of Maths Calculus without Errors */

#define XMAX 51  /* Max Step of RAZBIENIYA  */
#define YMAX 51

extern unsigned char NX , NY ;    /* Real Число прямоугл. в разбиении по X и Y */

extern float X1,Y1,X2,Y2,Z1,Z2, /* BИРТУАЛЬНЫЕ ГРАНИЦЫ области по X Y Z*/
	      DX,DY,                       /* Виртуальный шаг разбиения по X и Y */
	      Surf[XMAX][YMAX];            /* Массив Виртуальных значений функци
                                       (по X , потом по Y) */

extern char sX1[],sX2[],sY1[],sY2[],sZ1[],sZ2[];

extern char *AxisNames[] ;


extern struct PostFix *pFun;


void Line3D(float x1,float y1,float z1,float x2,float y2,float z2);

/***************************************************************************
	 Функция исчисления значений z=f(x,y) и многое другое
****************************************************************************/
char Counting() ;

void ShowBasis();

/***********************************************************************

**************************************************************************/
void ShowImage();
