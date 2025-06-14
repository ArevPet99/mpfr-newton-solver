#include <stdio.h>
#include <mpfr.h>
#include <time.h>

void example_basic_operations() {
    printf("=== Basic MPFR Operations ===\n");
    
    // Set precision to 256 bits (about 77 decimal digits)
    mpfr_set_default_prec(256);
    
    mpfr_t a, b, result;
    mpfr_init(a);
    mpfr_init(b);
    mpfr_init(result);
    
    // Set values
    mpfr_set_str(a, "1.23456789012345678901234567890", 10, MPFR_RNDN);
    mpfr_set_str(b, "9.87654321098765432109876543210", 10, MPFR_RNDN);
    
    printf("a = ");
    mpfr_printf("%.30Rf\n", a);
    printf("b = ");
    mpfr_printf("%.30Rf\n", b);
    
    // Addition
    mpfr_add(result, a, b, MPFR_RNDN);
    printf("a + b = ");
    mpfr_printf("%.30Rf\n", result);
    
    // Multiplication
    mpfr_mul(result, a, b, MPFR_RNDN);
    printf("a * b = ");
    mpfr_printf("%.30Rf\n", result);
    
    // Division
    mpfr_div(result, a, b, MPFR_RNDN);
    printf("a / b = ");
    mpfr_printf("%.30Rf\n", result);
    
    // Power
    mpfr_pow_ui(result, a, 10, MPFR_RNDN);
    printf("a^10 = ");
    mpfr_printf("%.30Rf\n", result);
    
    mpfr_clear(a);
    mpfr_clear(b);
    mpfr_clear(result);
    printf("\n");
}

void example_mathematical_functions() {
    printf("=== Mathematical Functions ===\n");
    
    mpfr_set_default_prec(128);
    
    mpfr_t x, result;
    mpfr_init(x);
    mpfr_init(result);
    
    mpfr_set_d(x, 0.5, MPFR_RNDN);
    
    printf("x = ");
    mpfr_printf("%.25Rf\n", x);
    
    // Trigonometric functions
    mpfr_sin(result, x, MPFR_RNDN);
    printf("sin(x) = ");
    mpfr_printf("%.25Rf\n", result);
    
    mpfr_cos(result, x, MPFR_RNDN);
    printf("cos(x) = ");
    mpfr_printf("%.25Rf\n", result);
    
    mpfr_tan(result, x, MPFR_RNDN);
    printf("tan(x) = ");
    mpfr_printf("%.25Rf\n", result);
    
    // Exponential and logarithm
    mpfr_exp(result, x, MPFR_RNDN);
    printf("exp(x) = ");
    mpfr_printf("%.25Rf\n", result);
    
    mpfr_log(result, x, MPFR_RNDN);
    printf("log(x) = ");
    mpfr_printf("%.25Rf\n", result);
    
    // Square root
    mpfr_sqrt(result, x, MPFR_RNDN);
    printf("sqrt(x) = ");
    mpfr_printf("%.25Rf\n", result);
    
    mpfr_clear(x);
    mpfr_clear(result);
    printf("\n");
}

void example_precision_comparison() {
    printf("=== Precision Comparison ===\n");
    
    mpfr_t pi_low, pi_high;
    
    // Low precision (64 bits)
    mpfr_init2(pi_low, 64);
    mpfr_const_pi(pi_low, MPFR_RNDN);
    
    // High precision (512 bits)
    mpfr_init2(pi_high, 512);
    mpfr_const_pi(pi_high, MPFR_RNDN);
    
    printf("Pi with 64-bit precision:  ");
    mpfr_printf("%.20Rf\n", pi_low);
    
    printf("Pi with 512-bit precision: ");
    mpfr_printf("%.50Rf\n", pi_high);
    
    mpfr_clear(pi_low);
    mpfr_clear(pi_high);
    printf("\n");
}

