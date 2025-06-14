# MPFR-based Newton Method Solvers

This project contains high-precision Newton method implementations using MPFR (Multiple Precision Floating-Point Reliable) library.

## Project Location
This project is located at: `~/mpfr-newton-solver/`

## Files Overview

### Core Programs
- **`newton_single.c`** - Single-variable Newton method solver
- **`newton_system.c`** - Multi-variable Newton method solver for systems of equations
- **`mpfr_examples.c`** - Comprehensive MPFR library examples and demonstrations

### Build System
- **`Makefile`** - Build configuration for all programs
- **`README.md`** - This documentation file

## Prerequisites

### macOS
```bash
brew install gmp mpfr
```

### Ubuntu/Debian
```bash
sudo apt-get install libgmp-dev libmpfr-dev
```

## Quick Start

```bash
cd ~/Desktop/mpfr-newton-solver
make all          # Build all programs
./newton_single   # Run single-variable Newton solver
./newton_system   # Run system Newton solver
./mpfr_examples   # Run MPFR library examples
```

## Building

```bash
make all          # Build all programs
make clean        # Clean build artifacts
make test         # Build and run all programs
```

## Program Details

### 1. Single Variable Newton Method (`newton_single`)

**Purpose:** Finds roots of single-variable equations using Newton's method.

**Example equation:** f(x) = x³ - 2x - 5 = 0

**Algorithm:**
```
x_{n+1} = x_n - f(x_n) / f'(x_n)
```

**Features:**
- 128-bit precision (≈38 decimal digits)
- Convergence tolerance: 1×10⁻³⁰
- Automatic derivative calculation
- Iteration tracking and verification

**Usage:**
```bash
./newton_single
```

**Expected Output:**
```
Solving f(x) = x^3 - 2*x - 5 = 0
Initial guess: 2.000000000000000
Tolerance: 1.0e-30

Newton Method Iterations:
Iter    x_n                     f(x_n)
0       2.000000000000000       -1.000000000000000
1       2.200000000000000       0.048000000000000
...
Converged after N iterations!

Root found: 2.0945514815423265914285714...
```

### 2. System Newton Method (`newton_system`)

**Purpose:** Solves systems of nonlinear equations using multi-variable Newton's method.

**Example system:**
- f₁(x,y) = x² + y² - 4 = 0
- f₂(x,y) = x² - y - 1 = 0

**Algorithm:**
```
x_{n+1} = x_n - J⁻¹(x_n) × F(x_n)
```
where J is the Jacobian matrix.

**Features:**
- 128-bit precision
- 2×2 system solver using Cramer's rule
- Jacobian matrix calculation
- Vector norm convergence checking

**Usage:**
```bash
./newton_system
```

### 3. MPFR Examples (`mpfr_examples`)

**Purpose:** Demonstrates various MPFR library features and capabilities.

**Sections:**
1. **Basic Operations** - Addition, multiplication, division, powers
2. **Mathematical Functions** - Trigonometric, exponential, logarithmic
3. **Precision Comparison** - Different precision levels
4. **Rounding Modes** - Various rounding strategies
5. **Special Values** - Infinity, NaN, signed zeros
6. **Performance Timing** - Benchmarking operations

**Usage:**
```bash
./mpfr_examples
```

## Key MPFR Concepts

### 1. Precision Management
```c
mpfr_set_default_prec(256);  // Set default precision to 256 bits
mpfr_init2(x, 128);          // Initialize with specific precision
```

### 2. Rounding Modes
- `MPFR_RNDN` - Round to nearest (default)
- `MPFR_RNDZ` - Round toward zero
- `MPFR_RNDU` - Round toward +∞
- `MPFR_RNDD` - Round toward -∞

### 3. Memory Management
```c
mpfr_init(x);     // Initialize variable
mpfr_clear(x);    // Free memory
mpfr_cleanup();   // Clean up global caches
```

### 4. Input/Output
```c
mpfr_set_str(x, "1.23456789", 10, MPFR_RNDN);  // Set from string
mpfr_printf("%.25Rf\n", x);                     // Print with precision
```

## Mathematical Background

### Newton's Method (Single Variable)
For finding roots of f(x) = 0:
1. Start with initial guess x₀
2. Iterate: x_{n+1} = x_n - f(x_n)/f'(x_n)
3. Stop when |f(x_n)| < tolerance

### Newton's Method (Multi-Variable)
For solving F(x) = 0 where F: ℝⁿ → ℝⁿ:
1. Start with initial guess x₀
2. Solve: J(x_n) × Δx = -F(x_n)
3. Update: x_{n+1} = x_n + Δx
4. Stop when ||F(x_n)|| < tolerance

Where J(x) is the Jacobian matrix:
```
J_ij = ∂F_i/∂x_j
```

## Performance Considerations

### Precision vs Speed
- Higher precision = slower computation
- Choose precision based on requirements
- 64-bit: ~19 decimal digits, fast
- 128-bit: ~38 decimal digits, moderate
- 256-bit: ~77 decimal digits, slower

### Memory Usage
- Each MPFR variable uses precision-dependent memory
- Always call `mpfr_clear()` to avoid memory leaks
- Use `mpfr_free_cache()` to clean global caches

## Extending the Code

### Adding New Functions
1. Define function and its derivatives
2. Implement evaluation functions
3. Modify the Newton iteration loop
4. Add convergence criteria

### Supporting Larger Systems
1. Generalize matrix operations
2. Implement LU decomposition or other solvers
3. Add pivoting for numerical stability

### Custom Precision
```c
// Set very high precision (1000 bits ≈ 300 decimal digits)
mpfr_set_default_prec(1000);
```

## Troubleshooting

### Common Issues
1. **Compilation errors:** Ensure GMP and MPFR are installed
2. **Slow convergence:** Try different initial guesses
3. **No convergence:** Check if function has roots in the search region
4. **Memory leaks:** Always pair `mpfr_init()` with `mpfr_clear()`

### Debugging Tips
- Print intermediate values to track convergence
- Verify derivatives analytically
- Check for singular Jacobian matrices
- Use different rounding modes for comparison

## References

1. [MPFR Documentation](https://www.mpfr.org/mpfr-current/mpfr.html)
2. [GMP Documentation](https://gmplib.org/manual/)
3. Numerical Methods textbooks for Newton's method theory
4. IEEE 754 standard for floating-point arithmetic

## License

This code is provided for educational purposes. Feel free to modify and distribute. 
