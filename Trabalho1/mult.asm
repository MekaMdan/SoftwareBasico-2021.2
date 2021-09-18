SECTION TEXT
INPUT N1 ;2
INPUT n2 ;4
comparacao: load n2
sub N1
jmpp multiplo
jmp fim
multiplo: load n2
div N1 
mul N1
store c
load n2
sub c
jmpz mult_sim
jmp mult_nao
mult_sim: output one
jmp fim
mult_nao: output zero
jmp fim
fim: STOP
SECTION DATA
n1: SPACE
n2: SPACE
c: space
one: const 1
zero: const 0
