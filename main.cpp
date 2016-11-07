/*
NOME........Riccardo
COGNOME.....Frigerio
MATRICOLA...781315
E-MAIL..... r.frigerio5@campus.unimib.it
*/

#include <iostream>
#include "graph.h"

/**
	Definizione di una struct compare_int che implementa una funzione di confronto fra interi
	@brief Struct che rappresenta una funzione di confronto fra interi
*/
struct compare_int{

	/**
	OPERATOR()
	Dati due interi operandi, effettua un controllo di uguaglianza su essi.
	@param a primo operando intero
	@param b secondo operando intero
	@return true se gli operandi sono uguali, false altrimenti
	*/ 
	bool operator()(const int a, const int b){
		return a==b;
	}
};

/**
	Definizione di una struct compare_int che implementa una funzione di confronto fra stringhe
	@brief Struct che rappresenta una funzione di confronto fra stringhe
*/
struct compare_string {

	/**
	OPERATOR()
	Date due stringhe operandi, effettua un controllo di uguaglianza su essi.
	@param a prima stringa operando
	@param b seconda stringa operando
	@return true se gli operandi sono uguali, false altrimenti
	*/
	bool operator()(const std::string &a, const std::string &b) const {
		return ucase(a)==ucase(b);
	}
	private:
	
		/**
		METODO AUSILIARIO
		Data una stringa, restituisce la stessa stringa con tutti i caratteri maiuscoli.
		@param str stringa in ingresso
		@return stringa con tutti i caratteri maiuscoli
		*/
		std::string ucase(const std::string &str) const {
			std::string tmp(str);
			for(int i=0; i< tmp.size(); ++i)
				tmp[i]=std::toupper(tmp[i]);
		
			return tmp;
		}	
};

/**
	Definizione di una struct compare_int che implementa una funzione di confronto fra caratteri
	@brief Struct che rappresenta una funzione di confronto fra caratteri
*/
struct compare_char{

	/**
	OPERATOR()
	Dati due caratteri operandi, effettua un controllo di uguaglianza su essi.
	@param a primo carattere operando
	@param b secondo carattere operando
	@return true se gli operandi sono uguali, false altrimenti
	*/
	bool operator()(const char a, const char b){
		return a==b;
	}
};

/**
METODO DI TEST
Data un grafo templato di interi, effettua delle chiamate alle funzioni pubbliche per testarle.
*/
void test_int(){
	
	std::cout << "---------------------TEST INT-------------------------" << std::endl;
	
	graph<int,compare_int> g;
	
	try{
		std::cout << "Aggiunta dei nodi 0,5,7,6..." << std::endl;
		g.add_node(0);
		g.add_node(5);
		g.add_node(7);
		g.add_node(6);
		std::cout << "Aggiunta di un ulteriore nodo 0..." << std::endl; 
		g.add_node(0); // Genera eccezione
	}
	catch(duplicated_node &e){
		std::cout << e.what() << std::endl;
	}
	
	try{
		std::cout << "Aggiunta degli archi <5,7>,<0,0>,<0,6>..." << std::endl;
		g.add_edge(5,7);
		g.add_edge(0,0);
		g.add_edge(0,6);
		std::cout << "Aggiunta di un ulteriore arco <7,5>..." << std::endl;
		g.add_edge(7,5); // Genera eccezione
	}
	catch(duplicated_edge &e){
		std::cout << e.what() << std::endl;
	}
	
	std::cout << "Test di esistenza di 5 e 90..." << std::endl;
	g.exists(5);
	g.exists(90);
	
	try{
		std::cout << "Test dei vicini di 5 e 90..." << std::endl;
		g.neighbors(5);
		g.neighbors(90); // Genera eccezione
	}
	catch(key_not_found &e){
		std::cout << e.what() << std::endl;
	}
	
	
	try{
		std::cout << "Test di esistenza di <0,0>,<5,7>,<7,5>,<6,5>..." << std::endl;	
		g.has_edge(0,0);
		g.has_edge(5,7);
		g.has_edge(7,5);
		g.has_edge(6,5);
		std::cout << "Test di esistenza di <0,90>..." << std::endl;
		g.has_edge(0,90); // Genera eccezione
	}
	catch(key_not_found &e){
		std::cout << e.what() << std::endl;
	}
	
	try{
		std::cout << "Test rimozione di 5..." << std::endl; 
		g.remove_node(5);
		std::cout << "Test esistenza di 5 e di <5,7>..." << std::endl; 
		g.exists(5);
		g.has_edge(5,7); // Genera eccezione
		
	}
	catch(key_not_found &e){
		std::cout << e.what() << std::endl;
	}
	
	try{
		std::cout << "Test rimozione di 90..." << std::endl;
		g.remove_node(90); // Genera eccezione
	}
	catch(key_not_found &e){
		std::cout << e.what() << std::endl;
	}
	
	
	try{
		std::cout << "Test rimozione di <0,6> e di esistenza successiva..." << std::endl;
		g.remove_edge(0,6);
		g.has_edge(0,6); 
		std::cout << "Test rimozione di <90,70>..." << std::endl;
		g.remove_edge(90,70); // Genera eccezione
	}
	catch(key_not_found &e){
		std::cout << e.what() << std::endl;
	}
	
	std::cout << "Test dei metodi per il ritorno di numero di nodi ed archi..." << std::endl;
	std::cout << "Il numero di nodi del grafo e' " << g.get_size_nodes() << "." << std::endl;
	std::cout << "Il numero di archi del grafo e' " << g.get_size_edges() << "." << std::endl;
	
	std::cout <<  "Test dell'operatore di stream, copy constructor e operatore=..." << std::endl;
	std::cout << "g: " << g << " " << std::endl;
	
	graph<int,compare_int> g2 = g;
	std::cout << "copia di g (o=): " << g2 << " " << std::endl;
	
	graph<int,compare_int> g3(g);
	std::cout << "copia di g (cc) : " << g2 << " " << std::endl;
}

