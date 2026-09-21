#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <string>


class grafo{
private:
    int numVertices=0;
    int numArestas=0;
    std::vector<std::vector<int>> adjacentes;
public:
    grafo(){}
    grafo(int n){
        numVertices=n;
        adjacentes.resize(numVertices);
    }

    void reajustarVertices(int n){
	    numVertices=n;
	    adjacentes.resize(n);
    }

    void adicionarAresta(int v, int u){
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

    void removerAresta(int v, int u){
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

   std::vector<int> informarAdjacentes(int v){
        return adjacentes[v];
    }

};

class BFS{
private:
    struct vertice{
	std::vector<int> adj;
	float distancia=INFINITY;
	bool explorado=false;
    };
    std::vector<vertice> grafoAlvo;
    int raiz;
public:
    BFS(grafo g, int n){
	for(int i=0;i<64;i++){
		vertice v;
		v.adj=g.informarAdjacentes(i);
		if(n==i){
			v.distancia=0;
		}
		grafoAlvo.push_back(v);
	}
        raiz=n;
    }

    float buscarConexao(int v){
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

};


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
    float calcularAtaque(int c){
        BFS busca(Casas, cavalos[c]);
        return busca.buscarConexao(rei);
    }
    void gravarPossivelJogada(int lin, int col, int cav){
	    int linAtual=cav/8;
	    int coAtual=cav%8;
	    if(linAtual+lin<=7&&linAtual+lin>=0&&coAtual+col<=7&&coAtual+col>=0){
		    Casas.adicionarAresta(cav, (linAtual+lin)*8+(coAtual+col));
	    }
    } 

    std::string traduzirPosicao(int ver){
	    std::string colunasPossiveis="abcdefgh";
	    char coluna=colunasPossiveis[ver%8];
	    char linha=(ver/8+1)+'0';
	    std::string pos;
	    pos.push_back(coluna);
	    pos.push_back(linha);
	    return pos;
    }	    

    coordenada traduzirPosicao(std::string pos){
	    coordenada coord;
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
    
    void adicionarCavalo(std::string pos){
	    coordenada coord=this->traduzirPosicao(pos);
	    cavalos.push_back(coord.linha*8+coord.coluna);
    }  

    void definirRei(std::string r){
	    coordenada c=this->traduzirPosicao(r);
	    rei=c.linha*8+c.coluna;
    }

public:
    Tabuleiro(){
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

   std::vector<posEdistancia> informarMelhorCavalo(){
	std::vector<posEdistancia> melhorCavalo;
        for(int i=0;i<cavalos.size();i++){
	    float b=this->calcularAtaque(i);
	    posEdistancia cav={this->traduzirPosicao(cavalos[i]),b};
            if(i==0){
		melhorCavalo.clear();
                melhorCavalo.push_back(cav);
            }
            else{
		coordenada co=this->traduzirPosicao(melhorCavalo[0].pos);
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
    
    void configurarTabuleiro(){
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

    void calcularMelhor(){
	    std::vector<posEdistancia> melhor=this->informarMelhorCavalo();
	    melhores.push_back(melhor);
    }
    
    void mostrarMelhoresCompleto(){
	    for(auto m : melhores){
		    for(auto n : m){
			    std::cout<<n.pos<<": "<<n.distancia-1<<" ";
		    }
		    std::cout<<"\n";
	    }
    }

    void mostrarMelhoresParcial(){
	    for(auto m : melhores){
		    for(auto n : m){
			    std::cout<<n.distancia-1<<" ";
		    }
		    std::cout<<"\n";
	    }
    }

};

int main(){
    Tabuleiro tab; 
    int n;
    std::cin>>n;
    for(int i=0;i<n;i++){
	    tab.configurarTabuleiro();
	    tab.calcularMelhor();
    }
//    tab.mostrarMelhoresCompleto(); //Essa saída é para alguém que queira saber de qual cavalo é o número que aparece, no caso saber qual cavalo tem que se mexer
    tab.mostrarMelhoresParcial();
}

