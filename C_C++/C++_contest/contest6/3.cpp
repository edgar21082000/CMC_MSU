#include <iostream>
#include <algorithm>
#include <cmath>

namespace Game{
    
    template<typename T>
    class Coord{
    public:
        typedef T value_type;
        T row, col;
        Coord(T row_ = T{}, T col_ = {}) : row(row_), col(col_){}   
    };    
    
    template<typename T>
    T dist(Coord<T> size, Coord<T> p1, Coord<T> p2){
        if (p1.row == p2.row)
            return abs(p1.col - p2.col);
        if (p1.col == p2.col)
            return abs(p1.row - p2.row);
            
        T y_steps = abs(p1.col - p2.col); 
        
        T xmin = p1.row - ((y_steps + p1.col%2)/2); 
        T xmax = p1.row + ((y_steps + (p1.col+1)%2)/2) ;  
        
        T x_steps = 0;
        if (p2.row < xmin)
            x_steps = xmin - p2.row;
        if (p2.row > xmax)
            x_steps = p2.row - xmax;
        
        return x_steps + y_steps;    
         
    }
}



