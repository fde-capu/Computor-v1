Computor v1
fde-capu @ 42sp

See `subject.md` for the project instructions.
`tests.sh` tests for exception cases and scrambled inputs.
`permutations.py` tests for factors positive, negative, zero, and empty, in all permutations, for random integers and floats:
```
| a | b | c | Example           |
|---|---|---|-------------------|
| + | + | + | +N*x^2 +N*x^1 +N*x^0 
| + | + | - | +N*x^2 +N*x^1 -N*x^0 
| + | + | 0 | +N*x^2 +N*x^1 0*x^0 
| + | + |   | +N*x^2 +N*x^1 
| + | - | + | +N*x^2 -N*x^1 +N*x^0 
| + | - | - | +N*x^2 -N*x^1 -N*x^0 
| + | - | 0 | +N*x^2 -N*x^1 0*x^0 
| + | - |   | +N*x^2 -N*x^1 
| + | 0 | + | +N*x^2 0*x^1 +N*x^0 
| + | 0 | - | +N*x^2 0*x^1 -N*x^0 
| + | 0 | 0 | +N*x^2 0*x^1 0*x^0 
| + | 0 |   | +N*x^2 0*x^1 
| + |   | + | +N*x^2 +N*x^0 
| + |   | - | +N*x^2 -N*x^0 
| + |   | 0 | +N*x^2 0*x^0 
| + |   |   | +N*x^2 
| - | + | + | -N*x^2 +N*x^1 +N*x^0 
| - | + | - | -N*x^2 +N*x^1 -N*x^0 
| - | + | 0 | -N*x^2 +N*x^1 0*x^0 
| - | + |   | -N*x^2 +N*x^1 
| - | - | + | -N*x^2 -N*x^1 +N*x^0 
| - | - | - | -N*x^2 -N*x^1 -N*x^0 
| - | - | 0 | -N*x^2 -N*x^1 0*x^0 
| - | - |   | -N*x^2 -N*x^1 
| - | 0 | + | -N*x^2 0*x^1 +N*x^0 
| - | 0 | - | -N*x^2 0*x^1 -N*x^0 
| - | 0 | 0 | -N*x^2 0*x^1 0*x^0 
| - | 0 |   | -N*x^2 0*x^1 
| - |   | + | -N*x^2 +N*x^0 
| - |   | - | -N*x^2 -N*x^0 
| - |   | 0 | -N*x^2 0*x^0 
| - |   |   | -N*x^2 
| 0 | + | + | 0*x^2 +N*x^1 +N*x^0 
| 0 | + | - | 0*x^2 +N*x^1 -N*x^0 
| 0 | + | 0 | 0*x^2 +N*x^1 0*x^0 
| 0 | + |   | 0*x^2 +N*x^1 
| 0 | - | + | 0*x^2 -N*x^1 +N*x^0 
| 0 | - | - | 0*x^2 -N*x^1 -N*x^0 
| 0 | - | 0 | 0*x^2 -N*x^1 0*x^0 
| 0 | - |   | 0*x^2 -N*x^1 
| 0 | 0 | + | 0*x^2 0*x^1 +N*x^0 
| 0 | 0 | - | 0*x^2 0*x^1 -N*x^0 
| 0 | 0 | 0 | 0*x^2 0*x^1 0*x^0 
| 0 | 0 |   | 0*x^2 0*x^1 
| 0 |   | + | 0*x^2 +N*x^0 
| 0 |   | - | 0*x^2 -N*x^0 
| 0 |   | 0 | 0*x^2 0*x^0 
| 0 |   |   | 0*x^2 
|   | + | + | +N*x^1 +N*x^0 
|   | + | - | +N*x^1 -N*x^0 
|   | + | 0 | +N*x^1 0*x^0 
|   | + |   | +N*x^1 
|   | - | + | -N*x^1 +N*x^0 
|   | - | - | -N*x^1 -N*x^0 
|   | - | 0 | -N*x^1 0*x^0 
|   | - |   | -N*x^1 
|   | 0 | + | 0*x^1 +N*x^0 
|   | 0 | - | 0*x^1 -N*x^0 
|   | 0 | 0 | 0*x^1 0*x^0 
|   | 0 |   | 0*x^1 
|   |   | + | +N*x^0 
|   |   | - | -N*x^0 
|   |   | 0 | 0*x^0 
|   |   |   | 
```
