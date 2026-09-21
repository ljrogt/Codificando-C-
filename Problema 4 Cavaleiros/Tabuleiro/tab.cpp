#include <iostream>
#include "../Grafo/grafo.h"
#include <string>
#include <vector>
#include "tab.h"
#include "../BFS/bfs.h"


Tabuleiro::Tabuleiro(){
	Casas.reajustarVertices(64);
        for(int i=0;i<64;i++){
	    this->gravarPossivelJogada(2,1,i);
            this->gravarPossivelJogada(2,-1,i);
            this->gravarPossivelJogada(-1,2,i);
	    this->gravarPossivelJogada(1,2,i);
            this->gravarPossivelJogada(-2,1,i);
            this->gravarPossivelJogada(-2,-1,i);
            this->gravarPossivelJogada(1,-2,i);
            this->gravarPossivelJogada(-1,-2,i);
        }
} 

float Tabuleiro::calcularAtaque(int c){
     BFS busca(Casas, cavalos[c]);
     return busca.buscarConexao(rei);
}
void Tabuleiro::gravarPossivelJogada(int lin, int col, int cav){
    int linAtual=cav/8;
    int coAtual=cav%8;
    if(linAtual+lin<=7&&linAtual+lin>=0&&coAtual+col<=7&&coAtual+col>=0){
	    Casas.adicionarAresta(cav, (linAtual+lin)*8+(coAtual+col));
    }
} 

std::string Tabuleiro::traduzirPosicao(int ver){
    std::string colunasPossiveis="abcdefgh";
    char coluna=colunasPossiveis[ver%8];
    char linha=(ver/8+1)+'0';
    std::string pos;
    pos.push_back(coluna);
    pos.push_back(linha);
    return pos;
}	    

Tabuleiro::coordenada Tabuleiro::traduzirPosicao(std::string pos){
    Tabuleiro::coordenada coord;
    std::string colunasPossiveis="abcdefgh";
    for(int i=0;i<8;i++){
	    if(pos[0]==colunasPossiveis[i]){
		    coord.coluna=i;
	    }
    }
    int l=pos[1]-'0';
    coord.linha=l-1;
    return coord;
}
    
void Tabuleiro::adicionarCavalo(std::string pos){
    Tabuleiro::coordenada coord=this->traduzirPosicao(pos);
    cavalos.push_back(coord.linha*8+coord.coluna);
}  

void Tabuleiro::definirRei(std::string r){
    Tabuleiro::coordenada c=this->traduzirPosicao(r);
    rei=c.linha*8+c.coluna;
}
    

std::vector<Tabuleiro::posEdistancia> Tabuleiro::informarMelhorCavalo(){
	std::vector<Tabuleiro::posEdistancia> melhorCavalo;
        for(int i=0;i<cavalos.size();i++){
	    float b=this->calcularAtaque(i);
	    Tabuleiro::posEdistancia cav={this->traduzirPosicao(cavalos[i]),b};
            if(i==0){
		melhorCavalo.clear();
                melhorCavalo.push_back(cav);
            }
            else{
		Tabuleiro::coordenada co=this->traduzirPosicao(melhorCavalo[0].pos);
		int c=co.linha*8+co.coluna;
		for(int j=0;j<cavalos.size();j++){
			if(c==cavalos[j]){
				c=j;
				break;
			}
		}
		float a=this->calcularAtaque(c);
                if(a>b){
                    melhorCavalo.clear();
		    melhorCavalo.push_back(cav);
                }
		else{
			if(a==b){
				melhorCavalo.push_back(cav);
			}
		}
            }
        }
        return melhorCavalo;
}
    
void Tabuleiro::configurarTabuleiro(){
    cavalos.clear();
    std::string ca;
    int quantidadeDeCavalos=4;
    for(int i=0;i<quantidadeDeCavalos;i++){
	    std::cin>>ca;
	    this->adicionarCavalo(ca);
    }
    std::string r;
    std::cin>>r;
    this->definirRei(r);
}

void Tabuleiro::calcularMelhor(){
    std::vector<posEdistancia> melhor=this->informarMelhorCavalo();
    melhores.push_back(melhor);
}
    
void Tabuleiro::mostrarMelhoresCompleto(){
    for(auto m : melhores){
	    for(auto n : m){
		    std::cout<<n.pos<<": "<<n.distancia-1<<" ";
	    }
	    std::cout<<"\n";
    }
}

void Tabuleiro::mostrarMelhoresParcial(){
    for(auto m : melhores){
	    for(auto n : m){
		    std::cout<<n.distancia-1<<" ";
	    }
	    std::cout<<"\n";
    }
}

