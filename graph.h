/*
NOME........Riccardo
COGNOME.....Frigerio
MATRICOLA...781315
E-MAIL..... r.frigerio5@campus.unimib.it
*/

#ifndef GRAPH_H
#define GRAPH_H

#include <stdexcept>	// contiene std::runtime_error
#include <algorithm>	// contiene std::swap
#include <new>			// contiene std::bad_alloc
#include <iterator>		// contiene std::forward_iterator_tag
#include <cstddef>		// contiene std::ptrdiff_t
#include "pair.h"

/**
	Definizione di una classe key_not_found() che estende le eccezioni standard
	Sollevata nel caso in cui cerco un nodo/arco inesistente
	@brief Eccezione custom che rappresenta l'evento di ricerca di un nodo/arco inesistente
*/
class key_not_found : public std::runtime_error{
	
	public:
		key_not_found(const char *message) : std::runtime_error(message){
		}
};

/**
	Definizione di una classe duplicated_node() che estende le eccezioni standard
	Sollevata nel caso in cui cerco di aggiungere un nodo gia' esistente
	@brief Eccezione custom che rappresenta l'evento di inserimento di un arco già presente
*/
class duplicated_node : public std::runtime_error{
	
	public:
		duplicated_node(const char *message) : std::runtime_error(message){
		}
};

/**
	Definizione di una classe duplicated_edge() che estende le eccezioni standard
	Sollevata nel caso in cui cerco di aggiungere un arco gia' esistente
	@brief Eccezione custom che rappresenta l'evento di inserimento di un nodo già presente
*/
class duplicated_edge : public std::runtime_error{
	
	public:
		duplicated_edge(const char *message) : std::runtime_error(message){
		}
};

/**
	Definizione di una classe bad_iterator() che estende le eccezioni standard
	Sollevata nel caso in cui cerco di operare su un iteratore che punta alla coda della lista
	@brief Eccezione custom che rappresenta l'evento di operazione su iteratore "nullo"
*/
class bad_iterator : public std::runtime_error{
	
	public:
		bad_iterator(const char *message) : std::runtime_error(message){
		}
};

/**
	Definizione di una classe graph<T,F> che implementa un grafo non orientato
	@brief Classe che rappresenta un grafo
*/
template<typename T, typename F>
class graph{

	private:
	
		typedef unsigned int size_type; ///< Tipo che definisce il numero dei nodi e degli archi
	
		/**
			Definizione di una struct node(T, node*) che implementa un nodo del grafo
			@brief Struct che rappresenta un nodo del grafo
		*/
		struct node {
		
			// DATI MEMBRO del nodo
			T _data; 		///< dato elementare di tipo T
			node* _next;	///< puntatore al nodo successivo
			
			/** 
			COSTRUTTORE DI DEFAULT di un nodo
			*/
			node () : _data(NULL), _next(NULL){
			}
			
			/**
			Costruttore del nodo dato un elemento
			@param other dato elementare di tipo T che identifica il nodo
			*/
			node(const T &other) : _data(other), _next(NULL){
			}
	
			/**
			DISTRUTTORE di un nodo
			*/
			~node() {
			}
			
			/**
			COPY CONSTRUCTOR di un nodo
			@param other nodo da cui copiare this
			*/
			node(const node &other) : _data(other._data), _next(other._next){
			}
	
			/**
			OPERATOR= di un nodo
			@param other nodo di cui copio lo stato in this
			@return nodo risultato dalla copia 
			*/
			node& operator=(const node &other) {
				
				if(this!=&other) {
				
					node tmp(other);
					tmp.swap(*this);
				}
			
				return *this;
			}
			
			private:
			
				/**
				Metodo utile allo swap dei dati membro di un nodo
				@param other nodo con cui scambiare i dati membro con this
				*/
				void swap(node &other){
						std::swap(this -> _data, other._data);
						std::swap(this -> _next, other._next);
				}
	
		}; // end struct node

		
		/**
			Definizione di una struct edge(pair, edge*) che implementa un arco del grafo
			@brief Struct che rappresenta un arco del grafo
		*/
		struct edge {
		
