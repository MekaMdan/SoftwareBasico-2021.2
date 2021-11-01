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

#define Absoluto 0
#define Relativo 1
// Classe nós que armazena os simbolos que serao inseridos na tabela de simbolos
class Node{
    std::string simbolo;
    int endereco;
    std::list <int> pendencia;
    std::string tipo; // Variavel ou label
    bool declarada;
    int pos_declaracao;
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
        printf("%s está no endereco %d\n", simbolo.c_str() ,endereco);
    }
    friend class TabelaDeSimbolos;
};

// Classe da Tabela de Simbolos
class TabelaDeSimbolos{
    std::vector <Node*> nodes;
public:
    // Insere um novo elemento na tabela que nao foi achado ainda
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

    bool verifica_id_decl(std::string id){
        std::vector<Node*>::size_type tam = nodes.size();
        for(unsigned i=0; i<tam; i++){
            if(nodes[i]->simbolo == id){
                if(nodes[i]->declarada){
                    return true;
                }
                return false;
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

    void inserir_constante(std::string id, int endereco, int valor, int posi){
        int pos = achar_id(id);
        nodes[pos]->endereco = endereco;
        nodes[pos]->tipo = "constante";
        nodes[pos]->valor = valor;
        nodes[pos]->pos_declaracao = posi;
        nodes[pos]->declarada = true;
    }

    void altera_end(int text){
        int tam = nodes.size();
        int i,p;
        for (i=0;i<tam;i++){
            if(nodes[i]->endereco==-1){
                p = nodes[i]->pos_declaracao;
                nodes[i]->endereco = text+p;
            }
        }
    }

    int retorna_valor(std::string id){
        int i = achar_id(id);
        return nodes[i]->valor;
    }

    int retorna_endereco(std::string id){
        int i = achar_id(id);
        return nodes[i]->endereco;
    }

    void inserir_label(std::string id, int endereco){
        int pos = achar_id(id);
        nodes[pos]->endereco = endereco;
        nodes[pos]->tipo = "label";
        nodes[pos]->declarada = true;
        nodes[pos]->valor = 0;
        nodes[pos]->pos_declaracao = -1;
    }

    void inserir_variavel(std::string id, int endereco, int posi){
        int pos = achar_id(id);
        nodes[pos]->endereco = endereco;
        nodes[pos]->tipo = "variavel";
        nodes[pos]->declarada = true;
        nodes[pos]->pos_declaracao = posi;
        nodes[pos]->valor = 0;
    }
    
    void adicionar_lista(std::string id, int pendencia){
        int pos = achar_id(id);
        nodes[pos]-> pendencia.push_back(pendencia);
    }

    // VERIFICA SE EXISTE ALGUMA VARIAVEL NaO DECLARADA NA TABELA DE PENDENCIAS
    bool verificaSimbDeclarados(){
        std::vector<Node*>::size_type tam = nodes.size();
        for(unsigned i=0; i<tam; i++){
            if(!nodes[i]->declarada){
                return false;
            }

        }
        return true;
        
    }
    
    //Retorna tamanho da tabela de simbolos
    int retornTam(){
        return nodes.size();
    }

    int retornEndById(int i){
        return nodes[i]->endereco;
    }

    int retornVarById(int i){
        return nodes[i]->valor;
    }

    int retornaPendencia(int i){
        int valor;
        if(!nodes[i]->pendencia.empty()){
            valor = nodes[i]->pendencia.back();
            nodes[i]->pendencia.pop_back();
            return valor;
        }
        return -1;
    }

    int RetornaIdPorPos(int p){
        int tam = nodes.size();
        for(int i=0; i<tam; i++){
            if(nodes[i]->pos_declaracao == p){
                return i;
            }
        }
        return -1;
    }

    void removeLista(){
        std::vector<Node*>::size_type tam = nodes.size();
        for(unsigned i=0;i<tam;i++){
            nodes[i]->pendencia.clear();
        }
    }

    void Mostra(){
        std::vector<Node*>::size_type tam = nodes.size();
        for(unsigned i=0; i<tam; i++){
            printf("id:%s tipo:%s declarada?%d pos:%d valor: %d end: %d\n",nodes[i]->simbolo.c_str(), nodes[i]->tipo.c_str(), nodes[i]->declarada, nodes[i]->pos_declaracao, nodes[i]->valor, nodes[i]->endereco);
            MostraPendencia(i);
        }
    }

    void MostraPendencia(int i){
        int tam = nodes[i]->pendencia.size();
        std::list <int>::iterator it = nodes[i]->pendencia.begin();
        int j;
        for(j=0;j<tam;j++){
            printf("%d-> %d ",j+1, *it);
            std::advance(it,1);
        }
        if(tam>0){
           printf("\n"); 
        }
        
    }

    bool RetornaDecl(int i){
        return(nodes[i]->declarada);
    }

    std::string RetornaSimbo(int i){
        return (nodes[i]->simbolo);
    }

    ~TabelaDeSimbolos(){
        removeLista();
        nodes.clear();
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

void CasefyLetters(std::string &s){
    for (auto & c: s) c = toupper(c);
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

void SeparaVar(std::vector<std::string>&v, std::string s){
    std::string word;
    for(auto x:s){
        if(x==','){
            v.push_back(word);
            word = "";
        }else{
            word = word + x;
        }
    }
    if(word!=""){
        v.push_back(word);
    }
}

void SeparaLabel(std::vector<std::string>&v, std::string s){
    std::string word;
    for(auto x:s){
        if(x==':'){
            v.push_back(word);
            word = "";
        }else{
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

void InsereDecl(std::vector <int> &v,std::vector <int> &bitmap, int p, TabelaDeSimbolos R, int &end){
    int valor,i;
    for(i=0;i<p;i++){
        valor = R.retornVarById(R.RetornaIdPorPos(i));
        v.push_back(valor);
        end++;
        bitmap.push_back(Absoluto);
    }
    end--;
}

void ResolvePendencias(std::vector <int> &v,TabelaDeSimbolos R){
    int tam = R.retornTam();
    int i, pend,end;
    for(i=0;i<tam;i++){
        pend = R.retornaPendencia(i);
        end = R.retornEndById(i);
        while(pend!=-1){
            v[pend]=end;
            pend = R.retornaPendencia(i);
        }
    }
}

void VerificaTS(TabelaDeSimbolos T){
    int tam = T.retornTam();
    int i;
    int qnt = 0;
    printf("Erro Semantico: Rotulo(s) ");    
    for (i=0;i<tam;i++){
        if(!T.RetornaDecl(i)){
            printf("%s ", T.RetornaSimbo(i).c_str());
            qnt++;
        }
        
    }
    if(qnt==1){
        printf("nao foi declarado\n");
    }else{
        printf("nao foram declarados\n");
    }
    
}
// Se a var/label possui apenas tokens aceitos, retorna true
bool VerificaTokens(std::string s){
    if((!isdigit(s.front()))&&(!HasSpecialCharacters(s.c_str()))){
        return true;
    }
    return false;
}

bool ChecaComma(std::string s){
    char valor = ',';
    if(strchr(s.c_str(),valor)!=NULL){
        return true;
    }
    return false;
}

bool ChecaMais(std::string s){
    char valor = '+';
    if(strchr(s.c_str(),valor)!=NULL){
        return true;
    }
    return false;
}

bool ChecaDoisPontos(std::string s){
    char valor = ':';
    if(strchr(s.c_str(),valor)!=NULL){
        return true;
    }
    return false;
}  

// Recebe argc e argc (padrao para receber entrada pela linha de comando)
// argc: Contador de entradas
// argv: Vetor de entradas
int main(int argc, char* argv[]) {
    // Lista que irá armazenar o valor de cada linha de endereco do programa na posicao correspondente do vetor
    // ex: 00 Add N1 -> v[0] = 01 (codigo add) v[1] = endereco N1
    std::vector <int> obj;
    std::string linha;    
    // MAPA COM INSTRUcÕES E VETOR QUE CONTEM OP CODE DA INSTRUcaO E NUMERO DE ENDEREcO OCUPADOS
    std::unordered_map <std::string, std::vector<int>> inst = {
        {"ADD",{1,2}},
        {"SUB",{2,2}},
        {"MUL",{3,2}},
        {"DIV",{4,2}}, 
        {"JMP",{5,2}},
        {"JMPN",{6,2}},
        {"JMPP",{7,2}},
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
    int atual = 1, endereco = 0; //linha do codigo, endereco da linha do codigo obj atual;
    int tam, i; // tamanho do vetor, variavel de iteracao


    if(argc<4){
        // Caso nao passe nenhum nome de arquivo
        printf("fatal error: no input files\nmontador terminated.");
    }else{
        if(!strcmp(argv[1],"-r")){
            int temp = atoi(argv[2]);
               if((temp==0)||(temp==1)){
                bool Info = temp;
                // printf("%d\n", Info);  

                TabelaDeSimbolos TS; //Cria Tabela de simbolos
                std::ifstream Arquivo(argv[3]); 
                std::vector<std::string> vetorLinha; //Vetor que guarda os strings da linha
                bool erro = false; // Desabilita a criacao de arquivos objeto caso tenha erros
                bool comentario; // indica se é comentario ou nao
                bool data = false;  //se está na secao de data ou nao
                bool frente = false;
                bool meio = false;
                std::string comando = ""; // guarda o valor da 
                std::string direc = "";  // guarda valor de diretiva ou rotulo
                std::string tipo = "";  // guarda valor de diretiva ou rotulo
                std::string var = "";  // guarda valor de diretiva ou rotulo
                std::string aux;
                int n_var = 0; // Recebe o numero de variaveis pela instrucao
                int text = -1;
                int data_end = -1;
                bool stop = false;
                int pos = 0;
                std::vector <std::string> hel;
                // variaveis do trabalho 2
                std::vector <int> addresslist;
                std::vector <int> bitmap;
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
                            if((vetorLinha[i].back() == ':' || vetorLinha[i]== ":" || vetorLinha[i].front()==':'||  ChecaDoisPontos(vetorLinha[i]) )&&(comando!="var")){
                                    
                                    // Se for na forma ROTULO: , remove os : para ter o rotulo
                                    if((vetorLinha[i]!=":")&&(vetorLinha[i].back() == ':')){
                                        direc = vetorLinha[i]; // dirac recebe valor de variavel ou de label
                                        direc.pop_back();
                                    }
                                    
                                    if((vetorLinha[i]!=":")&&(vetorLinha[i].front()!=':')&&(vetorLinha[i].back()!=':')&&(ChecaDoisPontos(vetorLinha[i]))){
                                        SeparaLabel(hel,vetorLinha[i]);
                                        direc = hel[0];
                                        meio = true;

                                    }
                                    
                                    if((vetorLinha[i]!=":")&&(vetorLinha[i].front()==':')){
                                        frente = true;
                                    }

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
                                                if(TS.verifica_id_decl(direc)){
                                                    err_linhastr = "Linha ";
                                                    err_linhastr += std::to_string(atual);
                                                    err_linhastr += " - Erro Semantico: declaracao de rotulos repetidos";
                                                    if(!ContemErr(erros_linha, err_linhastr))
                                                        erros_linha.push_back(err_linhastr);
                                                    err_linhastr = "";
                                                }else{
                                                    if(VerificaTokens(direc)){
                                                        if(!TS.verifica_id(direc)){
                                                            TS.inserir(direc);
                                                        }
                                                        TS.inserir_label(direc, text);
                                                        endereco++;

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
                                            direc = "";
                                            if(meio||frente){
                                                if(meio)
                                                    direc = hel[1];
                                                if(frente){
                                                    direc = vetorLinha[i];
                                                    direc.erase(0,1);
                                                }
                                                
                                                if((inst.find(direc) != inst.end())){
                                                    comando = "var";
                                                    endereco = text+1;

                                                    n_var = inst[direc][1];
                                                    text+=n_var;
                                                    n_var--;

                                                    obj.push_back(inst[direc][0]);
                                                    bitmap.push_back(Relativo);
                                                    if(direc=="STOP"){
                                                        stop = true;
                                                    }
                                                    if(text==-1){
                                                        text=-2;
                                                    }
                                                }else{
                                                    direc += hel[1];
                                                    comando = "naoidentificado";
                                                }
                                            }
                                    }else{  // se for declaracao de var ou const
                                        comando = "decl";
                                        if(frente||meio){
                                            if(frente){
                                                var = direc;
                                                
                                                tipo = vetorLinha[i];
                                                tipo.erase(0,1);
                                            }

                                            if(meio){
                                                var = hel[0];
                                                tipo = hel[1];
                                            }

                                            if(VerificaDiretiva(diretivas_var,tipo)){
                                                if(tipo=="SPACE"){
                                                    if(TS.verifica_id_decl(var)){
                                                        err_linhastr = "Linha ";
                                                        err_linhastr += std::to_string(atual);
                                                        err_linhastr += " - Erro Semantico: declaracao de rotulos repetidos";
                                                        if(!ContemErr(erros_linha, err_linhastr))
                                                            erros_linha.push_back(err_linhastr);
                                                        err_linhastr = "";
                                                    }else{
                                                            if(var.back()==' ')
                                                                var.pop_back();
                                                            if(VerificaTokens(var)){
                                                                if(!TS.verifica_id(var)){
                                                                    TS.inserir(var);
                                                                }
                                                                            
                                                                if(text<0){
                                                                    TS.inserir_variavel(var,-1,pos); 
                                                                }else{
                                                                    TS.inserir_variavel(var,text+pos,pos); 
                                                                }
                                                                pos++;
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
                                            }else{
                                                err_linhastr = "Linha ";
                                                err_linhastr += std::to_string(atual);
                                                err_linhastr += " - Erro Lexico: diretiva invalida";
                                                if(!ContemErr(erros_linha, err_linhastr))
                                                    erros_linha.push_back(err_linhastr);
                                                err_linhastr = "";           
                                            }

                                        }else{
                                            var = direc;
                                        }
                                        

                                    }

                                    if(meio){
                                        meio = false;
                                        EsvaziaVetor(hel);
                                        direc = "";
                                    }

                                    if(frente){
                                        frente = false;
                                        direc = "";
                                    }


                                }else{
                                        if((inst.find(vetorLinha[i]) != inst.end())&&(comando!="naoidentificado")){
                                            comando = "var";
                                            endereco = text+1;
                                            
                                            n_var = inst[vetorLinha[i]][1]; // numero total de variaveis
                                            text +=n_var;
                                            n_var--;
                                            
                                            obj.push_back(inst[vetorLinha[i]][0]); // Carrega no fim do vetor de codigo objeto o codigo da instrucao
                                            bitmap.push_back(Absoluto);
                                            if(vetorLinha[i]=="STOP"){
                                                stop = true;
                                            }
                                            if(text==-1){
                                                text=-2;
                                            }
                                        }else{
                                                if(comando=="var"){
                                                    if(((vetorLinha[i].back()==',')||(vetorLinha[i].front()==','))){
                                                        if(vetorLinha[i]==","){ // se vetorLinha[i] for apenas ,
                                                            // direc já é a variavel
                                                            
                                                            if(!TS.verifica_id(direc)){
                                                                TS.inserir(direc);
                                                            }
                                                            TS.adicionar_lista(direc, endereco);
                                                            obj.push_back(-1);
                                                            bitmap.push_back(Relativo);
                                                            addresslist.push_back(endereco);
                                                            endereco++;
                                                            n_var--;
                                                            direc = "";
                                                            // insere direc na tb e/ou insere na lista de pendencia
                                                        }else{  //senao é na forma [rotulo,]
                                                            // insere vetorLinha[i] no direc, remove o ultimo elemento do direc(seria a virgula)
                                                            

                                                            if((vetorLinha[i].front()==',')&&(direc!="")){
                                                                if(!TS.verifica_id(direc)){
                                                                    TS.inserir(direc);
                                                                }
                                                                TS.adicionar_lista(direc, endereco);
                                                                direc = "";
                                                                obj.push_back(-1);
                                                                bitmap.push_back(Relativo);
                                                                addresslist.push_back(endereco);
                                                                endereco++;
                                                                n_var--;
                                                            }

                                                            direc += vetorLinha[i];
                                                            
                                                            if(vetorLinha[i].front()==','){
                                                                direc.erase(0,1);
                                                            }

                                                            if(vetorLinha[i].back()==','){
                                                                direc.pop_back();
                                                                
                                                            }
                                                            
                                                            if(ChecaComma(direc)){
                                                                SeparaVar(hel, direc);
                                                                int tm = hel.size();
                                                                tm--;
                                                                int j;
                                                                for(j=0;j<tm;j++){
                                                                    direc = hel[j];
                                                                    if(!TS.verifica_id(direc)){
                                                                        TS.inserir(direc);
                                                                    }
                                                                    TS.adicionar_lista(direc, endereco);
                                                                    obj.push_back(-1);
                                                                    bitmap.push_back(Relativo);
                                                                    addresslist.push_back(endereco);
                                                                    endereco++;
                                                                    n_var--;
                                                                }
                                                                EsvaziaVetor(hel);
                                                                direc = hel[tm];
                                                            }
                                                            
                                                            
                                                            if(!TS.verifica_id(direc)){
                                                                TS.inserir(direc);
                                                            }
                                                            TS.adicionar_lista(direc, endereco);
                                                            addresslist.push_back(endereco);
                                                            direc = "";
                                                            obj.push_back(-1);
                                                            bitmap.push_back(Relativo);
                                                            endereco++;
                                                            n_var--;
                                                            // insere direc na tb e/ou insere na lista de pendencia
                                                        }
                                                    }else{
                                                        if(ChecaComma(vetorLinha[i])){ // se tiver , no meio da string
                                                            direc+=vetorLinha[i];
                                                            SeparaVar(hel, direc);
                                                            int tm = hel.size();
                                                            tm--;
                                                            int j;
                                                            for(j=0;j<tm;j++){
                                                                direc = hel[j];
                                                                if(!TS.verifica_id(direc)){
                                                                    TS.inserir(direc);
                                                                }
                                                                TS.adicionar_lista(direc, endereco);
                                                                obj.push_back(-1);
                                                                bitmap.push_back(Relativo);
                                                                addresslist.push_back(endereco);
                                                                endereco++;
                                                                n_var--;
                                                            }
                                                            EsvaziaVetor(hel);
                                                            direc = hel[tm];
                                                            // Se tem virgula no vetor, separa por virgula e retorna vetor  
                                                        }else{
                                                            if((vetorLinha[i].back()=='+')){ 
                                                                // adiciona + no direc
                                                                direc += vetorLinha[i];
                                                            }else{
                                                                if(ChecaMais(vetorLinha[i])){
                                                                    direc += vetorLinha[i];
                                                                }else{
                                                                    direc+=vetorLinha[i];
                                                                }
                                                            }
                                                        }
                                                    }
                                                }else{
                                                    if(((text == -1)&&(comando!= "decl"))||((stop==true)&&(data_end == -1))){
                                                        direc+=vetorLinha[i];
                                                        direc+=" ";
                                                        comando = "direc";
                                                    
                                                    }else{
                                                        if(vetorLinha[i]!=""){
                                                            if((data==true)&&(comando == "decl")){
                                                                direc = vetorLinha[i];
                                                            //printf("a %s\n",vetorLinha[i].c_str());
                                                                if(tipo == ""){
                                                                    if(VerificaDiretiva(diretivas_var,vetorLinha[i])){
                                                                        if(vetorLinha[i]=="SPACE"){
                                                                            tipo = "SPACE";
                                                                            if(TS.verifica_id_decl(var)){
                                                                                err_linhastr = "Linha ";
                                                                                err_linhastr += std::to_string(atual);
                                                                                err_linhastr += " - Erro Semantico: declaracao de rotulos repetidos";
                                                                                if(!ContemErr(erros_linha, err_linhastr))
                                                                                    erros_linha.push_back(err_linhastr);
                                                                                err_linhastr = "";
                                                                            }else{
                                                                                if(var.back()==' ')
                                                                                    var.pop_back();
                                                                                if(VerificaTokens(var)){
                                                                                    if(!TS.verifica_id(var)){
                                                                                        TS.inserir(var);
                                                                                    }
                                                                            
                                                                                    if(text<0){
                                                                                        TS.inserir_variavel(var,-1,pos); 
                                                                                    }else{
                                                                                        TS.inserir_variavel(var,text+pos,pos); 
                                                                                    }
                                                                                    pos++;
                                                                                }else{
                                                                                    err_linhastr = "Linha ";
                                                                                    err_linhastr += std::to_string(atual);
                                                                                    err_linhastr += " - Erro Lexico: Tokens invalidos";
                                                                                    if(!ContemErr(erros_linha, err_linhastr))
                                                                                        erros_linha.push_back(err_linhastr);
                                                                                    err_linhastr = "";
                                                                                }
                                                                            }
                                                                    
                                                                        }else{
                                                                            tipo = "CONST";
                                                                        }
                                                                    }else{
                                                                        err_linhastr = "Linha ";
                                                                        err_linhastr += std::to_string(atual);
                                                                        err_linhastr += " - Erro Lexico: diretiva invalida";
                                                                        if(!ContemErr(erros_linha, err_linhastr))
                                                                            erros_linha.push_back(err_linhastr);
                                                                        err_linhastr = "";
                                                                    
                                                                    }
                                                                }else{
                                                                    if(tipo== "CONST" ){
                                                                    
                                                                        int d = std::stoi(vetorLinha[i]);
                                                                        if(TS.verifica_id_decl(var)){
                                                                            err_linhastr = "Linha ";
                                                                            err_linhastr += std::to_string(atual);
                                                                            err_linhastr += " - Erro Semantico: declaracao de rotulos repetidos";
                                                                            if(!ContemErr(erros_linha, err_linhastr))
                                                                                erros_linha.push_back(err_linhastr);
                                                                            err_linhastr = "";
                                                                        }else{
                                                                            if(var.back()==' ')
                                                                                var.pop_back();
                                                                            if(VerificaTokens(var)){
                                                                                if(!TS.verifica_id(var)){
                                                                                    TS.inserir(var);
                                                                                }
                                                                            
                                                                            if(text<0){
                                                                            TS.inserir_constante(var,-1,d,pos); 
                                                                            }else{
                                                                                TS.inserir_constante(var,text+pos,d,pos); 
                                                                            }
                                                                            pos++;
                                                                            
                                                                        }else{
                                                                            err_linhastr = "Linha ";
                                                                            err_linhastr += std::to_string(atual);
                                                                            err_linhastr += " - Erro Lexico: Tokens invalidos";
                                                                            if(!ContemErr(erros_linha, err_linhastr))
                                                                                erros_linha.push_back(err_linhastr);
                                                                            err_linhastr = "";
                                                                        }
                                                                    }
                                                                    
                                                                }else{
                                                                    
                                                                    int d = std::stoi(vetorLinha[i]);
                                                                    int f;
                                                                    
                                                                    for(f=1;f<d;f++){
                                                                        aux = var;
                                                                        aux += "+";
                                                                        aux += std::to_string(f);
                                                                        
                                                                            if(!TS.verifica_id(aux)){
                                                                                TS.inserir(aux);
                                                                            }
                                                                            
                                                                            if(text<0){
                                                                                TS.inserir_variavel(aux,-1,pos); 
                                                                            }else{
                                                                                TS.inserir_variavel(aux,text+pos,pos); 
                                                                            }
                                                                            pos++;
                                                                        
                                                                    }
                                                                    
                                                                }
                                                            }
                                                        }else{
                                                            direc=vetorLinha[i];
                                                            comando = "naoidentificado";
                                                            }
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
                        if(direc != ""){

                            
                            //printf("%s", direc.c_str());
                            if(!TS.verifica_id(direc)){
                                TS.inserir(direc);
                            }
                            if((TS.retorna_endereco(direc)> 0)&&(TS.verifica_id_decl(direc))){
                                obj.push_back(TS.retorna_endereco(direc));
                                bitmap.push_back(Relativo);
                                
                            }else{
                                TS.adicionar_lista(direc, endereco);
                                addresslist.push_back(endereco);
                                obj.push_back(-1);
                                bitmap.push_back(Relativo);
                            }
                            endereco++;
                            n_var--;

                            
                            
                        }
                    }

                    if(comando == "decl"){
                        comando = "declarado";
                    }

                    if(n_var!=0){
                        if(!erro){
                            erro = true;
                        }
                        Printa(vetorLinha);
                        printf("Linha %d - Erro Sintatico: Instrucao com quantidade de operacoes errada\n",atual);
                    }

                    if(comando=="direc"){
                        direc.pop_back();
                        if(direc=="SECTION DATA"){
                            if(stop==true){
                                stop=false;
                            }
                            data = true;
                            data_end = endereco;
                        }else{
                            if(direc=="SECTION TEXT"){
                                text = 0;
                                data = false;
                            }else{
                                if(!erro){
                                    erro = true;
                                }
                                Printa(vetorLinha);
                                printf("Linha %d - Erro lexico: Diretiva incorreta\n",atual);

                            }
                        }                  
                        
                    }
                    
                    

                    if((comando == "naoidentificado")){
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
                    tipo = "";
                    n_var = 0;
                    var = "";
                    direc = "";
                    EsvaziaVetor(vetorLinha);
                    comentario = false; // reseta variavel de comentario
                    atual++; 
                    
                }

                if(text>data_end){
                    TS.altera_end(text);
                }
                
                //TS.Mostra();
                // Resolve Pendencias
                ResolvePendencias(obj,TS);
                // Insere variaveis no vetor objeto
                InsereDecl(obj,bitmap,pos,TS,endereco);
                // Achar Variaveis nao declaradas
                if(!TS.verificaSimbDeclarados()){
                    if(!erro){
                        erro = true;
                    }
                    VerificaTS(TS);
                    
                }

                //PrintaOBJ(bitmap);
                //PrintaOBJ(addresslist);
                //printf("%d\n",endereco);

                // Cria o nome do novo arquivo que será criado com o código objeto do programa
                if(!erro){
                    std::string prog = argv[3];
                    std::string nome = argv[3];
                    std::string toReplace(".asm");
                    size_t pos = nome.find(toReplace);
                    nome.replace(pos, toReplace.length(), ".obj");
                    prog.replace(pos, toReplace.length(), "");
                    CasefyLetters(prog);
                    //printf("%s \n", prog.c_str());
                    std::ofstream saida(nome);
                    int j;
                    saida << "H: ";
                    saida << prog;
                    saida << "\n";
                    saida << "H: ";
                    saida << endereco;
                    saida << "\n";
                    saida << "H: ";
                    if(!Info){
                        // imprimir lista de enderecos
                        int tm = addresslist.size();
                        for(j=0;j<tm;j++){
                            saida << addresslist[j];
                            saida << " ";
                        }
                    }else{
                        // imprimir mapa de bits
                        int tm = bitmap.size();
                        for(j=0;j<tm;j++){
                            saida << bitmap[j];
                            saida << " ";
                        }
                    }
                    saida << "\n";
                    saida << "T: ";
                    int tm = obj.size();
                    for(j=0;j<tm;j++){
                        saida << obj[j];
                        saida << " ";
                    }
                    saida.close();
                }  
                //printf("text: %d, data: %d\n", text, data_end);
                
            
                
                
                // FIM DA CRIAcaO DO NOME DO ARQUIVO OBJETO
                
                Arquivo.close();
                TS.~TabelaDeSimbolos();
                // Desaloca vetor da tabela de simbolos

            }else{
                printf("ERRO: o valor de -r deve ser 0 ou 1\n");
            }
        }else{
            printf("Erro: parametro deve ser -r\n");
        }
        
    }
    
    return 0;
}