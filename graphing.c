#include <stdio.h>
#include <stdlib.h>

void generate_data() {
    FILE *fptr = fopen("air_quality_data.txt", "w");
    if (fptr == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    // Sample data: CO2 levels and Temperature
    fprintf(fptr, "%d %d # A (Good)\n", 390, 25);  // Sample A
    fprintf(fptr, "%d %d # B (Poor)\n", 410, 30);  // Sample B
    fprintf(fptr, "%d %d # C (Good)\n", 400, 22);  // Sample C
    fprintf(fptr, "%d %d # D (Poor)\n", 420, 28);  // Sample D

    fclose(fptr);
}

void plot_data() {
    FILE *gnuplot = popen("gnuplot -persistent", "w");
    if (gnuplot == NULL) {
        printf("Error opening gnuplot!\n");
        exit(1);
    }

    // Gnuplot commands
    fprintf(gnuplot, "set title 'CO2 Levels vs Temperature'\n");
    fprintf(gnuplot, "set xlabel 'CO2 Levels (ppm)'\n");
    fprintf(gnuplot, "set ylabel 'Temperature (°C)'\n");
    fprintf(gnuplot, "set grid\n");
    fprintf(gnuplot, "set key outside\n");

    // Set y-axis range to match the temperature data
    fprintf(gnuplot, "set yrange [20:35]\n");  // Adjust the range based on the temperature values
    fprintf(gnuplot, "set xrange [385:425]\n"); // Set x-axis range for better view around CO2 levels
    
    // Explicitly set color and line type for the decision boundary
    fprintf(gnuplot, "set style line 1 lt 1 lc rgb '#FF00FF' lw 2\n");

    // Corrected plot command: x-axis is CO2 levels (1st column) and y-axis is temperature (2nd column)
    fprintf(gnuplot, "plot 'air_quality_data.txt' using 1:2:3 with labels point pt 7 offset char 1,1 title 'Data Points', '-' with lines linestyle 1 title 'Decision Boundary (CO2=400)'\n");

    // Data for the vertical line at CO2 = 400
    fprintf(gnuplot, "400 20\n");  // Start at temperature 20
    fprintf(gnuplot, "400 35\n");  // End at temperature 35
    fprintf(gnuplot, "e\n");       // End of data for the line

    pclose(gnuplot);
}

int main() {
    generate_data();
    plot_data();
    return 0;
}
