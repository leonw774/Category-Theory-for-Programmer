#include <iostream>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

class MonoidalString {
    public:
    static const std::string unit;
    std::string data;
    // MonoidalString(const char* const s) {
    //     data = std::string(s);
    // };
    MonoidalString(std::string const &s) {
        data = s;
    };
    // mapping object pair to object
    static MonoidalString concat(MonoidalString a, MonoidalString b) {
        return MonoidalString(a.data + b.data);
    };
    // mapping morphism pair to morphism
    static std::vector<int> fconcat(std::vector<int>& p1, std::vector<int>& p2) {
        std::vector<int> result = p1;
        for (int i: p2) {
            result.push_back(i + p1.size());
        }
        return result;
    };

    bool operator== (MonoidalString& other) {
        return other.data == data;
    };
};
// Define unit
const std::string MonoidalString::unit = std::string();

std::ostream& operator<< (std::ostream& os, const MonoidalString& s) {
    os << s.data;
    return os;
};

int main() {
    MonoidalString a1("hello"), a2("holel"), b1("world!"), b2("ldo!rw"), c("monoid");
    std::vector<int> pa = {1, 4, 3, 5, 2}, pb = {6, 3, 5, 1, 2, 4};
    // Bifunctor
    std::cout << "Morphism in category of strings is pa: a1 -> a2 if a1 permute into a2 with pa:\n"
            << "pa = {1, 4, 3, 5, 2}: 'hello' -> 'holel'\n"
            << "pb = {6, 3, 5, 1, 2, 4}: 'world!' -> 'ldo!rw'\n";
    auto a1b1 = MonoidalString::concat(a1, b1);
    auto a2b2 = MonoidalString::concat(a2, b2);
    auto pab = MonoidalString::fconcat(pa, pb);
    std::string pab_str("{");
    char buf[8];
    for (int i: pab) {
        itoa(i, buf, 10);
        pab_str = pab_str + buf + ", ";
    }
    pab_str = pab_str.substr(0, pab_str.size()-2) + "}";
    std::cout << "a1b1 = MonoidalString::concat('" << a1 << "', '" << b1 << "') == " << a1b1 << std::endl;
    std::cout << "a2b2 = MonoidalString::concat('" << a2 << "', '" << b2 << "') == " << a2b2 << std::endl;
    std::cout << "pab = MonoidalString::fconcat(pa, pb) == " << pab_str << std::endl;
    std::string tempstr(pab.size(), '_');
    for (int i = 0; i < pab.size(); i++) {
        tempstr[pab[i]-1] = a1b1.data[i];
    }
    std::cout << "pab(a1b1) = " << tempstr << " == " << a2b2 << std::endl;
    std::cout << "\nTest Associativity\n";
    std::cout << MonoidalString::concat(MonoidalString::concat(a1, b1), c) << std::endl;
    std::cout << MonoidalString::concat(a1, MonoidalString::concat(b1, c)) << std::endl;
    
    std::cout << "\nTest Unit Object\n";
    std::cout << MonoidalString::concat(a1, MonoidalString::unit) << " == " << a1 << std::endl;
    std::cout << MonoidalString::concat(MonoidalString::unit, a1) << " == " << a1 << std::endl;
    return 0;
}