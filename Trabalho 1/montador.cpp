#include<iostream>
#include<string>
#include <fstream>
#include <ctype.h>
#include <list>
#include <vector>
#include <algorithm>
#include <sstream>

// Classe nós que armazena os simbolos que serão inseridos na tabela de simbolos
class Node{
    std::string simbolo;
    int endereco;
    std::list <int> pendencia;
    std::string tipo; // Variavel ou label
    bool declarada;
    int valor;
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

    // Insere um novo elemento na tabela que não foi achado ainda
    void inserir(std::string id){
        Node* novo = new Node;
        novo->simbolo = id;
        novo->declarada = false;
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

    void inserir_constante(std::string id, int endereco, int valor){
        int pos = achar_id(id);
        nodes[pos]->endereco = endereco;
        nodes[pos]->tipo = "constante";
        nodes[pos]->valor = valor;
        nodes[pos]->declarada = true;
    }


    void inserir_label(std::string id, int endereco){
        int pos = achar_id(id);
        nodes[pos]->endereco = endereco;
        nodes[pos]->tipo = "label";
        nodes[pos]->declarada = true;
        nodes[pos]->valor = 0;
    }

    void inserir_variavel(std::string id, int endereco){
        int pos = achar_id(id);
        nodes[pos]->endereco = endereco;
        nodes[pos]->tipo = "variavel";
        nodes[pos]->declarada = true;
        nodes[pos]->valor = 0;
    }
    
    void adicionar_lista(std::string id, int pendencia){
        int pos = achar_id(id);
        nodes[pos]-> pendencia.push_back(pendencia);
    }

    // VERIFICA SE EXISTE ALGUMA VARIAVEL NÃO DECLARADA NA TABELA DE PENDENCIAS
    void verificaSimbDeclarados(){
        std::vector<Node*>::size_type tam = nodes.size();
        for(unsigned i=0; i<tam; i++){
            if(!nodes[i]->declarada){
                printf("Variavel %s não foi declarada",nodes[i]->simbolo.c_str());
            }
        }
        
    }

    void removeLista(){
        std::vector<Node*>::size_type tam = nodes.size();
        for(unsigned i=0;i<tam;i++){
            while(!nodes[i]->pendencia.empty()){
                nodes[i]->pendencia.pop_back();
            }
        }
    }

    ~TabelaDeSimbolos(){
        removeLista();
        if (!nodes.empty()){
            nodes.pop_back();
        }
    }
};

void Printa(std::vector<std::string> v){
    int t = v.size();
    if(t<1){
        printf("Vazio\n");
    }else{
        for(int i=0;i<t;++i)
		std::cout<<v[i]<<std::endl;
    }
    
}

void SeparaString(std::vector<std::string> &v, std::string s){
    bool anterior = false;
    std::string word;
    for (auto x: s){
        if((x == ' ')){
            if(anterior==false){
                anterior = true;
                v.push_back(word);
                word = "";
            }
        }else{
            if(anterior==true){
                anterior = false;
            }
            word = word + x;
        }
    }
    if(word!=""){
        v.push_back(word);
    }
}

void EsvaziaVetor(std::vector<std::string> &v){
    while(!v.empty()){
        v.pop_back();
    }
}

void CriaVetorObjeto(std::vector<std::string> &v, int i){
    std::string ins;
    if (i<10){
        ins = "0";
        ins += std::to_string(i);
    }else{
        ins = "";
        ins += std::to_string(i);
    }
    v.push_back(ins);
}

// Recebe argc e argc (padrão para receber entrada pela linha de comando)
// argc: Contador de entradas
// argv: Vetor de entradas
int main(int argc, char* argv[]) {
    // Lista que irá armazenar o valor de cada linha de endereço do programa na posição correspondente do vetor
    // ex: 00 Add N1 -> v[0] = 01 (codigo add) v[1] = endereço N1
    std::vector <std::string> obj;
    std::string linha;    
    // vetor com todas as instruções validas. OPCODE = posição no vetor + 1|| pos(STOP) == 13 || pos(COPY) == 8
    std::vector<std::string> instrucoes = {"ADD","SUB","MUL","DIV","JMP","JMPN",
                                               "JNPP","JMPZ","COPY","LOAD","STORE",
                                               "INPUT","OUTPUT","STOP"};
                        
    std::vector<std::string> diretivas = {"SECTION DATA","SECTION TEXT","CONST","SPACE"};
    int atual = 0, endereco = 0; //linha do codigo, endereço da linha do codigo obj atual;
    int tam, i; // tamanho do vetor

    std::string caracteres = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890_";

    if(argc<2){
        // Caso não passe nenhum nome de arquivo
        printf("fatal error: no input files\nmontador terminated.");
    }else{
        TabelaDeSimbolos TS; //Cria Tabela de simbolos
        std::ifstream Arquivo(argv[1]);
        std::vector<std::string> vetorLinha;
        bool erro = false; // Desabilita a criação de arquivos objeto caso tenha erros
        int secao = -1; // Recebe -1 caso seção não seja lida, 1 se for dados, e 0 se for text
        bool comentario;

        // Leitura do arquivo
        while (getline (Arquivo, linha)) {
            for (auto & c: linha) c = toupper(c);
            SeparaString(vetorLinha, linha);
            atual++;
            tam = vetorLinha.size();
            for(i=0;i<tam;i++){
                if(!comentario){
                    if(vetorLinha[i]==";" || vetorLinha[i].front() == ';'){
                        comentario = true;
                        
                    }else{
                        
                    }
                }
            }
            printf("\n");
            EsvaziaVetor(vetorLinha);
            comentario = false;
        }
        // Cria o nome do novo arquivo que será criado com o código objeto do programa
        std::string nome = argv[1];
        std::string toReplace(".asm");
        size_t pos = nome.find(toReplace);
        nome.replace(pos, toReplace.length(), ".obj");
        // FIM DA CRIAÇÃO DO NOME DO ARQUIVO OBJETO

        Arquivo.close();
        TS.~TabelaDeSimbolos(); // Desaloca vetor da tabela de simbolos
    }
    
    return 0;
}