			// DATI MEMBRO dell'arco
			pair<T> _pair;		///< coppia di dati elementari T che rappresentano il nodo dell'arco 
			edge* _next;	///< puntatore all'arco successivo
			
			/** 
			COSTRUTTORE DI DEFAULT di un arco
			*/
			edge(): _pair(NULL), _next(NULL){
			}
			
			/**
			Costruttore dell'arco dato un elemento
			@param value1 dato elementare di tipo T che identifica il nodo sorgente
			@param value2 dato elementare di tipo T che identifica il nodo destinazione
			*/
			edge(const T &value1, const T &value2) : _pair(value1, value2), _next(NULL) {
			}
	
			/**
			DISTRUTTORE di un arco
			*/
			~edge() {
			}
	
			/**
			COPY CONSTRUCTOR di un arco
			@param other arco da cui copiare this
			*/
			edge(const edge &other) : _pair(other._pair), _next(other._next) {
			}
	
			/**
			OPERATOR= di un arco
			@param other arco di cui copio lo stato in this
			@return arco risultante dalla copia 
			*/
			edge& operator=(const edge &other) {
				
				if(this!=&other) {
				
					edge tmp(other);
					tmp.swap(*this);
				
				}
				return *this;
			}
			
			private:
		
				/**
				Metodo utile allo swap dei dati membro di un arco
				@param other arco con cui scambiare i dati membro con this
				*/
				void swap(edge &other){

					std::swap(this -> _pair, other._pair);
					std::swap(this -> _next, other._next);
				}
	
		}; // end struct edge
	
		// DATI MEMBRO DEL GRAFO
		node* _headN; 		 ///< testa della lista dei nodi
		edge* _headE; 		 ///< testa della lista degli archi
		size_type num_nodes; ///< numero di nodi
		size_type num_edges; ///< numero di archi
		
		/**
		METODO AUSILIARIO
		Dato un elemento, ritorna il relativo puntatore al nodo se esistente, altrimenti NULL.
		@param value dato elementare T di cui cerco il nodo
		@return puntatore al relativo nodo, se esistente
		*/ 
		node* find_N_helper(const T &value) const{
		
			node *tmp = _headN; 
			F comp_node;
	
			while(tmp!=0) {
			
				if(comp_node(tmp -> _data, value))
					return tmp;
				
				tmp = tmp -> _next;
			}
			
			return NULL;
		}
		
		/**
		METODO AUSILIARIO
		Dato due elementi, ritorna il relativo puntatore all'arco se esistente, altrimenti NULL.
		@param value1 dato elementare T del nodo sorgente dell'arco che cerco
		@param value2 dato elementare T del nodo sorgente dell'arco che cerco
		@return puntatore al relativo arco, se esistente
		*/ 
		edge* find_E_helper(const T &value1, const T &value2) const{
			
			edge *tmp = _headE;
			F comp_node;
			
			while(tmp!=0){
			
				if(comp_node(tmp -> _pair.src(), value1) && comp_node(tmp -> _pair.dst(), value2))
					return tmp;
				
				tmp = tmp -> _next;
			}
	
			return NULL;		
		}
		
		/**
		METODO AUSILIARIO
		Dato un elemento, effettua un controllo sull'eventuale nodo relativo.
		@param value dato elementare T del nodo che cerco
		@return true se il puntatore cercato è nullo, false altrimenti
		*/ 
		bool check_N(const T &value) const{
			return find_N_helper(value)==NULL;
		}
			
