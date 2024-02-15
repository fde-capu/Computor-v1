#!/bin/bash

short="false";
show_output="true";
paused="false";
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
	output_shown="true"

	((ko++))
}

print_ok() {
	green "[ OK ]";
	([[ "$short" != "true" ]] || [[ "$show_output" == "true" ]]) && echo || echo -n " ";
	((ok++));
}

test_computor() {
	test_name="${1}"
    input="${2}"
    [[ "${3}" != "manual" ]] && expected_output=$(./permutations.py ${3} 0) || expected_output="${4}"
	tmpfile=$(mktemp);
    actual_output=$(./computor "${input}" 2>"$tmpfile")
	errno=$?;
	err_output=$(<"$tmpfile")
	output_shown="false"
	rm "$tmpfile"

	if [[ "$short" != "true" ]]; then
		bold "$test_name:"
		[[ "$show_output" == "true" ]] && [[ "$output_shown" != "true" ]] && echo && blue "./computor ";
		blue "\"$input\" "
	fi

	if [[ "$expected_output" == "error" ]]; then
		[[ "$errno" == "0" ]] && (print_ko "error") || print_ok && [[ "$show_output" == "true" ]] && [[ "$output_shown" != "true" ]] && [[ "$short" != "true" ]] && echo; 
		return 0;
	fi;

	first_part="$(echo -e "$expected_output" | head -n -2)"
	second_part="$(echo -e "$expected_output" | tac | head -2)"
	expected_output_inverted="$first_part"$'\n'"$second_part"
    if (diff -q <(echo -e "${expected_output}") <(echo -e "${actual_output}") > /dev/null) || \
		(diff -q <(echo -e "${expected_output_inverted}") <(echo -e "${actual_output}") > /dev/null); then
		print_ok;
    else
		print_ko "output";
    fi

    [[ "$show_output" == "true" ]] && [[ "$output_shown" != "true" ]] && [[ "$short" != "true" ]] && echo "${actual_output}" && echo;
	[[ "$ko_break" == "true" ]] && [[ "$ko" != "0" ]] && exit 1;
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
	test_computor "${1}" "${2}" "${3}" "${4}"
}

if false; then
	echo "dummy line so jump may be right below" 2> /dev/null;

############################################################### Begin

fi # > > > > > > > > > > > > > > > > > > > > > > > Jump line!

c1_test \
"Just passing 0" \
"0" \
"0 0 0"

c1_test \
"Just passing 1" \
"1" \
"0 0 1"

c1_test \
"Passing 0 = 0" \
"0 = 0" \
"0 0 0"

c1_test \
"Passing impossible statement" \
"0 = 1" \
"0 0 1"

c1_test \
"Same but inverted" \
"1 = 0" \
"0 0 1"

c1_test \
"Minus zero as c" \
"0 = -0" \
"0 0 0"

c1_test \
"Minus zero as b" \
"-0x = 0" \
"0 0 0"

c1_test \
"Minus zero as a" \
"-0x^2 = 0" \
"0 0 0"

c1_test \
"Passing only 'b'" \
"42.31x^1 = 0" \
"0 42.31 0"

c1_test \
"Passing only 'b', but factor of zero" \
"0x^1 = 0" \
"0 0 0"

c1_test \
"Passing 'b' and 'c'" \
"42x^1 + 7 = 0" \
"0 42 7"

c1_test \
"Passing 'b' and 'c', but 'b' is zero" \
"0x^1 + 7 = 0" \
"0 0 7"

c1_test \
"Passing zero 'b' and zero 'c'" \
"0x^1 + 0 = 0" \
"0 0 0"

c1_test \
"Passing a (only) as multiplication" \
"xx" \
"1 0 0"

c1_test \
"i3" \
"0x^2 = 0" \
"0 0 0"

c1_test \
"i4" \
"42*X^0 = 42*X^0" \
"0 0 0"

c1_test \
"i5" \
"42*X^0 = 42" \
"0 0 0"

c1_test \
"i6" \
"42*X^0 + 1x^2 = 42*X^0 + 1x^2" \
"0 0 0"

c1_test \
"i7" \
"X^2 + 6 = 0x^0" \
"1 0 6"

c1_test \
"xxx" \
"xxx" \
"manual" \
"Reduced form: +1*x^3 +0*x^2 +0*x^1 +0*x^0 = 0
Polynomial degree: 3
The polynomial degree is strictly greater than 2, I can't solve."

c1_test \
"i8" \
"5 + 4 * X + X^2" \
"1 4 5"

