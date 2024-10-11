#include <stdio.h>
#include <stdlib.h>

void generate_data() {
    FILE *fptr = fopen("ml_decision_data.txt", "w");
    if (fptr == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    fclose(fptr);
}

void plot_data() {
    FILE *gnuplot = popen("gnuplot -persistent", "w");
    if (gnuplot == NULL) {
        printf("Error opening gnuplot!\n");
        exit(1);
    }

    // Gnuplot commands for the ML decision regions
    fprintf(gnuplot, "set title 'ML Decision Regions for Browsing vs Intending to Buy'\n");
    fprintf(gnuplot, "set xlabel 'X1: Time Spent on Page'\n");
    fprintf(gnuplot, "set ylabel 'X2: Scrolling Speed'\n");
    fprintf(gnuplot, "set grid\n");
    fprintf(gnuplot, "set key outside\n");

    // Set the axis limits
    fprintf(gnuplot, "set xrange [-1.5:4]\n");
    fprintf(gnuplot, "set yrange [-1.5:2]\n");

    // Plot the decision boundaries for Y=0 (Browsing) - Blue Square with solid color
    fprintf(gnuplot, "set object 1 rect from -1,-1 to 1,1 lw 1 fc rgb 'blue' fs solid 0.3 border lc rgb 'blue'\n");
    
    // Plot the decision boundaries for Y=1 (Intending to Buy) - Red Rectangle with solid color
    fprintf(gnuplot, "set object 2 rect from 0.5,0.5 to 3.5,1.5 lw 1 fc rgb 'red' fs solid 0.3 border lc rgb 'red'\n");
    
    // Plot the overlap region - Green Dashed Rectangle
    fprintf(gnuplot, "set object 3 rect from 0.5,0.5 to 1,1 lw 1 fc rgb 'green' fs empty border lc rgb 'green' dashtype 2\n");

    // Labels for the decision regions
    fprintf(gnuplot, "set label 1 'Y=0 (Browsing User)' at -1, 1.5 tc rgb 'blue'\n");
    fprintf(gnuplot, "set label 2 'Y=1 (Intending to Buy)' at 2, 1.7 tc rgb 'red'\n");
    fprintf(gnuplot, "set label 3 'Overlap Region' at 1.2, 1.2 tc rgb 'green'\n");

    // Display the plot
    fprintf(gnuplot, "plot NaN notitle\n");

    pclose(gnuplot);
}

int main() {
    generate_data();  // No actual data is needed for this plot
    plot_data();
    return 0;
}
