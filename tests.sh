#!/bin/bash

short="false";
show_output="true";
paused="true";
ko_break="true";
ok=0;
ko=0;

ansi() { echo -ne "\e[${1}m${*:2}\e[0m"; }
bold() { ansi 1 "$@"; }
italic() { ansi 3 "$@"; }
underline() { ansi 4 "$@"; }
strikethrough() { ansi 9 "$@"; }
red() { ansi 31 "$@"; }
green() { ansi 32 "$@"; }
blue() { ansi 34 "$@"; }

print_ko() {
	red "[ KO ]";
	if [[ "$short" == "true" ]]; then
		echo;
		bold "$test_name "
		[[ "$show_output" == "true" ]] && echo && blue "./computor ";
		blue "\"$input\" "
	fi
	echo

	bold ">>> Actual output:"
	echo
	[[ "$actual_output" != "" ]] && echo "$actual_output" || echo "(empty)"

	if [[ "$err_output" != "" ]] ; then
		bold ">>> Error from program:"
		echo
		echo "$err_output"
	fi;

	bold "<<< Expected $1"
	if [[ "$1" == "error" ]] ; then
		echo ".";
	else
		echo ":";
		echo "$expected_output";
	fi

	((ko++))
}

print_ok() {
	green "[ OK ]";
	[[ "$short" != "true" ]] && echo || echo -n " ";
	((ok++));
}

test_computor() {
	test_name="${1}"
    input="${2}"
    expected_output="${3}"
	tmpfile=$(mktemp);
    actual_output=$(./computor "${input}" 2>"$tmpfile")
	errno=$?;
	err_output=$(<"$tmpfile")
	rm "$tmpfile"

	if [[ "$short" != "true" ]]; then
		bold "$test_name "
		[[ "$show_output" == "true" ]] && echo && blue "./computor ";
		blue "\"$input\" "
	fi

	if [[ "$expected_output" == "error" ]]; then
		[[ "$errno" == "0" ]] && (print_ko "error") || print_ok && [[ "$show_output" == "true" ]] && [[ "$short" != "true" ]] && echo; 
		return 0;
	fi;

    if diff -q <(echo "${expected_output}") <(echo "${actual_output}") > /dev/null; then
		print_ok;
    else
		print_ko "output";
    fi

    [[ "$show_output" == "true" ]] && [[ "$short" != "true" ]] && echo "${actual_output}" && echo;
	[[ "$ko_break" == "true" ]] && [[ "$ko" != "0" ]] && exit;
	[[ "$paused" == "true" ]] && read;
}

final() {
	bold "[ Total: "
	blue "`echo \"$ok + $ko\" | bc`";
	bold " | ";
	green "OK: $ok";
	bold " | ";
	[[ "$ko" != "0" ]] && red "KO: $ko" || green "Perfect!";
	bold " ]";
	echo;
}

c1_test() {
	test_computor "${1}" "${2}" "${3}"
}

if false; then
	echo "dummy line so jump may be right below" 2> /dev/null;

############################################################### Begin

# coefficient is zero..?
c1_test \
"Just passing 0" \
"0" \
"Reduced form: 0 = 0
Polynomial degree: 0
Tautology. All real numbers possible as solution."

c1_test \
"Just passing 1" \
"1" \
"Reduced form: +1*x^0 = 0
Polynomial degree: 0
No solution."

c1_test \
"Passing 0 = 0" \
"0 = 0" \
"Reduced form: 0 = 0
Polynomial degree: 0
Tautology. All real numbers possible as solution."

c1_test \
"Passing impossible statement." \
"0 = 1" \
"Reduced form: -1*x^0 = 0
Polynomial degree: 0
No solution.";

c1_test \
"Same but inverted." \
"1 = 0" \
"Reduced form: +1*x^0 = 0
Polynomial degree: 0
No solution.";

c1_test \
"Passing only 'b'" \
"42.31x^1 = 0" \
"Reduced form: +42.31*x^1 = 0
Polynomial degree: 1
Equation is first degree. One solution:
0";

c1_test \
"Passing only 'b', but factor of zero" \
"0x^1 = 0" \
"Reduced form: 0 = 0
Polynomial degree: 1
Tautology. All real numbers possible as solution.";

c1_test \
"Passing 'b' and 'c'" \
"42x^1 + 7 = 0" \
"Reduced form: +42*x^1 +7*x^0 = 0
Polynomial degree: 1
Equation is first degree. One solution:
-0.166667";

c1_test \
"Passing 'b' and 'c', but 'b' is zero" \
"0x^1 + 7 = 0" \
"Reduced form: +7*x^0 = 0
Polynomial degree: 1
No solution.";