		/** 
		METODO AUSILIARIO
		Dati due elementi, effettua dei controlli sull'eventuale arco relativo.
		@param value1 dato elementare T del nodo sorgente dell'arco che cerco
		@param value2 dato elementare T del nodo destinazione dell'arco che cerco
		@return 1 se i due valori sono entrambi nodi e l'arco esiste; 0 se i due valori sono entrambi nodi e l'arco non esiste; -1 se almeno uno dei due valori non corrisponde a nessun nodo
		*/
		int check_E(const T &value1, const T &value2) const{
		
			if(!check_N(value1)&&!check_N(value2)){
				if (find_E_helper(value1, value2)==NULL)
					return 0;
				else
					return 1;
			}
			else
				return -1;		
		}
		
		/**
		METODO AUSILIARIO
		Pulisce la memoria allocata da nodi e archi.
		*/
		void clear(){
			
			// Cancello i nodi
			node *tmpN = _headN;
			node *tmpN2 = NULL;
		
			while(tmpN!=NULL) {
			
				tmpN2 = tmpN -> _next;
				delete tmpN;
				tmpN = tmpN2;
			}
			
			// Cancello gli archi
			edge *tmpE = _headE;
			edge *tmpE2 = NULL;
			
			while(tmpE!=NULL) {
				
				tmpE2 = tmpE -> _next;
				delete tmpE;
				tmpE = tmpE2;
			}		
		}
		
		/**
		METODO AUSILIARIO
		Aggiorna gli archi in seguito ad una rimozione del nodo, per mantenere il grafo in uno stato coerente
		@param value elemento T che identifica il nodo da cui deriva l'aggiornamento
		*/
		void update_edges(const T &value){
			
			F comp;
			edge *tmpE = _headE;
			edge *tmpE2 = NULL;
			
			while(tmpE!=NULL) {
				
				tmpE2 = tmpE -> _next;
				if(comp(tmpE -> _pair.src(), value)||comp(tmpE -> _pair.dst(), value)){
					safe_remove_edge(tmpE -> _pair.src(), tmpE -> _pair.dst());
				}
				tmpE = tmpE2;
			}	
		}
		
		/**
		METODO AUSILIARIO
		Rimuove fisicamente l'arco, una volta che sono sicuro sia esistente.
		@param value1 dato elementare T del nodo sorgente dell'arco
		@param value2 dato elementare T del nodo destinazione dell'arco
		*/
		void safe_remove_edge(const T &value1, const T &value2){
					
				edge* tmp = _headE;
				F comp;				
				if(comp(tmp -> _pair.src(),value1)&&comp(tmp -> _pair.dst(), value2)){
				
					_headE = tmp -> _next;
					delete tmp; 
				}	
				else{
				
					while(!comp(tmp -> _next -> _pair.src(),value1)&&!comp(tmp -> _next -> _pair.dst(),value2)){
						edge* tmp2 = tmp -> _next;
						tmp = tmp2;
					}
					
					edge* tmp2 = tmp -> _next;
					std::swap(tmp -> _next, tmp2 -> _next);
					delete tmp2;  
				}
		}
		
		/**
		Metodo utile allo swap dei dati membro di un grafo
		@param other grafo con cui scambiare i dati membro con this
		*/
		void swap(graph &other){
				
			std::swap(this ->_headN, other._headN);
			std::swap(this ->_headN, other._headE);
			std::swap(this -> num_nodes, other.num_nodes);
			std::swap(this -> num_edges, other.num_edges);
		}
		
	public:
			
		/** 
		COSTRUTTORE DI DEFAULT di un grafo
		*/
		graph(): _headN(NULL), _headE(NULL), num_nodes(0), num_edges(0){
		}
	
		/**
		DISTRUTTORE di un grafo
		*/
		~graph() {
			clear();
		}
		
