#include <iostream>
#include "bfs.h"
#include <cmath>
#include <vector>
#include <queue>

BFS::BFS(grafo g, int n){
	for(int i=0;i<g.informarVertice();i++){
		vertice v;
		v.explorado=false;
		v.distancia=INFINITY;
		v.adj=g.informarAdjacentes(i);
		if(n==i){
			v.distancia=0;
		}
		grafoAlvo.push_back(v);
	}
        raiz=n;
}

float BFS::buscarConexao(int v){
	if(raiz==v){
		return 0.0;
	}
        std::queue<vertice> Q;
	grafoAlvo[raiz].explorado=true;
        Q.push(grafoAlvo[raiz]);
        while (!Q.empty()){
            vertice u=Q.front();
            Q.pop();
            std::vector<int> adj=u.adj;
            for (int i=0;i<adj.size();i++){
                if(adj[i]==v){
                    return u.distancia+1;
                }
                else{
                    if(!grafoAlvo[adj[i]].explorado){
                        grafoAlvo[adj[i]].explorado=true;
			vertice v;
			v.adj=grafoAlvo[adj[i]].adj;
			v.distancia=u.distancia+1;
			v.explorado=true;
			Q.push(v);
                    }
                }
            }
        }
        int distancia = INFINITY;
        return distancia;
}


