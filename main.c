#include <stdio.h>
#include <math.h>

typedef struct s_complex
{
	double real;
	double imaginary;
} t_complex;

typedef struct s_fractol
{
	int fractal_type;   // 0 = Mandelbrot, 1 = Julia
	int max_iter;       // Maximum iterations for fractal calculations
	t_complex c_julia;  // Julia set constant (only used if fractal_type == 1)
} t_fractol;

t_complex complex_square(t_complex num)
{
	t_complex result;
	result.real = num.real * num.real - num.imaginary * num.imaginary;
	result.imaginary = 2 * num.imaginary * num.real;
	return result;
}

t_complex complex_add(t_complex num1, t_complex num2)
{
	t_complex result;
	result.real = num1.real + num2.real;
	result.imaginary = num1.imaginary + num2.imaginary;
	return result;
}

int fractal_suite(t_complex value, t_fractol *fractol)
{
    t_complex z;  // We'll use z as the variable in the iteration
    t_complex c;  // And c as the constant
    int i;
    
    // Initialize z and c based on fractal type
    if (fractol->fractal_type == 0)  // Mandelbrot
    {
		z = value;
        c = value;  // For Mandelbrot, c is the input point
    }
    else  // Julia
    {
        z = value;  // For Julia, z starts as the input point
        c = fractol->c_julia;  // And c is the Julia constant
    }
    
    i = 0;
    while (i < fractol->max_iter)
    {
        // Calculate z = z² + c
        printf("z%i point (%.3f , %.3f i) \n",i, z.real, z.imaginary);
        z = complex_add(complex_square(z), c);
        // Check if |z| > 2 (escape condition)
        if ((z.real * z.real + z.imaginary * z.imaginary) > 4.0)
            return i;
            
        i++;
    }
    
    return -1;  // Didn't escape within max iterations
}

void test_mandelbrot()
{
    t_complex point;
    int result;
    t_fractol fractol;
    
    fractol.fractal_type = 0;  // Mandelbrot
    fractol.max_iter = 1000;
    
    // Test 1: Point at origin (0,0) - should be in the set
    point.real = 0.0;
    point.imaginary = 0.0;
    result = fractal_suite(point, &fractol);
    printf("Mandelbrot Test 1: Point (%.2f, %.2f) - Result: %d (Expected: -1)\n", 
           point.real, point.imaginary, result);
    
    // Test 2: Point at (2,0) - definitely outside the set
    point.real = 2.0;
    point.imaginary = 0.0;
    result = fractal_suite(point, &fractol);
    printf("Mandelbrot Test 2: Point (%.2f, %.2f) - Result: %d (Expected: small value, not -1)\n", 
           point.real, point.imaginary, result);
    
    // Test 3: Point at (-2,0) - on the edge of the set
    point.real = -2.0;
    point.imaginary = 0.0;
    result = fractal_suite(point, &fractol);
    printf("Mandelbrot Test 3: Point (%.2f, %.2f) - Result: %d (Expected: value near max_iter or -1)\n", 
           point.real, point.imaginary, result);
    
    // Test 4: Point at (-1,0) - should be in the set
    point.real = -1.0;
    point.imaginary = 0.0;
    result = fractal_suite(point, &fractol);
    printf("Mandelbrot Test 4: Point (%.2f, %.2f) - Result: %d (Expected: -1)\n", 
           point.real, point.imaginary, result);
    
    // Test 5: Point at (0.25,0.5) - close to the boundary
    point.real = 0.25;
    point.imaginary = 0.5;
    result = fractal_suite(point, &fractol);
    printf("Mandelbrot Test 5: Point (%.2f, %.2f) - Result: %d\n", 
           point.real, point.imaginary, result);
	point.real = -0.7435669;
	point.imaginary = 0.1314023;
	result = fractal_suite(point, &fractol);
	printf("Mandelbrot Test 6: Point (%.7f, %.7f) - Result: %d (Expected: ~150)\n", 
		point.real, point.imaginary, result);

	// Test 7: Another point near boundary with escape around 150
	point.real = -0.7565466;
	point.imaginary = -0.0780691;
	result = fractal_suite(point, &fractol);
	printf("Mandelbrot Test 7: Point (%.7f, %.7f) - Result: %d (Expected: ~150)\n", 
		point.real, point.imaginary, result);

	// Test 8: Point near the needle-like formation
	point.real = -1.2956713;
	point.imaginary = 0.0103617;
	result = fractal_suite(point, &fractol);
	printf("Mandelbrot Test 8: Point (%.7f, %.7f) - Result: %d (Expected: ~150)\n", 
		point.real, point.imaginary, result);

	// Test 9: Point near the main cardioid boundary
	point.real = -0.1132351;
	point.imaginary = 0.7923312;
	result = fractal_suite(point, &fractol);
	printf("Mandelbrot Test 9: Point (%.7f, %.7f) - Result: %d (Expected: ~150)\n", 
		point.real, point.imaginary, result);
	point.real = -0.755;
	point.imaginary = 0.1;
	result = fractal_suite(point, &fractol);
	printf("Mandelbrot Test 6 (Revised): Point (%.3f, %.3f) - Result: %d (Expected: ~100-150)\n", 
		point.real, point.imaginary, result);

	// Test 7 (revised): Should escape around 150-200 iterations
	point.real = -0.749;
	point.imaginary = 0.125;
	result = fractal_suite(point, &fractol);
	printf("Mandelbrot Test 7 (Revised): Point (%.3f, %.3f) - Result: %d (Expected: ~150-200)\n", 
		point.real, point.imaginary, result);

	// Test 8 (revised): Should definitely escape (not stay in the set)
	point.real = -0.74;
	point.imaginary = -0.14;
	result = fractal_suite(point, &fractol);
	printf("Mandelbrot Test 8 (Revised): Point (%.3f, %.3f) - Result: %d (Expected: 20 -40)\n", 
		point.real, point.imaginary, result);
}

