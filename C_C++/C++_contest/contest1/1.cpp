class Sum {
private:
    int res;
public:
    Sum(int a, int b) : res(a+b) {}
    
    Sum(Sum a, int b) : res(a.res + b) {}
    
    
    int get() const {
        return res;
    }
            
};


