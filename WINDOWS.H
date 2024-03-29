

/*******************************************************************
            IMAGES
*******************************************************************/

struct Image {
  int dx,dy;
  void *p;
};

void ReleaseImage(struct Image *im);
struct Image* LoadImage(char *fn);


/* ------- DeskTop �� � � ��ਪ� DeskTop -----------*/
void Desktop(int x1,int y1,int x2,int y2);

/*��������������������������������������������������������������������������
���������������������      Giper Global Vars �������������������������������
��������������������������������������������������������������������������*/
extern int GCX0,GCY0;      /* Left-Top side of GlobalControl Area */
extern unsigned char
      Process ;             /* N ᫥�. �����-���뢠��� */
extern void(*MegaFun)() ;   /* Global Function */
extern char  MMAccess ;           /* ����� � Main Menu */
/*-------------------------------------------------------------------------
		     BOX  &  RECTANGLE
--------------------------------------------------------------------------*/
#define POP  0
#define PUSH 1

struct Rect {unsigned int x1,y1,x2,y2;}; /* ��� ��אַ㣮�쭨� */

/*------------------- Rect (���⮩) -------------------------*/
void SetRect(struct Rect *r,char m); /* ���. Rectangle � ON ��� OFF ०�� */
/* Draw ���� Rectangle (���⮩) */
void DrawRect(struct Rect *r,unsigned char c,unsigned char type);
/* ------------------- Box (������) ---------------------------*/
void SetNormalBox(struct Rect *r); /* ���. Rectangle � OFF ०�� */
void SetActiveBox(struct Rect *r); /* ���. Rectangle � ON ०�� */
void DrawBox(struct Rect *r); /* Draw ���� Rectangle (᫮���) */
char InSide(struct Rect *r,int x,int y);

/*------------------------------------------------------------------------
	   ����⨩��-��ࠢ�塞� ������� ( Hi - Fi )
=========================================================================*/

#define CONTROLPROCESS      1  /*--------- ���祭�� ��६����� Process ----- */
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
         ���� �����
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

/* ���� ��-⮢ Control'a */
enum CONTROL {BUTTOM,INPUTLINE,INPUTLINE_,POPUP,CHECKBOX,CHECKBOX_,
	      RADIOBUTTOM,USERCONTROL};

extern
struct Control {
   unsigned char n, /* ���-�� ��-⮢ Control'a */
	       exi,
		 c; /* N ⥪. ��-� Control'a */
   enum CONTROL **p;
   void(*show)(void);
   void (*MW)(int x,int y);
   void (*KW)(int x);
	       }  *GC; /* Global Pointer to Control-Array */



/* ----------------- ������砥� ----------------*/

/*-----------------------------------------------------------------------
	     ��।��塞  �������
-----------------------------------------------------------------------*/

struct Buttom { /* ��� ������ */
       enum CONTROL t;   /* ��� Control'a */
  char *s,sc,kod,*shk,  /* ���-�� ������ */
		  exi;  /* if(exi==1) then ��室 �� Control'a (for LOCAL) */
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

struct InputLine { /* ��� ������ ����� */
  enum CONTROL t;   /* ��� Control'a */
  unsigned char n, /* MAX ���-�� ᨬ����� */
		f; /* ��ਭ� ���� ����� (� ᨬ�����) */
	  char *p; /* Pointer �� ᠬ� ��ப� */
    struct Rect r;
   char *s,sc,kod;
   char (*proc)(char *s);
};

struct InputLine *DefineInputLine(int x,int y,char *p,unsigned char n,unsigned char f,
				  char *s,char sc,char kod,char (*proc)(char *));

/*-----------------------------------------------------------------------
	     ��।��塞  CheckBox
-----------------------------------------------------------------------*/

struct CheckBox { /* ��� CheckBox */
       enum CONTROL t;   /* ��� Control'a */
  char *s,sc,kod,*f;  /* ���-�� ������ */
	  struct Rect r;
};

struct CheckBox *DefineCheckBox(int x,int y,char *s,char sc,char kod,char *f);

/*    --------------------------------------------------------------------
		    POPUP
=======================================================================*/
struct Popup { /* ��� Popup */
  enum CONTROL t;   /* ��� Control'a */
  unsigned char n, /* MAX ���-�� ᨬ����� */
     width,height,
		c,
		top;
	  char **p; /* Pointer �� ᠬ ���ᨢ ��権 */
    struct Rect r;
   char *s,sc,kod;
};

struct Popup *DefinePopup(int x,int y,unsigned char n,unsigned char width,
			  unsigned char height,char *s,char sc,char kod);

/*=====================================================================
            CONTROL , ��p����塞� ����
=======================================================================*/

struct UserControl { /* ��� User's  */
  enum CONTROL t;   /* ��� Control'a */
    char *s,sc,kod;  /* ���-�� */
     struct Rect r;
     void (*show)(void); /* Shower - �㭪�� */
     void (*f)(void);    /* Doer - �㭪�� */
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