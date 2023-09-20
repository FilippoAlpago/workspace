export module smart_ptr;

import <cstddef>;
import <cassert>;
import <utility>;
import <type_traits>;


namespace smart_ptr
{
	// uno smart points ha un tipo a cui punta ed una dimensiona statica templatizzata, il cui valore di default 1 se un non-array altrimenti la lunghezza del suo extent
	// NOTA: si chiama extent la lunghezza statica degli array, ad esempio la parte tra parentesi quadre in: int[10]
	export
	template <class Ty)>
	class smart_ptr
	{
	private:
		using self = smart_ptr<Ty>;//è un typedef
	protected:
		Ty* pt;
		ptrdiff_t offset;//distanza a cui sono arrivato nel pointer
		size_t* cnt;//conta quanti smart pointer puntano allo stesso oggetto in memoria
        bool is_array;
		void dec()
		{
			--(*cnt);
			if (*cnt == 0)
			{
				if(is_array==true){
                    delete[] pt;
                }
				else delete pt;
				delete cnt;
			}
		}

		void inc()
		{
			++(*cnt);
		}

        smart_ptr(Ty* pt_, ptrdiff_t offset_, size_t* cnt_, bool is_Array_)
			: pt(pt_), offset(offset_), cnt(cnt_),is_array(is_Array_)
		{
			inc();//nuovo pointer quindi incremento
		}

	public:
		
		explicit smart_ptr(Ty* p) : smart_ptr(p, 0, new size_t(1),false) {}
        smart_ptr(Ty* p,bool is_Array_) : smart_ptr(p, 0, new size_t(1),is_Array_) {}
		smart_ptr(const self& p)
			: pt(p.pt), cnt(p.cnt), offset(p.offset),is_array(p.is_array)
		{
			inc();//incremento perchè ora puntiamo alla stessa cosa, quindi una volta in più
		}

		~smart_ptr()
		{
			dec();
		}

		self& operator=(const self& p)
		{
			if (pt != p.pt)
			{
				dec();//non punto più al vecchio
				pt = p.pt;
				cnt = p.cnt;
				offset = p.offset;
                is_array=p.is_array;
				inc();//adesso punto uno in più a quello che ho passato
			}
			return *this;
		}

		T& operator*()
		{
			return const_cast<Ty&>(*std::as_const(*this));
		}

		const T& operator*() const
		{
			return pt[offset];
		}

		bool operator==(const self& p) const
		{
			return pt == p.pt && offset == p.offset&& is_array==p.is_array;
		}

		bool operator!=(const self& p) const
		{
			return !(*this == p);
		}

		operator T* ()//operatore di conversione, trasforma uno smart pointer in un pointer
		{
			return const_cast<T*>(std::as_const(*this).operator const T * ());
		}

		operator const T* () const
		{
			return pt + offset;
		}

		self operator+(ptrdiff_t d) const
		{
			return self(pt, offset + d, cnt, is_array);
		}

		self operator-(ptrdiff_t d) const
		{
			return *this + (-d);//in questo modo richiama quello sopra
		}

		self& operator+=(ptrdiff_t d)
		{
			//assert(offset + d >= 0 && offset + d < L);
			offset += d;
			return *this;
		}

		self& operator-=(ptrdiff_t d)
		{
			return *this += -d;
		}

		self& operator++()
		{
			return *this += 1;
		}

		self operator++(int)
		{
			self r(*this);
			++(*this);
			return r;
		}

		self& operator--()
		{
			return *this -= 1;
		}

		self operator--(int)
		{
			self r(*this);
			--(*this);
			return r;
		}

		T* operator->()
		{
			return const_cast<T*>(std::as_const(*this).operator->());
		}

		const T* operator->() const
		{
			return pt + offset;
		}

		T& operator[](ptrdiff_t i)
		{
			return const_cast<T&>(std::as_const(*this)[i]);
		}

		const T& operator[](ptrdiff_t i) const
		{
			assert(offset + i >= 0 && offset + i < L);
			return pt[offset + i];
		}
	};



	// usa tutti gli operatori utilizzabili per i pointer classici
	// è templatizzata così è possibile utilizzarla con tipi qualunque, basta che implementino gli operatori richiesti
	// la usiamo per testare gli smart pointer
	template <class Pointer>
	void demo(Pointer p)
	{
		Pointer p2(p);
		p = p2;
		*p;		// in C, C++ ed altri linguaggi imperativi non è necessario utilizzare il risultato di una chiamata a funzione o operatore
		const Pointer p3(p + 2);
		p2 = p + 2;
		++p2;
		p++;
		--p2;
		p += 1;
		p -= 2;
		p3[0];
	}


	export void test()
	{
		int* a = new int[10];
		demo(a);

		smart_ptr<int[5]> a2(new int[5]);
		demo(a2);

		smart_ptr<int, 10> b(a);
		demo(b);

		smart_ptr<double[10]> d(new double[10]);
		demo(d);

	}

}


