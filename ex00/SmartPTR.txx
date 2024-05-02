#ifndef SMARTPTR_TXX
# define SMARTPTR_TXX

#include <iostream>

template <typename T>
class SmartPTR
{
    private:
        T* ptr;
        SmartPTR();
        SmartPTR(const SmartPTR &copy);
        SmartPTR& operator=(const SmartPTR &copy); 

    public:
        SmartPTR(T* &ptr);
        ~SmartPTR();
        T* getPTR();
};


template <typename T>
SmartPTR<T>::SmartPTR(T* &PTR)
{
    this->ptr = PTR;
}

template <typename T>
SmartPTR<T>& SmartPTR<T>::operator=(const SmartPTR& ptr)
{
    std::cout << "Never copy a pointer idiot" << std::endl;
    (void)ptr;
    return(*this);
}

template <typename T>
T* SmartPTR<T>::getPTR(void)
{
    return(this->ptr);
}

template <typename T> 
void del(T* &ptr)
{
    delete ptr;
    ptr = NULL;
}

template <typename T>
SmartPTR<T>::~SmartPTR()
{
    del(this->ptr);
}

#endif