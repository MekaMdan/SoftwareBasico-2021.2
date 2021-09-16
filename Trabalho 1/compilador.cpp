#include <iostream>
#include <string.h>
#include <vector>
#include <fstream>
#include <conio.h>

void VetorInstrucao(std::vector <int> &v, std::string s){
    bool anterior = false;
    std::string word;
    int n;
    for (auto x: s){
        if((x == ' ')){
            if(anterior==false){
                anterior = true;
                n = std::stoi(word);
                v.push_back(n);
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
        n = std::stoi(word);
        v.push_back(n);
    }
}

void PrintaVetor(std::vector <int> v){
    int tam = v.size();
    for(int i=0;i<tam;i++){
        printf("%d ",v[i]);
    }
    printf("\n");
}


int BasicInst(int op, int acc, int valor, int end){
    switch (op)
    {
    case 1:
        printf("ADD %d   \n", end);
        acc = acc + valor;
        break;
    
    case 2:
        printf("SUB %d   \n", end);
        acc = acc - valor;

        break;
    
    case 3:
        printf("MUL %d   \n", end); 
        acc = acc * valor;
        break;

    case 4:
        printf("DIV %d   \n", end);
        acc = acc/valor;
        break;
    }
    return acc;
}

int JumpInst(int op, int acc, int end, int pc){
    switch (op){
    case 5:
        printf("JMP %d   \n",end);
        pc = end;
        break;

    case 6:
        printf("JMPN %d  \n",end);
        if(acc<0){
            pc = end;
        }else{
            pc+=2;
        }
        break;

    case 7:
        printf("JMPP %d  \n",end);
        if(acc>0){
            pc = end;
        }else{
            pc+=2;
        }
        break;

    case 8:
        printf("JMPZ %d  \n",end);
        if(acc==0){
            pc = end;
        }else{
            pc+=2;
        }
        break;

    }
    return pc;
}


void Execucao(std::string nome){
    std::ifstream Arquivo(nome);
    std::string linha;
    std::vector  <int> v;
    getline(Arquivo,linha);
    VetorInstrucao(v, linha);
    int acc = v.size();
    bool fim = false;
    if(acc<=0){
        fim = true;
    }
    acc = 0;
    int arg1, arg2;
    int pc = 0;
    int op;
    
    
    while(!fim){
        printf("\n*********************\n");
        printf("ACC = %d\n",acc);
        printf("PC = %d\n",pc);
        op = v[pc];
        switch (op) {
        case 1: case 2: case 3: case 4:
            arg1 = v[pc+1];
            acc = BasicInst(op, acc, v[arg1],arg1);
            pc+=2;
            break;

        case 10:
            arg1 = v[pc+1];
            printf("LOAD  %d \n", arg1);
            acc = v[arg1];  
            pc += 2;
            break;
        
        case 11:
            arg1= v[pc+1];
            printf("STORE %d \n",arg1);
            v[arg1] = acc;
            pc += 2;
            break;

        case 12:
            arg1 = v[pc+1];
            printf("INPUT %d \n", arg1);
            scanf("%d", &arg2);
            v[arg1] = arg2;
            pc += 2;
            break;

        case 13:
            arg1 = v[pc+1];
            arg2 = v[arg1];
            printf("OUTPUT:%d\n", arg2);
            getch();
            pc += 2;
            break;

        case 5: case 6: case 7: case 8:
            pc = JumpInst(op,acc,v[pc+1],pc);
            break;

        case 9:
            arg1 = v[pc+1];
            arg2 = v[pc+2];
            printf("COPY %d %d\n", arg1,arg2);
            v[arg2] = v[arg1];
            pc += 3;
            break;

        case 14:
            printf("STOP    \n");
            fim = true;
        default:
            break;
        }
        printf("*********************\n\n");
    }
    
}

// Recebe argc e argc (padrao para receber entrada pela linha de comando)
// argc: Contador de entradas
// argv: Vetor de entradas
int main(int argc, char* argv[]) {
    //int i;
    std::vector <int> objeto;
    std::string linha;
    if(argc<2){
        printf("fatal error: no input files\ncompilador terminated.");
    }else{
        Execucao(argv[1]);
    }
    
    return 0;
}