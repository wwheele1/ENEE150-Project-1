#!/bin/sh

echo "*** test1 ***"
gcc pr2.c airlines_database.h airlines_database.c 
#test1.in<a.out>test1_results
diff test1_results test1.out

echo "*** test2 ***"
#test2.in<a.out>test2_results
diff test2_results test2.out

echo "*** test3 ***"
#test3.in<a.out>test3_results
diff test3_results test3.out

echo "*** test4 ***"
#test4.in<a.out>test4_results
diff test4_results test4.out

echo "*** test5 ***"
#test5.in<a.out>test5_results
diff test5_results test5.out

echo "*** test6 ***"
#test6.in<a.out>test6_results
diff test6_results test6.out
