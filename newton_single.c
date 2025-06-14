#include <stdio.h>
#include <mpfr.h>

#define MAX_ITER 100

// Function: f(x) = x^3 - 2*x - 5
void function_f(mpfr_t result, const mpfr_t x, mpfr_rnd_t rnd) {
    mpfr_t x2, x3, temp;
    mpfr_init2(x2, mpfr_get_prec(x));
    mpfr_init2(x3, mpfr_get_prec(x));
    mpfr_init2(temp, mpfr_get_prec(x));
    
    // x^2
    mpfr_mul(x2, x, x, rnd);
    // x^3
    mpfr_mul(x3, x2, x, rnd);
    // 2*x
    mpfr_mul_ui(temp, x, 2, rnd);
    // x^3 - 2*x
    mpfr_sub(result, x3, temp, rnd);
    // x^3 - 2*x - 5
    mpfr_sub_ui(result, result, 5, rnd);
    
    mpfr_clear(x2);
    mpfr_clear(x3);
    mpfr_clear(temp);
}

// Derivative: f'(x) = 3*x^2 - 2
void function_df(mpfr_t result, const mpfr_t x, mpfr_rnd_t rnd) {
    mpfr_t x2;
    mpfr_init2(x2, mpfr_get_prec(x));
    
    // x^2
    mpfr_mul(x2, x, x, rnd);
    // 3*x^2
    mpfr_mul_ui(result, x2, 3, rnd);
    // 3*x^2 - 2
    mpfr_sub_ui(result, result, 2, rnd);
    
    mpfr_clear(x2);
}

int newton_method_single(mpfr_t root, const mpfr_t initial_guess, 
                        const mpfr_t tolerance, mpfr_rnd_t rnd) {
    mpfr_t x_current, x_next, f_val, df_val, abs_diff;
    int precision = mpfr_get_prec(root);
    
    mpfr_init2(x_current, precision);
    mpfr_init2(x_next, precision);
    mpfr_init2(f_val, precision);
    mpfr_init2(df_val, precision);
    mpfr_init2(abs_diff, precision);
    
    mpfr_set(x_current, initial_guess, rnd);
    
    printf("Newton Method Iterations:\n");
    printf("Iter\tx_n\t\t\tf(x_n)\n");
    
    for (int iter = 0; iter < MAX_ITER; iter++) {
        // Calculate f(x_current)
        function_f(f_val, x_current, rnd);
        
        // Print current iteration
        mpfr_printf("%d\t%.15Rf\t%.15Rf\n", iter, x_current, f_val);
        
        // Check if we're close enough to zero
        mpfr_abs(abs_diff, f_val, rnd);
        if (mpfr_cmp(abs_diff, tolerance) < 0) {
            mpfr_set(root, x_current, rnd);
            printf("\nConverged after %d iterations!\n", iter);
            
            mpfr_clear(x_current);
            mpfr_clear(x_next);
            mpfr_clear(f_val);
            mpfr_clear(df_val);
            mpfr_clear(abs_diff);
            return 1; // Success
        }
        
        // Calculate f'(x_current)
        function_df(df_val, x_current, rnd);
        
        // Check if derivative is too small (avoid division by zero)
        mpfr_abs(abs_diff, df_val, rnd);
        if (mpfr_cmp_ui(abs_diff, 0) == 0) {
            printf("Derivative is zero! Cannot continue.\n");
            mpfr_clear(x_current);
            mpfr_clear(x_next);
            mpfr_clear(f_val);
            mpfr_clear(df_val);
            mpfr_clear(abs_diff);
            return 0; // Failure
        }
        
        // Newton step: x_next = x_current - f(x_current) / f'(x_current)
        mpfr_div(abs_diff, f_val, df_val, rnd);
        mpfr_sub(x_next, x_current, abs_diff, rnd);
        
        mpfr_set(x_current, x_next, rnd);
    }
    
    printf("Failed to converge after %d iterations.\n", MAX_ITER);
    mpfr_clear(x_current);
    mpfr_clear(x_next);
    mpfr_clear(f_val);
    mpfr_clear(df_val);
    mpfr_clear(abs_diff);
    return 0; // Failure
}

int main() {
    // Set precision to 128 bits (about 38 decimal digits)
    mpfr_set_default_prec(128);
    
    mpfr_t root, initial_guess, tolerance;
    mpfr_init(root);
    mpfr_init(initial_guess);
    mpfr_init(tolerance);
    
    // Set initial guess to 2.0
    mpfr_set_ui(initial_guess, 2, MPFR_RNDN);
    
    // Set tolerance to 1e-30
    mpfr_set_str(tolerance, "1e-30", 10, MPFR_RNDN);
    
    printf("Solving f(x) = x^3 - 2*x - 5 = 0\n");
    printf("Initial guess: ");
    mpfr_printf("%.15Rf\n", initial_guess);
    printf("Tolerance: ");
    mpfr_printf("%.2Re\n\n", tolerance);
    
    if (newton_method_single(root, initial_guess, tolerance, MPFR_RNDN)) {
        printf("\nRoot found: ");
        mpfr_printf("%.30Rf\n", root);
        
        // Verify the solution
        mpfr_t verification;
        mpfr_init2(verification, 128);
        function_f(verification, root, MPFR_RNDN);
        printf("Verification f(root) = ");
        mpfr_printf("%.2Re\n", verification);
        mpfr_clear(verification);
    }
    
    mpfr_clear(root);
    mpfr_clear(initial_guess);
    mpfr_clear(tolerance);
    mpfr_free_cache();
    
    return 0;
} 