#pragma once
#include <iostream>
#include "../Grafo/grafo.h"
#include <cmath>
#include <queue>
#include <vector>


class BFS{
private:
    struct vertice{
	std::vector<int> adj;
	float distancia;
	bool explorado;
    };
    std::vector<vertice> grafoAlvo;
    int raiz;
public:
    BFS(grafo g, int n);

    float buscarConexao(int v);

};
