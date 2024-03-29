/*
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北�
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北�
�                                                                           �
�       Mathematical Analysis Header                                        �
�       屯屯屯屯屯屯屯屯屯屯屯屯屯屯                                        �
�            analysis.h  analysis.obj                                       �
�                                                                           �
�           Copyright (c)  Alexandr Alexeychuk  1997                        �
�                                                                           �
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北�
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北�
北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北�
*/


   /*======================= 帢垇妶 �崁媹噣拵悁 ======================= */
#define maOk            0    /* Ok - 崶� 庤ā */
        /* 庤ā ム犳ī : */
#define maOperOUFlow   10    /* 彞啷キē ǐ� 猊囡 Л犵ì猕 */
#define maDivZero      11    /* 劌� 瓲  */
        /* 庤ā MathAnal : */
#define maSintax       20    /* 懆牚屺绁岐狅 ā獱 */
#define maSkobki       21    /* 崰嚆瑗� 珷� 岐 */
#define maOper         22    /* 崶ěⅴ徕瓲� ム犳 */
#define maInvPar       23    /* 崶噜オ猸氅 癄酄忄 */
#define maInvConPar    24    /* 崶噜オ猸 绋岖� 癄酄忄 */
#define maNoPost       25    /* 崶噜オ猸 ㈦酄Ε� */


#define INDEFPARAM 255     /* 崶啷ぅ �- 癄酄忄 */


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
enum POSTTYPE { NUM ,        /*  忇猱  绋岖� : float x */
                VAR ,        /*  嚟犵キē 啷 : struct Var * p  */
                FUNCTION ,   /*  斻妯� : struct Function * p  */
                OPER ,       /*  幆ム犳 : struct Oper * p   */
                ARG ,        /*  �啵- 溷妯� �- : unsigned char n */
                SYMBOL ,     /*  戓氆獱 瓲 彞啷泐 : 岈. VAR   */
                APOSTFIX     /*  戓氆獱 瓲 徕�-� ㈦�-� : struct POSTFIX * p  */
              };             /* POSTFIX */

struct INFIX { enum INTYPE t;
               union {float x;void *p;unsigned char n;} u;};
struct POSTFIX {enum POSTTYPE t;
                struct POSTFIX *next;
                union {float x;           /*  only for t=NUM */
                       unsigned char n;    /*  only for t=ARG */
                       void *p;} u;};

extern
struct Var {char *s; /* -------- 儷牜飙狅 彞啷狅 --------- */
            float x;
            struct Var *next;}*ListVar;

extern
struct Function {  /* ---------- 斻妯� ------------ */
		 char s[7];
                 enum POSTTYPE *ps;    /* FOR STANDART FUNS AND NOT(...) ONLY */
                 unsigned char n;      /* 姰�- 彔酄忄
					  FOR STANDART FUNS  :
					    if n=255 then (...)
					  FOR USER's FUNS    :
					    if n=255 then ラ�  �-
					      �- 酄酄�-喈� */
                 struct POSTFIX *p; /* if p==NULL then 憣. f (STANDART) */
                 float(*f)();      /* if f==NULL then 憣. p (USER'S) */
                 struct Function *next;
                }*ListFun;

extern
struct Oper {  /* ---------------- 幆ム犳 ----------------- */
		 char *s;
    /* Level */  unsigned char l;
                 unsigned char n;   /* 姰�- 彔酄忄   1  or 2  */
                 float(*f)();
                 struct Oper *next;
                }*ListOper;


/* 摥ㄧ猱Ε� POSTFIX 岑ㄡ獱 -------------------------------------- */
void DestroyPostFix(struct POSTFIX *p);

/* 忇ム獱 瓲 妯á牠ē POSTFIX 傠�-� ------------------------------*/
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




/*----------------------------------- 濃� 溷妯� 岙♂猗キ 牠牜ě犫--
              �H�媹�  (...)
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