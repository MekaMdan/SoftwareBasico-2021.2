#include<iostream>
#include<string>

using namespace std;

// Recebe argc e argc (padrão para receber entrada pela linha de comando)
// argc: Contador de entradas
// argv: Vetor de entradas
int main(int argc, char* argv[]) {
    int i;

    if(argc<2){
        printf("fatal error: no input files\nmontador terminated.");
    }else{
        for(i=1;i<=argc;i++){
            printf("%s\n", argv[i]);
        } 
    }
    
    return 0;
}