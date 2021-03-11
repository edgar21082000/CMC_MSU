#include <iostream>
#include "student.h"

int student::init(const char*n, int v)
{
	value=v;
	if(n)
	{
		name = new char[strlen(n)+1];
		if (!name)
            return -1;
		strcpy(name,n);
	}
	else name=0;
	return 0;
}

void student::destroy()
{
	if(name)
	{
	    delete [] name;
	    name=0;
	}
	value=0;
}

student::student(const student&x)
{
	init(x.name, x.value);
}

student::student(student&&x)
{
	value=x.value;
	name=x.name;
	x.value=0;
	x.name=nullptr;
}

student& student::operator=(const student&x)
{
	destroy();
	init(x.name,x.value);
	return *this;
}

student& student::operator=(student&&x)
{
	destroy();
	value=x.value;
	name=x.name;
	x.value=0;
	x.name=nullptr;
	return *this;
}

student::~student()
{destroy();}

#define LEN 1234

int student::read(FILE*fp)
{
	char buf[LEN];
	destroy();
	if (fscanf(fp,"%s%d",buf,&value)!=2)
	{
		if(feof(fp))return 1;
		printf("gghhjg\n");
		return -1;
	}
	
	if(init(buf,value))return -2;
	
	return 0;
}

void student::print(FILE*out)
{
	fprintf(out,"%s %d\n",name,value);
	return;
}

int student::operator<(const student&x)
{
	if(!name&&!x.name)return value<x.value;
	
	if(!name)return 1;
	if(!x.name)return 0;
	
	int res=strcmp(name,x.name);
	
	if(res<0)return 1;
	if(res>0)return 0;
	
	return value<x.value;
}

int student::operator>(const student&x)
{
	if(!name&&!x.name)return value>x.value;
	
	if(!name)return 0;
	if(!x.name)return 1;
	
	int res=strcmp(name,x.name);
	
	if(res<0)return 0;
	if(res>0)return 1;
	
	return value>x.value;
}

int student::operator==(const student &x)
{
    if ( (!name && !x.name)&& (value==x.value) )
        return 1;
    int res=strcmp(name,x.name);
    if ( (res==0)&&(value==x.value) )
        return 1;
    return 0;
}

void student::swap(student&x)
{
	char *t;
    int val;
    val = x.value;
    t = x.name;
    x.value = value;
	x.name = name;
    value = val;
    name = t;
}

void student::copy(student&x)
{
	value=x.value;
	name=x.name;
}
