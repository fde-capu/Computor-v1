#!/bin/python3
# Outputs made according to my Computor v1 output

debug = False

import itertools
import random
import numpy as np
import sys
import re
import pdb
import difflib
import subprocess

if debug:
	pdb.set_trace()

characters = ['+', '-', '0', ' ']
random_max = 100

if len(sys.argv) != 4 and len(sys.argv) != 1:
    print("Call without arguments to run all tests. Call with a, b, and c as arguments to run once.")
    sys.exit(1)

ok_count = 0
ko_count = 0

# Use itertools.product to generate all permutations
perms = list(itertools.product(characters, repeat=3))

# Map characters to integers or keep them as they are
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
			return random.uniform(0.1, random_max)
		elif char == '-':
			return -random.uniform(0.1, random_max)
		elif char == '0':
			return 0;
		else:
			return char;

# Create two lists with mapped values
integers_perms = [[map_chars(char, 'integer') for char in perm] for perm in perms]
floating_perms = [[map_chars(char, 'floatin') for char in perm] for perm in perms]

def build_polynomial(element):
	try:
		for i in range(3):
			element[i] = 0.0 if i <= len(element) and not element[i] else element[i]
		a, b, c = element
		if a != characters[3]:
			a_sig = '+' if a >= 0 else '-'
			a_abs = abs(a)
			a_str = f'{a_sig}{format_number(a_abs)}*x^2 '
		else:
			a_str = ''
			a = 0
		if b != characters[3]:
			b_sig = '+' if b >= 0 else '-'
			b_abs = abs(b)
			b_str = f'{b_sig}{format_number(b_abs)}*x^1 '
		else:
			b_str = ''
			b = 0
		if c != characters[3]:
			c_sig = '+' if c >= 0 else '-'
			c_abs = abs(c)
			c_str = f'{c_sig}{format_number(c_abs)}*x^0 '
		else:
			c_str = ''
			c = 0
		f_str = f'Reduced form: '
		f_str += f'{a_str}'
		f_str += f'{b_str}'
		f_str += f'{c_str}= 0'
		d_degr = re.sub(' ', '', f_str)
		d_test = re.findall('\^(\d)', d_degr)
		d_numb = [int(d) for d in d_test]
		degree = max(d_numb) if d_numb else 0
		f_str += f'\nPolynomial degree: {degree}\n'
		# Calculate the roots
		discriminant = b**2 - 4*a*c
		if a:
			if discriminant >= 0:
				root1 = (-b + np.sqrt(discriminant)) / (2*a)
				root2 = (-b - np.sqrt(discriminant)) / (2*a)
			else:
				real_part = -b / (2*a)
				imaginary_part = np.sqrt(-discriminant) / (2*a)
				root1 = complex(real_part, imaginary_part)
				root2 = complex(real_part, -imaginary_part)
			f_str += interpret_result([root1, root2], discriminant)
		else:
			f_str += 'Equation is first degree. One solution:\n'
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
			if len(roots) == 1:
				out += f'Discriminant is zero, the polynomial has exactly one real root:\n{ra}'
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

def pre_float(line):
	return re.sub(r'(^.\d*\.{1}\d*?).*', r'\1', line)

def sort_last_two_lines(multiline_string):
	try:
		lines = multiline_string.split('\n')
		last_two_lines = lines[-2:]
		sorted_lines = sorted([float(pre_float(line)) for line in last_two_lines], key = lambda x: x.real)
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

def format_number(num):
	if not num:
		return '0'
	if isinstance(num, str):
		return num
	if num == int(num):
		return str(int(num))
	else:
		if num < 1:
			out = f"{num:.6f}"
		else:
			out = f"{num:.5f}"
		return out

def diff_exec(args):
	global ko_count
	global ok_count

	py_test = build_polynomial(args)
	c1_test = subprocess.run(['./computor', str(args[0]) + 'x^2', str(args[1]) + 'x', str(args[2])], stdout=subprocess.PIPE).stdout.decode('utf-8').strip()
	print('= py_test ================================================= py_test ::::\n', py_test)
	print('= c1_test ================================================= c1_test ::::\n', c1_test)
	pyc1 = diff_strings(py_test, c1_test)
	if len(pyc1) == 0:
		ok_count += 1
		print (	'==============================================================>>>>> [OK]')
	else:
		ko_count += 1
		print(	'===================================================== py< >c1 >>>>> [KO] :(\n', pyc1, len(pyc1))
		print(f'[OK]: {ok_count}', end = '')
		if ko_count:
			print(f' [KO]: {ko_count}')
		else:
			print()
		input("Press Enter to continue...")

if len(sys.argv) == 4:
	a = float(sys.argv[1])
	b = float(sys.argv[2])
	c = float(sys.argv[3])
	diff_exec([a, b, c])
	exit()

for perm in integers_perms:
	diff_exec(perm)