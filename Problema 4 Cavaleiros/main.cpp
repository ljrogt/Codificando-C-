#include <iostream>
#include "Grafo/grafo.h"
#include "BFS/bfs.h"
#include "Tabuleiro/tab.h"

int main(){
    Tabuleiro tab; 
    int n;
    std::cin>>n;
    for(int i=0;i<n;i++){
	    tab.configurarTabuleiro();
	    tab.calcularMelhor();
    }
    tab.mostrarMelhoresCompleto(); //Essa saída é para alguém que queira saber de qual cavalo é o número que aparece, no caso saber qual cavalo tem que se mexer
}

