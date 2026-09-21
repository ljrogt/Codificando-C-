#include "grafo.h"
#include <iostream>
#include <vector>

    grafo::grafo(){}
    grafo::grafo(int n){
        numVertices=n;
	numArestas=0;
        adjacentes.resize(numVertices);
    }

    void grafo::reajustarVertices(int n){
	    numVertices=n;
	    adjacentes.resize(n);
    }

    void grafo::adicionarAresta(int v, int u){
        bool controle=true;
        std::vector<int> adj=this->informarAdjacentes(v);
        for(int i=0;i<adj.size();i++){
            if(adj[i]==u){
                controle=false;
            }
        }
        if(v>=numVertices||v<0||v==u||u<0||u>=numVertices){
            controle=false;
        }
        if(controle){
            adjacentes[v].push_back(u);
            adjacentes[u].push_back(v);
            numArestas+=1;
        }
    }

    void grafo::removerAresta(int v, int u){
        std::vector<int> temp;
        for(auto vertice : adjacentes[v]){
            if(vertice != u){
                temp.push_back(vertice);
            }
        }
        adjacentes[v]=temp;
        temp.clear();
        for(auto vertice : adjacentes[u]){
            if(vertice != v){
                temp.push_back(vertice);
            }
        }
        adjacentes[u]=temp;
    }

   std::vector<int> grafo::informarAdjacentes(int v){
        return adjacentes[v];
    }