		/**
		COPY CONSTRUCTOR di un grafo
		@param other grafo da cui copiare this
		@throw ... nel caso in cui qualche new fallisca
		*/
		graph(const graph &other):_headN(NULL), _headE(NULL), num_nodes(0), num_edges(0){
			
			// Delego il lavoro alla funzione add utilizzando un meccanismo di error recovery
			node *tmpN = other._headN;
			edge *tmpE = other._headE;
			
			try
			{
				while(tmpN!=0)
				{
					add_node(tmpN -> _data);
					tmpN = tmpN -> _next;
				}
				
				while(tmpE!=0)
				{
					add_edge(tmpE -> _pair.src(), tmpE -> _pair.dst());
					tmpE = tmpE -> _next;
				}
				
			}
			catch(...)
			{
				clear(); // Riporto l'oggetto in uno stato coerente
				throw;
			}
		}
		
		/**
		OPERATOR= di un grafo
		@param other grafo di cui copio lo stato in this
		@return grafo risultante dalla copia 
		*/
		graph& operator=(const graph &other) {
			
			if(this!=&other) {
				graph temp(other);
				temp.swap(*this);
			}
			
			return *this;
		}

		/**
		METODO PUBBLICO
		Getter del numero dei nodi di this
		@return numero dei nodi del grafo
		*/
		size_type get_size_nodes() const{
			return this -> num_nodes;
		}
		
		/**
		METODO PUBBLICO
		Getter del numero degli archi di this
		@return numero degli archi del grafo
		*/
		size_type get_size_edges() const{
			return this -> num_edges;
		}
		
		/**
		METODO PUBBLICO RICHIESTO DA PROGETTO
		Aggiunge un nodo, dato il relativo valore, se non ancora esistente
		@param value dato elementare T da cui aggiungere il nodo
		@throw duplicated_node nel caso in cui si cerchi di aggiungere un nodo già esistente
		@throw std::bad_alloc nel caso in cui l'allocazione di memoria non vada a buon fine
		*/
		void add_node(const T &value){
			
			if(check_N(value)){
				
				try{
				
					if(_headN==NULL)
						_headN = new node(value);
					else{
						
						node *tmp = _headN;
						_headN = new node(value);
						_headN -> _next = tmp;		
					}
					
					num_nodes++;
				}
				catch(std::bad_alloc &e){
					std::cout << e.what() << std::endl;
					throw;
				}
			}
			else throw duplicated_node("EXCEPTION: Impossibile aggiungere un nodo gia' esistente!");
		}
		
		/**
		METODO PUBBLICO RICHIESTO DA PROGETTO
		Rimuove un nodo, dato il relativo valore, se esistente
		@param value dato elementare T da cui rimuovere il nodo
		@throw key_not_found nel caso si cerchi di rimuovere un nodo inesistente
		*/
		void remove_node(const T &value){
			if(!check_N(value)){
				node* tmp = _headN;
				F comp;
				
				if(comp(tmp -> _data,value)){
					_headN = tmp -> _next;
					delete tmp; 
				}	
				else{
					while(!comp(tmp -> _next -> _data,value)){
						node* tmp2 = tmp -> _next;
						tmp = tmp2;
					}
					node* tmp2 = tmp -> _next;
					std::swap(tmp -> _next, tmp2 -> _next);
					delete tmp2;  
				}
				update_edges(value);
			}
			else throw key_not_found("EXCEPTION: Impossibile rimuovere un nodo inesistente!");
		}
		
		/** METODO PUBBLICO RICHIESTO DA PROGETTO
		Aggiunge un arco, dati i relativi valori, se non ancora esistente e i valori sono nodi esistenti
		@param value1 dato elementare T che identifica il nodo sorgente da cui aggiungere l'arco
		@param value2 dato elementare T che identifica il nodo destinazione da cui aggiungere l'arco
		@throw duplicated_edge nel caso in cui si cerchi di aggiungere un arco già esistente
		@throw key_not_found nel caso in cui si cerchi di aggiungere un arco su nodi inesistenti
		@throw std::bad_alloc nel caso in cui l'allocazione di memoria non vada a buon fine
		*/
		void add_edge(const T &value1, const T &value2){
		
			if(check_E(value1, value2)==0 && check_E(value2, value1)==0){
				try{
					
					if(_headE==NULL)
						_headE = new edge(value1, value2);
					else{
	
						edge *tmp = _headE;
						_headE = new edge(value1, value2);
						_headE -> _next = tmp;		
					}				
					num_edges++;
				}
				catch(std::bad_alloc &e){
					std::cout << e.what() << std::endl;
					throw;
				}
			}
			else {
				if (check_E(value1, value2)>0 || check_E(value2, value1)>0)
					throw duplicated_edge("EXCEPTION: Impossibile aggiungere un arco gia' esistente!");
				else throw key_not_found("EXCEPTION: Impossibile aggiungere un arco su un nodo inesistente!");
			}
		}
		
