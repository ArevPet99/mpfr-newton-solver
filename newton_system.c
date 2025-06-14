#include <stdio.h>
#include <mpfr.h>
#include <stdlib.h>

#define N 2  // Number of variables/equations
#define MAX_ITER 100

// System of equations:
// f1(x,y) = x^2 + y^2 - 4 = 0
// f2(x,y) = x^2 - y - 1 = 0
// Solution should be approximately (1.618, 1.618) and (-1.618, 1.618)

void system_f(mpfr_t f[N], const mpfr_t x[N], mpfr_rnd_t rnd) {
    mpfr_t x2, y2, temp;
    int precision = mpfr_get_prec(x[0]);
    
    mpfr_init2(x2, precision);
    mpfr_init2(y2, precision);
    mpfr_init2(temp, precision);
    
    // f1 = x^2 + y^2 - 4
    mpfr_mul(x2, x[0], x[0], rnd);  // x^2
    mpfr_mul(y2, x[1], x[1], rnd);  // y^2
    mpfr_add(f[0], x2, y2, rnd);    // x^2 + y^2
    mpfr_sub_ui(f[0], f[0], 4, rnd); // x^2 + y^2 - 4
    
    // f2 = x^2 - y - 1
    mpfr_sub(f[1], x2, x[1], rnd);   // x^2 - y
    mpfr_sub_ui(f[1], f[1], 1, rnd); // x^2 - y - 1
    
    mpfr_clear(x2);
    mpfr_clear(y2);
    mpfr_clear(temp);
}

// Jacobian matrix:
// J = [∂f1/∂x  ∂f1/∂y]   [2x   2y]
//     [∂f2/∂x  ∂f2/∂y] = [2x   -1]
void jacobian(mpfr_t J[N][N], const mpfr_t x[N], mpfr_rnd_t rnd) {
    // J[0][0] = 2*x
    mpfr_mul_ui(J[0][0], x[0], 2, rnd);
    
    // J[0][1] = 2*y
    mpfr_mul_ui(J[0][1], x[1], 2, rnd);
    
    // J[1][0] = 2*x
    mpfr_mul_ui(J[1][0], x[0], 2, rnd);
    
    // J[1][1] = -1
    mpfr_set_si(J[1][1], -1, rnd);
}

// Solve 2x2 linear system using Cramer's rule: J * delta = -f
int solve_linear_system_2x2(mpfr_t delta[N], mpfr_t J[N][N], mpfr_t f[N], mpfr_rnd_t rnd) {
    mpfr_t det, temp1, temp2, neg_f0, neg_f1;
    int precision = mpfr_get_prec(f[0]);
    
    mpfr_init2(det, precision);
    mpfr_init2(temp1, precision);
    mpfr_init2(temp2, precision);
    mpfr_init2(neg_f0, precision);
    mpfr_init2(neg_f1, precision);
    
    // Calculate determinant: det = J[0][0]*J[1][1] - J[0][1]*J[1][0]
    mpfr_mul(temp1, J[0][0], J[1][1], rnd);
    mpfr_mul(temp2, J[0][1], J[1][0], rnd);
    mpfr_sub(det, temp1, temp2, rnd);
    
    // Check if determinant is zero
    if (mpfr_zero_p(det)) {
        printf("Singular Jacobian matrix!\n");
        mpfr_clear(det); mpfr_clear(temp1); mpfr_clear(temp2);
        mpfr_clear(neg_f0); mpfr_clear(neg_f1);
        return 0;
    }
    
    // Negate f values for right-hand side
    mpfr_neg(neg_f0, f[0], rnd);
    mpfr_neg(neg_f1, f[1], rnd);
    
    // Solve using Cramer's rule
    // delta[0] = (neg_f0 * J[1][1] - neg_f1 * J[0][1]) / det
    mpfr_mul(temp1, neg_f0, J[1][1], rnd);
    mpfr_mul(temp2, neg_f1, J[0][1], rnd);
    mpfr_sub(temp1, temp1, temp2, rnd);
    mpfr_div(delta[0], temp1, det, rnd);
    
    // delta[1] = (J[0][0] * neg_f1 - J[1][0] * neg_f0) / det
    mpfr_mul(temp1, J[0][0], neg_f1, rnd);
    mpfr_mul(temp2, J[1][0], neg_f0, rnd);
    mpfr_sub(temp1, temp1, temp2, rnd);
    mpfr_div(delta[1], temp1, det, rnd);
    
    mpfr_clear(det); mpfr_clear(temp1); mpfr_clear(temp2);
    mpfr_clear(neg_f0); mpfr_clear(neg_f1);
    return 1;
}

