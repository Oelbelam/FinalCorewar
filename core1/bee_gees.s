.name "batman"
.comment "This city needs me"

live:
sti	r1, %:live, %1;change live by the right value
ld %2, r1;
ld %2, r1 ;

add r1, r2, r3;
add r1, r2, r3 ;

xor r2, r3, r2;
xor r2, r3, r2 ;

fork %3;
fork %3 ;

lld 5, r4;
lld 5, r4 ;

zjmp %3;
zjmp %3 ;

aff r2;
aff r4 ;

lldi r1, r2, r4;
lldi r1, r2, r4 ;
