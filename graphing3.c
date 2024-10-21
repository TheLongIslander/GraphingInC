#include <stdio.h>
#include <stdlib.h>

void plot_data() {
    FILE *gnuplot = popen("gnuplot -persistent", "w");
    if (gnuplot == NULL) {
        printf("Error opening gnuplot!\n");
        exit(1);
    }

    // Gnuplot commands to set up the plot
    fprintf(gnuplot, "set title 'PDFs of Reflectivity Levels for Different Materials'\n");
    fprintf(gnuplot, "set xlabel 'Reflectivity Level (X)'\n");
    fprintf(gnuplot, "set ylabel 'PDF'\n");
    fprintf(gnuplot, "set grid\n");
    fprintf(gnuplot, "set xrange [0:20]\n");  // Reflectivity range from 0 to 20
    fprintf(gnuplot, "set yrange [0:0.5]\n"); // Set reasonable y-axis range for PDFs
    fprintf(gnuplot, "set key outside\n");

    // Define the probability density function (PDF) for Metal: uniform between 0 and 10
    fprintf(gnuplot, "f_metal(x) = (x >= 0 && x <= 10) ? 1.0/10 : 0\n");

    // Define the probability density function (PDF) for Plastic: uniform between 6 and 11
    fprintf(gnuplot, "f_plastic(x) = (x >= 6 && x <= 11) ? 1.0/5 : 0\n");

    // Define the probability density function (PDF) for Composite: exponential starting at x >= 5
    fprintf(gnuplot, "f_composite(x) = (x >= 5) ? exp(-(x - 5)) : 0\n");

    // Plot the PDFs for metal, plastic, and composite materials with different colors
    fprintf(gnuplot, "plot f_metal(x) title 'Material is Metal' lt rgb 'blue' lw 2, \\\n");
    fprintf(gnuplot, "     f_plastic(x) title 'Material is Plastic' lt rgb 'green' lw 2, \\\n");
    fprintf(gnuplot, "     f_composite(x) title 'Material is Composite' lt rgb 'red' lw 2\n");

    // Close the gnuplot pipe
    pclose(gnuplot);
}

int main() {
    plot_data();
    return 0;
}
