#pragma once

#include<iostream>
#include<vector>

class grafo{
private:
    int numVertices;
    int numArestas;
    std::vector<std::vector<int>> adjacentes;
public:
    grafo();
    grafo(int n);

    void reajustarVertices(int n);

    void adicionarAresta(int v, int u);

    void removerAresta(int v, int u);

   std::vector<int> informarAdjacentes(int v);
    int informarVertice();
};
