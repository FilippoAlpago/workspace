#include<iostream>
#include<vector>
int main()
{
    /*std::cout<<"hello wordl"<<std::endl;
    for(int i=0;i<10;i++)
    {
        std::cout<<i<<std::endl;
    }
    char c;
    int n=48;
    c=(char)n;
    std::cout<<n<<" this is N \n";
    std::cout<<c<<" this is the char of N";*/
    
    std::vector<std::vector<int>> matrix;//matrice di interi, vettore di vettori
    std::vector<int> colonna;//dichiaro un vettore 'colonna'
    matrix.push_back(colonna);//aggiungo la colonna, dato che nella "prima posizione" si aspetta un vettore
    matrix.at(0).push_back(10);//ora posso aggiungere qualcosa in quella colonna, dato che all'inizio era vuoto
    int A=matrix.at(0).at(0);
    std::cout<<A<<std::endl;

    return 0;
}