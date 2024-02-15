#!/bin/python3
# Outputs made according to my own Computor v1 output, ipsi litteris.

import itertools
import random
import sys
import re
import pdb
import difflib
import subprocess

debug = False

HEADER = '\033[94m'
OK = '\033[92m'
KO = '\033[91m'
ENDC = '\033[0m'

if debug:
	pdb.set_trace()

random_max = 100
characters = ['+', '-', '0', ' ']

if len(sys.argv) != 1 and \
	len(sys.argv) != 2 and \
	len(sys.argv) != 4 and \
	len(sys.argv) != 5:
	print("Call without arguments to run all tests.")
	print("Call with a, b, and c as arguments to run manual test.")
	print("Call with a b c and `d` argument (any value) to run only Python test.")
	print("`--table`: outputs permutation table")
	sys.exit(1)

perms = list(itertools.product(characters, repeat=3))
if len(sys.argv) == 2 and sys.argv[1] == '--table':
	print('| a | b | c | Example')
	print('|---|---|---|')
	for p in perms:
		print(f'| {p[0]} | {p[1]} | {p[2]} | ', end = '')
		i = 2
		for e in p:
			if e == '+':
				print(f'+N*x^{i} ', end = '')
			elif e == '-':
				print(f'-N*x^{i} ', end = '')
			elif e == '0':
				print(f'0*x^{i} ', end = '')
			elif e == ' ':
				print('', end = '')
			i -= 1
			if i == -1:
				print()
	exit(0)

ok_count = 0
ko_count = 0

def map_chars(char, t):
	if t == 'integer':
		if char == '+':
			return random.randint(1, random_max)
		elif char == '-':
			return -random.randint(1, random_max)
		elif char == '0':
			return 0;
		else:
			return char;
	elif t == 'floatin':
		if char == '+':
			return random.uniform(0.0, random_max)
		elif char == '-':
			return -random.uniform(0.0, random_max)
		elif char == '0':
			return 0;
		else:
			return char;

integers_perms = [[map_chars(char, 'integer') for char in perm] for perm in perms]
floating_perms = [[map_chars(char, 'floatin') for char in perm] for perm in perms]

def epsilon_pass(a, b):
	epsilon = 0.0000001
	return abs(a - b) <= epsilon

def sqrt(number):
	error = 0.000001
	guess = 1.0
	if not number or number == 1:
		return number
	while abs((guess * guess) - number) > error:
		guess = (guess + (number / guess)) / 2
	if epsilon_pass(guess, int(guess)):
		guess = int(guess)
	return guess

def build_polynomial(element):
	global characters;
	try:
		for i in range(3):
			element[i] = 0.0 if i <= len(element) and not element[i] else element[i]
		a, b, c = element
		a_str = '+0*x^2'
		if a != characters[3]:
			a_sig = '+' if a >= 0 else '-'
			a_abs = abs(a)
			if a:
				a_str = f'{a_sig}{format_number(a_abs,True)}*x^2'
		b_str = '+0*x^1'
		if b != characters[3]:
			b_sig = '+' if b >= 0 else '-'
			b_abs = abs(b)
			if b:
				b_str = f'{b_sig}{format_number(b_abs,True)}*x^1'
		c_str = '+0*x^0'
		if c != characters[3]:
			c_sig = '+' if c >= 0 else '-'
			c_abs = abs(c)
			if c:
				c_str = f'{c_sig}{format_number(c_abs,True)}*x^0'
		f_str = f'Reduced form: '
		f_str += f'{a_str} '
		f_str += f'{b_str} '
		f_str += f'{c_str} '
		f_str += '= 0'
		new_f_str = re.sub('[^\d][\+\-]?0\*x\^2', '', f_str)
		if new_f_str != f_str:
			f_str = new_f_str
			f_str = re.sub('[^\d][\+\-]?0\*x\^1', '', f_str)
		d_test = re.findall(r'\^(\d)', f_str)
		d_numb = [int(d) for d in d_test]
		degree = max(d_numb) if d_numb else 0
		f_str += f'\nPolynomial degree: {degree}\n'
		if degree == 0:
			if c:
				f_str += 'No solution.'
			else:
				f_str += 'Tautology. All real numbers possible as solution.'
			return f_str
		discriminant = (b**2) - (4*a*c)
		if a:
			if discriminant >= 0:
				root1 = (-b + sqrt(discriminant)) / (2*a)
				root2 = (-b - sqrt(discriminant)) / (2*a)
			else:
				real_part = -b / (2*a)
				imaginary_part = sqrt(-discriminant) / (2*a)
				root1 = complex(real_part, imaginary_part)
				root2 = complex(real_part, -imaginary_part)
			f_str += interpret_result([root1, root2], discriminant)
		else:
			if b:
				f_str += f'Equation is first degree. One solution:\n{format_number(-c/b)}'
		return f_str
	except Exception as e:
		print(f'--[{e}]--')
		pdb.set_trace()

