#include<iostream>
#include<string>
#include<sstream>

// Mapping from int to float
float foo(int x) {
    float result = x;
    result /= 7; 
    return result;
}

// Mapping from double to int
int bar(double x) {
    int result = x * 10.0;
    return result;
}

int iden_int(int x) {
    return x;
}

double iden_double(double x) {
    return x;
}

// The functor
template <typename T, typename U>
auto stringWrap(T (*func)(U)) {
    return [func] (std::string x) {
        std::stringstream ss;
        U unwrappedInput;
        ss << x;
        ss >> unwrappedInput;
        return std::to_string(func(unwrappedInput));
    };
}

int main() {
    int a = 10;
    std::string sa = "10";
    std::cout << "foo(a):" << foo(a) << std::endl;
    std::cout << "stringWrap(foo)(sa):" << stringWrap(foo)(sa) << std::endl;
    
    double b = 3.333333;
    std::string sb = "3.333333";
    std::cout << "bar(b):" << bar(b) << std::endl;
    std::cout << "stringWrap(bar)(sb):" << stringWrap(bar)(sb) << std::endl;
    std::cout << "------\n";

    std::cout << "foo(bar(a)):" << foo(bar(a)) << std::endl;
    std::cout << "stringWrap(foo)(stringWrap(bar)(sa)):" << stringWrap(foo)(stringWrap(bar)(sa)) << std::endl;
    std::cout << "------\n";

    std::cout << "iden_int(a):" << iden_int(a) << std::endl;
    std::cout << "iden_double(b):" << iden_double(b) << std::endl;
    std::cout << "stringWrap(iden_int)(sa):" << stringWrap(iden_int)(sa) << std::endl;
    std::cout << "stringWrap(iden_double)(sb):" << stringWrap(iden_double)(sb) << std::endl;
    return 0;
}
