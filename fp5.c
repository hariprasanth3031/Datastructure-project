//2018503031
//MINI PROJECT ON ONLINE COUNSELLING
#include<stdio.h>
#include<malloc.h>
#include<string.h>
typedef struct node1
{
  char course[10];
  int cnt;
  struct node1* next1;
}list;
typedef list* list1;
typedef struct node
{
  int code;
  struct node1* colle;
  struct node* next;
}NODE;
typedef NODE* LIST;
LIST CreateList()
{
	return NULL;
}
int IsIncourse(char c[][16],int k,char* d)
{
	int j;
	for(j = 0;j < k;j++)
	{
		if(strcmp(c[j],d) == 0)
			return 1;
	}
	return 0;
}
list1 InSert()
{
    list1 l;
    static char c[100][16];
    char ch[16];
  	int d,k,n = 0,f,g;
  	static int i=0;
  	l = (list1)malloc(sizeof(list));
  	scanf("%s",ch);
  	if(strcmp(ch,"zzz") == 0)
  	{
  		l = NULL;
  		for(f = 0;f < 100;f++)
  		{
  			for(g = 0;g < 16;g++)
			  c[f][g] = '\0';	
		}
    	return l;
  	}
  	if(!IsIncourse(c,i,ch))
  	{
	  	strcpy(c[i],ch);
	  	i++;
		scanf("%d",&d);
	    strcpy(l->course,ch);
	    l->cnt = d;
	    l->next1 = InSert();
	}
	else
	{
		printf("\nALREADY THIS COURSE ENTERED.ENTER DIFFERENT COURSE WITH ITS NUMBER OF SEATS\n\n");
		i++;
		l = InSert();
	}
}
LIST makeNode(int data)
{
	LIST temp;
	temp = (LIST)malloc(sizeof(NODE));
	temp->code = data;
  	printf("\nEnter the courses with their respestive number of seats(Enter zzz to break) : \n");
  	temp->colle = InSert();
	temp->next = NULL;
	return temp;
}
int IsIncode(LIST t,int d)
{
	while(t)
	{
		if(t->code == d)
			return 1;
		t = t->next;
	}
	return 0;	
}
LIST InsertAtTail(LIST l, int d)
{
	if(!IsIncode(l,d))
	{
		if(!l)
		return makeNode(d);
		LIST t = l;
		while( t->next )
			t = t->next;
		t->next = makeNode(d);
		return l;	
	}
	printf("\n ALREADY COLLEGE WITH THIS CODE IS ENTERED.ENTER DIFFERENT COLLEGE CODE \n\n");
	return l;
}
LIST SeArcH(LIST t,int r,char code[][5],char str1[][4],int cn)
{
	FILE *fptr;
	LIST l = t;
	int da = atoi(code[0]);
	int i = 0,j = 0,v = 1,d;
	A:
	while(l)
	{
	    d = l->code;
  	    if(d == da)
        { 
     		list* t1 = l->colle;
        	while(t1)
        	{
            	if(strcmp(t1->course,str1[j]) == 0 && t1->cnt != 0 )
            	{
                	t1->cnt -= 1;
                	fptr = fopen("finalallotment.txt", "a");
                	fprintf(fptr,"%2d\t",r);
                	fprintf(fptr,"\t%7d",d);
                	fprintf(fptr,"%15s\n",str1[j]);
                	fclose(fptr);
                	return t;
            	}
            	else
                t1 = t1->next1;
        	}
            if(!t1)
			{
				if(j >= cn)
				{
					fptr = fopen("finalallotment.txt", "a");
				    fprintf(fptr,"%2d\t",r);
		            fprintf(fptr,"\tNO COLLEGE\t");
		            fprintf(fptr,"\tNO COURSE\n");
		            fclose(fptr);
					return t;
				}	
				else if(j < cn)
				{
					i += 1;
					j += 1;
					da = atoi(code[i]);
					l = t;
					goto A;	
				}
			}
    	}
      	else if(l->next != NULL)
        	l = l->next;
	  	else if(l->next == NULL)
	    {
	  		if(i < cn)
	  		{
		   		i += 1;
		   		j += 1;
		   		da=atoi(code[i]);
				l = t;
				goto A;
			}
			else
			{
				fptr = fopen("finalallotment.txt", "a");
			    fprintf(fptr,"%2d\t",r);
	            fprintf(fptr,"\tNO COLLEGE\t");
	            fprintf(fptr,"\tNO COURSE\n");
	            fclose(fptr);
			    return t;
			}
	    }
	}
	if(!l)
	{
		fptr = fopen("finalallotment.txt", "a");
		fprintf(fptr,"%2d\t",r);
		fprintf(fptr,"\tNO COLLEGE\t");
		fprintf(fptr,"\tNO COURSE\n");
		fclose(fptr);
		return t;
	}
}
LIST CouNsel(LIST l,char* filename,int rank)
{
    LIST f = l;
    int p,k,i = 0,cn = 0;
    char ch,file_name[20];
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
    	printf("Error while opening the file.\n");
     	return NULL;
 	}
  	while(!feof(fp))
    {
       ch = fgetc(fp);
       if(ch == '\n') cn++;
	}
	fclose(fp);
	cn = cn-1;
	fp = fopen(filename, "r");
    char code[cn][5],str1[cn][4];
    for(i = 0;i < cn;i++)
    {
    	p = 0,k = 0;
        while((ch = fgetc(fp)) != ' ')
        {
            code[i][k] = ch;
            k++;
        }
        code[i][k] = '\0';
        while((ch = fgetc(fp)) != '\n')
        {
            str1[i][p] = ch;
            p++;
        }
        str1[i][p] = '\0';
    } 
	f = SeArcH(l,rank,code,str1,cn);
	fclose(fp);
    return f;
}
void display(LIST l)
{
	LIST l1 = l;
	while(l1)
  	{
		printf("\t\t\t\t\t\t\t\t\t%8d", l1->code);
		list* t = l1->colle;
    while(t)
    {
        printf("\t%5s\t\t%4d\n\t\t\t\t\t\t\t\t\t\t",t->course,t->cnt);
        t = t->next1;
    }
	l1 = l1->next;
    printf("\n\n");
  	}
  	return;
}
int main()
{
	FILE *fpp,*fptr = fopen("finalallotment.txt","w");
	fclose(fptr);
	fptr=fopen("finalallotment.txt","a");
	fprintf(fptr,"Rank\t  College\t\t  Course \n");
	fclose(fptr);
	LIST l = CreateList(),f;
	int k,s,cn,c,d,t = 0;
	char cha,filename[10],ch;
	printf("\t\t\t\t\t\t\t\t########## WELCOME TO ONLINE ENGINEERING COUNSELLING ###########\n\n");
	printf("\t\t\t\t\t\t\t\t\tENTER THE COLLEGE CODE WITH ITS RESPECTIVE COURSES\n\n\n");
	while(1)
	{
		printf("Enter the college code(Enter -1 to break) :");
  		scanf("%d",&d);
        if(d == -1)
        break;
  		l = InsertAtTail(l,d);
	}
	printf("\n\t\t\t\t\t\t\t\t***************** THE LIST BEFORE ALLOTMENT IS ****************\n");
	printf("\n\n\t\t\t\t\t\t\t\t\tCOLLEGE CODE \t COURSE \t NUMBER OF SEATS\n\n");
	display(l);
  	fpp=fopen("file.txt","r");
  	while(!feof(fpp))
    {
       ch = fgetc(fpp);
       if(ch == '\n') cn++;
	}
	fclose(fpp);
	fpp=fopen("file.txt","r");
	for(s = 1;s <= cn-1;s++)
  	{
  		k=0;
  		f = l;
        while((ch = fgetc(fpp)) != '\n')
        {
            filename[k] = ch;
            k++;
        }
        filename[k] = '\0';
    	f = CouNsel(f,filename,s);
	}
	fclose(fpp);
	printf("\n\t\t\t\t\t\t\t\t***************** THE LIST AFTER ALLOTMENT IS ****************\n");
	printf("\n\n\t\t\t\t\t\t\t\t\tCOLLEGE CODE \t COURSE \t NUMBER OF SEATS\n\n");
	display(l);
	printf("\n\n\t\t\t\t\t-_- -_- -_- -_- -_- -_- -_- -_-Open finalallotment.txt file to see the alloted seats-_- -_- -_- -_- -_- -_- -_- -_-\n\n");
	return 0;
}