def interpret_result(roots, discriminant):
	try:
		ra, rb = roots
		out = ''
		if discriminant > 0:
			out += f'Discriminant (delta): {format_number(discriminant)}\n'\
				+ f'Discriminant is strictly positive, the two solutions are:\n'\
				+ f'{format_number(ra)}\n{format_number(rb)}'
			return out
		if discriminant == 0:
			if len(roots) == 0:
				out += "Tautology. All real numbers possible as solution."
				return out
			if len(roots) >= 1: # because it's [0.0, -0.0]
				out += f'Discriminant (delta): {format_number(discriminant)}\n'
				out += f'Discriminant is zero, the polynomial has exactly one real root:\n{format_number(ra)}'
				return out
		str_r0 = '0' if ra.real == 0.0 else f'{format_number(ra.real)}'
		str_r1 = '0' if rb.real == 0.0 else f'{format_number(rb.real)}'
		if discriminant < 0:
			out += f'Discriminant (delta): {format_number(discriminant)}\n'\
				+ 'Discriminant is negative, the polynomial has two distinct complex roots.\n'
			if ra.real < 1:
				out += f'{str_r0}+{format_number(abs(ra.imag))}i'
			else:
				out += f'{str_r0}+{format_number(abs(ra.imag))}i'
			if rb.real < 1:
				out += f'\n{str_r1}-{format_number(abs(rb.imag))}i'
			else:
				out += f'\n{str_r1}-{format_number(abs(rb.imag))}i'
		return out
	except Exception as e:
		print(f'--[{e}]--')
		pdb.set_trace()

def sort_last_two_lines(multiline_string):
	try:
		lines = multiline_string.split('\n')
		last_two_lines = lines[-2:]
		sorted_lines = sorted([line for line in last_two_lines])
		sorted_multiline_string = '\n'.join(lines[:-2] + [format_number(line) for line in sorted_lines])
		return sorted_multiline_string
	except Exception as e:
		print(f'--[{e}]--\n{locals()}')
		pdb.set_trace()

def diff_strings(str1, str2):
	str1 = sort_last_two_lines(str1)
	str2 = sort_last_two_lines(str2)
	str1_lines = str1.splitlines(True)
	str2_lines = str2.splitlines(True)
	diff_gen = difflib.unified_diff(str1_lines, str2_lines)
	diff_str = '\n'.join(diff_gen)
	diff_str = re.sub('\n+', '\n', diff_str)
	return diff_str

def format_number(num, cut_trailing_zeros = False):
	if not num:
		return '0'
	if isinstance(num, str):
		return num
	if num == int(num):
		return str(int(num))
	else:
		out = f"{num:.6f}"
		out = re.sub('^[+-]?0?\.?0{6}$', '0', out)
		if cut_trailing_zeros:
			out = re.sub('0+$', '', out)
		return out

def diff_exec(args):
	global characters;
	global ko_count
	global ok_count

	for i in range(len(args)):
		if args[i] == characters[3]:
			args[i] = 0
	a, b, c = args
	print(HEADER, f'\n                           {args}', ENDC)
	print(HEADER, '//= py_test ============================================\\\\ py_test ::::', ENDC)
	py_test = build_polynomial(args)
	print(py_test)
	print(HEADER, '||= c1_test ============================================|| c1_test ::::', ENDC)
	c1_test = subprocess.run([f'./computor', f'{str(a)}x^2 {str(b)}x {str(c)}'], stdout=subprocess.PIPE).stdout.decode('utf-8').strip()
	print(c1_test)
	pyc1 = diff_strings(py_test, c1_test)
	if len(pyc1) == 0:
		ok_count += 1
		print (HEADER, f'\\\\======================================================// {OK}>>>>>>> [OK]', ok_count, ENDC)
		return 0
	else:
		ko_count += 1
		print(HEADER, f' \\\\========================================= py < > c1 =// {KO}>>>>>>> [KO] :(\n', ENDC, pyc1)
		print(f'{OK}[OK]{ENDC}: {ok_count}', end = '')
		if ko_count:
			print(f' {KO}[KO]{ENDC}: {ko_count}')
			return 1

if len(sys.argv) >= 4:
	a = float(sys.argv[1])
	b = float(sys.argv[2])
	c = float(sys.argv[3])
	if len(sys.argv) == 5:
		print(build_polynomial([a, b, c]))
		exit(0)
	exit(diff_exec([a, b, c]))

for perm in integers_perms:
	out = diff_exec(perm)
	print()
	if out:
		exit(1)

for perm in floating_perms:
	out = diff_exec(perm)
	print()
	if out:
		exit(1)

exit(0)