		/** METODO PUBBLICO RICHIESTO DA PROGETTO
		Rimuove un arco, dati i relativi valori, se esistente e i valori sono nodi esistenti
		@param value1 dato elementare T che identifica il nodo sorgente da cui rimuovere l'arco
		@param value2 dato elementare T che identifica il nodo destinazione da cui rimuovere l'arco
		@throw duplicated_edge nel caso in cui si cerchi di rimuovere un arco inesistente
		@throw key_not_found nel caso in cui si cerchi di rimuovere un arco su nodi inesistenti
		*/
		void remove_edge(const T &value1, const T &value2){
			
			if(check_E(value1, value2)>0 || check_E(value2,value1)>0){
				safe_remove_edge(value1, value2);
			}
			else {
				if (check_E(value1,value2)==0 || check_E(value2,value1)==0)
					throw key_not_found("EXCEPTION: Impossibile rimuovere un arco inesistente!");
				else throw key_not_found("EXCEPTION: Impossibile rimuovere un arco su un nodo inesistente!");
			}
		}
		
		/** METODO PUBBLICO RICHIESTO DA PROGETTO
		Stampa true se il valore corrisponde ad un nodo, false altrimenti
		@param value dato elementare T del nodo che cerco
		*/
		void exists(const T &value) const{
			if(!check_N(value))
				std::cout <<  "exists(" << value << ") = true" << std::endl;
			else
				std::cout <<  "exists(" << value << ") = false" << std::endl;
		}
		
		/** METODO PUBBLICO RICHIESTO DA PROGETTO
		Stampa true se il valore corrisponde ad un arco di nodi esistenti, false altrimenti
		@param value1 dato elementare T che rappresenta il nodo sorgente dell'arco che cerco
		@param value2 dato elementare T che rappresenta il nodo destinazione dell'arco che cerco
		@throw key_not_found nel caso in cui si cerchi un arco su nodi inesistenti
		*/
		void has_edge(const T &value1, const T &value2) const{
		
			if(!check_N(value1)&&!check_N(value2)){
				
				if(check_E(value1, value2)>0 || check_E(value2, value1)>0)
					std::cout <<  "has_edge(" << value1 << "," << value2 << ") = true" << std::endl;
				else
					std::cout <<  "has_edge(" << value1 << "," << value2 << ") = false" << std::endl;
			}
			else throw key_not_found("EXCEPTION: Impossibile ricercare un arco su un nodo inesistente!");	
		}
		
		/** METODO PUBBLICO RICHIESTO DA PROGETTO
		Stampa la lista dei nodi raggiungibili da un nodo, se esistente, dato un valore
		@param value dato elementare T del nodo di cui stampare i "vicini"
		@throw key_not_found nel caso in cui si cerchi un nodo inesistente
		*/
		void neighbors(const T &value) const{
			if(!check_N(value)){
			
				edge *tmp = _headE;
				F comp_node;
		
				std::cout << "neighbors(" << value << ")={";
				
				while(tmp!=0){
			
					if(comp_node(tmp -> _pair.src(), value))
						std::cout << tmp -> _pair.dst() << ",";
					if(comp_node(tmp -> _pair.dst(), value))
						std::cout << tmp -> _pair.src() << ",";

					tmp = tmp -> _next;
				}
				
				std::cout << "}" << std::endl;
			}
			else throw key_not_found("EXCEPTION: Impossibile stampare neighbors() di un nodo inesistente!");
		}	
		
