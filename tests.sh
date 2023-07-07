#!/bin/bash

verbose="true";
paused="true";
ko_break="true";
ok=0;
ko=0;

test_computor() {
	test_name="${1}"
    input="${2}"
    expected_output="${3}"
    actual_output=$(./computor "${input}")

    echo -n "$test_name) \`$input\` "
    if diff -q <(echo "${expected_output}") <(echo "${actual_output}") > /dev/null; then
        echo "[ OK ]"
		((ok++))
    else
        echo "[ KO ]"
		echo "==="
		echo "<<< Expected:"
		echo "$expected_output"
		echo ">>> Actual output:"
		echo "$actual_output"
		if [ "$ko_break" == "true" ]; then
			exit 
		fi
		echo "==="
		((ko++))
    fi

    [[ "$verbose" == "true" ]] && echo "${actual_output}" && echo;
	[[ "$paused" == "true" ]] && read;
}

final() {
	echo -n "[ Total: `echo \"$ok + $ko\" | bc`";
	echo -n " | OK: $ok";
	echo " | KO: $ko ]";
}

# coefficient is zero..?
test_computor \
"i0 - Just passing 0" \
"0" \
"Reduced form: +0*x^0 = 0
Polynomial degree: 0
Tautology. All real numbers possible as solution."

test_computor \
"i01 - Just passing 1" \
"1" \
"Reduced form: +1*x^0 = 0
Polynomial degree: 0
No solution."

test_computor \
"i1" \
"0 = 0" \
"Reduced form: +0*x^0 = 0
Polynomial degree: 0
Tautology. All real numbers possible as solution."

test_computor \
"i2" \
"0x = 0" \
"Reduced form: +0*x^1 +0*x^0 = 0
Polynomial degree: 1
Tautology. All real numbers possible as solution."

test_computor \
"i3" \
"0x^2 = 0" \
"Reduced form: +0*x^2 +0*x^1 +0*x^0 = 0
Polynomial degree: 2
Discriminant (delta): 0
Tautology. All real numbers possible as solution."

test_computor \
"i4" \
"42*X^0 = 42*X^0" \
"Reduced form: +0*x^0 = 0
Polynomial degree: 0
Tautology. All real numbers possible as solution."

test_computor \
"i5" \
"42*X^0 = 42" \
"Reduced form: +0*x^0 = 0
Polynomial degree: 0
Tautology. All real numbers possible as solution."

test_computor \
"i6" \
"42*X^0 + 1x^2 = 42*X^0 + 1x^2" \
"Reduced form: +0*x^2 +0*x^1 +0*x^0 = 0
Polynomial degree: 2
Discriminant (delta): 0
Tautology. All real numbers possible as solution."

test_computor \
"i7" \
"X^2 + 6 = 0x^0" \
"Reduced form: +1*x^2 +0*x^1 +6*x^0 = 0
Polynomial degree: 2
Discriminant (delta): -24
Discriminant is negative, the polinomial has two distinct complex roots.
0+2.44949i
0-2.44949i"

test_computor \
"i8" \
"5 + 4 * X + X^2" \
"Reduced form: +1*x^2 +4*x^1 +5*x^0 = 0
Polynomial degree: 2
Discriminant (delta): -4
Discriminant is negative, the polinomial has two distinct complex roots.
-2+1i
-2-1i"

test_computor \
"i9" \
"1 + 1x + 1xx" \
"Reduced form: +1*x^2 +1*x^1 +1*x^0 = 0
Polynomial degree: 2
Discriminant (delta): -3
Discriminant is negative, the polinomial has two distinct complex roots.
-0.5+0.866025i
-0.5-0.866025i"

test_computor \
"i10" \
"1.0 + 2.1x + 3.2xx = +4.3x^2" \
"Reduced form: -1.1*x^2 +2.1*x^1 +1*x^0 = 0
Polynomial degree: 2
Discriminant (delta): 8.81
Discriminant is strictly positive, the two solutions are:
2.30371
-0.39462"

test_computor \
"i11" \
"x" \
"Reduced form: +1*x^1 +0*x^0 = 0
Polynomial degree: 1"

test_computor \
"i12" \
"-x" \
"Reduced form: -1*x^1 +0*x^0 = 0
Polynomial degree: 1"

test_computor \
"i13" \
"x X x\t \t  XX" \
"Reduced form: +1*x^5 +0*x^4 +0*x^3 +0*x^2 +0*x^1 +0*x^0 = 0
Polynomial degree: 5
The polynomial degree is strictly greater than 2, I can't solve."

test_computor \
"i14" \
"-0.x *  x  * X x x X X x" \
"Reduced form: +0*x^8 +0*x^7 +0*x^6 +0*x^5 +0*x^4 +0*x^3 +0*x^2 +0*x^1 +0*x^0 = 0
Polynomial degree: 8
The polynomial degree is strictly greater than 2, I can't solve."

test_computor \
"i15" \
"\t5 + 4 * X\t\t   ^  1     - 9.3 * X^2    \t = -.1 * X^0 - -+++--x^2" \
"Reduced form: -10.3*x^2 +4*x^1 +5.1*x^0 = 0
Polynomial degree: 2
Discriminant (delta): 226.12
Discriminant is strictly positive, the two solutions are:
0.92414
-0.535791"

test_computor \
"i16" \
"5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0" \
"Reduced form: -9.3*x^2 +4*x^1 +4*x^0 = 0
Polynomial degree: 2
Discriminant (delta): 164.8
Discriminant is strictly positive, the two solutions are:
0.905239
-0.475131"

test_computor \
"i17" \
"5 * X^0 + 4 * X^1 = 4 * X^0" \
"Reduced form: +4*x^1 +1*x^0 = 0
Polynomial degree: 1"

test_computor \
"i18" \
"8 * X^0 - 6 * X^1 + 0 * X^2 - 5.6 * X^3 = 3 * X^0" \
"Reduced form: -5.6*x^3 +0*x^2 -6*x^1 +5*x^0 = 0
Polynomial degree: 3
The polynomial degree is strictly greater than 2, I can't solve."

final
