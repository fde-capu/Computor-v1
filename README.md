Computor v1
fde-capu @ 42sp

See `subject.md` for the project instructions.
`tests.sh` tests all possible cases for second degree polynomial equations (listed below).
`permutations.py` tests for factors positive, negative, zero, and empty, in all permutationsr:
```
| a   | b   | c   | Example           |
|-----|-----|-----|-------------------|
| 0   | 0   | 0   | 0x^2 + 0x + 0 = 0 |
| 0   | 0   | ?   | 0x^2 + 0x  = 0    | 
| 0   | ?   | 0   | 0x^2 + 0 = 0      |
| 0   | ?   | ?   | 0 = 0             |
| ?   | 0   | 0   | 0 = 0             |
| ?   | 0   | ?   | 0 = 0             |
| ?   | ?   | 0   | 0 = 0             |
| ?   | ?   | ?   | =                 |
| 0   | 0   | -   | -1 = 0            |
| 0   | 0   | +   | 1 = 0             |
| 0   | -   | 0   | -x = 0            |
| 0   | -   | -   | -x - 1 = 0        |
| 0   | -   | +   | -x + 1 = 0        |
| 0   | +   | 0   | x = 0             |
| 0   | +   | -   | x - 1 = 0         |
| 0   | +   | +   | x + 1 = 0         |
| -   | 0   | 0   | -x^2 = 0          |
| -   | 0   | -   | -x^2 - 1 = 0      |
| -   | 0   | +   | -x^2 + 1 = 0      |
| -   | -   | 0   | -x^2 - x = 0      |
| -   | -   | -   | -x^2 - x - 1 = 0  |
| -   | -   | +   | -x^2 - x + 1 = 0  |
| -   | +   | 0   | -x^2 + x = 0      |
| -   | +   | -   | -x^2 + x - 1 = 0  |
| -   | +   | +   | -x^2 + x + 1 = 0  |
| +   | 0   | 0   | x^2 = 0           |
| +   | 0   | -   | x^2 - 1 = 0       |
| +   | 0   | +   | x^2 + 1 = 0       |
| +   | -   | 0   | x^2 - x = 0       |
| +   | -   | -   | x^2 - x - 1 = 0   |
| +   | -   | +   | x^2 - x + 1 = 0   |
| +   | +   | 0   | x^2 + x = 0       |
| +   | +   | -   | x^2 + x - 1 = 0   |
| +   | +   | +   | x^2 + x + 1 = 0   |
```
`tests.sh` tests for parsing and flux control:
- Scrambled inputs, many forms.
- Optional equality syntax "= 0", "=", and empty.
- Cases of third, forth, or N degree.
Note:
- PRECISION set to 6, to be compatible with the python test.
  (ie. 28x^2+9x: was resulting 1.26629e-13 instead of 0.)
  Still, some tests might fail on the 6th decimal with factor >= 10.
  `for i in {0..100}; do permutations.py || break; done` will probably show that. 
- ANOTHER PRECISION PROBLEM is for too narrow parabole solution.