/**
METODO DI TEST
Data un grafo templato di stringhe, effettua delle chiamate alle funzioni pubbliche per testarle.
*/
void test_string(){
	
	std::cout << "---------------------TEST STRING-------------------------" << std::endl;
	
	graph<std::string,compare_string> g;
	
	try{
		std::cout << "Aggiunta dei nodi Paperino,Pippo,Topolino,Pluto..." << std::endl;
		g.add_node("Paperino");
		g.add_node("Pippo");
		g.add_node("Topolino");
		g.add_node("Pluto");
		std::cout << "Aggiunta di un ulteriore nodo Paperino..." << std::endl; 
		g.add_node("Paperino"); // Genera eccezione
	}
	catch(duplicated_node &e){
		std::cout << e.what() << std::endl;
	}
	
	try{
		std::cout << "Aggiunta degli archi <Paperino,Pippo>,<Topolino,Topolino>,<Topolino,Pluto>..." << std::endl;
		g.add_edge("Paperino","Pippo");
		g.add_edge("Topolino","Topolino");
		g.add_edge("Topolino","Pluto");
		std::cout << "Aggiunta di un ulteriore arco <Pluto,Topolino>..." << std::endl;
		g.add_edge("Pluto","Topolino"); // Genera eccezione
	}
	catch(duplicated_edge &e){
		std::cout << e.what() << std::endl;
	}
	
	std::cout << "Test di esistenza di Paperino e Minni..." << std::endl;
	g.exists("Paperino");
	g.exists("Minni");
	
	try{
		std::cout << "Test dei vicini di Paperino e Minni..." << std::endl;
		g.neighbors("Paperino");
		g.neighbors("Minni"); // Genera eccezione
	}
	catch(key_not_found &e){
		std::cout << e.what() << std::endl;
	}
	
	
	try{
		std::cout << "Test di esistenza di <Topolino,Topolino>,<Paperino,Pippo>,<Pippo,Paperino>,<Pluto,Paperino>..." << std::endl;	
		g.has_edge("Topolino","Topolino");
		g.has_edge("Paperino","Pippo");
		g.has_edge("Pippo","Paperino");
		g.has_edge("Pluto","Paperino");
		std::cout << "Test di esistenza di <Topolino,Minni>..." << std::endl;
		g.has_edge("Topolino","Minni"); // Genera eccezione
	}
	catch(key_not_found &e){
		std::cout << e.what() << std::endl;
	}
	
	try{
		std::cout << "Test rimozione di Paperino..." << std::endl; 
		g.remove_node("Paperino");
		std::cout << "Test esistenza di Paperino e di <Paperino,Pluto>..." << std::endl; 
		g.exists("Paperino");
		g.has_edge("Paperino","Pluto"); // Genera eccezione
		
	}
	catch(key_not_found &e){
		std::cout << e.what() << std::endl;
	}
	
	try{
		std::cout << "Test rimozione di Minni..." << std::endl;
		g.remove_node("Minni"); // Genera eccezione
	}
	catch(key_not_found &e){
		std::cout << e.what() << std::endl;
	}
	
	
	try{
		std::cout << "Test rimozione di <Topolino,Pluto> e di esistenza successiva..." << std::endl;
		g.remove_edge("Topolino","Pluto");
		g.has_edge("Topolino","Pluto"); 
		std::cout << "Test rimozione di <Minni,Paperina>..." << std::endl;
		g.remove_edge("Minni","Paperina"); // Genera eccezione
	}
	catch(key_not_found &e){
		std::cout << e.what() << std::endl;
	}
	
	std::cout << "Test dei metodi per il ritorno di numero di nodi ed archi..." << std::endl;
	std::cout << "Il numero di nodi del grafo e' " << g.get_size_nodes() << "." << std::endl;
	std::cout << "Il numero di archi del grafo e' " << g.get_size_edges() << "." << std::endl;
	
	std::cout <<  "Test dell'operatore di stream, copy constructor e operatore=..." << std::endl;
	std::cout << "g:{ " << g << " }" << std::endl;
	graph<std::string,compare_string> g2 = g;
	std::cout << "copia di g (o=):{ " << g2 << " }" << std::endl;
	graph<std::string,compare_string> g3(g);
	std::cout << "copia di g (cc) :{ " << g2 << " }" << std::endl;
}

/**
ENTRY POINT
Crea un grafo templato e chiama le funzioni per testarlo
@param argc numero parametri passati da linea di comando
@param argv parametri passati da linea di comando
*/
int main(int argc, char* argv[]){

	/* Test sugli interi */
	test_int();
	std::cout << std::endl;	
	
	/* Test sulle stringhe
	test_string();
	std::cout << std::endl;	
	*/

	std::cout << "Esecuzione terminata!" << std::endl;
	return 0;
}
