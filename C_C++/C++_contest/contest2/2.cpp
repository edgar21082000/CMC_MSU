#include <iostream>

void *operator new(size_t size);
void operator delete(void *);

namespace numbers{
    enum{
        SIZE = 16,
    };
    class complex_stack{
        private:
            int len, ssize;
            complex *stack;
        public:
            complex_stack(int len_ = 0): len(len_), ssize(SIZE){
                if (len >= ssize)
                    ssize = len + 1;
                stack = static_cast<complex *>(::operator new(ssize * sizeof(complex)));
            }
            
            complex_stack(const complex_stack &v): len(v.len), ssize(v.ssize){
                stack = static_cast<complex *>(::operator new(ssize * sizeof(complex)));
                for (int i = 0; i < len; i++)
                    new(&stack[i]) complex(v.stack[i]);
            }
            
            size_t size() const{
                return len;
            }
            
            complex operator [] (const int i) const{
                return stack[i];
            }
            
            complex_stack operator = (const complex_stack &v){
                if (this == &v)
                    return *this;
                len = v.len;
                ssize = v.ssize;
                ::operator delete(stack);
                stack = static_cast<complex *>(::operator new(ssize * sizeof(complex)));
                for (int i = 0; i < len; i++)
                    new(&stack[i]) complex(v.stack[i]);
                    
                return *this;      
            }
            
            complex_stack operator << (complex z) const{
                complex_stack res(len+1);
                for (int i = 0; i < len; i++)
                    new(&res.stack[i]) complex(stack[i]);
                new(&res.stack[len]) complex(z);
                return res;
            }
            
            complex operator + () const{
                return stack[len - 1];
            }
            
            complex_stack operator ~ () const{
                complex_stack v(*this);
                v.len--;
                return v;
            }
            
            ~complex_stack(){
                for (int i = 0; i < len; i++)
                    stack[i].~complex();
                ::operator delete(stack);
            }     
    };
}
