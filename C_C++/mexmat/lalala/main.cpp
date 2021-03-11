#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include "student.h"
#include "tree.h"
#include "tree_node.h"
#define LEN 10


int main(int argc,char*argv[])
{
	tree a;
	char*name;
	int res = 0;
	FILE*fp;
	double t;
	
	if(argc!=2)
	{
		printf("Usage:%s\n",argv[0]);
		return 1;
	}
	name=argv[1];
	fp = fopen(name,"r");
	if(!fp)
	{
		printf("cannot read!\n");
		return 1;
	}
	
	
	if(res!=0)
	{
		printf("cannot read\n");
		return 1;
	}
	
	res = a.read(fp);
	fclose(fp);
	
	if(res<0)
	{
		switch(res)
		{
			case -1:
			printf("not enough memory\n");
			break;
			
			case -2:
			printf("cannot read\n");
			break;
			
			default:
			printf("Uknown error in %s\n",name);
		}
		a.delete_tree();
		return 1;
	}
	
	a.print_tree();
	
	t=clock();
	a.f();////???
	t=clock()-t;
	
	
	printf("after:\n");
	
	a.print_tree();
	
	printf("\nTIME: %lf\n",t/CLOCKS_PER_SEC);
	
	a.delete_tree();
	return 0;
	
}
