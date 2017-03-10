/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */
#pragma once

#include <cmath>
#include <random>

namespace java {
namespace lang {

/**
 * The class {@code Math} contains methods for performing basic numeric operations such as the elementary exponential,
 * logarithm, square root, and trigonometric functions.
 *
 * @see  <a href="https://docs.oracle.com/javase/8/docs/api/java/lang/Math.html">
 *       Java - Math</a>
 * @version 7.0
 */
class Math final {

    Math() {
    } // Cannot be instantiated.

public:
    /**
     * The {@code double} value that is closer than any other <i>e</i>, the base of the natural logarithms.
     */
    static constexpr double E = 2.7182818284590452354;

    /**
     * The {@code double} value that is closer than any other to <i>pi</i>, the ratio of the circumference
     * of a circle to its diameter.
     */
    static constexpr double PI = 3.14159265358979323846;

    /** Returns the trigonometric sine of an angle.  */
    static double sin(double a) {
        return std::sin(a);
    }

    /** Returns the trigonometric cosine of an angle. */
    static double cos(double a) {
        return std::cos(a);
    }

    /** Returns the trigonometric tangent of an angle. */
    static double tan(double a) {
        return std::tan(a);
    }

    /** Returns the arc sine of a value; the returned angle is in the range -<i>pi</i>/2 through <i>pi</i>/2.
     */
    static double asin(double a) {
        return std::asin(a);
    }

    /** Returns the arc cosine of a value; the returned angle is in the range 0.0 through <i>pi</i>. */
    static double acos(double a) {
        return std::acos(a);
    }

    /** Returns the arc tangent of a value; the returned angle is in the range -<i>pi</i>/2 through <i>pi</i>/2. */
    static double atan(double a) {
        return std::atan(a);
    }

    /** Converts an angle measured in degrees to an approximately equivalent angle measured in radians. */
    static double toRadians(double angdeg) {
        return angdeg / 180.0 * PI;
    }

    /** Converts an angle measured in radians to an approximately equivalent angle measured in degrees. */
    static double toDegrees(double angrad) {
        return angrad * 180.0 / PI;
    }

    /** Returns Euler's number <i>e</i> raised to the power of a {@code double} value. */
    static double exp(double a) {
        return std::exp(a);
    }

    /** Returns the natural logarithm (base <i>e</i>) of a {@code double} value. */
    static double log(double a) {
        return std::log(a);
    }

    /** Returns the base 10 logarithm of a {@code double} value. */
    static double log10(double a) {
        return std::log10(a);
    }

    /** Returns the positive square root of a {@code double} value. */
    static double sqrt(double a) {
        return std::sqrt(a);
    }

    /** Returns the cube root of a {@code double} value. */
    static double cbrt(double a) {
        return std::cbrt(a);
    }

    /** Computes the remainder operation on two arguments as prescribed by the IEEE 754 standard. */
    static double IEEEremainder(double d1, double d2) {
        return std::remainder(d1, d2);
    }

    /** Returns the smallest (closest to negative infinity) {@code double} value that is greater than or equal to the
     * argument and is equal to a mathematical integer.*/
    static double ceil(double a) {
        return std::ceil(a);
    }

    /** Returns the largest (closest to positive infinity) {@code double} value that is less than or equal to the
     *  argument and is equal to a mathematical integer.*/
    static double floor(double a) {
        return std::floor(a);
    }

    /** Returns the {@code double} value that is closest in value to the argument and is equal to a mathematical
     *  integer.*/
    static double rint(double a) {
        return std::rint(a); // default impl. delegates to StrictMath
    }

    /** Returns the angle <i>theta</i> from the conversion of rectangular coordinates ({@code x},&nbsp;{@code y})
     * to polar coordinates (r,&nbsp;<i>theta</i>). */
    static double atan2(double y, double x) {
        return std::atan2(y, x);
    }

    /** Returns the value of the first argument raised to the power of the second argument. */
    static double pow(double a, double b) {
        return std::pow(a, b);
    }

    /** Returns the closest {@code int} to the argument, with ties rounding to positive infinity. */
    static int round(float a) {
        return (int) std::round(a);
    }

    /** Returns the closest {@code long} to the argument, with ties rounding to positive infinity. */
    static long round(double a) {
        return (long) std::round(a);
    }