// Function to test Julia setund another point to test with. The image you shared is from a Mandelbrot set 
void test_julia()
{
    t_fractol fractol;
    t_complex point;
    int result;
    
    fractol.fractal_type = 1;  // Julia
    fractol.max_iter = 1000;
    
    // Common Julia set parameter: c = -0.7 + 0.27015i
    fractol.c_julia.real = -0.7;
    fractol.c_julia.imaginary = 0.27015;
    
    // Test 1: Point at origin (0,0)
    point.real = 0.0;
    point.imaginary = 0.0;
    result = fractal_suite(point, &fractol);
    printf("Julia Test 1: Point (%.2f, %.2f) with c=(%.5f, %.5f) - Result: %d\n", 
           point.real, point.imaginary, fractol.c_julia.real, fractol.c_julia.imaginary, result);
    
    // Test 2: Point at (0.5,0.5)
    point.real = 0.5;
    point.imaginary = 0.5;
    result = fractal_suite(point, &fractol);
    printf("Julia Test 2: Point (%.2f, %.2f) with c=(%.5f, %.5f) - Result: %d\n", 
           point.real, point.imaginary, fractol.c_julia.real, fractol.c_julia.imaginary, result);
    
    // Test 3: Point quite far from the origin - should escape quickly
    point.real = 2.0;
    point.imaginary = 2.0;
    result = fractal_suite(point, &fractol);
    printf("Julia Test 3: Point (%.2f, %.2f) with c=(%.5f, %.5f) - Result: %d (Expected: small value, not -1)\n", 
           point.real, point.imaginary, fractol.c_julia.real, fractol.c_julia.imaginary, result);
    
    // Try another Julia set parameter: c = 0.285 + 0.01i
    fractol.c_julia.real = 0.285;
    fractol.c_julia.imaginary = 0.01;
    
    // Test 4: Point at origin with different c
    point.real = 0.0;
    point.imaginary = 0.0;
    result = fractal_suite(point, &fractol);
    printf("Julia Test 4: Point (%.2f, %.2f) with c=(%.5f, %.5f) - Result: %d\n", 
           point.real, point.imaginary, fractol.c_julia.real, fractol.c_julia.imaginary, result);
}

int main()
{
    printf("Testing Mandelbrot set calculations:\n");
    printf("-----------------------------------\n");
	t_complex point;
    t_fractol fractol;
    fractol.fractal_type = 0;  // Mandelbrot
    fractol.max_iter = 500;

	point.real = -0.0;
    point.imaginary = -0.650000;
	fractal_suite(point, &fractol);


    // test_mandelbrot();
    
    // printf("\nTesting Julia set calculations:\n");
    // printf("----------------------------\n");
    // test_julia();
    
    return 0;
}

