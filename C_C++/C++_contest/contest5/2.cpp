#include <iostream>



class Rectangle : public Figure
{
private:
    double width;
    double height;
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    double get_square() const override {return width * height;}
    static Rectangle* make(std::string s) {
        Rectangle* fig = new Rectangle;
        std::istringstream s(str);
        s >> fig->widht >> fig->height;
        return fig;
    }
    ~Rectangle();
};

class Circle : public Figure
{
private:
    double radius;
public:
    Circle(double r) : radius(r) {}
    double get_square() const override { return radius * radius * 3.14159265;}
    static Circle* make(std::string s) {
        Circle* fig = new Circle;
        std::istringstream s(str);
        s >> fig->radius;
        return fig;
    }
    ~Circle();
};

class Square : public Figure
{
private:
    double a,
public:
    Square(double b) : a(b) {}
    double get_square() const override { return a*a;}
    static Square* make(std::string s) {
        Square* fig = new Square;
        std::istringstream s(str);
        s >> fig->a;
        return fig;
    }
    ~Square();
};

