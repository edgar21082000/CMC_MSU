#ifndef STUDENT_H
#define STUDENT_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
class student
{
	private:
		char*name= nullptr;
		int value= 0;
	public:
		student(){};
		student(const student&x);
		student(student&&x);
		student& operator=(const student& x);
		student& operator=(student&& x);
		~student();
		const char*get_name()const
			{return (const char*)name;}
		int get_value()const
			{return value;}
		int init(const char*n,int v);
		void destroy();
		int read(FILE*);
		void print(FILE*out= stdout);
		int operator<(const student&x);
		int operator>(const student&x);
		int operator==(const student &x);
		void swap(student&x);
		void copy(student&x);
};

#endif //STUDENT_H