    /** Returns a {@code double} value with a positive sign, greater than or equal to {@code 0.0} and less
     * than {@code 1.0}. */
    static double random() {
        static std::random_device rd;  //Will be used to obtain a seed for the random number engine
        static std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
        static std::uniform_real_distribution<double> dis(0, 1.0);
        return dis(gen); //Each call to dis(gen) generates a new random double.
    }

    /** Returns the absolute value of an {@code int} value. */
    static int abs(int a) {
        return (a < 0) ? -a : a;
    }

    /** Returns the absolute value of a {@code long} value. */
    static long abs(long a) {
        return (a < 0) ? -a : a;
    }

    /** Returns the absolute value of a {@code float} value. */
    static float abs(float a) {
        return std::abs(a);
    }

    /** Returns the absolute value of a {@code double} value. */
    static double abs(double a) {
        return std::abs(a);
    }

    /** Returns the greater of two {@code int} values. */
    static int max(int a, int b) {
        return (a >= b) ? a : b;
    }

    /** Returns the greater of two {@code long} values. */
    static long max(long a, long b) {
        return (a >= b) ? a : b;
    }

    /** Returns the greater of two {@code float} values.*/
    static float max(float a, float b) {
        return std::fmax(a, b);
    }

    /** Returns the greater of two {@code double} values.*/
    static double max(double a, double b) {
        return std::fmax(a, b);
    }

    /** Returns the smaller of two {@code int} values. */
    static int min(int a, int b) {
        return (a <= b) ? a : b;
    }

    /** Returns the smaller of two {@code long} values. */
    static long min(long a, long b) {
        return (a <= b) ? a : b;
    }

    /** Returns the smaller of two {@code float} values. */
    static float min(float a, float b) {
        return std::fmin(a, b);
    }

    /** Returns the smaller of two {@code double} values. */
    static double min(double a, double b) {
        return std::fmin(a, b);
    }

    /** Returns the signum function of the argument; zero if the argument is zero, 1.0 if the argument is greater
     *  than zero, -1.0 if the argument is less than zero. */
    static double signum(double d) {
        return (d == 0.0 || std::isnan(d)) ? d : std::copysign(1.0, d);
    }

    /** Returns the signum function of the argument; zero if the argument is zero, 1.0f if the argument is greater
     *  than zero, -1.0f if the argument is less than zero.  */
    static float signum(float f) {
        return (f == 0.0f || std::isnan(f)) ? f : std::copysign(1.0f, f);
    }

    /** Returns the hyperbolic sine of a {@code double} value. */
    static double sinh(double x) {
        return std::sinh(x);
    }

    /** Returns the hyperbolic cosine of a {@code double} value. */
    static double cosh(double x) {
        return std::cosh(x);
    }

    /** Returns the hyperbolic tangent of a {@code double} value. */
    static double tanh(double x) {
        return std::tanh(x);
    }

    /** Returns sqrt(<i>x</i><sup>2</sup>&nbsp;+<i>y</i><sup>2</sup>).*/
    static double hypot(double x, double y) {
        return std::hypot(x, y);
    }

    /** Returns <i>e</i><sup>x</sup>&nbsp;-1.*/
    static double expm1(double x) {
        return std::expm1(x);
    }

    /** Returns the natural logarithm of the sum of the argument and 1. */
    static double log1p(double x) {
        return std::log1p(x);
    }

    /** Returns the first floating-point argument with the sign of the
     * second floating-point argument. */
    static double copySign(double magnitude, double sign) {
        return std::copysign(magnitude, sign);
    }

    /** Returns the first floating-point argument with the sign of the
     * second floating-point argument. */
    static float copySign(float magnitude, float sign) {
        return std::copysign(magnitude, sign);
    }

    /** Returns the floating-point number adjacent to the first
     *  argument in the direction of the second argument. */
    static double nextAfter(double start, double direction) {
        return std::nextafter(start, direction);
    }

    /** Returns the floating-point number adjacent to the first
     * argument in the direction of the second argument. */
    static float nextAfter(float start, double direction) {
        return (float) std::nextafter(start, direction);
    }

    /**Returns {@code d} &times; 2<sup>{@code scaleFactor}</sup>. */
    static double scalb(double d, int scaleFactor) {
        return std::scalbn(d, scaleFactor);
    }

    /** Returns {@code f} &times; 2<sup>{@code scaleFactor}</sup>. */
    static float scalb(float f, int scaleFactor) {
        return std::scalbn(f, scaleFactor);
    }

};

}
}
