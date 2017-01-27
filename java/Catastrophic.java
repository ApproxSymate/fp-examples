/******************************************************************************
 *  Compilation:  javac Catastrophic.java
 *  Execution:    java Catastrophic N
 *
 *  Plot fl(x) = (1 - cos x) / x^2 in the interval from
 *  -4 * 10^-8 to 4 * 10^-8. Catastrophic cancellation
 *  leads to extremely inaccurate values in this range.
 *  The true answer is approximately 0.5 for all x values
 *  in this range.
 *
 *  % java Catastrophic 10000
 *
 *  From: http://introcs.cs.princeton.edu/java/91float/Catastrophic.java.html
 *  Copyright © 2000–2016 Robert Sedgewick and Kevin Wayne.
 *  All rights reserved.
 *
 *  The issue is also described in the article "Dynamic
 *  Floating-Point Cancellation Detection" by Lam, 
 *  Hollingsworth, and Stewart, Section 4.1.
 *
 ******************************************************************************/

public class Catastrophic {

    // compute f(x)  = (1 - cos x) / x^2 in floating point
    public static double fl(double x) {
        double a = Math.cos(x);
        double b = 1.0 - a;
        double c = b / (x*x);
        return c;
    }

    // compute f(x)  = (1 - cos x) / x^2 in floating point
    // compiler may produce more accurate results by using more precision than
    // IEEE requires
    public static double fl2(double x) {
        return (1.0 - Math.cos(x)) / (x*x);
    }

    public static double f(double x) {
        return 2 * Math.sin(x/2) * Math.sin(x/2) / (x*x);
    }

    public static void main(String[] args) { 
        // number of line segments to plot
        int N = Integer.parseInt(args[0]);


        // x-interval to plot
        double x0 = -4.0e-8;
        double x1 = +4.0e-8;

        // rescale the coordinates
        StdDraw.setXscale(x0, x1);
        StdDraw.setYscale(-.1, 1.1);
        StdDraw.enableDoubleBuffering();

        double[] vals1 = new double[N+1];
        double[] vals2 = new double[N+1];
        double[] vals3 = new double[N+1];
        for (int i = 0; i <= N; i++) {
            vals1[i] = fl(x0 + (x1 - x0) * i / N);
            vals2[i] = fl2(x0 + (x1 - x0) * i / N);
            vals3[i] = f(x0 + (x1 - x0) * i / N);
        }
        StdDraw.setPenColor(StdDraw.BLACK);
        StdStats.plotLines(vals3);
        StdDraw.setPenColor(StdDraw.BLUE);
        StdStats.plotLines(vals1);
        StdDraw.show();
    }

}
