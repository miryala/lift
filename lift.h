#include "Stack.c"

//person structure is in LList.h


typedef struct _avg_time avg_time;
struct _avg_time{
	int time;
	int no_pers;
};


typedef struct _LIFT LIFT;
struct _LIFT{
	int status;        //1=moving up  0=stopped  -1=moving down
	int start_floor;   //position from which lift started
	int position;	   //current position of the lift
	int destination;   //destination of lift
	int destination2;  //original destination
	int time;          //total time the lift is being run
	int size;		   //number of persons in lift
	Stack* list;       //list of persons in the lift
};

void simulate(Stack* up,Stack* down,LIFT* lift,int q,avg_time* t);//simulates lift

void simulate3(Stack* up,Stack* down,LIFT* lift,int q,avg_time* t);//simulates lift

void simulate2(Stack* up,Stack* down,LIFT* lift1,LIFT* lift2); 

void decision(Stack* up,Stack* down,LIFT* lift1,LIFT* lift2);   //function to decide which lift should go to which floor
