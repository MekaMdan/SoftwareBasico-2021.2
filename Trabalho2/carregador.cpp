#include <iostream>
#include <string.h>
#include <vector>
#include <fstream>
#include <stdio.h>

bool hasEnding (std::string const &fullString, std::string const &ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

void PrintaVetorInt(std::vector<int>v){
    int t = v.size();
    if(t>=1){
        for(int i=0;i<t;i++){
            printf("%d ", v[i]);
        }
        printf("\n");
    }
}

void PrintaVetorString(std::vector<std::string>v){
    int t = v.size();
    if(t>=1){
        for(int i=0;i<t;i++){
            printf("%s ", v[i].c_str());
        }
        printf("\n");
    }
}

void VetorName(std::string &s, std::string l){
    bool anterior = false;
    std::string word;
    for(auto x: l){
        if(x==' '){
            if(!anterior){
                anterior = true;
                if(strcmp(word.c_str(),"H:")){
                    s = word;
                }
                word = "";
            }
        }else{
            if(anterior){
                anterior = false;
            }
            word = word+x;
        }
    }
    if(word!=""){
        s = word;
    }
}

void VetorSize(int &size, std::string l){
    bool anterior = false;
    std::string word;
    for(auto x: l){
        if(x==' '){
            if(!anterior){
                anterior = true;
                if(strcmp(word.c_str(),"H:")){
                    size = std::stoi(word);
                }
                word = "";
            }
            
        }else{
            if(anterior){
                anterior = false;
            }
            word = word + x;
        }
    }
    if(word!=""){
        size = std::stoi(word);
    }
}

void VetorInt(std::vector <int> &v, std::string l){
    bool anterior = false;
    std::string word;
    int n;
    for(auto x: l){
        if(x==' '){
            if(!anterior){
                anterior = true;
                if((strcmp(word.c_str(),"H:"))&&(strcmp(word.c_str(),"T:"))){
                    n = std::stoi(word);
                    v.push_back(n);
                }
                word = "";
            }
            
        }else{
            if(anterior){
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

void Remove(int &p, int &v, int &endereco){
    while((p>0)&&(v>0)){
        v--;
        p--;
        endereco++;
    }
}

void Simulacao(int &p, int v){
    while((p>0)&&(v>0)){
        v--;
        p--;
    }
}

void EsvaziaVetor(std::vector<std::string> &v){
    while(!v.empty()){
        v.pop_back();
    }
}

void EsvaziaInt(std::vector<int> &v){
    while(!v.empty()){
        v.pop_back();
    }
}

int main(int argc, char* argv[]) {
    std::string end = ".obj";
    int i = 1;
    if(argc<2){
        printf("fatal error: no input files\ncompilador terminated.");
    }else{
        int chunks;
        std::vector <int> tam;
        std::vector <int> address;
        std::vector <std::string> files;
        bool isFile = true;
        bool isChunk = false;
        bool isSize = false;
        bool isAddress = false;
        bool Allocated = false;
        bool Deu = false;
        int aux, j, k, Fsize, Tamsize, initial, fin, Tamsi;
        //std::vector <std::string> vs;
        std::string linha;
        std::vector <std::string> v;
        // Files infos
        std::string name;
        int SizeOf;
        std::vector <int> info;
        std::vector <int> machinecode;
        std::vector <int> firstadress;
        std::vector <int> adresssizeof;

        // Leitura e separação da entrada
        while(i<argc){
            if(isFile){
                if(hasEnding(argv[i],end)){
                    files.push_back(argv[i]);
                }else{
                    isFile = false;
                    isChunk = true;
                }
            }
            if(isChunk){
                chunks = atoi(argv[i]);
                isChunk = false;
                isSize = true;
                aux = chunks;
            }else{
                if(isSize){
                    j = atoi(argv[i]);
                    tam.push_back(j);
                    aux--;
                    if(aux==0){
                        isSize = false;
                        aux = chunks;
                        isAddress = true;
                    }
                }else{
                    if(isAddress){
                        j = atoi(argv[i]);
                        address.push_back(j);
                        aux--;
                        if(aux==0){
                            isAddress = false;
                        }
                    }
                }
            }

            i++;
        }

        // loop de leitura de arquivos e realização do alocamento
        Fsize = files.size();
        for (i=0;i<Fsize;i++){
            std::string NameFile = files[i];
            std::ifstream Arquivo(NameFile);
            
            // Get name on header
            getline(Arquivo, linha);
            VetorName(name,linha);
            //printf("name: %s\n", name.c_str());
            // Get size on header
            getline(Arquivo, linha);
            VetorSize(SizeOf, linha);
            //printf("tamanho: %d\n", SizeOf);
            // Get bitmap/address list
            getline(Arquivo, linha);
            VetorInt(info, linha);
            //PrintaVetorInt(info);
            // Get machine code
            getline(Arquivo, linha);
            VetorInt(machinecode, linha);
            //PrintaVetorInt(machinecode);

            // Aloca caso seja possivel
            Tamsize = tam.size();
            Tamsi = Tamsize-1;
            // Apenas um chuck de memoria
            for(j=0;j<Tamsize;j++){
                if((tam[j]>=SizeOf)&&(!Allocated)){
                    Allocated = true;
                    adresssizeof.push_back(tam[j]);
                    firstadress.push_back(address[j]);
                    tam[j] = tam[j] - SizeOf;
                    address[j] += SizeOf;
                }
            }

            // combinação de dois chucks de memoria
            if((!Allocated)&&(Tamsize>1)){
                for(j=0;j<Tamsi;j++){
                    for(k=1;k<Tamsize;k++){
                        if(((j+k)>=SizeOf)&&(!Allocated)){
                            Allocated = true;
                            aux = SizeOf;
                            adresssizeof.push_back(tam[j]);
                            adresssizeof.push_back(tam[k]);
                            firstadress.push_back(address[j]);
                            firstadress.push_back(address[k]);
                            Remove(aux,tam[j],address[j]);
                            Remove(aux,tam[k], address[k]);
                        }
                    }
                }
            }

            // mais de dois
            if((!Allocated)&&(Tamsize>2)){
                aux = SizeOf;
                j = 0;
                initial = 0;
                while ((j<Tamsize)&&(aux>0)){
                    Simulacao(aux, tam[j]);
                    if(aux==0){
                        Deu = true;
                        fin = j;
                        Allocated = true;
                    }
                    j++;
                }
                
            }

            if(Deu){
                aux = SizeOf;
                for(j=initial;j<=fin;j++){
                    adresssizeof.push_back(tam[j]);
                    firstadress.push_back(address[j]);
                    Remove(aux,tam[j],address[j]);
                }
            }

            if(Allocated){
                printf("Alocado:");
                PrintaVetorInt(adresssizeof);
                printf("\n");
                printf("tam: ");
                PrintaVetorInt(tam);
                printf("primeiro endereco: ");
                PrintaVetorInt(firstadress);
            }
            PrintaVetorInt(address);
            EsvaziaInt(adresssizeof);
            EsvaziaInt(firstadress);
            EsvaziaInt(info);
            EsvaziaInt(machinecode);
            

            if(!Allocated){
                printf("%s NAO FOI POSSIVEL ALOCAR\n", name.c_str());
            }
            Allocated = false;
            Deu = false;
        }
        /*
        printf("chunck: %d\n", chunks);
        printf("files: ");
        PrintaVetorString(files);
        printf("sizes: ");
        PrintaVetorInt(tam);
        printf("addresses ");
        PrintaVetorInt(address);
        */
    }
    return 0;
}