#include<iostream>
class prova_subtyping
{
private:
    /* data */
    int prova;
public:
    int y;
     prova_subtyping(){prova=0;
    std::cout<<"default costuctor \n";}
    prova_subtyping(int x){prova=x;}
    ~prova_subtyping(){}
};


class b: public prova_subtyping{
    public:
        int id;
         explicit b( ){std::cout<<"default costructor b \n";};
        b(int x):id(x){};
        
};
int main(){

    b prova;

}