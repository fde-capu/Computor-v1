#!/bin/sh

test_computor() {
	echo "Testing: ${1}";
	./computor "${1}"
	echo ;
}

#test_computor "x"
#test_computor "x X X XX"
#test_computor "x *  x  * X x x X X x"
test_computor "5 + 4 * X^1 - 9.3 * X^2 = 1 * X^0"
#test_computor "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0"
#test_computor "5 * X^0 + 4 * X^1 = 4 * X^0"
#test_computor "8 * X^0 - 6 * X^1 + 0 * X^2 - 5.6 * X^3 = 3 * X^0"
