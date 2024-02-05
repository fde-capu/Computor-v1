Computor v1
fde-capu @ 42sp

See `subject.md` for the project instructions.
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
`tests.sh` tests for exception cases:
- Scrambled inputs, many forms.
- Optional equality syntax "= 0", "=", and empty.
- Cases of third, forth, or N degree.

Note:
- PRECISION set to 6, to be compatible with the python test.
  Still, some tests might fail on the 6th or even 7th decimal
  (ie. `0.1 1.3 0`, and `0.1 1.2 0`).
