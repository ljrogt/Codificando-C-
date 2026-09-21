#pragma once
#include <iostream>
#include "../Grafo/grafo.h"
#include <string>
#include <vector>



class Tabuleiro{
private:
    struct posEdistancia{
	    std::string pos;
	    float distancia;
    };
    struct coordenada{
	    int linha;
	    int coluna;
    };
    grafo Casas;
    std::vector<std::vector<posEdistancia>> melhores;
    std::vector<int> cavalos;
    int rei;
    float calcularAtaque(int c);

    void gravarPossivelJogada(int lin, int col, int cav);

    std::string traduzirPosicao(int ver);

    coordenada traduzirPosicao(std::string pos);
    
    void adicionarCavalo(std::string pos);

    void definirRei(std::string r);

public:
    Tabuleiro();

   std::vector<posEdistancia> informarMelhorCavalo();
    
    void configurarTabuleiro();

    void calcularMelhor();
    
    void mostrarMelhoresCompleto();

    void mostrarMelhoresParcial();
};

