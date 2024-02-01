#!/bin/python3

import itertools
import random
import numpy as np
import sys

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
	e_a = element[0]
	e_b = element[1]
	e_c = element[2]
	if e_a != '?':
		a_sig = '+ ' if e_a >= 0 else '- '
		a_abs = abs(e_a)
		a_str = f'{a_sig}{a_abs}x^2 '
	else:
		a_str = ''
		e_a = 0
	if e_b != '?':
		b_sig = '+' if e_b >= 0 else '-'
		b_abs = abs(e_b)
		b_str = f'{b_sig} {b_abs}x '
	else:
		b_str = ''
		e_b = 0
	if e_c != '?':
		c_sig = '+' if e_c >= 0 else '-'
		c_abs = abs(e_c)
		c_str = f'{c_sig} {c_abs}'
	else:
		c_str = ''
		e_c = 0
	f_str = f'{a_str}{b_str}{c_str} = 0'
	f_str = f_str[2:] if f_str.startswith('+ ') else f_str
	# Calculate the roots
	discriminant = e_b**2 - 4*e_a*e_c
	if discriminant >= 0:
		root1 = (-e_b + np.sqrt(discriminant)) / (2*e_a)
		root2 = (-e_b - np.sqrt(discriminant)) / (2*e_a)
	else:
		real_part = -e_b / (2*e_a)
		imaginary_part = np.sqrt(-discriminant) / (2*e_a)
		root1 = complex(real_part, imaginary_part)
		root2 = complex(real_part, -imaginary_part)
	return f_str, [root1, root2], discriminant

# Made according to my Computor v1 output
def interpret_result(roots, discriminant):
	if discriminant > 0:
		return f'Discriminant (delta): {discriminant}\n'\
			+ f'Discriminant is strictly positive, the two solutions are:\n{roots[0]}\n{roots[1]}'
	if discriminant == 0:
		if len(roots) == 0:
			return "Tautology. All real numbers possible as solution."
		if len(roots) == 1:
			return f'Discriminant is zero, the polyunomial has exactly one real root:\n{roots[0]}'
	str_r0 = '0' if roots[0].real == 0.0 else f'{roots[0].real}'
	str_r1 = '0' if roots[1].real == 0.0 else f'{roots[1].real}'
	if discriminant < 0:
		return f'Discriminant (delta): {discriminant}\n'\
			+ 'Discriminant is negative, the polinomial has two distinct complex roots.\n' + \
			f'{str_r0}+{abs(roots[0].imag):.5f}i\n{str_r1}-{abs(roots[1].imag):.5f}i'


#element = integers_perms[0]
#poly_string, poly_roots, poly_discriminant = build_polynomial(element)
#print(poly_string, f'-> delta: {poly_discriminant} -> y =', poly_roots)

args = [a, b, c]
poly_string, poly_roots, poly_discriminant = build_polynomial(args)
print(poly_string, f'-> delta: {poly_discriminant} -> y =', poly_roots)
print(interpret_result(poly_roots, poly_discriminant))

