export module gp;



template <class T>//così si dichiara un generic in c++, va definito per ogni funzione
T sum2(T a, T b)
{
    return a+b; //posso fare questa operazione in c++ a differenza di java
}


template<class T>
T sum(const std::vector<T
>& v)
{

}

int main()
{
    double x= sum2(1.3,4.5);
    
}