		/**	
		Definizione di una classe const_iterator che implementa gli ITERATORI FORWARD sui nodi
		
		@brief Classe che rappresenta un iteratore forward sui nodi
		*/
		class const_iterator {
		
			private:

				const node* n;			///< puntatore al nodo contenente il dato "puntato" dall'iteratore	
				friend class graph;		///< classe padre
				friend class iterator;	///< classe padre
	
				/** 
				Costruttore secondario di un iteratore forward sui nodi, dato un puntatore al nodo
				@param p puntatore al nodo
				*/
				const_iterator(const node* p): n(p) { 
				}
			
			public:
			
				//Traits degli iteratori
				typedef std::forward_iterator_tag	iterator_category;	///< tag corrispondente all'iteratore forward
				typedef T			             	value_type;			///< definizionde del tipo di dato "puntato" dall'iteratore
				typedef ptrdiff_t                	difference_type;	///< tipo (di default) usato per differenziare due puntatori
				typedef const T*			     	pointer;			///< definizione del puntatore al tipo di dato "puntato" dall'iteratore
				typedef const T&					reference; 			///< definizione del puntatore al tipo di dato "puntato" dall'iteratore
			
				/** 
				COSTRUTTORE DEFAULT di un iteratore forward sui nodi
				*/
				const_iterator() : n(NULL){
				}					
		
				/** 
				DISTRUTTORE di un iteratore forward sui nodi
				*/
				~const_iterator() {
				}					
			
				/**
				COPY CONSTRUCTOR di un iteratore forward sui nodi
				@param other iteratore da cui copiare this
				*/
				const_iterator(const const_iterator &other): n(other.n){
				}
			
				/**
				OPERATOR= di un iteratore forward sui nodi
				@param other iteratore di cui copio lo stato in this
				@return iteratore risultante dalla copia 
				*/
				const_iterator& operator=(const const_iterator &other){
					
					if(this!=&other) {
						const_iterator tmp(other);
						tmp.swap(*this);
					}					
					return *this;		
				}
				
				/**
				OPERATOR& di deferenziamento di iteratore forward sui nodi
				@return dato riferito dall'iteratore
				@throw bad_iterator nel caso in cui si cerchi di dereferenziare un iteratore "nullo"
				*/
				const reference operator*() const {
					
					if(n==NULL) throw bad_iterator("EXCEPTION: impossibile dereferenziare un iteratore nullo!");
					return n -> _data; //ritorno il valore del nodo
				}
				
				/**
				OPERATOR -> di deferenziamento di iteratore forward sui nodi
				@return puntatore al dato riferito dall'iteratore
				@throw bad_iterator nel caso in cui si cerchi di dereferenziare un iteratore "nullo"
				*/
				const pointer operator->() const {
				
					if(n==NULL) throw bad_iterator("EXCEPTION: impossibile dereferenziare un iteratore nullo!");
					return &(n -> _data); //ritorno il puntatore al valore del nodo
				}
		
				/**
				OPERATOR++ di iterazione post-incremento di iteratore forward sui nodi
				@return puntatore allo stato precedente
				@throw bad_iterator nel caso in cui si cerchi di incrementare un iteratore "nullo"
				*/
				const_iterator operator++(int) {
					
					if(n==NULL) throw bad_iterator("EXCEPTION: impossibile incrementare un iteratore nullo!");
					const_iterator tmp(*this);	//vecchio stato
					n = n -> _next; 			//cambio lo stato corrente
					return tmp;					//ritorno il vecchio stato
				}
	
