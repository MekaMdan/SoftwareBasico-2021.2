#include<iostream>
#include<string>
#include <fstream>
#include <ctype.h>
#include <list>
#include <vector>


const int MAX = 1000;

// Classe nós que armazena os simbolos que serão inseridos na tabela de simbolos
class Node{
    std::string simbolo;
    int endereco;
    std::list <int> pendencia;
    std::string tipo; // Variavel ou label
    // Node* next;
public:
    Node(){
        // next = NULL;
    }

    Node(std::string simbolo){
        this->simbolo = simbolo;
        // next=NULL;
    }

    Node(std::string simbolo, int endereco){
        this->simbolo = simbolo;
        this->endereco = endereco;
        // next=NULL;
    }

    void print(){
        printf("%s está no endereço %d\n", simbolo.c_str() ,endereco);
    }
    friend class TabelaDeSimbolos;
};


// Classe da Tabela de Simbolos
class TabelaDeSimbolos{
    std::vector <Node*> nodes;
public:
    TabelaDeSimbolos(){

    }

    // Insere um novo elemento na tabela
    void inserir(std::string id){
        Node* novo = new Node;
        novo->simbolo = id;
        nodes.push_back(novo);
    }

    // Verifica se o simbolo ja está na tabela de simbolos
    bool verifica_id(std::string id){
        std::vector<Node*>::size_type tam = nodes.size();
        for(unsigned i=0; i<tam; i++){
            if(nodes[i]->simbolo == id){
                return true;
            }
        }
        return false;
    }

    int achar_id(std::string id){
        std::vector<Node*>::size_type tam = nodes.size();
        for(unsigned i=0; i<tam; i++){
            if(nodes[i]->simbolo == id){
                return i;
            }
        }
        return -1;
    }

    void modificar(){

    }
    
    void adicionar_lista(std::string id, int pendencia){
        int pos = achar_id(id);
        
    }

    ~TabelaDeSimbolos(){
        if (!nodes.empty()){
            nodes.pop_back();
        }
    }
};


// Recebe o nome de um arquivo, abre o arquivo e le.


// Recebe argc e argc (padrão para receber entrada pela linha de comando)
// argc: Contador de entradas
// argv: Vetor de entradas
int main(int argc, char* argv[]) {
    
    std::string linha;    
    //int atual = 0, end = 0;

    if(argc<2){
        printf("fatal error: no input files\nmontador terminated.");
    }else{
        TabelaDeSimbolos TS;
        TS.inserir("a");
        std::cout << TS.verifica_id("a");
        std::cout << '\n';
        std::cout << TS.verifica_id("afa");
        std::cout << '\n';
        std::cout << TS.achar_id("afa");
        std::cout << '\n';
        std::cout << TS.achar_id("a");
        TS.inserir("afa");
        TS.inserir("b");
        TS.inserir("f");
        std::cout << '\n';
        std::cout << TS.achar_id("afa");
        std::cout << '\n';
        std::cout << TS.achar_id("f");
        TS.~TabelaDeSimbolos();
        //printf("%s\n",argv[1]);
        //std::ifstream Arquivo(argv[1]);
        //while (getline (Arquivo, linha)) {
        //    toupper(linha);
        //    printf("%s\n",linha.c_str());
        //}
        //Arquivo.close();
        
        // Le o arquivo com o nome no argv[2] e
    }
    
    return 0;
}