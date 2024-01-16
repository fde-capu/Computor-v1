See `subject.md` for the project instructions.
`tests.sh` tests all possible cases for second degree polinomial equations (listed below).
```
| a   | b   | c   | Example           | Explanation |
|-----|-----|-----|-------------------|-------------|
| 0   | 0   | 0   | 0 = 0             | All real numbers are solutions because the equation is always true regardless of the value of x. |
| 0   | 0   | -   | -1 = 0            | The equation has no solution. |
| 0   | 0   | +   | 1 = 0             | The equation has no solution. |
| 0   | -   | 0   | -x = 0            | The equation has one solution: x = 0. |
| 0   | -   | -   | -x - 1 = 0        | The equation is a first degree equation. It has one solution: x = -1. |
| 0   | -   | +   | -x + 1 = 0        | The equation is a first degree equation. It has one solution: x = 1. |
| 0   | +   | 0   | x = 0             | The equation has one solution: x = 0. |
| 0   | +   | -   | x - 1 = 0         | The equation is a first degree equation. It has one solution: x = 1. |
| 0   | +   | +   | x + 1 = 0         | The equation is a first degree equation. It has one solution: x = -1. |
| -   | 0   | 0   | -x^2 = 0          | The equation has one solution: x = 0. |
| -   | 0   | -   | -x^2 - 1 = 0      | The equation can be factored to (-x + 1)*(-x - 1) = 0. It has two solutions: x = 1 and x = -1. |
| -   | 0   | +   | -x^2 + 1 = 0      | No real number can be squared to get a negative number, so there are no real solutions. However, there are two complex solutions: x = i and x = -i. |
| -   | -   | 0   | -x^2 - x = 0      | The equation can be factored to x*(-x - 1) = 0. It has two solutions: x = 0 and x = -1. |
| -   | -   | -   | -x^2 - x - 1 = 0  | The discriminant is (-1)^2 - 4*(-1)*(-1) = -3, which is less than zero. The equation has two complex solutions: x = 0.5 + sqrt(3)i/2 and x = 0.5 - sqrt(3)i/2. |
| -   | -   | +   | -x^2 - x + 1 = 0  | The discriminant is (-1)^2 - 4*(-1)*1 = 5, which is greater than zero. The equation has two real solutions: x = [1 + sqrt(5)]/2 and x = [1 - sqrt(5)]/2. |
| -   | +   | 0   | -x^2 + x = 0      | The equation can be factored to x*(-x + 1) = 0. It has two solutions: x = 0 and x = 1. |
| -   | +   | -   | -x^2 + x - 1 = 0  | The discriminant is 1^2 - 4*(-1)*(-1) = -3, which is less than zero. The equation has two complex solutions: x = 0.5 + sqrt(3)i/2 and x = 0.5 - sqrt(3)i/2. |
| -   | +   | +   | -x^2 + x + 1 = 0  | The discriminant is 1^2 - 4*(-1)*1 = 5, which is greater than zero. The equation has two real solutions: x = [-1 + sqrt(5)]/2 and x = [-1 - sqrt(5)]/2. |
| +   | 0   | 0   | x^2 = 0           | The equation has one solution: x = 0. |
| +   | 0   | -   | x^2 - 1 = 0       | The equation can be factored to (x + 1)*(x - 1) = 0. It has two solutions: x = 1 and x = -1. |
| +   | 0   | +   | x^2 + 1 = 0       | No real number can be squared to get a negative number, so there are no real solutions. However, there are two complex solutions: x = i and x = -i. |
| +   | -   | 0   | x^2 - x = 0       | The equation can be factored to x*(x - 1) = 0. It has two solutions: x = 0 and x = 1. |
| +   | -   | -   | x^2 - x - 1 = 0   | The discriminant is (-1)^2 - 4*1*(-1) = 5, which is greater than zero. The equation has two real solutions: x = [1 + sqrt(5)]/2 and x = [1 - sqrt(5)]/2. |
| +   | -   | +   | x^2 - x + 1 = 0   | The discriminant is (-1)^2 - 4*1*1 = -3, which is less than zero. The equation has two complex solutions: x = 0.5 + sqrt(3)i/2 and x = 0.5 - sqrt(3)i/2. |
| +   | +   | 0   | x^2 + x = 0       | The equation can be factored to x*(x + 1) = 0. It has two solutions: x = 0 and x = -1. |
| +   | +   | -   | x^2 + x - 1 = 0   | The discriminant is 1^2 - 4*1*(-1) = 5, which is greater than zero. The equation has two real solutions: x = [-1 + sqrt(5)]/2 and x = [-1 - sqrt(5)]/2. |
| +   | +   | +   | x^2 + x + 1 = 0   | The discriminant is 1^2 - 4*1*1 = -3, which is less than zero. The equation has two complex solutions: x = -0.5 + sqrt(3)i/2 and x = -0.5 - sqrt(3)i/2. |
```
Also, tests:
- Floating point numbers for all cases of integers above.
- Ommiting the term for all cases when the term is 0 above.
```
| a   | b   | c   | Example           | Explanation |
|-----|-----|-----|-------------------|-------------|
| 0   | 0   | 0   | 0x^2 + 0x + 0 = 0 | All real numbers are solutions because the equation is always true regardless of the value of x. |
| 0   | 0   | ?   | 0x^2 + 0x  = 0             | All real numbers are solutions because the equation is always true regardless of the value of x. |
| 0   | ?   | 0   | 0x^2 + 0 = 0             | All real numbers are solutions because the equation is always true regardless of the value of x. |
| 0   | ?   | ?   | 0 = 0             | All real numbers are solutions because the equation is always true regardless of the value of x. |
| ?   | 0   | 0   | 0 = 0             | All real numbers are solutions because the equation is always true regardless of the value of x. |
| ?   | 0   | ?   | 0 = 0             | All real numbers are solutions because the equation is always true regardless of the value of x. |
| ?   | ?   | 0   | 0 = 0             | All real numbers are solutions because the equation is always true regardless of the value of x. |
| ?   | ?   | ?   | =                 | All real numbers are solutions because the equation is always true regardless of the value of x. |
| 0   | 0   | -   | -1 = 0            | The equation has no solution. |
| 0   | 0   | +   | 1 = 0             | The equation has no solution. |
| 0   | -   | 0   | -x = 0            | The equation has one solution: x = 0. |
| 0   | -   | -   | -x - 1 = 0        | The equation is a first degree equation. It has one solution: x = -1. |
| 0   | -   | +   | -x + 1 = 0        | The equation is a first degree equation. It has one solution: x = 1. |
| 0   | +   | 0   | x = 0             | The equation has one solution: x = 0. |
| 0   | +   | -   | x - 1 = 0         | The equation is a first degree equation. It has one solution: x = 1. |
| 0   | +   | +   | x + 1 = 0         | The equation is a first degree equation. It has one solution: x = -1. |
| -   | 0   | 0   | -x^2 = 0          | The equation has one solution: x = 0. |
| -   | 0   | -   | -x^2 - 1 = 0      | The equation can be factored to (-x + 1)*(-x - 1) = 0. It has two solutions: x = 1 and x = -1. |
| -   | 0   | +   | -x^2 + 1 = 0      | No real number can be squared to get a negative number, so there are no real solutions. However, there are two complex solutions: x = i and x = -i. |
| -   | -   | 0   | -x^2 - x = 0      | The equation can be factored to x*(-x - 1) = 0. It has two solutions: x = 0 and x = -1. |
| -   | -   | -   | -x^2 - x - 1 = 0  | The discriminant is (-1)^2 - 4*(-1)*(-1) = -3, which is less than zero. The equation has two complex solutions: x = 0.5 + sqrt(3)i/2 and x = 0.5 - sqrt(3)i/2. |
| -   | -   | +   | -x^2 - x + 1 = 0  | The discriminant is (-1)^2 - 4*(-1)*1 = 5, which is greater than zero. The equation has two real solutions: x = [1 + sqrt(5)]/2 and x = [1 - sqrt(5)]/2. |
| -   | +   | 0   | -x^2 + x = 0      | The equation can be factored to x*(-x + 1) = 0. It has two solutions: x = 0 and x = 1. |
| -   | +   | -   | -x^2 + x - 1 = 0  | The discriminant is 1^2 - 4*(-1)*(-1) = -3, which is less than zero. The equation has two complex solutions: x = 0.5 + sqrt(3)i/2 and x = 0.5 - sqrt(3)i/2. |
| -   | +   | +   | -x^2 + x + 1 = 0  | The discriminant is 1^2 - 4*(-1)*1 = 5, which is greater than zero. The equation has two real solutions: x = [-1 + sqrt(5)]/2 and x = [-1 - sqrt(5)]/2. |
| +   | 0   | 0   | x^2 = 0           | The equation has one solution: x = 0. |
| +   | 0   | -   | x^2 - 1 = 0       | The equation can be factored to (x + 1)*(x - 1) = 0. It has two solutions: x = 1 and x = -1. |
| +   | 0   | +   | x^2 + 1 = 0       | No real number can be squared to get a negative number, so there are no real solutions. However, there are two complex solutions: x = i and x = -i. |
| +   | -   | 0   | x^2 - x = 0       | The equation can be factored to x*(x - 1) = 0. It has two solutions: x = 0 and x = 1. |
| +   | -   | -   | x^2 - x - 1 = 0   | The discriminant is (-1)^2 - 4*1*(-1) = 5, which is greater than zero. The equation has two real solutions: x = [1 + sqrt(5)]/2 and x = [1 - sqrt(5)]/2. |
| +   | -   | +   | x^2 - x + 1 = 0   | The discriminant is (-1)^2 - 4*1*1 = -3, which is less than zero. The equation has two complex solutions: x = 0.5 + sqrt(3)i/2 and x = 0.5 - sqrt(3)i/2. |
| +   | +   | 0   | x^2 + x = 0       | The equation can be factored to x*(x + 1) = 0. It has two solutions: x = 0 and x = -1. |
| +   | +   | -   | x^2 + x - 1 = 0   | The discriminant is 1^2 - 4*1*(-1) = 5, which is greater than zero. The equation has two real solutions: x = [-1 + sqrt(5)]/2 and x = [-1 - sqrt(5)]/2. |
| +   | +   | +   | x^2 + x + 1 = 0   | The discriminant is 1^2 - 4*1*1 = -3, which is less than zero. The equation has two complex solutions: x = -0.5 + sqrt(3)i/2 and x = -0.5 - sqrt(3)i/2. |
```
- Some cases of third and forth degree, to show the program complaining.
- Ending with "= 0", only "=", and without any "=" statement.
- Ommiting and passing the "1" in place.
- All sequence of terms:
	abc, acb, bac, bca, cab, cba.
