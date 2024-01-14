/*
▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
▒                                                                           ▒
▒       Mathematical Analysis Header                                        ▒
▒       ════════════════════════════                                        ▒
▒            analysis.h  analysis.obj                                       ▒
▒                                                                           ▒
▒           Copyright (c)  Alexandr Alexeychuk  1997                        ▒
▒                                                                           ▒
▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
*/


   /*======================= ОШИБКИ АНАЛИЗАТОРА ======================= */
#define maOk            0    /* Ok - Нет Ошибок */
        /* Ошибки операций : */
#define maOperOUFlow   10    /* Переполнение или потеря значимости */
#define maDivZero      11    /* Деление на ноль */
        /* Ошибки MathAnal : */
#define maSintax       20    /* Синтаксическая ошибка */
#define maSkobki       21    /* Нарушение баланса скобок */
#define maOper         22    /* Неизвестная операция */
#define maInvPar       23    /* Некорректный параметр */
#define maInvConPar    24    /* Некорректное число параметров */
#define maNoPost       25    /* Некорректное выражение */


#define INDEFPARAM 255     /* Неопределенное кол-во параметров */


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
enum POSTTYPE { NUM ,        /*  Просто  число : float x */
                VAR ,        /*  Значение переменной : struct Var * p  */
                FUNCTION ,   /*  Функция : struct Function * p  */
                OPER ,       /*  Операция : struct Oper * p   */
                ARG ,        /*  Арг-нт функции польз-ля : unsigned char n */
                SYMBOL ,     /*  Ссылка на Переменную : см. VAR   */
                APOSTFIX     /*  Ссылка на постф-е выр-ние : struct POSTFIX * p  */
              };             /* POSTFIX */

struct INFIX { enum INTYPE t;
               union {float x;void *p;unsigned char n;} u;};
struct POSTFIX {enum POSTTYPE t;
                struct POSTFIX *next;
                union {float x;           /*  only for t=NUM */
                       unsigned char n;    /*  only for t=ARG */
                       void *p;} u;};

extern
struct Var {char *s; /* -------- Глобальная Переменная --------- */
            float x;
            struct Var *next;}*ListVar;

extern
struct Function {  /* ---------- Функция ------------ */
		 char s[7];
                 enum POSTTYPE *ps;    /* FOR STANDART FUNS AND NOT(...) ONLY */
                 unsigned char n;      /* Кол-во Параметров
					  FOR STANDART FUNS  :
					    if n=255 then (...)
					  FOR USER's FUNS    :
					    if n=255 then еще не опр-но
					      кол-во рарам-ров */
                 struct POSTFIX *p; /* if p==NULL then СМ. f (STANDART) */
                 float(*f)();      /* if f==NULL then СМ. p (USER'S) */
                 struct Function *next;
                }*ListFun;

extern
struct Oper {  /* ---------------- Операция ----------------- */
		 char *s;
    /* Level */  unsigned char l;
                 unsigned char n;   /* Кол-во Параметров   1  or 2  */
                 float(*f)();
                 struct Oper *next;
                }*ListOper;


/* Уничтожение POSTFIX списка -------------------------------------- */
void DestroyPostFix(struct POSTFIX *p);

/* Проверка на зацикливание POSTFIX Выр-ния ------------------------------*/
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




/*----------------------------------- Эта функция собственно анализатор--
              АHАЛИЗ  (...)
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