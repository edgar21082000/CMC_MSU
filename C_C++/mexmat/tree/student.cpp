#include <iostream>
#include "student.h"

int student::init(const char*n, int v)
{
	value=v;
	if (n)
	{
		name = new char[strlen(n)+1];
		if (!name)
            return -1;
		strcpy(name,n);
	}
	else name = 0;
	return 0;
}

void student::destroy()
{
	if (name)
	{
	    delete [] name;
	    name = 0;
	}
	value = 0;
}

student::student(const student&x)
{
	init(x.name, x.value);
}

student::student(student&&x)
{
	value = x.value;
	name = x.name;
	x.value = 0;
	x.name = nullptr;
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
	value = x.value;
	name = x.name;
	x.value = 0;
	x.name = nullptr;
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
		if (feof(fp)) return 1;
		printf("gghhjg\n");
		return -1;
	}
	
	if (init(buf,value)) return -2;
	
	return 0;
}

void student::print(FILE*out)
{
	fprintf(out,"%s %d\n",name,value);
	return;
}