- Repetition of all terms:
a,b,c,a
a,b,a,c
a,c,b,a
a,c,a,b
a,a,b,c
a,a,c,b
b,a,c,a
b,a,a,c
b,c,a,a
c,a,b,a
c,a,a,b
c,b,a,a
a,b,c,b
a,b,b,c
a,c,b,b
b,a,c,b
b,a,b,c
b,c,a,b
b,c,b,a
b,b,a,c
b,b,c,a
c,a,b,b
c,b,a,b
c,b,b,a
a,b,c,c
a,c,b,c
a,c,c,b
b,a,c,c
b,c,a,c
b,c,c,a
c,a,b,c
c,a,c,b
c,b,a,c
c,b,c,a
c,c,a,b
c,c,b,a
a,b,c,a,b
a,b,c,b,a
a,b,a,c,b
a,b,a,b,c
a,b,b,c,a
a,b,b,a,c
a,c,b,a,b
a,c,b,b,a
a,c,a,b,b
a,a,b,c,b
a,a,b,b,c
a,a,c,b,b
b,a,c,a,b
b,a,c,b,a
b,a,a,c,b
b,a,a,b,c
b,a,b,c,a
b,a,b,a,c
b,c,a,a,b
b,c,a,b,a
b,c,b,a,a
b,b,a,c,a
b,b,a,a,c
b,b,c,a,a
c,a,b,a,b
c,a,b,b,a
c,a,a,b,b
c,b,a,a,b
c,b,a,b,a
c,b,b,a,a
a,b,c,a,c
a,b,c,c,a
a,b,a,c,c
a,c,b,a,c
a,c,b,c,a
a,c,a,b,c
a,c,a,c,b
a,c,c,b,a
a,c,c,a,b
a,a,b,c,c
a,a,c,b,c
a,a,c,c,b
b,a,c,a,c
b,a,c,c,a
b,a,a,c,c
b,c,a,a,c
b,c,a,c,a
b,c,c,a,a
c,a,b,a,c
c,a,b,c,a
c,a,a,b,c
c,a,a,c,b
c,a,c,b,a
c,a,c,a,b
c,b,a,a,c
c,b,a,c,a
c,b,c,a,a
c,c,a,b,a
c,c,a,a,b
c,c,b,a,a
a,b,c,b,c
a,b,c,c,b
a,b,b,c,c
a,c,b,b,c
a,c,b,c,b
a,c,c,b,b
b,a,c,b,c
b,a,c,c,b
b,a,b,c,c
b,c,a,b,c
b,c,a,c,b
b,c,b,a,c
b,c,b,c,a
b,c,c,a,b
b,c,c,b,a
b,b,a,c,c
b,b,c,a,c
b,b,c,c,a
c,a,b,b,c
c,a,b,c,b
c,a,c,b,b
c,b,a,b,c
c,b,a,c,b
c,b,b,a,c
c,b,b,c,a
c,b,c,a,b
c,b,c,b,a
c,c,a,b,b
c,c,b,a,b
c,c,b,b,a


- Some random cases of messy syntax, to test the parser.
