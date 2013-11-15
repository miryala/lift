#include "lift.h"

#define FLOOR_TO_FLOOR_TIME 4

#define WAITING_TIME 1

#define MAX_FLOORS 10

#define MAX_LIMIT 10




//modulus of number
int modulo(int a){
	if(a>=0)
		return a;
	else return -a;
}



void simulate2(Stack* up,Stack* down,LIFT* lift1,LIFT* lift2){
	avg_time* t;
	t=malloc(sizeof(avg_time));
	t->time=0;
	t->no_pers=0;
	while(down->head!=NULL||up->head!=NULL){
		decision(up,down,lift1,lift2);
		simulate3(up,down,lift1,1,t);
		simulate(up,down,lift1,1,t);
		simulate3(up,down,lift2,2,t);
		simulate(up,down,lift2,2,t);
	}
	float h=((float)(t->time))/t->no_pers;
	printf("\n\n");
	printf("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n");
	printf("Average waiting time: %fsec  &&&\n",h);
	printf("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n");
}

void simulate(Stack* up,Stack* down,LIFT *lift,int q,avg_time* t){
	int i,j=0;
	//lift is moving up
	if(lift->status==1){
		for (i=lift->position;i<=lift->destination2;i++)
		{
			lift->position=i;  //assigning the current position
			Node *idx;
			int flag=0;
			if(lift->start_floor!=i){
				j=1;
				printf("lift%d is now in %d floor \n",q,i);
			}
			printf("..................................................\n\n\n");
			sleep(1);
			//system("clear");
			idx=lift->list->head;	//checking if any person has current floor as destination
			while(idx!=NULL&&lift->size!=0){
				if(idx->p.to_floor==lift->position){
					printf("person %d got of lift%d on %d floor\n",idx->p.id,q,lift->position);
					printf("WAITING TIME :  %d\n",idx->p.time);  //printing the waiting time of each person
					printf("<><><><><><><><><><><><><><><><><><><><><><>><><>\n\n\n");
					t->time=t->time+idx->p.time;  //calculating the total waiting time
					t->no_pers=t->no_pers+1;      //total number of persons
					sleep(2);
					//system("clear");
					lift->list=delete_(lift->list,idx);          //after person gets down deleting him from list
					lift->size -= 1;     //decreasing the number of perons by 1
					if(flag==0){         //increasing the waiting time of each person
						/*Node* wait;
						  wait=lift->list->head;
						  while(wait!=NULL){
						  wait->p.time += WAITING_TIME;
						  wait=wait->next;
						  }*/
						lift->time +=WAITING_TIME;  //total time of lift increases by waiting time
						flag=1;
					}
					idx=lift->list->head;
					continue;
				}
				idx=idx->next;
			}

			idx=up->head;
			do {
				if(idx==NULL) break;
				//checking if any person wants to get on lift
				if(idx->p.to_floor>=lift->position && lift->time >= idx->p.time  
						&& lift->size<MAX_LIMIT && lift->position==idx->p.from_floor)
				{  //checking the max limit of lift and time constraints
					printf("person %d got into lift%d on %d floor \n",idx->p.id,q,lift->position);
					printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\n\n");
					sleep(1);
					if(idx->p.to_floor>lift->destination2)
						lift->destination2=idx->p.to_floor;
					//system("clear");
					if(flag==0){  //if flag is one,it implies that lift stopped to drop some persons.assumption is with in waiting time all persons gets down and gets into lift
						/*Node* wait;
						  wait=lift->list->head;
						  while(wait!=NULL){
						  wait->p.time += WAITING_TIME;
						  wait=wait->next;
						  }*/
						lift->time +=WAITING_TIME;
						flag=1;
					}
					person p;
					p.id=idx->p.id;
					p.time=lift->time-idx->p.time; //calculating waiting time of person
					p.to_floor=idx->p.to_floor;
					p.from_floor=idx->p.from_floor;
					lift->list=stack_push(lift->list,p);  //pushing the person on lift
					lift->size += 1;   //increasing number of persons
					up=delete_(up,idx);//deleting the person from up stack
					idx=up->head;
					continue;

				}
				Node* k;
				k=lift->list->head;
				while(k!=NULL&&lift->size>=0){
					if(k->p.to_floor==lift->position){
						printf("person %d got of lift%d on %d floor\n",k->p.id,q,lift->position);
						printf("WAITING TIME :  %d\n",k->p.time);
						printf("<><><><><><><><><><><><><><><><><><><><><><>><><><><><><\n\n\n");
						t->time=t->time+idx->p.time;
						t->no_pers=t->no_pers+1;
						sleep(2);
						//system("clear");
						lift->list=delete_(lift->list,k);
						lift->size -= 1;
						if(flag==0){
							/*Node* wait;
							  wait=lift->list->head;
							  while(wait!=NULL){                                          
							  wait->p.time += WAITING_TIME;
							  wait=wait->next;
							  }*/
							lift->time +=WAITING_TIME;
							flag=1;
						}
						k=lift->list->head;
						continue;
					}
					k=k->next;
				}

				idx=idx->next;
			}while(idx!=NULL);
			if(j==1)lift->time +=FLOOR_TO_FLOOR_TIME;
		}
		lift->status=0;
	}
	//lift is moving down
	if(lift->status==-1){
		for (i=lift->position;i>=lift->destination2;i--)
		{
			lift->position=i;  //assigning the current position
			Node *idx;
			int flag=0;
			if(lift->start_floor!=i)
				j=1;
			{
				printf("lift%d is now in %d floor \n",q,i);
				printf("..................................................\n\n\n");
				sleep(1);
				//system("clear");
				idx=lift->list->head;	//checking if any person has current floor as destination
				while(idx!=NULL&&lift->size!=0){
					if(idx->p.to_floor==lift->position){
						printf("person %d got of lift%d on %d floor\n",idx->p.id,q,lift->position);
						printf("WAITING TIME :  %d\n",idx->p.time);  //printing the waiting time of each person
						printf("<><><><><><><><><><><><><><><><><><><><><><>><><>\n\n\n");
						t->time=t->time+idx->p.time;
						t->no_pers=t->no_pers+1;
						sleep(2);
						//system("clear");
						lift->list=delete_(lift->list,idx);          //after person gets down deleting him from list
						lift->size -= 1;     //decreasing the number of perons by 1
						if(flag==0){         //increasing the waiting time of each person
							/*Node* wait;
							  wait=lift->list->head;
							  while(wait!=NULL){
							  wait->p.time += WAITING_TIME;
							  wait=wait->next;
							  }*/
							lift->time +=WAITING_TIME;  //total time of lift
							flag=1;
						}
						idx=lift->list->head;
						continue;
					}
					idx=idx->next;
				}
			}
			idx=down->head;
			do {
				if(idx==NULL) break;
				//checking if any person wants to get on lift
				if(idx->p.to_floor<=lift->position && lift->time >= idx->p.time  
						&& lift->size<MAX_LIMIT && lift->position==idx->p.from_floor)
				{  //checking the max limit of lift
					printf("person %d got into lift%d on %d floor \n",idx->p.id,q,lift->position);
					printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\n\n");
					if(idx->p.to_floor < lift->destination2)
						lift->destination2=idx->p.to_floor;
					sleep(1);
					//system("clear");
					if(flag==0){  //if flag is one,it implies that lift stopped to drop some persons.assumption is with in waiting time all persons gets down and gets on lift
						/*Node* wait;
						  wait=lift->list->head;
						  while(wait!=NULL){
						  wait->p.time += WAITING_TIME;
						  wait=wait->next;
						  }*/
						lift->time +=WAITING_TIME;
						flag=1;
					}
					person p;
					p.id=idx->p.id;
					p.time=lift->time-idx->p.time; //calculating waiting time of person
					p.to_floor=idx->p.to_floor;
					p.from_floor=idx->p.from_floor;
					lift->list=stack_push(lift->list,p);  //pushing the person on lift
					lift->size += 1;   //increasing number of persons
					down=delete_(down,idx);//deleting the person from up stack
					idx=up->head;
					continue;

				}
				Node* k;
				k=lift->list->head;
				while(k!=NULL&&lift->size>=0){
					if(k->p.to_floor==lift->position){
						printf("person %d got of lift%d on %d floor\n",k->p.id,q,lift->position);
						printf("WAITING TIME :  %d\n",k->p.time);
						printf("<><><><><><><><><><><><><><><><><><><><><><>><><><><><><\n\n\n");
						t->time=t->time+idx->p.time;
						t->no_pers=t->no_pers+1;
						sleep(2);
						//system("clear");
						lift->list=delete_(lift->list,k);
						lift->size -= 1;
						if(flag==0){
							/*Node* wait;
							  wait=lift->list->head;
							  while(wait!=NULL){                                          
							  wait->p.time += WAITING_TIME;
							  wait=wait->next;
							  }*/
							lift->time +=WAITING_TIME;
							flag=1;
						}
						k=lift->list->head;
						continue;
					}
					k=k->next;
				}

				idx=idx->next;
			}while(idx!=NULL);
			if(j==1)lift->time +=FLOOR_TO_FLOOR_TIME;
		}
	}
	lift->status=0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void simulate3(Stack* up,Stack* down,LIFT *lift,int q,avg_time* t){
	int i,j=0;
	//lift is moving up
	if(lift->position!=lift->destination){
		if(lift->status==1){
			for (i=lift->position;i<=lift->destination2;i++)
			{
				lift->position=i;  //assigning the current position
				Node *idx;
				int flag=0;
				if(lift->start_floor!=i){
					j=1;
					printf("lift%d is now in %d floor \n",q,i);
				}
				printf("..................................................\n\n\n");
				sleep(1);
				//system("clear");
				idx=lift->list->head;	//checking if any person has current floor as destination
				while(idx!=NULL&&lift->size!=0){
					if(idx->p.to_floor==lift->position){
						printf("person %d got of lift%d on %d floor\n",idx->p.id,q,lift->position);
						printf("WAITING TIME :  %d\n",idx->p.time);  //printing the waiting time of each person
						printf("<><><><><><><><><><><><><><><><><><><><><><>><><>\n\n\n");
						t->time=t->time+idx->p.time;
						t->no_pers=t->no_pers+1;
						sleep(2);
						//system("clear");
						lift->list=delete_(lift->list,idx);          //after person gets down deleting him from list
						lift->size -= 1;     //decreasing the number of perons by 1
						if(flag==0){         //increasing the waiting time of each person
							/*Node* wait;
							  wait=lift->list->head;
							  while(wait!=NULL){
							  wait->p.time += WAITING_TIME;
							  wait=wait->next;
							  }*/
							lift->time +=WAITING_TIME;  //total time of lift
							flag=1;
						}
						idx=lift->list->head;
						continue;
					}
					idx=idx->next;
				}

				idx=up->head;
				do {
					if(idx==NULL) break;
					//checking if any person wants to get on lift
					if(idx->p.to_floor>=lift->position && lift->time >= idx->p.time  
							&& lift->size<MAX_LIMIT && lift->position==idx->p.from_floor)
					{  //checking the max limit of lift
						printf("person %d got into lift%d on %d floor \n",idx->p.id,q,lift->position);
						printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\n\n");
						if(idx->p.to_floor>lift->destination)
							lift->destination=idx->p.to_floor;
						sleep(1);
						//system("clear");
						if(flag==0){  //if flag is one,it implies that lift stopped to drop some persons.assumption is with in waiting time all persons gets down and gets on lift
							/*Node* wait;
							  wait=lift->list->head;
							  while(wait!=NULL){
							  wait->p.time += WAITING_TIME;
							  wait=wait->next;
							  }*/
							lift->time +=WAITING_TIME;
							flag=1;
						}
						person p;
						p.id=idx->p.id;
						p.time=lift->time-idx->p.time; //calculating waiting time of person
						p.to_floor=idx->p.to_floor;
						p.from_floor=idx->p.from_floor;
						lift->list=stack_push(lift->list,p);  //pushing the person on lift
						lift->size += 1;   //increasing number of persons
						up=delete_(up,idx);//deleting the person from up stack
						idx=up->head;
						continue;

					}
					Node* k;
					k=lift->list->head;
					while(k!=NULL&&lift->size>=0){
						if(k->p.to_floor==lift->position){
							printf("person %d got of lift%d on %d floor\n",k->p.id,q,lift->position);
							printf("WAITING TIME :  %d\n",k->p.time);
							printf("<><><><><><><><><><><><><><><><><><><><><><>><><><><><><\n\n\n");
							t->time=t->time+idx->p.time;
							t->no_pers=t->no_pers+1;
							sleep(2);
							//system("clear");
							lift->list=delete_(lift->list,k);
							lift->size -= 1;
							if(flag==0){
								/*Node* wait;
								  wait=lift->list->head;
								  while(wait!=NULL){                                          
								  wait->p.time += WAITING_TIME;
								  wait=wait->next;
								  }*/
								lift->time +=WAITING_TIME;
								flag=1;
							}
							k=lift->list->head;
							continue;
						}
						k=k->next;
					}

					idx=idx->next;
				}while(idx!=NULL);
				if(j==1)lift->time +=FLOOR_TO_FLOOR_TIME;
			}
			lift->start_floor=lift->position;
			if(lift->destination2>lift->destination)
				lift->status=1;
			else
				lift->status=-1;
		}
		//changing
		if(lift->status==-1){
			for (i=lift->position;i>=lift->destination;i--)
			{
				lift->position=i;  //assigning the current position
				Node *idx;
				int flag=0;
				if(lift->start_floor!=i)
					j=1;
				{
					printf("lift%d is now in %d floor \n",q,i);
					printf("..................................................\n\n\n");
					sleep(1);
					//system("clear");
					idx=lift->list->head;	//checking if any person has current floor as destination
					while(idx!=NULL&&lift->size!=0){
						if(idx->p.to_floor==lift->position){
							printf("person %d got of lift%d on %d floor\n",idx->p.id,q,lift->position);
							printf("WAITING TIME :  %d\n",idx->p.time);  //printing the waiting time of each person
							printf("<><><><><><><><><><><><><><><><><><><><><><>><><>\n\n\n");
							t->time=t->time+idx->p.time;
							t->no_pers=t->no_pers+1;
							sleep(2);
							//system("clear");
							lift->list=delete_(lift->list,idx);          //after person gets down deleting him from list
							lift->size -= 1;     //decreasing the number of perons by 1
							if(flag==0){         //increasing the waiting time of each person
								/*Node* wait;
								  wait=lift->list->head;
								  while(wait!=NULL){
								  wait->p.time += WAITING_TIME;
								  wait=wait->next;
								  }*/
								lift->time +=WAITING_TIME;  //total time of lift
								flag=1;
							}
							idx=lift->list->head;
							continue;
						}
						idx=idx->next;
					}
				}
				idx=down->head;
				do {
					if(idx==NULL) break;
					//checking if any person wants to get on lift
					if(idx->p.to_floor<=lift->destination && lift->time >= idx->p.time  
							&& lift->size<MAX_LIMIT && lift->position==idx->p.from_floor)
					{  //checking the max limit of lift
						printf("person %d got into lift%d on %d floor \n",idx->p.id,q,lift->position);
						printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\n\n");
						if(idx->p.to_floor<=lift->position)
							lift->destination=idx->p.to_floor;
						sleep(1);
						//system("clear");
						if(flag==0){  //if flag is one,it implies that lift stopped to drop some persons.assumption is with in waiting time all persons gets down and gets on lift
							/*Node* wait;
							  wait=lift->list->head;
							  while(wait!=NULL){
							  wait->p.time += WAITING_TIME;
							  wait=wait->next;
							  }*/
							lift->time +=WAITING_TIME;
							flag=1;
						}
						person p;
						p.id=idx->p.id;
						p.time=lift->time-idx->p.time; //calculating waiting time of person
						p.to_floor=idx->p.to_floor;
						p.from_floor=idx->p.from_floor;
						lift->list=stack_push(lift->list,p);  //pushing the person on lift
						lift->size += 1;   //increasing number of persons
						down=delete_(down,idx);//deleting the person from up stack
						idx=up->head;
						continue;

					}
					Node* k;
					k=lift->list->head;
					while(k!=NULL&&lift->size>=0){
						if(k->p.to_floor==lift->position){
							printf("person %d got of lift%d on %d floor\n",k->p.id,q,lift->position);
							printf("WAITING TIME :  %d\n",k->p.time);
							printf("<><><><><><><><><><><><><><><><><><><><><><>><><><><><><\n\n\n");
							t->time=t->time+idx->p.time;
							t->no_pers=t->no_pers+1;
							sleep(2);
							//system("clear");
							lift->list=delete_(lift->list,k);
							lift->size -= 1;
							if(flag==0){
								/*Node* wait;
								  wait=lift->list->head;
								  while(wait!=NULL){                                          
								  wait->p.time += WAITING_TIME;
								  wait=wait->next;
								  }*/
								lift->time +=WAITING_TIME;
								flag=1;
							}
							k=lift->list->head;
							continue;
						}
						k=k->next;
					}

					idx=idx->next;
				}while(idx!=NULL);
			}
			if(j==1)lift->time +=FLOOR_TO_FLOOR_TIME;

		}
	}
	lift->start_floor=lift->position;
	if(lift->destination2>lift->position)
		lift->status=1;
	else
		lift->status=-1;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//function to decide which lift should goto which floor
void decision(Stack* up,Stack* down,LIFT *lift1,LIFT *lift2){
	int k=0;
	Node* idx=up->head;
	person p;
	p.time=10000;
	while(idx!=NULL ){    //checking which person is coming first
		if(idx->p.time <= p.time){
			p.time=idx->p.time;
			p.to_floor=idx->p.to_floor;
			p.from_floor=idx->p.from_floor;
			p.id=idx->p.id;
			k=0;
		}
		idx=idx->next;
	}
	idx=down->head;
	while(idx!=NULL ){
		if(idx->p.time < p.time){
			p.time=idx->p.time;
			p.to_floor=idx->p.to_floor;
			p.from_floor=idx->p.from_floor;
			p.id=idx->p.id;
			k=1;
		}
		idx=idx->next;
	}
	///////////////////////////////////////////1
	//flagging the person so that other lift is not assigned to this person again
	idx=up->head;
	while(idx!=NULL ){    
		if(p.id==idx->p.id){
			idx->p.flag=-1;
		}
		idx=idx->next;
	}
	idx=down->head;
	while(idx!=NULL ){
		if(p.id==idx->p.id){
			idx->p.flag=-1;
		}
		idx=idx->next;
	}
	//////////////////////////////////////////1
	if(lift1->position-p.from_floor==0){
		lift1->destination=p.from_floor;
		lift1->destination2=p.to_floor;
		lift1->start_floor=lift1->position;
		if(lift1->start_floor==lift1->destination && lift1->time < p.time)
			lift1->time=p.time;
		if(lift1->destination>lift1->position)
			lift1->status=1;
		else
			lift1->status =-1;
		//////////////////////////////////////////2
		//assigning other lift
		idx=up->head;
		p.time=100000;
		while(idx!=NULL ){    
			if(idx->p.time <= p.time && idx->p.flag!=-1){
				p.time=idx->p.time;
				p.to_floor=idx->p.to_floor;
				p.from_floor=idx->p.from_floor;
				p.id=idx->p.id;
				k=0;
			}
			idx=idx->next;
		}
		idx=down->head;
		while(idx!=NULL ){
			if(idx->p.time < p.time && idx->p.flag!=-1){
				p.time=idx->p.time;
				p.to_floor=idx->p.to_floor;
				p.from_floor=idx->p.from_floor;
				p.id=idx->p.id;
				k=1;
			}
			idx=idx->next;
		}
		if(p.time!=100000){
			lift2->destination=p.from_floor;
			lift2->destination2=p.to_floor;
			lift2->start_floor=lift2->position;
			if(lift2->destination>lift2->position)
				lift2->status=1;
			else
				lift2->status =-1;
		}
		/////////////////////////////////////////2
	}
	else if(lift2->position-p.from_floor==0){
		lift2->destination=p.from_floor;
		lift2->destination2=p.to_floor;
		lift2->start_floor=lift2->position;
		if(lift2->start_floor==lift2->destination && lift2->time < p.time)
			lift2->time=p.time;
		if(lift2->destination>lift2->position)
			lift2->status=1;
		else
			lift2->status =-1;
		/////////////////////////////////////////3
		idx=up->head;
		p.time=100000;
		while(idx!=NULL ){    
			if(idx->p.time <= p.time && idx->p.flag!=-1){
				p.time=idx->p.time;
				p.to_floor=idx->p.to_floor;
				p.from_floor=idx->p.from_floor;
				p.id=idx->p.id;
				k=0;
			}
			idx=idx->next;
		}
		idx=down->head;
		while(idx!=NULL ){
			if(idx->p.time < p.time && idx->p.flag!=-1){
				p.time=idx->p.time;
				p.to_floor=idx->p.to_floor;
				p.from_floor=idx->p.from_floor;
				p.id=idx->p.id;
				k=1;
			}
			idx=idx->next;
		}
		if(p.time!=100000){
			lift1->destination=p.from_floor;
			lift1->destination2=p.to_floor;
			lift1->start_floor=lift1->position;
			if(lift1->destination>lift1->position)
				lift1->status=1;
			else
				lift1->status =-1;
		}
		/////////////////////////////////////////3
	}
	else if((lift1->position-p.from_floor)*FLOOR_TO_FLOOR_TIME+lift1->time<(lift2->position-p.from_floor)*FLOOR_TO_FLOOR_TIME+lift2->time){  //sending the lift which is nearer
		lift1->destination=p.from_floor;
		lift1->destination2=p.to_floor;
		lift1->start_floor=lift1->position;
		if(lift1->start_floor==lift1->destination && lift1->time < p.time)
			lift1->time=p.time;
		if(lift1->destination>lift1->position)
			lift1->status=1;
		else
			lift1->status =-1;
		///////////////////////////////////////4		
		idx=up->head;
		p.time=100000;
		while(idx!=NULL ){    
			if(idx->p.time <= p.time && idx->p.flag!=-1){
				p.time=idx->p.time;
				p.to_floor=idx->p.to_floor;
				p.from_floor=idx->p.from_floor;
				p.id=idx->p.id;
				k=0;
			}
			idx=idx->next;
		}
		idx=down->head;
		while(idx!=NULL ){
			if(idx->p.time < p.time && idx->p.flag!=-1){
				p.time=idx->p.time;
				p.to_floor=idx->p.to_floor;
				p.from_floor=idx->p.from_floor;
				p.id=idx->p.id;
				k=1;
			}
			idx=idx->next;
		}
		if(p.time!=100000){
			lift2->destination=p.from_floor;
			lift2->destination2=p.to_floor;
			lift2->start_floor=lift2->position;
			if(lift2->start_floor==lift2->destination && lift2->time < p.time)
				lift2->time=p.time;
			if(lift2->destination>lift2->position)
				lift2->status=1;
			else
				lift2->status =-1;
		}
	}
	//////////////////////////////////////4
	else{

		lift2->destination=p.from_floor;
		lift2->destination2=p.to_floor;
		lift2->start_floor=lift2->position;
		if(lift2->start_floor==lift1->destination && lift2->time < p.time)
			lift2->time=p.time;
		if(lift2->destination>lift2->position)
			lift2->status=1;
		else
			lift2->status=-1;
		////////////////////////////////////5
		idx=up->head;
		p.time=100000;
		while(idx!=NULL ){    
			if(idx->p.time <= p.time && idx->p.flag!=-1){
				p.time=idx->p.time;
				p.to_floor=idx->p.to_floor;
				p.from_floor=idx->p.from_floor;
				p.id=idx->p.id;
				k=0;
			}
			idx=idx->next;
		}
		idx=down->head;
		while(idx!=NULL ){
			if(idx->p.time < p.time && idx->p.flag!=-1){
				p.time=idx->p.time;
				p.to_floor=idx->p.to_floor;
				p.from_floor=idx->p.from_floor;
				p.id=idx->p.id;
				k=1;
			}
			idx=idx->next;
		}
		if(p.time!=100000){
			lift1->destination=p.from_floor;
			lift1->destination2=p.to_floor;
			lift1->start_floor=lift1->position;
			if(lift1->start_floor==lift1->destination && lift1->time < p.time)
				lift1->time=p.time;
			if(lift1->destination>lift1->position)
				lift1->status=1;
			else
				lift1->status =-1;
		}
		///////////////////////////////////////5
	}
}