c1_test \
"Passing zero 'b' and zero 'c'" \
"0x^1 + 0 = 0" \
"Reduced form: 0 = 0
Polynomial degree: 1
Tautology. All real numbers possible as solution.";

c1_test \
"Passing only a" \
"xx" \
"Reduced form: +1*x^2 = 0
Polynomial degree: 2
Discriminant (delta): 0
Discriminant is zero, the polynomial has exactly one real root:
0"

c1_test \
"i3" \
"0x^2 = 0" \
"Reduced form: 0 = 0
Polynomial degree: 2
Discriminant (delta): 0
Tautology. All real numbers possible as solution."

c1_test \
"i4" \
"42*X^0 = 42*X^0" \
"Reduced form: 0 = 0
Polynomial degree: 0
Tautology. All real numbers possible as solution."

c1_test \
"i5" \
"42*X^0 = 42" \
"Reduced form: 0 = 0
Polynomial degree: 0
Tautology. All real numbers possible as solution."

c1_test \
"i6" \
"42*X^0 + 1x^2 = 42*X^0 + 1x^2" \
"Reduced form: 0 = 0
Polynomial degree: 2
Discriminant (delta): 0
Tautology. All real numbers possible as solution."

fi # > > > > > > > > > > > > > > > > > > > > > > > Jump line!
c1_test \
"i7" \
"X^2 + 6 = 0x^0" \
"Reduced form: +1*x^2 +6*x^0 = 0
Polynomial degree: 2
Discriminant (delta): -24
Discriminant is negative, the polinomial has two distinct complex roots.
0+2.44949i
0-2.44949i"

c1_test \
"xxx" \
"xxx" \
"Reduced form: +1*x^3 = 0
Polynomial degree: 3
The polynomial degree is strictly greater than 2, I can't solve."

c1_test \
"i8" \
"5 + 4 * X + X^2" \
"Reduced form: +1*x^2 +4*x^1 +5*x^0 = 0
Polynomial degree: 2
Discriminant (delta): -4
Discriminant is negative, the polinomial has two distinct complex roots.
-2+1i
-2-1i"

c1_test \
"i9" \
"1 + 1x + 1xx" \
"Reduced form: +1*x^2 +1*x^1 +1*x^0 = 0
Polynomial degree: 2
Discriminant (delta): -3
Discriminant is negative, the polinomial has two distinct complex roots.
-0.5+0.866025i
-0.5-0.866025i"

c1_test \
"i10" \
"1.0 + 2.1x + 3.2xx = +4.3x^2" \
"Reduced form: -1.1*x^2 +2.1*x^1 +1*x^0 = 0
Polynomial degree: 2
Discriminant (delta): 8.81
Discriminant is strictly positive, the two solutions are:
2.30371
-0.39462"

c1_test \
"i11" \
"x" \
"Reduced form: +1*x^1 = 0
Polynomial degree: 1
Equation is first degree. One solution:
0"

c1_test \
"i12" \
"-x" \
"Reduced form: -1*x^1 = 0
Polynomial degree: 1
Equation is first degree. One solution:
0"

c1_test \
"i13" \
"x X x\t \t  XX" \
"Reduced form: +1*x^5 = 0
Polynomial degree: 5
The polynomial degree is strictly greater than 2, I can't solve."

c1_test \
"i14" \
"-0.x *  x  * X x x X X x" \
"Reduced form: 0 = 0
Polynomial degree: 8
The polynomial degree is strictly greater than 2, I can't solve."

c1_test \
"i15" \
"\t5 + 4 * X\t\t   ^  1     - 9.3 * X^2    \t = -.1 * X^0 - -+++--x^2" \
"Reduced form: -10.3*x^2 +4*x^1 +5.1*x^0 = 0
Polynomial degree: 2
Discriminant (delta): 226.12
Discriminant is strictly positive, the two solutions are:
0.92414
-0.535791"

c1_test \
"i16" \
"5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0" \
"Reduced form: -9.3*x^2 +4*x^1 +4*x^0 = 0
Polynomial degree: 2
Discriminant (delta): 164.8
Discriminant is strictly positive, the two solutions are:
0.905239
-0.475131"

c1_test \
"err1" \
"blablabla" \
"error"


c1_test \
"i17" \
"5 * X^0 + 4 * X^1 = 4 * X^0" \
"Reduced form: +4*x^1 +1*x^0 = 0
Polynomial degree: 1
Equation is first degree. One solution:
-0.25"

c1_test \
"i18" \
"8 * X^0 - 6 * X^1 + 0 * X^2 - 5.6 * X^3 = 3 * X^0" \
"Reduced form: -5.6*x^3 -6*x^1 +5*x^0 = 0
Polynomial degree: 3
The polynomial degree is strictly greater than 2, I can't solve."

final
