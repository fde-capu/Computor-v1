#!/bin/python3
# Outputs made according to my Computor v1 output

debug = False

import itertools
import random
import numpy as np
import sys
import re
import pdb

if debug:
	pdb.set_trace()

characters = ['+', '-', '0', ' ']
random_max = 100

if len(sys.argv) != 4:
    print("Needs a, b, and c as arguments.")
    sys.exit(1)

a = float(sys.argv[1])
b = float(sys.argv[2])
c = float(sys.argv[3])

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

#for perm in integers_perms:
#  print(perm)

#for perm in floating_perms:
#  print(perm)

def build_polynomial(element):
	try:
		for i in range(3):
			element[i] = 0.0 if i <= len(element) and not element[i] else element[i]
		a, b, c = element
		if a != characters[3]:
			a_sig = '+' if a >= 0 else '-'
			a_abs = abs(a)
			a_str = f'{a_sig}{format_number(a_abs)}x^2 '
		else:
			a_str = ''
			a = 0
		if b != characters[3]:
			b_sig = '+' if b >= 0 else '-'
			b_abs = abs(b)
			b_str = f'{b_sig}{format_number(b_abs)}x^1 '
		else:
			b_str = ''
			b = 0
		if c != characters[3]:
			c_sig = '+' if c >= 0 else '-'
			c_abs = abs(c)
			c_str = f'{c_sig}{format_number(c_abs)}x^0 '
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
		if discriminant >= 0:
			root1 = (-b + np.sqrt(discriminant)) / (2*a)
			root2 = (-b - np.sqrt(discriminant)) / (2*a)
		else:
			real_part = -b / (2*a)
			imaginary_part = np.sqrt(-discriminant) / (2*a)
			root1 = complex(real_part, imaginary_part)
			root2 = complex(real_part, -imaginary_part)
		f_str += interpret_result([root1, root2], discriminant)
		return f_str
	except Exception as e:
		print(f'--[{e}]--')
		pdb.set_trace()

def format_number(num):
	if isinstance(num, str):
		return num
	if num == int(num):
		return str(int(num))
	else:
		return f"{num:.6f}"

def interpret_result(roots, discriminant):
	try:
		root_a, root_b = roots
		out = ''
		if discriminant > 0:
			out += f'Discriminant (delta): {discriminant:.4f}\n'\
				+ f'Discriminant is strictly positive, the two solutions are:\n{root_a}\n{root_b}'
			return out
		if discriminant == 0:
			if len(roots) == 0:
				out += "Tautology. All real numbers possible as solution."
				return out
			if len(roots) == 1:
				out += f'Discriminant is zero, the polyunomial has exactly one real root:\n{root_a}'
				return out
		str_r0 = '0' if root_a.real == 0.0 else f'{root_a.real}'
		str_r1 = '0' if root_b.real == 0.0 else f'{root_b.real}'
		if discriminant < 0:
			out += f'Discriminant (delta): {discriminant:.4f}\n'\
				+ 'Discriminant is negative, the polinomial has two distinct complex roots.\n' + \
				f'{str_r0}+{abs(root_a.imag):.5f}i\n{str_r1}-{abs(root_b.imag):.5f}i'
			return out
	except Exception as e:
		print(f'--[{e}]--')
		pdb.set_trace()

#element = integers_perms[0]
#poly_string, poly_roots, poly_discriminant = build_polynomial(element)
#print(poly_string, f'-> delta: {poly_discriminant} -> y =', poly_roots)

args = [a, b, c]
poly_string = build_polynomial(args)
print(poly_string)
#print(interpret_result(poly_roots, poly_discriminant))

