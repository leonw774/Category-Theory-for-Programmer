#include <iostream>
#include <cmath>

typedef struct {
    int x;
    int y;
} Cartesian;

typedef struct {
    double thida;
    double r;
} Polar;

Polar C2P(Cartesian coord) {
    Polar p;
    p.r = std::sqrt(coord.x * coord.x + coord.y * coord.y);
    p.thida = std::asin(coord.y/p.r);
    return p;
}

double P2R(Polar coord) {
    return coord.r;
}

template <typename T, typename U, typename V>
V funcComp(V (*func1)(U), U (*func2)(T), T in) {
    return (*func1)((*func2)(in));
}

int main() {
    Cartesian c;
    c.x = 16;
    c.y = 8;
    Polar p = C2P(c);
    double d = P2R(p);
    double d2 = funcComp(P2R, C2P, c);
    std::cout << d << std::endl << d2 << std::endl;
    return 0;
}