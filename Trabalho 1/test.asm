; oi
;oi
; section text
; LoAd um
; ADd um
; load res
; OutPut res
; stop
; section data
; um: const 1
; res: space

SECTION text
input n1 ;oi
input n2 ; a
load n1 
add n2
store n1
copy n1,n2 
output n1
output n2
stop

SECTION DATA
n1: space 
n2: space 
;if(vetorLinha[i]=="SECTION"){
;                            direc = vetorLinha[i];
;                            direc += ' ';
;                        }else{
;                            if(direc!=""){
;                                direc+=vetorLinha[i];
;                            }
;                        }
;printf("%s ", vetorLinha[i].c_str());
;                                    for (int i: inst.find(vetorLinha[i])->second ){
;                                        printf("%d ", i);
;                                    }
;                                    printf("\n");

;if(vetorLinha[i].back()==','){
;                                                // Atribui a Direc a variavel contida no vetorLinha[i] (tirando a virgula do final) N1, -> N1
;                                                vetorLinha[i].pop_back();
;                                                direc = vetorLinha[i];
;                                                vetorLinha[i].push_back(',');
;                                            }else{
;                                                if(vetorLinha[i]==","){
;
;                                                }