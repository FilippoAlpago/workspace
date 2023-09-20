export module pairs;

import <string>;
import <functional>;


export
template <class A, typename B>// modo di fare generi programming in c.
class pair
{
	template <class C, typename D> friend class pair;	// necessario per il copy constructor templatizzato, sono per i punti bomus, vaffanculo.
private:
	A first;
	B second;

public:
	// 2.a

    // i : servono per poter costruire direttamente gli ogetti, evitando di passare per il costruttore di default. es nel secondo costruttore evita di costruire con quello di default first e second
    // ma li costruisce direttamente per copia
	pair() : first(), second() {}//costruttore senza parametri(di default) di pair che die di costruire di default fist e second.  first(), second() vogliono dire che chiamano il costruttor di default del tipo di first, A, e second, B.
	pair(const A& a, const B& b) : first(a), second(b) {}// costrutore di pair a cui passo i valori che first e second devono avere. first(a), second(b) utilizzo i costruttori di copia del tipo  di first e second
	pair(const pair<A, B>& p) : first(p.first), second(p.second) {}
    // questo qui è il copy costructor di pair, li passo come parametro un pair<A, B>. first(p.first), second(p.second), utilizzo i costruttori di copia del tipo di di first e second
	pair<A, B>& operator=(const pair<A, B>& p)// deve tornare una refernce di un pair<A,B> di me stesso
	{//modifico me stesso
		first = p.first;
		second = p.second;
		return *this;// ritorno me stesso con le modifiche fatte
	}

	// 2.c
	template <class C, typename D>
	pair(const pair<C, D>& p) : first(p.first), second(p.second) {}


	// 2.b
	pair<A, B> operator++(int)// questo è il post-incremento
	{
		pair<A, B> tmp(*this);//creo una copia di me stesso
		first++;// incremento i miei campi
		second++;
		return tmp;//torno la mia copia senza i valori modificati, perchè è il post-incremento
	}

	pair<A, B>& operator++()//pre-incremento  
	{
		++first;
		++second;
		return *this;//ritono me stesso con i valori modificati
	}

	bool operator==(const pair<A, B>& p) const//const alla fine vuol dire che il metodo è costante, non modifica i valori di this
	{
		return first == p.first && second == p.second;
	}

	bool operator!=(const pair<A, B>& p) const
	{
        //return !(this->operator==(p));
		return !(*this == p);//sfrutto l'operatorer di == sopra definito
	}

	// altri operatori aritmentici ed in-place sono analoghi
	pair<A, B> operator+(const pair<A, B>& p) const
	{
		return pair<A, B>(first + p.first, second + p.second);// torno un nuovo pair che a valori first + p.first, second + p.second, che sono quelli miei e quello che che ho passato
	}

	pair<A, B>& operator+=(const pair<A, B>& p)//a+=b==== a=a+b
	{//vado a modificare me stesso, difatti non ha const alla fine
		first += p.first;
		second += p.second;
		return *this;
	}

    //sono i getter, anche quelli const
	const A& fst() const
	{
		return first;
	}

	A& fst()
	{
		return first;
	}

	const B& snd() const
	{
		return second;
	}

	B& snd()
	{
		return second;
	}

};


export int main()
{
	pair<int, int> p1(4, 5);
	pair<int, int> p2(p1);

	pair<std::string, bool> p3("ciao", true);
	pair<double, double> p4(p1);

	p1 = p2;

	int n = p1.fst();
	p1.snd() = p1.snd() * 3;
	p4 += p1;	// converte implicitamente il RV in un pair<double, double> tramite un conversion copy-constructor templatizzato

	return 0;
}

using real = double;
using unary_fun = function<real(const real&)>;

#define RESOLUTION (10)