				/**
				OPERATOR++ di iterazione pre-incremento di iteratore forward
				@return puntatore allo stato nuovo
				@throw bad_iterator nel caso in cui si cerchi di incrementare un iteratore "nullo"
				*/
				const_iterator& operator++() {
					
					if(n==NULL) throw bad_iterator("EXCEPTION: impossibile incrementare un iteratore nullo!");
					n = n -> _next; //cambio lo stato corrente
					return *this;	//ritorno il nuovo stato
				}

				/**
				OPERATOR!= di uguaglianza un iteratore forward sui nodi
				@param other iteratore da confrontare
				@return true se other e' uguale al puntatore a nodi, false altrimenti
				*/
				bool operator==(const const_iterator &other) const {
				
					return (n == other.n);
				}
		
				/**
				OPERATOR!= di diversita' un iteratore forward sui nodi
				@param other iteratore da confrontare
				@return true se other e' diverso dal puntatore a nodi, false altrimenti
				*/
				bool operator!=(const const_iterator &other) const {
					
					return (n != other.n);
				}
				
				/**
				Metodo utile allo swap dei dati membro di un iteratore forward sui nodi
				@param other iteratore con cui scambiare i dati membro con this
				*/
				void swap(const_iterator &other){
				
					std::swap(this -> n, other.n);
				}
			
		}; // end class const_iterator

	/**
	ME'TODO PUBBLICO
	Restituisce un const_iterator alla testa della lista dei nodi del grafo
	@return iteratore alla testa
	*/
	const_iterator begin() const{
		return const_iterator(_headN);
	}

	/**
	METODO PUBBLICO
	Restituisce un const_iterator alla coda della lista dei nodi del grafo
	@return iteratore alla coda
	*/
	const_iterator end() const{
		return const_iterator(NULL);
	}

	/**	
	Definizione di una classe const_iterator_E che implementa gli ITERATORI FORWARD sugli archi
	@brief Classe che rappresenta un iteratore forward sugli archi
	*/
	class const_iterator_E {
	
		private:
			const edge* e;			///< puntatore all'arco contenente il dato "puntato" dall'iteratore	
			friend class graph;		///< classe padre

			/** 
			Costruttore secondario di un iteratore forward sugli archi, dato un puntatore all'arco
			@param p puntatore all'arco
			*/
			const_iterator_E(const edge* p): e(p) { 
			}
		
			public:
		
			//Traits degli iteratori
			typedef std::forward_iterator_tag	iterator_category;	///< tag corrispondente all'iteratore forward
			typedef pair<T>			            value_type;			///< definizionde del tipo di dato "puntato" dall'iteratore
			typedef ptrdiff_t                	difference_type;	///< tipo (di default) usato per differenziare due puntatori
			typedef const pair<T>*			     	pointer;			///< definizione del puntatore al tipo di dato "puntato" dall'iteratore
			typedef const pair<T>&					reference; 			///< definizione del puntatore al tipo di dato "puntato" dall'iteratore
		
			/** 
			COSTRUTTORE DEFAULT di un iteratore forward sugli archi
			*/
			const_iterator_E() : e(NULL){
			}					
	
			/** 
			DISTRUTTORE di un iteratore forward sugli archi
			*/
			~const_iterator_E() {
			}					
		
			/**
			COPY CONSTRUCTOR di un iteratore forward sugli archi
			@param other iteratore da cui copiare this
			*/
			const_iterator_E(const const_iterator_E &other): e(other.e){
			}
		
			/**
			OPERATOR= di un iteratore forward sugli archi
			@param other iteratore di cui copio lo stato in this
			@return iteratore risultante dalla copia 
			*/
			const_iterator_E& operator=(const const_iterator_E &other){
				
				if(this!=&other) {
					const_iterator_E tmp(other);
					tmp.swap(*this);
				}					
				return *this;		
			}
			
			/**
			OPERATOR& di deferenziamento di iteratore forward sugli archi
			@return dato riferito dall'iteratore
			@throw bad_iterator nel caso in cui si cerchi di dereferenziare un iteratore "nullo"
			*/
			const reference operator*() const {
				
				if(e==NULL) throw bad_iterator("EXCEPTION: impossibile dereferenziare un iteratore nullo!");
				return e -> _pair; //ritorno il valore dell'arco
			}
			