void example_rounding_modes() {
    printf("=== Rounding Modes ===\n");
    
    mpfr_set_default_prec(64);
    
    mpfr_t a, b, result;
    mpfr_init(a);
    mpfr_init(b);
    mpfr_init(result);
    
    mpfr_set_str(a, "1.0", 10, MPFR_RNDN);
    mpfr_set_str(b, "3.0", 10, MPFR_RNDN);
    
    printf("Computing 1/3 with different rounding modes:\n");
    
    // Round to nearest
    mpfr_div(result, a, b, MPFR_RNDN);
    printf("MPFR_RNDN (nearest): ");
    mpfr_printf("%.20Rf\n", result);
    
    // Round toward zero
    mpfr_div(result, a, b, MPFR_RNDZ);
    printf("MPFR_RNDZ (toward 0): ");
    mpfr_printf("%.20Rf\n", result);
    
    // Round toward +infinity
    mpfr_div(result, a, b, MPFR_RNDU);
    printf("MPFR_RNDU (toward +∞): ");
    mpfr_printf("%.20Rf\n", result);
    
    // Round toward -infinity
    mpfr_div(result, a, b, MPFR_RNDD);
    printf("MPFR_RNDD (toward -∞): ");
    mpfr_printf("%.20Rf\n", result);
    
    mpfr_clear(a);
    mpfr_clear(b);
    mpfr_clear(result);
    printf("\n");
}

void example_special_values() {
    printf("=== Special Values ===\n");
    
    mpfr_t x, result;
    mpfr_init(x);
    mpfr_init(result);
    
    // Infinity
    mpfr_set_inf(x, 1);  // +infinity
    printf("x = +infinity: ");
    mpfr_printf("%.10Rf\n", x);
    
    mpfr_set_inf(x, -1); // -infinity
    printf("x = -infinity: ");
    mpfr_printf("%.10Rf\n", x);
    
    // NaN (Not a Number)
    mpfr_set_nan(x);
    printf("x = NaN: ");
    mpfr_printf("%.10Rf\n", x);
    
    // Zero
    mpfr_set_zero(x, 1);  // +0
    printf("x = +0: ");
    mpfr_printf("%.10Rf\n", x);
    
    mpfr_set_zero(x, -1); // -0
    printf("x = -0: ");
    mpfr_printf("%.10Rf\n", x);
    
    // Testing special values
    mpfr_set_d(x, 0.0, MPFR_RNDN);
    mpfr_log(result, x, MPFR_RNDN);  // log(0) = -infinity
    printf("log(0) = ");
    mpfr_printf("%.10Rf\n", result);
    
    mpfr_set_d(x, -1.0, MPFR_RNDN);
    mpfr_sqrt(result, x, MPFR_RNDN); // sqrt(-1) = NaN
    printf("sqrt(-1) = ");
    mpfr_printf("%.10Rf\n", result);
    
    mpfr_clear(x);
    mpfr_clear(result);
    printf("\n");
}

void example_performance_timing() {
    printf("=== Performance Timing ===\n");
    
    const int iterations = 10000;
    clock_t start, end;
    
    mpfr_set_default_prec(256);
    
    mpfr_t a, b, result;
    mpfr_init(a);
    mpfr_init(b);
    mpfr_init(result);
    
    mpfr_set_str(a, "1.23456789", 10, MPFR_RNDN);
    mpfr_set_str(b, "9.87654321", 10, MPFR_RNDN);
    
    // Time multiplication
    start = clock();
    for (int i = 0; i < iterations; i++) {
        mpfr_mul(result, a, b, MPFR_RNDN);
    }
    end = clock();
    
    double time_mul = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time for %d multiplications: %.6f seconds\n", iterations, time_mul);
    
    // Time division
    start = clock();
    for (int i = 0; i < iterations; i++) {
        mpfr_div(result, a, b, MPFR_RNDN);
    }
    end = clock();
    
    double time_div = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time for %d divisions: %.6f seconds\n", iterations, time_div);
    
    // Time square root
    start = clock();
    for (int i = 0; i < iterations; i++) {
        mpfr_sqrt(result, a, MPFR_RNDN);
    }
    end = clock();
    
    double time_sqrt = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time for %d square roots: %.6f seconds\n", iterations, time_sqrt);
    
    mpfr_clear(a);
    mpfr_clear(b);
    mpfr_clear(result);
    printf("\n");
}

int main() {
    printf("MPFR (Multiple Precision Floating-Point Reliable) Examples\n");
    printf("=========================================================\n\n");
    
    example_basic_operations();
    example_mathematical_functions();
    example_precision_comparison();
    example_rounding_modes();
    example_special_values();
    example_performance_timing();
    
    // Clean up MPFR caches
    mpfr_free_cache();
    
    return 0;
} 