#include <stdio.h>
#include "s21_math.h"
int s21_abs(int x) {
    if (x < 0) {
        x = x * (-1);
    }
    return x;
}

long double s21_fabs(double x) {
    if (x == S21_INFINITY || x == S21_M_INFINITY || x == S21_NAN) {
        return x;
    } else {
        if (x < 0) {
            x = x * (-1.0);
        }
        return (long double)x;
    }
}

long double s21_floor(double x) {
    if (x > -1 && x < 0) x = -1.0;
    double repl = x;
    if ((x == S21_INFINITY || x == S21_M_INFINITY) || x != x) {
        return x;
    } else {
        x = (long double)(int)x;
        if (x < 0 && (int)repl - repl != 0) {
            x -= 1;
        }
        return x;
    }
}

long double s21_ceil(double x) {
    double res, repl = x;
    if (x == S21_INFINITY || x == S21_M_INFINITY || x != x) {
        res = x;
    } else {
        if (x > -1 && x < 0) {
            res = -0.0;
        } else {
            if (x > 0 && x < 1) {
                res = 1;
            } else {
                res = (long double)(int)x;
                if (res > 0 && (int)repl - repl != 0) {
                    res += 1;
                }
            }
        }
    }
    return res;
}

long double s21_fmod(double x, double y) {
    double private, private_check, remainder;
    if (x == S21_NAN || y == S21_NAN) remainder = S21_NAN;
    private = x / y;
    if (x < 0 && y < 0) {
        private_check = s21_abs(private);
    } else if (x < 0 || y < 0) {
        private_check = (-1) * s21_abs(private);
    } else {
        private_check = s21_abs(private);
    }
    remainder = x - private_check * y;
    if (y == 0) {
        remainder = 0 / 0.0;
    }
    return remainder;
}
long double s21_exp(double x) {
    long double res = 0;
    if (x < 0) {
        res = 1 / s21_exp((-1) * x);
    } else {
        for (int k = 0; k < 2000; ++k) {
            double current = 1;
            for (int j = 1; j <= k; ++j) {
                current *= x;
                current /= j;
            }
            res += current;
        }
    }
    return res;
}

long double s21_sqrt(double x) {
    long double eps = 1e-18;
    long double n = 1;
    if (x == S21_INFINITY || x != x) {
        n = x;
    } else {
        if (x == S21_M_INFINITY) {
            n = S21_NAN;
        } else {
            if (x > 0) {
                while (s21_fabs(n * n - x) > eps) n = (n + (x / n)) / 2;
            }
            if (x == 0) n = 0;
            if (x < 0) n = 0 / 0.0;
        }
    }
    return n;
}

long double s21_log(double x) {
    double y = x - 1.0;
    long double res = y;
    double eps = 0.000001;
    int counter = 0;
    if (x < 0) {
        res = S21_NAN;
    } else if (x == 0) {
        res = S21_M_INFINITY;
    } else {
        do {
            y = res;
            res = y + 2 * (x - s21_exp(y)) / (x + s21_exp(y));
            counter++;
        } while (s21_fabs(y - res) > eps);
    }
    return res;
}

long double s21_pow(double base, double exp) {
    long double res = 1;
    if ((base != base) && (exp != exp)) {
        res = S21_NAN;
    } else {
        if (base < 0 && exp != s21_floor(exp)) {
            res = -S21_NAN;
        } else if (base == 0 && exp < 0) {
            res = S21_INFINITY;
        } else if (exp == 0 || base != base || exp != exp) {
            res = 1;
        } else if (s21_fmod(exp, 1) == 0) {
            if (exp > 0) {
            for (int i = 0; i < exp; i++) {
                res = res * base;
            }
          } else {
               for (int i = 0; i < s21_abs(exp); i++) {
                res = (res * base);
          }
          res = 1 / res;
          }
          } else {
            if (exp > 0) {
            res = s21_exp(exp * s21_log(base));
            } else {
            res = 1 / s21_exp(s21_fabs(exp) * (s21_log(base)));
    }
    }
    }
    return res;
}
long double s21_sin(double x) {
    long double res;
    int flag = 1;
    if (x == S21_INFINITY || x == S21_M_INFINITY) {
        res = S21_NAN;
    } else {
        if (x == S21_NAN) {
            res = S21_NAN;
        } else if (x == 0) {
            res = x;
        } else if (x < 0) {
            x = (-1) * x;
            flag = -1;
     while (x > s21_PI || x < -s21_PI) {
    x += x > s21_PI ? -2 * s21_PI : 2 * s21_PI;
  }
long double result = x, temp = x;
  long double i = 1.;
  while (s21_fabs(result) > 1e-18) {
    result = -1 * result * x * x / (2 * i * (2 * i + 1));
    i += 1.;
    temp += result;
  }
  return temp;
        }
    return res;
}

double shift_2pi(long double x) {
    int flag = 1;
    if (x < 0) {
        x = -x;
        flag = -1;
    }
    while (x > s21_PI_9) x -= s21_PI_9;
    while (x > s21_PI_8) x -= s21_PI_8;
    while (x > s21_PI_7) x -= s21_PI_7;
    while (x > s21_PI_6) x -= s21_PI_6;
    while (x > s21_PI_5) x -= s21_PI_5;
    while (x > s21_PI_4) x -= s21_PI_4;
    while (x > s21_PI_3) x -= s21_PI_3;
    while (x > s21_PI_2) x -= s21_PI_2;
    while (x > 2 * s21_PI) x -= 2 * s21_PI;
    return flag * x;
}

long double s21_cos(double x) {
    long double res;
    if (x == S21_INFINITY || x == S21_M_INFINITY)
        res = S21_NAN;
    else if (x == S21_NAN)
        res = S21_NAN;
    else if (x == 0)
        res = x;
    x = shift_2pi(x);
    res = s21_sin(s21_PI_POPOLAM - x);
    return res;
}

long double s21_tan(double x) {
    long double res;
    // if (fmod(x + M_PI_2, M_PI)) {
    if (x == S21_M_INFINITY || x == S21_INFINITY || x == S21_NAN)
        res = S21_NAN;
    else
        res = s21_sin(x) / s21_cos(x);
    // } else {
    //     res = 1.22465e-16;
    // }
    return res;
}

long double s21_atan(double x) {
    int val_1 = 0, val_2 = 0;
    long double res_1, res_2;
    if (x < 0.F) {
        x = -x;
        val_1 |= 1;
    }
    if (x > 1.F) {
        x = 1.F / x;
        val_1 |= 2;
    }
    while (x > M_PI12) {
        val_2++;
        res_2 = x + SQRT3;
        res_2 = 1.F / res_2;
        x *= SQRT3;
        x -= 1.F;
        x *= res_2;
    }
    res_1 = x * x;
    res_2 = res_1 + 1.4087812F;
    res_2 = 0.55913709F / res_2;
    res_2 += 0.60310579F;
    res_2 -= 0.05160454F * res_1;
    res_2 *= x;
    while (val_2 > 0) {
        res_2 += M_PI6;
        val_2--;
    }
    if (val_1 & 2) res_2 = M_PI2 - res_2;
    if (val_1 & 1) res_2 = -res_2;
    return (res_2);
}

long double s21_asin(double x) {
    long double res;
    if (x > 1 || x < -1)
        res = S21_NAN;
    else
        res = s21_atan(x / (s21_sqrt(1 - (s21_pow(x, 2)))));
    return res;
}

long double s21_acos(double x) {
    long double res;
    if (x > 1 || x < -1)
        res = S21_NAN;
    else
        res = M_PI2 - s21_asin(x);
    return res;
}
