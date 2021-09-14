#include<iostream>
#include<string.h>
#include <fstream>
#include <ctype.h>
#include <list>
#include <vector>
#include <algorithm>
#include <sstream>
#include <unordered_map>
#include <stdio.h>

// Classe nós que armazena os simbolos que serão inseridos na tabela de simbolos
class Node{
    std::string simbolo;
    int endereco;
    std::list <int> pendencia;
    std::string tipo; // Variavel ou label
    bool declarada;
    int pos_declaração;
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

    void modifica_end(std::string id, int endereco){
        int pos = achar_id(id);
        nodes[pos]->endereco = endereco;
    }

    void inserir_constante(std::string id, int endereco, int valor, int posi){
        int pos = achar_id(id);
        nodes[pos]->endereco = endereco;
        nodes[pos]->tipo = "constante";
        nodes[pos]->valor = valor;
        nodes[pos]->pos_declaração = posi;
        nodes[pos]->declarada = true;
    }


    void inserir_label(std::string id, int endereco){
        int pos = achar_id(id);
        nodes[pos]->endereco = endereco;
        nodes[pos]->tipo = "label";
        nodes[pos]->declarada = true;
        nodes[pos]->valor = 0;
    }

    void inserir_variavel(std::string id, int endereco, int posi){
        int pos = achar_id(id);
        nodes[pos]->endereco = endereco;
        nodes[pos]->tipo = "variavel";
        nodes[pos]->declarada = true;
        nodes[pos]->pos_declaração = posi;
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
    if(t>=1){
        for(int i=0;i<t;++i){
		    printf("%s ", v[i].c_str());
        }
        printf("\n");    
    }
    
}

void PrintaOBJ(std::vector<int> v){
    int t = v.size();
    if(t>=1){
        for(int i=0;i<t;++i){
		    printf("%d ", v[i]);
        }
        printf("\n");    
    }
    
}

void PrintaErro(std::vector<std::string> v){
    int t = v.size();
    if(t>=1){
        for(int i=0;i<t;++i)
            printf("%s \n", v[i].c_str());
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

bool VerificaDiretiva(std::vector<std::string> v, std::string s){
    int tam,i;
    tam = v.size();
    for(i=0;i<tam;i++){
        if(v[i]==s){
            return true;
        }
    }
    return false;
}

bool ContemErr(std::vector<std::string> v, std::string s){
    int t = v.size();
    if(t>0){
        for(int i=0;i<t;i++){
            if(v[i]==s){
                return true;
            }
        }
    }
    return false;
}

bool HasSpecialCharacters(const char *str)
{
    return str[strspn(str, "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_")] != 0;
}

// Se a var/label possui apenas tokens aceitos, retorna true
bool VerificaTokens(std::string s){
    if((!isdigit(s.front()))&&(!HasSpecialCharacters(s.c_str()))){
        return true;
    }
    return false;
}

// Recebe argc e argc (padrão para receber entrada pela linha de comando)
// argc: Contador de entradas
// argv: Vetor de entradas
int main(int argc, char* argv[]) {
    // Lista que irá armazenar o valor de cada linha de endereço do programa na posição correspondente do vetor
    // ex: 00 Add N1 -> v[0] = 01 (codigo add) v[1] = endereço N1
    std::vector <int> obj;
    std::string linha;    
    // MAPA COM INSTRUÇÕES E VETOR QUE CONTEM OP CODE DA INSTRUÇÃO E NUMERO DE ENDEREÇO OCUPADOS
    std::unordered_map <std::string, std::vector<int>> inst = {
        {"ADD",{1,2}},
        {"SUB",{2,2}},
        {"MUL",{3,2}},
        {"DIV",{4,2}}, 
        {"JMP",{5,2}},
        {"JMPN",{6,2}},
        {"JNPP",{7,2}},
        {"JMPZ",{8,2}},
        {"COPY",{9,3}},
        {"LOAD",{10,2}},
        {"STORE",{11,2}},
        {"INPUT",{12,2}},
        {"OUTPUT",{13,2}},
        {"STOP",{14,1}}
    };

    std::vector<std::string> diretivas_sec = {"SECTION DATA","SECTION TEXT"};
    std::vector<std::string> diretivas_var = {"CONST","SPACE"};
    int atual = 1, endereco = 0; //linha do codigo, endereço da linha do codigo obj atual;
    int tam, i; // tamanho do vetor, variavel de iteração


    if(argc<2){
        // Caso não passe nenhum nome de arquivo
        printf("fatal error: no input files\nmontador terminated.");
    }else{
        TabelaDeSimbolos TS; //Cria Tabela de simbolos
        
        std::ifstream Arquivo(argv[1]); 

        std::vector<std::string> vetorLinha; //Vetor que guarda os strings da linha
        bool erro = false; // Desabilita a criação de arquivos objeto caso tenha erros
        bool comentario; // indica se é comentario ou não
        bool data = false;  //se está na seção de data ou não
        std::string comando = ""; // guarda o valor da 
        std::string direc = "";  // guarda valor de diretiva ou rotulo
        int n_var; // Recebe o numero de variaveis pela instrução
        int text = -1;
        int data_end = -1;
        bool stop = false;

        // vetor de erros e string que irá receber erro
        std::vector<std::string> erros_linha;
        std::string err_linhastr;

        // Leitura do arquivo
        while (getline (Arquivo, linha)) {
            for (auto & c: linha) c = toupper(c);
            SeparaString(vetorLinha, linha);
            
            tam = vetorLinha.size();
            
            for(i=0;i<tam;i++){
                // Verifica se o que foi lido é comentario
                if(!comentario){
                    if(vetorLinha[i]==";" || vetorLinha[i].front() == ';'){ 
                        comentario = true;
                        vetorLinha.erase(vetorLinha.begin() + i); // separa os comentarios do código
                    }else{
                        if((vetorLinha[i].back() == ':' || vetorLinha[i]== ":" )&&(comando!="var")){
                            
                            // Se for na forma ROTULO: , remove os : para ter o rotulo
                            if(vetorLinha[i].back() == ':'){
                                vetorLinha[i].pop_back();
                                direc = vetorLinha[i]; // dirac recebe valor de variavel ou de label
                                vetorLinha[i].push_back(':'); 
                            }
                            //printf("entra aqui %s \n ", vetorLinha[i].c_str());    

                            if(data == false){ // ser for label
                                if(comando == "label"){
                                        err_linhastr = "Linha ";
                                        err_linhastr += std::to_string(atual);
                                        err_linhastr += " - Erro Sintatico: dois ou mais rotulos na mesma linha";
                                        if(!ContemErr(erros_linha, err_linhastr))
                                            erros_linha.push_back(err_linhastr);
                                        err_linhastr = "";
                                        if((direc!="")&&(!VerificaTokens(direc))){
                                            err_linhastr = "Linha ";
                                            err_linhastr += std::to_string(atual);
                                            err_linhastr += " - Erro Lexico: Tokens invalidos";
                                            if(!ContemErr(erros_linha, err_linhastr))
                                                erros_linha.push_back(err_linhastr);
                                            err_linhastr = "";
                                        }
                                    }else{
                                        comando = "label";
                                        if(TS.verifica_id(direc)){
                                            err_linhastr = "Linha ";
                                            err_linhastr += std::to_string(atual);
                                            err_linhastr += " - Erro Semantico: declaração de rotulos repetidos";
                                            if(!ContemErr(erros_linha, err_linhastr))
                                                erros_linha.push_back(err_linhastr);
                                            err_linhastr = "";
                                        }else{
                                            if(VerificaTokens(direc)){
                                                TS.inserir(direc);
                                            }else{
                                                err_linhastr = "Linha ";
                                                err_linhastr += std::to_string(atual);
                                                err_linhastr += " - Erro Lexico: Tokens invalidos";
                                                if(!ContemErr(erros_linha, err_linhastr))
                                                    erros_linha.push_back(err_linhastr);
                                                err_linhastr = "";
                                            }
                                        }
                                    }
                            }else{  // se for declaração de var ou const
                                
                                    
                                    
                                    
                                    
                            }
                        }else{
                                if((inst.find(vetorLinha[i]) != inst.end())&&(comando!="invalido")){
                                    comando = "var";
                                    n_var += inst[vetorLinha[i]][1]; // numero total de variaveis
                                    endereco++;
                                    obj.push_back(inst[vetorLinha[i]][0]); // Carrega no fim do vetor de codigo objeto o codigo da instrução
                                    if(vetorLinha[i]=="STOP"){
                                        stop = true;
                                    }
                                    if(text==-1){
                                        text=-2;
                                    }
                                }else{
                                    if(comando=="var"){
                                        if(n_var>0){
                                            //printf("DIRETIVA: %s\n",direc.c_str());


                                        }
                                    }else{
                                        if(((data==false)&&(text==-1))||((stop==true)&&(data_end == -1))){
                                            direc+=vetorLinha[i];
                                            direc+=" ";
                                            comando = "direc";
                                        }
                                        else{
                                            if(data==true){
                                                direc+=vetorLinha[i];
                                                comando = "declara";
                                            }else{
                                                direc+=vetorLinha[i];
                                                comando = "naoidentificado";
                                            }
                                            
                                            
                                        }
                                    }

                                }
                                
                                    
                        }
                    }

                }else{ // se for comentario
                    vetorLinha.erase(vetorLinha.begin() + i);
                }
            }

            if(comando=="var"){
                comando = "inst";
            }

            if(comando=="direc"){
                direc.pop_back();
                if(direc=="SECTION DATA"){
                    data = true;
                    data_end = endereco;
                }else{
                    if(direc=="SECTION TEXT"){
                        text = endereco;
                    }else{
                        if(!erro){
                            erro = true;
                        }
                        Printa(vetorLinha);
                        printf("Linha %d - Erro lexico: Diretiva incorreta/ Instrucao Invalida\n",atual);

                    }
                }                  
                
            }

            if(comando == "naoidentificado"){
                Printa(vetorLinha);
                printf("Linha %d - Erro lexico: Instrucao Invalida\n",atual);
                if(!erro){
                    erro = true;
                }
            }

            if(erros_linha.size()>0){
                Printa(vetorLinha);
                PrintaErro(erros_linha);
                EsvaziaVetor(erros_linha);
                if(!erro){
                    erro = true;
                }
            }
            direc = "";
            EsvaziaVetor(vetorLinha);
            comentario = false; // reseta variavel de comentario
            atual++; 
        }
        // Cria o nome do novo arquivo que será criado com o código objeto do programa
        if(!erro){
            std::string nome = argv[1];
            std::string toReplace(".asm");
            size_t pos = nome.find(toReplace);
            nome.replace(pos, toReplace.length(), ".obj");
        }  
        // FIM DA CRIAÇÃO DO NOME DO ARQUIVO OBJETO
        PrintaOBJ(obj);
        Arquivo.close();
        TS.~TabelaDeSimbolos(); // Desaloca vetor da tabela de simbolos
    }
    
    return 0;
}