c1_test \
"i9" \
"1 + 1x + 1xx" \
"1 1 1"

c1_test \
"i10" \
"1.0 + 2.1x + 3.2xx = +4.3x^2" \
"-1.1 2.1 1"

c1_test \
"i11" \
"x" \
"0 1 0"

c1_test \
"i12" \
"-x" \
"0 -1 0"

c1_test \
"i13" \
"x X x\t \t  XX" \
"manual" \
"Reduced form: +1*x^5 +0*x^4 +0*x^3 +0*x^2 +0*x^1 +0*x^0 = 0
Polynomial degree: 5
The polynomial degree is strictly greater than 2, I can't solve."

c1_test \
"i14" \
"-0.x *  x  * X x x X X x" \
"0 0 0"

c1_test \
"i15" \
"\t5 + 4 * X\t\t   ^  1     - 9.3 * X^2    \t = -.1 * X^0 - -+++--x^2" \
"-10.3 4 5.1"

c1_test \
"i16" \
"5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0" \
"-9.3 4 4"

c1_test \
"err1" \
"blablabla" \
"error"

c1_test \
"i17" \
"5 * X^0 + 4 * X^1 = 4 * X^0" \
"0 4 1"

c1_test \
"i18" \
"8 * X^0 - 6 * X^1 + 0 * X^2 - 5.6 * X^3 = 3 * X^0" \
"manual" \
"Reduced form: -5.6*x^3 +0*x^2 -6*x^1 +5*x^0 = 0
Polynomial degree: 3
The polynomial degree is strictly greater than 2, I can't solve."

c1_test \
"i19" \
"1 + 2x + 3x^2 = 4x - 5x^2 - 6" \
"8 -2 7"

c1_test \
"i20" \
"0 = -1 - x^1 + x^2" \
"-1 1 1"

c1_test \
"i21" \
"1 = -1 + x^1 - x^2" \
"1 -1 2"

c1_test \
"i22" \
"1 = 2 - x^1 - x^2" \
"1 1 -1"

c1_test \
"i23" \
"1 + 2x = -2 - x^1 - 3x^2" \
"3 3 3"

c1_test \
"i24" \
"-6x + 1 + 2x = -2 - x^1 + 3x^2" \
"-3 -3 3"

c1_test \
"i25" \
"-6 + 2x = -2 - x^1 + 3x^2" \
"-3 3 -4"

c1_test \
"i26" \
"-2 + 3x^2 + 2x = 2 + 5x^1" \
"3 -3 -4"

c1_test \
"i27" \
"-2 + 3x^2 + 2x = +6x^2 + 2 + 5x^1" \
"-3 -3 -4"

c1_test \
"i28" \
"-2*3 + 3x + 2x = -1x^2" \
"1 5 -6"

c1_test \
"i29" \
"-2^3 + 3x + 2x = 0" \
"0 5 -8"

c1_test \
"i30" \
"-2^-3 + 3x + 2x = 0" \
"error"

c1_test \
"i31" \
"-2^3^2 + 3x + 2x = 0" \
"0 5 -64"

c1_test \
"i32" \
"-2^^2 + 3x^2 + 2x = +6x^2 + 2 + 5x^1" \
"error"

c1_test \
"i33" \
"-2^2 + 2 3x = 0" \
"0 3 -2"

c1_test \
"i34" \
"-2^2 + 2*3x = 0" \
"0 6 -4"

c1_test \
"i35" \
"-22^2 = 484x" \
"0 -484 -484"

c1_test \
"i36" \
"-2^2 + 3x 2 = 0" \
"0 3 -2"

c1_test \
"i36" \
"-2.2^2 + 3.1^2x^2 = 0" \
"9.61 0 -4.84"

c1_test \
"i36b" \
"-2^3^4 + 3.1x^2 = 0" \
"3.1 0 -4096"

c1_test \
"i36c" \
"3x^2*4 = 0" \
"12 0 0"

c1_test \
"i36d" \
"3x^2^4 = 0" \
"error"

c1_test \
"i36e" \
"3x^/2 = 0" \
"error"

c1_test \
"i36f" \
"3x^*2 = 0" \
"error"

c1_test \
"i36g" \
"3x^-2 = 0" \
"error"

c1_test \
"i36h" \
"3x^+2 = 0" \
"3 0 0"

c1_test \
"i36i" \
"3x^+-2 = 0" \
"error"

c1_test \
"i36j" \
"3x+^2 = 0" \
"error"

