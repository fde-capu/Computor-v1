#!/bin/bash

verbose="false";
ok=0;
ko=0;
test_computor() {
    input="${1}"
    expected_output="${2}"

    echo -n "Testing: \`$input\` "

    actual_output=$(./computor "${input}")

    [[ "$verbose" == "true" ]] && echo "${actual_output}"

    if diff -q <(echo "${expected_output}") <(echo "${actual_output}") > /dev/null; then
        echo "[ OK ]"
		((ok++))
    else
        echo "[ KO ]"
		echo "==="
		echo "<<< Expected:"
		echo "$expected_output"
		echo ">>> Actual ouput:"
		echo "$actual_output"
		echo "==="
		((ko++))
    fi
}

final() {
	echo "Total: `echo \"$ok + $ko\" | bc`";
	echo "OK: $ok";
	echo "KO: $ko";
}

# coefficient is zero..?
test_computor "0" "Reduced form: +0*x^0 = 0
Polynomial degree: 0
Tautology. All real numbers possible as solution."


test_computor "0 = 0"
#test_computor "0x = 0"
#test_computor "0x^2 = 0"
#test_computor "42*X^0 = 42*X^0"
#test_computor "42*X^0 = 42"
#test_computor "42*X^0 + 1x^2 = 42*X^0 + 1x^2"
## R: all real numbers


#test_computor "X^2 + 6 = 0x^0"
#test_computor "5 + 4 * X + X^2"
## R: -1.25

#test_computor "1 + 1x + 1xx"
# R: complex

#test_computor "1.0 + 2.1x + 3.2xx = +4.3x^2"
#test_computor "x"
#test_computor "-x"
#test_computor "x X x\t \t  XX"
#test_computor "-0.x *  x  * X x x X X x"
#test_computor "\t5 + 4 * X\t\t   ^  1     - 9.3 * X^2    \t = -.1 * X^0 - -+++--x^2"

#test_computor "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0"
#test_computor "5 * X^0 + 4 * X^1 = 4 * X^0"
#test_computor "8 * X^0 - 6 * X^1 + 0 * X^2 - 5.6 * X^3 = 3 * X^0"

final
