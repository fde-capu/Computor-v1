#!/bin/python3

import itertools
import random
import numpy as np

characters = ['+', '-', '0', ' ']
random_max = 100

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

# Print each mapped permutation in a separate line
for perm in integers_perms:
  print(perm)

for perm in floating_perms:
  print(perm)

def build_polynomial(element):
	a = element[0]
	b = element[1]
	c = element[2]
	if a != '?':
		a_sig = '+ ' if a >= 0 else '- '
		a_abs = abs(a)
		a_str = f'{a_sig}{a_abs}x^2 '
	else:
		a_str = ''
		a = 0
	if b != '?':
		b_sig = '+' if b >= 0 else '-'
		b_abs = abs(b)
		b_str = f'{b_sig} {b_abs}x '
	else:
		b_str = ''
		b = 0
	if c != '?':
		c_sig = '+' if c >= 0 else '-'
		c_abs = abs(c)
		c_str = f'{c_sig} {c_abs}'
	else:
		c_str = ''
		c = 0
	f_str = f'{a_str}{b_str}{c_str} = 0'
	f_str = f_str[2:] if f_str.startswith('+ ') else f_str
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


element = integers_perms[0]
poly_string, poly_roots, poly_discriminant = build_polynomial(element)
print(poly_string, f'-> delta: {poly_discriminant} -> y =', poly_roots)

manual = [1, 0, 6]
poly_string, poly_roots, poly_discriminant = build_polynomial(manual)
print(poly_string, f'-> delta: {poly_discriminant} -> y =', poly_roots)

print(interpret_result(poly_roots, poly_discriminant))

