

/*******************************************************************
            IMAGES
*******************************************************************/

struct Image {
  int dx,dy;
  void *p;
};

void ReleaseImage(struct Image *im);
struct Image* LoadImage(char *fn);


/* ------- DeskTop он и в Африке DeskTop -----------*/
void Desktop(int x1,int y1,int x2,int y2);

/*▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒      Giper Global Vars ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒*/
extern int GCX0,GCY0;      /* Left-Top side of GlobalControl Area */
extern unsigned char
      Process ;             /* N след. процесса-прерывания */
extern void(*MegaFun)() ;   /* Global Function */
extern char  MMAccess ;           /* Доступ к Main Menu */
/*-------------------------------------------------------------------------
		     BOX  &  RECTANGLE
--------------------------------------------------------------------------*/
#define POP  0
#define PUSH 1

struct Rect {unsigned int x1,y1,x2,y2;}; /* Тип прямоугольник */

/*------------------- Rect (Простой) -------------------------*/
void SetRect(struct Rect *r,char m); /* Уст. Rectangle в ON или OFF режим */
/* Draw чистый Rectangle (простой) */
void DrawRect(struct Rect *r,unsigned char c,unsigned char type);
/* ------------------- Box (Сложный) ---------------------------*/
void SetNormalBox(struct Rect *r); /* Уст. Rectangle в OFF режим */
void SetActiveBox(struct Rect *r); /* Уст. Rectangle в ON режим */
void DrawBox(struct Rect *r); /* Draw чистый Rectangle (сложный) */
char InSide(struct Rect *r,int x,int y);

/*------------------------------------------------------------------------
	   Событийно-Управляемые Навороты ( Hi - Fi )
=========================================================================*/

#define CONTROLPROCESS      1  /*--------- Значения переменной Process ----- */
#define NEXTCONTROL         2
#define PREVCONTROL         3
#define PROCPROCESS         4
#define MAINMENUPROCESS     5
#define MAINMENUPUSHPROCESS 6
#define MES_1_PROCESS       7
#define MES_2_PROCESS       8


void KWControl(int k);
void MWControl(int x,int y);



/************************************************************************
         Окна Здесь
**********************************************************************/
struct Win {
  struct Rect r;
  char *s,c,save;
  void *back;
};


void DefineWin(struct Win *w,int x1,int y1,int x2,int y2,char *s,char c,char save);
void ShowWin(struct Win *w);
void HideWin(struct Win *w);
void ClipWin(struct Win *w);
void UnClipWin();


/*************************************************************************
              Mainmenu
*************************************************************************/

#define ColMM1  0
#define ColMM2  7
#define ColMM3  15
#define ColMM4  1



extern unsigned char
    MainCount ,
    MainCur   ,
    Floor     ;  /* 1 - SubMenu-On */

extern int *MainMenuX;

extern
struct MenuItem {
  char *s,sc,kod;
  void(*f)();
  struct MenuPopup {
    struct Win w;
    unsigned char n,c;
    struct MenuItem *itms;
  } *p;
} *MainMenu ;



struct MenuPopup * DefineMenuPopup(int x1,int y1,int x2,int y2,unsigned char n);

void DefineMenuItem(struct MenuItem *mi,char *s,char sc,char kod,void(*f)(),
                struct MenuPopup *p);

void ShowMainMenu();
void DoMenuPopup(struct MenuPopup * p);
void DoMainMenu(char Key_Push);


/*---------------------------------------------------------------------
		       CONTROL
----------------------------------------------------------------------*/

/* Типы Эл-тов Control'a */
enum CONTROL {BUTTOM,INPUTLINE,INPUTLINE_,POPUP,CHECKBOX,CHECKBOX_,
	      RADIOBUTTOM,USERCONTROL};