c1_test \
"i36k" \
"3x-^2 = 0" \
"error"

c1_test \
"i36k" \
"3x+^2^1 = 0" \
"error"

c1_test \
"i37a" \
"-2^2x = -2^2x" \
"0 0 0"

c1_test \
"i37a1" \
"-2^2x -3^2x = 1" \
"0 -13 -1"

c1_test \
"i37a1b" \
"-2^2x -3^2x = 0" \
"0 -13 0"

c1_test \
"i37a1b2" \
"-2^3x -3^3x = 1" \
"0 -35 -1"

c1_test \
"i37a1bc" \
"-2^3x -3^3x = 0" \
"0 -35 0"

c1_test \
"i37a2" \
"-2^2x = -3^2x" \
"0 5 0"

c1_test \
"i38" \
"-2^2x = 2^2x" \
"0 -8 0"

c1_test \
"i39" \
"2^1.2 = 2^1.2" \
"error"

c1_test \
"i40" \
"4//2 = 2" \
"error"

c1_test \
"i41" \
"4///2 = 2" \
"error"

c1_test \
"i40a" \
"4**2 = 2" \
"error"

c1_test \
"i40b" \
"4**2 = 2" \
"error"

c1_test \
"i40c" \
"4/*2 = 2" \
"error"

c1_test \
"i40d" \
"4*/2 = 2" \
"error"

c1_test \
"i40d" \
"4*^2 = 2" \
"error"

c1_test \
"i40d" \
"4/^2 = 2" \
"error"

c1_test \
"i42" \
"-2^2 + 3x2 = 0" \
"3 0 -4"

c1_test \
"i43" \
"-2^2 + 3x2 + 2x = +6x^2 + 2 + 5x^1" \
"-3 -3 -6"

c1_test \
"i44a" \
"x^3 = 21" \
"manual" \
"Reduced form: +1*x^3 +0*x^2 +0*x^1 -21*x^0 = 0
Polynomial degree: 3
The polynomial degree is strictly greater than 2, I can't solve."

c1_test \
"i44b" \
"2x^100 = 0" \
"manual" \
"Reduced form: +2*x^100 +0*x^99 +0*x^98 +0*x^97 +0*x^96 +0*x^95 +0*x^94 +0*x^93 +0*x^92 +0*x^91 +0*x^90 +0*x^89 +0*x^88 +0*x^87 +0*x^86 +0*x^85 +0*x^84 +0*x^83 +0*x^82 +0*x^81 +0*x^80 +0*x^79 +0*x^78 +0*x^77 +0*x^76 +0*x^75 +0*x^74 +0*x^73 +0*x^72 +0*x^71 +0*x^70 +0*x^69 +0*x^68 +0*x^67 +0*x^66 +0*x^65 +0*x^64 +0*x^63 +0*x^62 +0*x^61 +0*x^60 +0*x^59 +0*x^58 +0*x^57 +0*x^56 +0*x^55 +0*x^54 +0*x^53 +0*x^52 +0*x^51 +0*x^50 +0*x^49 +0*x^48 +0*x^47 +0*x^46 +0*x^45 +0*x^44 +0*x^43 +0*x^42 +0*x^41 +0*x^40 +0*x^39 +0*x^38 +0*x^37 +0*x^36 +0*x^35 +0*x^34 +0*x^33 +0*x^32 +0*x^31 +0*x^30 +0*x^29 +0*x^28 +0*x^27 +0*x^26 +0*x^25 +0*x^24 +0*x^23 +0*x^22 +0*x^21 +0*x^20 +0*x^19 +0*x^18 +0*x^17 +0*x^16 +0*x^15 +0*x^14 +0*x^13 +0*x^12 +0*x^11 +0*x^10 +0*x^9 +0*x^8 +0*x^7 +0*x^6 +0*x^5 +0*x^4 +0*x^3 +0*x^2 +0*x^1 +0*x^0 = 0
Polynomial degree: 100
The polynomial degree is strictly greater than 2, I can't solve."

c1_test \
"i45" \
"^2" \
"error"

c1_test \
"i46" \
"x^2" \
"1 0 0"

c1_test \
"i47a" \
"x^2x" \
"error"

c1_test \
"i47b" \
"x^2x^1" \
"error"

c1_test \
"i48" \
"x^2x^2" \
"error"

c1_test \
"i49" \
"x^" \
"error"

c1_test \
"i50" \
"-1x2 0x -1" \
"-1 0 -1"

final
