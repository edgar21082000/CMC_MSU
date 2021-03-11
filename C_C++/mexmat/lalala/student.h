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
		student(const student&x);//конструктор копирования
		student(student&&x);//конструктор перемещения
		student& operator=(const student& x);//оператор присваивания
		student& operator=(student&& x);//присваивание, получающее ссылку на объект
		~student();//деструктор
		const char*get_name()const
			{return (const char*)name;}
		int get_value()const
			{return value;}
		int init(const char*n,int v);
		void destroy();// очищает
		int read(FILE*);
		void print(FILE*out= stdout);
		int operator<(const student&x);
		int operator>(const student&x);
		int operator==(const student &x);
		void swap(student&x);
		void copy(student&x);
};

#endif //STUDENT_H