extern
struct Control {
   unsigned char n, /* Кол-во эл-тов Control'a */
	       exi,
		 c; /* N тек. Эл-та Control'a */
   enum CONTROL **p;
   void(*show)(void);
   void (*MW)(int x,int y);
   void (*KW)(int x);
	       }  *GC; /* Global Pointer to Control-Array */



/* ----------------- Подключаем ----------------*/

/*-----------------------------------------------------------------------
	     Определяем  Кнопоку
-----------------------------------------------------------------------*/

struct Buttom { /* Тип КНОПКА */
       enum CONTROL t;   /* Тип Control'a */
  char *s,sc,kod,*shk,  /* Пар-ры кнопки */
		  exi;  /* if(exi==1) then выход из Control'a (for LOCAL) */
	       int hk;  /* Hot Key Kod */
     struct Image *im;
	  struct Rect r;
	void (*f)(void);
};

struct Buttom *DefineButtom(int x,int y,char *s,char sc,char kod,
			    char *shk,int hk,char exi,struct Image *im,
			    void(*f)(void) );

/*888888888888888888888888888888888888888888888888888888888888888888
			MESSAGE
8888888888888888888888888888888888888888888888888888888888888888888*/

#define MesButOk       0
#define MesButOkCancel 1
#define MesButYesNo    2

void Message_Ok();  void Message_Cancel();

unsigned char Message(int x,int y,char *mes,char *title,unsigned char c,
							unsigned char ATTR);

/*-----------------------------------------------------------------------
		    INPUT  LINE
==========================================================================*/

struct InputLine { /* Тип СТРОКА ВВОДА */
  enum CONTROL t;   /* Тип Control'a */
  unsigned char n, /* MAX кол-во символов */
		f; /* Ширина поля ввода (в символах) */
	  char *p; /* Pointer на саму строку */
    struct Rect r;
   char *s,sc,kod;
   char (*proc)(char *s);
};

struct InputLine *DefineInputLine(int x,int y,char *p,unsigned char n,unsigned char f,
				  char *s,char sc,char kod,char (*proc)(char *));

/*-----------------------------------------------------------------------
	     Определяем  CheckBox
-----------------------------------------------------------------------*/

struct CheckBox { /* Тип CheckBox */
       enum CONTROL t;   /* Тип Control'a */
  char *s,sc,kod,*f;  /* Пар-ры кнопки */
	  struct Rect r;
};

struct CheckBox *DefineCheckBox(int x,int y,char *s,char sc,char kod,char *f);

/*    --------------------------------------------------------------------
		    POPUP
=======================================================================*/
struct Popup { /* Тип Popup */
  enum CONTROL t;   /* Тип Control'a */
  unsigned char n, /* MAX кол-во символов */
     width,height,
		c,
		top;
	  char **p; /* Pointer на сам массив опций */
    struct Rect r;
   char *s,sc,kod;
};

struct Popup *DefinePopup(int x,int y,unsigned char n,unsigned char width,
			  unsigned char height,char *s,char sc,char kod);

/*=====================================================================
            CONTROL , опpеделяемый нами
=======================================================================*/

struct UserControl { /* Тип User's  */
  enum CONTROL t;   /* Тип Control'a */
    char *s,sc,kod;  /* Пар-ры */
     struct Rect r;
     void (*show)(void); /* Shower - функция */
     void (*f)(void);    /* Doer - функция */
};

struct UserControl *DefineUserControl(int x1,int y1,int x2,int y2,
		  char *s,char sc,char kod,void(*show)(void),
		  void (*f)(void));



/*======================================================================
	    CONTROL  Functions
=========================================================================*/



struct Control *DefineControl(unsigned char n,void(*show)(void),
			      void (*MW)(int x,int y),
			      void (*KW)(int x),char exi);

void ReleaseControl(struct Control *c);

void ShowControl(struct Control *c);


int Serviser(void);




/*  Filer ------------------------------- */

#define LOAD_MODE 1
#define SAVE_MODE 0

char Filer(int x,int y,char *title,char mode,char *mask);