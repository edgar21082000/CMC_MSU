#include <algorithm>
#include <cmath>

template<typename T>
class Coord{
public:
    typedef T value_type;
    T row, col;
    Coord(T row_ = T{}, T col_ = {}) : row(row_), col(col_){}   
};

template<typename T>
T dist(Coord<T> size, Coord<T> p1, Coord<T> p2){
    T m = size.row, n = size.col;
    T r1 = p1.row, c1 = p1.col;
    T r2 = p2.row, c2 = p2.col;
    return std::max(std::min((static_cast<T>(abs(r1-r2))), static_cast<T>(m - abs(r1-r2))),
            std::min(static_cast<T>(abs(c1-c2)), static_cast<T>(n - abs(c1-c2))));
}

