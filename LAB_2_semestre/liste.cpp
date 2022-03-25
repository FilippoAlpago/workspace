#include<iostream>

class ListInt{
	public:
		ListInt();  //Deafult Constructor
		~ListInt();  //Destructor
		ListInt(const ListInt& s); //Copy constructor

		void prepend(int el);
		void append(int el);
		void print() const;
		void read();

		void merge(const ListInt& l1, const ListInt& l2); //date due liste ordinate l1 e l2
		                                    //l'oggetto corrente contiene tutti gli elementi di l1
														//ed l2 duplicati ed ordinati (l1 e l2 non vengono modificate)
		void merge_and_destroy(ListInt& l1, ListInt& l2);  //date due liste ordinate l1 e l2
																			//l'oggetto corrente 'ruba' lo stato di l1 e l2
																			//memorizzandone le celle in ordine. Dopo la
																			//chiamata sia l1 che l2 sono le liste vuote

		int& at(unsigned int pos);
		const int& at(unsigned int pos) const;

		ListInt& operator=(const ListInt& x);
		ListInt operator+(const ListInt& x) const;

		
	private:
		struct Cell {
			int info;
			Cell* next;
		};

		typedef Cell* Pcell;

		Pcell head;
		int dummy;

		void destroy(Pcell pc);
		Pcell copy(Pcell source) const;
		Pcell merge_rec(Pcell h1, Pcell h2);
		Pcell merge_dest_rec(Pcell l1, Pcell l2);

};

ListInt::ListInt() {
	head = nullptr;
}

ListInt::~ListInt() {
	destroy(head);
}
			
void ListInt::destroy(Pcell pc) {

	if (pc!=nullptr) {
		destroy(pc->next);
		delete pc;
	}
}

void ListInt::read() {
	destroy(head);
	head=nullptr;
	int elem;
	std::cin>>elem;

	for (int i=0; i<elem; i++) {
		int e;
		std::cin>>e;
		append(e);
	}
}


void ListInt::append(int el) {
	if (head==nullptr) 
		prepend(el);
	else {
		Pcell pc = head;
		while (pc->next!=nullptr)
			pc = pc->next;
		pc->next = new Cell;
		pc->next->info = el;
		pc->next->next = nullptr;
	}
}

void ListInt::prepend(int el) {
	Pcell newone = new Cell;
	newone->info = el;
	newone->next = head;
	head = newone;
}

void ListInt::print() const {
	Pcell pc = head;
	while (pc) {
		std::cout<<pc->info<<std::endl;
		pc = pc->next;
	}
}


ListInt::ListInt(const ListInt& s) {
	head = copy(s.head);
}

ListInt::Pcell ListInt::copy(Cell* source) const{
	if (source == nullptr)
		return nullptr;
	else {
		Pcell dest = new Cell;
		dest->info = source->info;
		dest->next = copy(source->next);
		return dest;
	}
}

ListInt& ListInt::operator=(const ListInt& x) {
	if (this != &x) {
		destroy(head);
		head = copy(x.head);
	}
	return *this;
}	


ListInt ListInt::operator+(const ListInt& x) const{
	ListInt supp(*this);
	Pcell pc = supp.head;
	if (pc == nullptr) {
		supp.head = copy(x.head);
	}
	else {
		while (pc->next!=nullptr)
			pc = pc->next;
		pc->next = copy(x.head);
	}

	return supp;
}


int& ListInt::at(unsigned int pos) {
	Pcell pc = head;
	while (pc!=nullptr && pos>0) {
		pc = pc->next;
		pos--;
	}

	if (pc) 
		return pc->info;
	else
		return dummy;
}

const int& ListInt::at(unsigned int pos) const {
	Pcell pc = head;
	while (pc!=nullptr && pos>0) {
		pc = pc->next;
		pos--;
	}

	if (pc) 
		return pc->info;
	else
		return dummy;
}


void ListInt::merge(const ListInt& l1, const ListInt& l2) {
	destroy(head);
	head = merge_rec(l1.head, l2.head);
}


ListInt::Pcell ListInt::merge_rec(Pcell h1, Pcell h2) {
	if (h1==nullptr && h2==nullptr) 
		return nullptr;
	else {
		if (h1 == nullptr) { //h1 vuota, h2 non vuota
			Pcell newone = new Cell;
			newone->info = h2->info;
			newone->next = merge_rec(h1, h2->next);
			return newone;
		}
		else {
			if (h2 == nullptr) { //h1 non vuota, h2 vuota
				Pcell newone = new Cell;
				newone->info = h1->info;
				newone->next = merge_rec(h1->next, h2);
				return newone;
			}
			else { //nessuna lista vuota
				Pcell newone = new Cell;
				if (h1->info < h2->info) {
					newone->info = h1->info;
					newone->next = merge_rec(h1->next, h2);
				}
				else {
					newone->info = h2->info;
					newone->next = merge_rec(h1, h2->next);
				}
				return newone;
			}
		}
	}
}


void ListInt::merge_and_destroy(ListInt& l1, ListInt& l2) {
  

	if (this != &l1 && this != &l2) {
	  	if (&l1!=&l2) {//tre oggetti distinti
			destroy(head);

			head = merge_dest_rec(l1.head, l2.head);

			l1.head=nullptr;
			l2.head=nullptr;
		} 
		else {   //chiamata a = merge_and_destroy(b,b);
			ListInt supp(l2);
			merge_and_destroy(l1, supp);
		}
	}
	else {
		if (this == &l1 && this!=&l2) {  //chiamata a = merge_and_destroy(a,b)
			ListInt supp(l1);        //duplico l1
			merge_and_destroy(supp, l2);			
		}
		else if (this != &l1 && this == &l2) {   //chiamata a = merge_and_destroy(b,a)
			ListInt supp(l2);                //duplico l2
			merge_and_destroy(l1, supp);
		}
		else {    //chiamata a = merge_and_destroy(a,a)
			ListInt supp1(l1);  //duplico entrambi
			ListInt supp2(l2);
			merge_and_destroy(supp1, supp2);
		}
	}
}


ListInt::Pcell ListInt::merge_dest_rec(Pcell l1, Pcell l2){
	if (l1 == nullptr && l2 == nullptr) 
		return nullptr;
	else {
		if (l1==nullptr) 
			return l2;
		else 
			if (l2==nullptr)
				return l1;
			else
				if (l1->info < l2->info) {
					l1->next = merge_dest_rec(l1->next, l2);
					return l1;
				}
				else {
					l2->next = merge_dest_rec(l1, l2->next);
					return l2;
				}
	}
}


int main() {
	ListInt l1, l2;
	
	l1.read();
	l2.read();
	{
		ListInt l;
		l.merge(l1,l2);
	   	l.print();
	}
	l1.print();
	l2.print();

	l1=l2;
	l1.print();
	return 0;
}
