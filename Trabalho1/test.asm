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
n1 : space
n2: space 