int newton_method_system(mpfr_t x[N], const mpfr_t initial_guess[N], 
                        const mpfr_t tolerance, mpfr_rnd_t rnd) {
    mpfr_t f[N], J[N][N], delta[N], norm, temp;
    int precision = mpfr_get_prec(x[0]);
    
    // Initialize all variables
    for (int i = 0; i < N; i++) {
        mpfr_init2(f[i], precision);
        mpfr_init2(delta[i], precision);
        for (int j = 0; j < N; j++) {
            mpfr_init2(J[i][j], precision);
        }
        mpfr_set(x[i], initial_guess[i], rnd);
    }
    mpfr_init2(norm, precision);
    mpfr_init2(temp, precision);
    
    printf("Newton Method for System of Equations:\n");
    printf("Iter\tx\t\ty\t\tf1(x,y)\t\tf2(x,y)\t\tnorm\n");
    
    for (int iter = 0; iter < MAX_ITER; iter++) {
        // Evaluate function at current point
        system_f(f, x, rnd);
        
        // Calculate norm of f vector
        mpfr_set_ui(norm, 0, rnd);
        for (int i = 0; i < N; i++) {
            mpfr_mul(temp, f[i], f[i], rnd);
            mpfr_add(norm, norm, temp, rnd);
        }
        mpfr_sqrt(norm, norm, rnd);
        
        // Print current iteration
        mpfr_printf("%d\t%.10Rf\t%.10Rf\t%.2Re\t%.2Re\t%.2Re\n", 
                   iter, x[0], x[1], f[0], f[1], norm);
        
        // Check convergence
        if (mpfr_cmp(norm, tolerance) < 0) {
            printf("\nConverged after %d iterations!\n", iter);
            
            // Clean up
            for (int i = 0; i < N; i++) {
                mpfr_clear(f[i]);
                mpfr_clear(delta[i]);
                for (int j = 0; j < N; j++) {
                    mpfr_clear(J[i][j]);
                }
            }
            mpfr_clear(norm);
            mpfr_clear(temp);
            return 1;
        }
        
        // Calculate Jacobian
        jacobian(J, x, rnd);
        
        // Solve linear system J * delta = -f
        if (!solve_linear_system_2x2(delta, J, f, rnd)) {
            printf("Failed to solve linear system!\n");
            
            // Clean up
            for (int i = 0; i < N; i++) {
                mpfr_clear(f[i]);
                mpfr_clear(delta[i]);
                for (int j = 0; j < N; j++) {
                    mpfr_clear(J[i][j]);
                }
            }
            mpfr_clear(norm);
            mpfr_clear(temp);
            return 0;
        }
        
        // Update x: x_new = x_old + delta
        for (int i = 0; i < N; i++) {
            mpfr_add(x[i], x[i], delta[i], rnd);
        }
    }
    
    printf("Failed to converge after %d iterations.\n", MAX_ITER);
    
    // Clean up
    for (int i = 0; i < N; i++) {
        mpfr_clear(f[i]);
        mpfr_clear(delta[i]);
        for (int j = 0; j < N; j++) {
            mpfr_clear(J[i][j]);
        }
    }
    mpfr_clear(norm);
    mpfr_clear(temp);
    return 0;
}

int main() {
    // Set precision to 128 bits
    mpfr_set_default_prec(128);
    
    mpfr_t x[N], initial_guess[N], tolerance;
    
    for (int i = 0; i < N; i++) {
        mpfr_init(x[i]);
        mpfr_init(initial_guess[i]);
    }
    mpfr_init(tolerance);
    
    // Set initial guess: (1.5, 1.5)
    mpfr_set_d(initial_guess[0], 1.5, MPFR_RNDN);
    mpfr_set_d(initial_guess[1], 1.5, MPFR_RNDN);
    
    // Set tolerance
    mpfr_set_str(tolerance, "1e-25", 10, MPFR_RNDN);
    
    printf("Solving system:\n");
    printf("f1(x,y) = x^2 + y^2 - 4 = 0\n");
    printf("f2(x,y) = x^2 - y - 1 = 0\n\n");
    printf("Initial guess: (");
    mpfr_printf("%.10Rf, ", initial_guess[0]);
    mpfr_printf("%.10Rf)\n", initial_guess[1]);
    printf("Tolerance: ");
    mpfr_printf("%.2Re\n\n", tolerance);
    
    if (newton_method_system(x, initial_guess, tolerance, MPFR_RNDN)) {
        printf("\nSolution found:\n");
        printf("x = ");
        mpfr_printf("%.25Rf\n", x[0]);
        printf("y = ");
        mpfr_printf("%.25Rf\n", x[1]);
        
        // Verify the solution
        mpfr_t f_verify[N];
        for (int i = 0; i < N; i++) {
            mpfr_init2(f_verify[i], 128);
        }
        
        system_f(f_verify, x, MPFR_RNDN);
        printf("\nVerification:\n");
        printf("f1(x,y) = ");
        mpfr_printf("%.2Re\n", f_verify[0]);
        printf("f2(x,y) = ");
        mpfr_printf("%.2Re\n", f_verify[1]);
        
        for (int i = 0; i < N; i++) {
            mpfr_clear(f_verify[i]);
        }
    }
    
    // Clean up
    for (int i = 0; i < N; i++) {
        mpfr_clear(x[i]);
        mpfr_clear(initial_guess[i]);
    }
    mpfr_clear(tolerance);
    mpfr_free_cache();
    
    return 0;
} 