			/**
			OPERATOR -> di deferenziamento di iteratore forward sugli archi
			@return puntatore al dato riferito dall'iteratore
			@throw bad_iterator nel caso in cui si cerchi di dereferenziare un iteratore "nullo"
			*/
			const pointer operator->() const {
			
				if(e==NULL) throw bad_iterator("EXCEPTION: impossibile dereferenziare un iteratore nullo!");
				return &(e -> _pair); //ritorno il puntatore al valore dell'arco
			}
	
			/**
			OPERATOR++ di iterazione post-incremento di iteratore forward sugli archi
			@return puntatore allo stato precedente
			@throw bad_iterator nel caso in cui si cerchi di incrementare un iteratore "nullo"
			*/
			const_iterator_E operator++(int) {
				
				if(e==NULL) throw bad_iterator("EXCEPTION: impossibile incrementare un iteratore nullo!");
				const_iterator_E tmp(*this);	//vecchio stato
				e = e -> _next; 			//cambio lo stato corrente
				return tmp;					//ritorno il vecchio stato
			}

			/**
			OPERATOR++ di iterazione pre-incremento di iteratore forward sugli archi
			@return puntatore allo stato nuovo
			@throw bad_iterator nel caso in cui si cerchi di incrementare un iteratore "nullo"
			*/
			const_iterator_E& operator++() {
				
				if(e==NULL) throw bad_iterator("EXCEPTION: impossibile incrementare un iteratore nullo!");
				e = e -> _next; //cambio lo stato corrente
				return *this;	//ritorno il nuovo stato
			}

			/**
			OPERATOR!= di uguaglianza un iteratore forward sugli archi
			@param other iteratore da confrontare
			@return true se other e' uguale al puntatore a archi, false altrimenti
			*/
			bool operator==(const const_iterator_E &other) const {
			
				return (e == other.e);
			}
	
			/**
			OPERATOR!= di diversita' un iteratore forward sugli archi
			@param other iteratore da confrontare
			@return true se other e' diverso dal puntatore a archi, false altrimenti
			*/
			bool operator!=(const const_iterator_E &other) const {
				
				return (e != other.e);
			}
			
			/**
			Metodo utile allo swap dei dati membro di un iteratore forward sugli archi
			@param other iteratore con cui scambiare i dati membro con this
			*/
			void swap(const_iterator_E &other){
			
				std::swap(this -> e, other.e);
			}
		
	}; // end class const_iterator_E

	/**
	METODO PUBBLICO
	Restituisce un const_iterator alla testa della lista degli archi del grafo
	@return iteratore alla testa
	*/
	const_iterator_E begin_E() const{
		return const_iterator_E(_headE);
	}

	/**
	METODO PUBBLICO
	Restituisce un const_iterator alla coda della lista degli archi del grafo
	@return iteratore alla coda
	*/
	const_iterator_E end_E() const{
		return const_iterator_E(NULL);
	}

}; // end class graph

/** 
OPERATOR<< di un grafo
Permette di stampare il grafo su std::cout
@param os stream a cui "spedire" il grafo
@param g grafo da stampare
@return stream del grafo
*/
template <typename T, typename F>
std::ostream& operator<<(std::ostream &os, const graph<T,F> &g) {
	
	os << "{";
	
	typename graph<T,F>::const_iterator startN, endN;
	
	for(startN = g.begin(), endN = g.end(); startN != endN; ++startN) 
		os << "node: " << *startN << "; ";
		
	os << std::endl;
	
	typename graph<T,F>::const_iterator_E startE, endE;
	
	for(startE = g.begin_E(), endE = g.end_E(); startE != endE; ++startE) 
		os << "edge: " << startE -> src() << "," << startE -> dst() << "; ";
		
	os << "}"; 
		
	return os;
}

#endif
