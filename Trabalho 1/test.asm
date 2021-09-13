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

section rext
input n1 ;oi
input n2 ; a
load n1
2labela: 
add n2
2labela:
store n1
output
stop
section data
n1: space
n2: space 
LABEL: INST SAD
;if(vetorLinha[i]=="SECTION"){
;                            direc = vetorLinha[i];
;                            direc += ' ';
;                        }else{
;                            if(direc!=""){
;                                direc+=vetorLinha[i];
;                            }
;                        }