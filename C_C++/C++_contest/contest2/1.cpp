#include <iostream>
#include <cmath>

namespace numbers{
    enum {
        SIZE = 64,
    };
    class complex {
    private:
        double a, b;
    public:
        complex(double re = 0, double im = 0): a(re), b(im){
        
        }
        double re() const{
            return a;
        }
        double im() const{
            return b;
        }
        
        explicit complex(std::string str){
            sscanf(&str[0], "(%lf,%lf)", &a, &b);
        } 
        
        double abs2() const{
            return a*a + b*b;
        }
        double abs() const{
            return sqrt(a*a + b*b);
        }
        
        std::string to_string() const{
            std::string res(SIZE, '\t');
            snprintf(res.data(), SIZE, "(%.10g,%.10g)", a, b);
            res.resize(res.find('\0'));
            return res;
        }
        
        complex operator += (const complex &c){
            a += c.a;
            b += c.b;
            return *this;
        }
        complex operator -= (const complex &c){
            a -= c.a;
            b -= c.b;
            return *this;
        }
        complex operator *= (const complex &c){
            double tmpa = a, tmpb = b;
            a = tmpa * c.a - tmpb * c.b;
            b = tmpa * c.b + tmpb * c.a;
            return *this;
        }
        complex operator /= (const complex &c){
            double tmpa = a; double tmpb = b;
            a = (tmpa * c.a + tmpb * c.b) / (c.a * c.a + c.b * c.b);
            b = (c.a * tmpb - tmpa * c.b) / (c.a * c.a + c.b * c.b);
            return *this;
        }
        
        friend complex operator + (const complex &c1, const complex &c2);
        friend complex operator - (const complex &c1, const complex &c2);
        friend complex operator * (const complex &c1, const complex &c2);
        friend complex operator / (const complex &c1, const complex &c2);
        
        complex operator ~ () const{
            return complex(a, -b);
        }
        complex operator - () const{ 
            return complex(-a, -b);
        }                
    };
    
    complex operator + (const complex &c1, const complex &c2){
        return complex(c1.a + c2.a, c1.b + c2.b);
    }
    complex operator - (const complex &c1, const complex &c2){
        return complex(c1.a - c2.a, c1.b - c2.b);
    }
    complex operator * (const complex &c1, const complex &c2){
        return complex(c1.a * c2.a - c1.b * c2.b, c1.b * c2.a +  c1.a * c2.b);
    }
    complex operator / (const complex &c1, const complex &c2){
        double zn = (c2.a * c2.a + c2.b * c2.b);
        return complex((c1.a * c2.a + c1.b * c2.b) / zn, (c2.a * c1.b - c1.a * c2.b) / zn);    
    }
    
}
