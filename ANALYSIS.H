/*
�����������������������������������������������������������������������������
�����������������������������������������������������������������������������
�                                                                           �
�       Mathematical Analysis Header                                        �
�       ����������������������������                                        �
�            analysis.h  analysis.obj                                       �
�                                                                           �
�           Copyright (c)  Alexandr Alexeychuk  1997                        �
�                                                                           �
�����������������������������������������������������������������������������
�����������������������������������������������������������������������������
�����������������������������������������������������������������������������
*/


   /*======================= ������ ����������� ======================= */
#define maOk            0    /* Ok - ��� �訡�� */
        /* �訡�� ����権 : */
#define maOperOUFlow   10    /* ��९������� ��� ����� ���稬��� */
#define maDivZero      11    /* ������� �� ���� */
        /* �訡�� MathAnal : */
#define maSintax       20    /* ���⠪��᪠� �訡�� */
#define maSkobki       21    /* ����襭�� ������ ᪮��� */
#define maOper         22    /* �������⭠� ������ */
#define maInvPar       23    /* �����४�� ��ࠬ��� */
#define maInvConPar    24    /* �����४⭮� �᫮ ��ࠬ��஢ */
#define maNoPost       25    /* �����४⭮� ��ࠦ���� */


#define INDEFPARAM 255     /* ����।������� ���-�� ��ࠬ��஢ */


#define MAXARG 10


extern unsigned char MAErr;
extern char *MAErrName;

extern
struct CalculStack {
  enum CS_TYPE {CS_NUM,CS_SYMBOL,CS_POSTFIX } t;
  union {float x; void *p; } u;
  struct CalculStack *next;
} *GCS;





/*------------------------- MATH ERROR -------------------------------*/
int matherr(struct exception *e);





enum INTYPE {Hash,Oper,Fun,Skoba_In,Skoba_Out,Koma,Symbol,Num,Arg};/* INFIX */
enum POSTTYPE { NUM ,        /*  ����  �᫮ : float x */
                VAR ,        /*  ���祭�� ��६����� : struct Var * p  */
                FUNCTION ,   /*  �㭪�� : struct Function * p  */
                OPER ,       /*  ������ : struct Oper * p   */
                ARG ,        /*  ��-�� �㭪樨 ����-�� : unsigned char n */
                SYMBOL ,     /*  ��뫪� �� ��६����� : �. VAR   */
                APOSTFIX     /*  ��뫪� �� �����-� ���-��� : struct POSTFIX * p  */
              };             /* POSTFIX */

struct INFIX { enum INTYPE t;
               union {float x;void *p;unsigned char n;} u;};
struct POSTFIX {enum POSTTYPE t;
                struct POSTFIX *next;
                union {float x;           /*  only for t=NUM */
                       unsigned char n;    /*  only for t=ARG */
                       void *p;} u;};

extern
struct Var {char *s; /* -------- ������쭠� ��६����� --------- */
            float x;
            struct Var *next;}*ListVar;

extern
struct Function {  /* ---------- �㭪�� ------------ */
		 char s[7];
                 enum POSTTYPE *ps;    /* FOR STANDART FUNS AND NOT(...) ONLY */
                 unsigned char n;      /* ���-�� ��ࠬ��஢
					  FOR STANDART FUNS  :
					    if n=255 then (...)
					  FOR USER's FUNS    :
					    if n=255 then �� �� ���-��
					      ���-�� �ࠬ-஢ */
                 struct POSTFIX *p; /* if p==NULL then ��. f (STANDART) */
                 float(*f)();      /* if f==NULL then ��. p (USER'S) */
                 struct Function *next;
                }*ListFun;

extern
struct Oper {  /* ---------------- ������ ----------------- */
		 char *s;
    /* Level */  unsigned char l;
                 unsigned char n;   /* ���-�� ��ࠬ��஢   1  or 2  */
                 float(*f)();
                 struct Oper *next;
                }*ListOper;


/* ����⮦���� POSTFIX ᯨ᪠ -------------------------------------- */
void DestroyPostFix(struct POSTFIX *p);

/* �஢�ઠ �� ��横������� POSTFIX ���-��� ------------------------------*/
char CyclePostFix(char *f,struct POSTFIX *p);


/* ------------------------- FIND  VAR  ------------------------------- */
struct Var * FindVar(char *s);
/*------------------------- ADD  NEW  VAR  ---------------------------*/
struct Var *AddVar(char *s,float x);
/*------------------------- DELETE VAR --------------------------*/
void DelVar(struct Var *v);
/* ------------------------- FIND  OPER  ------------------------------- */
struct Oper *FindOper(char *s,unsigned char n);
/*------------------------- ADD  NEW  OPER  ---------------------------*/
struct Oper *AddOper(char *s,unsigned char n,unsigned char l,float(*f)(void));
/*------------------------- DELETE OPER --------------------------*/
void DelOper(struct Oper *v);
/* ------------------------- FIND  FUN  ------------------------------- */
struct Function *FindFun(char *s);
/*------------------------- ADD  NEW  FUN  ---------------------------*/
struct Function *AddFun(char *s,unsigned n,struct POSTFIX *p,
                        float(*f)(void),enum POSTTYPE *ps);
/*------------------------- DELETE FUN --------------------------*/
void DelFun(struct Function *v);




/*----------------------------------- �� �㭪�� ᮡ�⢥��� ���������--
              �H����  (...)
----------------------------------------------------------------------*/
struct POSTFIX *MathAnal(char *s,unsigned char n,...);




/*------------------------- CALCULATE -----------------------------*/
float Calcul(struct POSTFIX *p,unsigned char NA);



/* Special for CALCULATE functions ------------------------------------ */
void PushCS();
void PopCS();


/*----------------------------------------------------- Install Analizator */
void InitMathAn(void);
