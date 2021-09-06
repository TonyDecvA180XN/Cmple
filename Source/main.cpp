#include "main.h"

BigInt& BigInt::operator +(BigInt &b) {
    BigInt *res = new BigInt;
    res->data.resize(std::max(this->data.size(), b.data.size()) + 1);
    for(size_t i = 0; i < std::max(this->data.size(), b.data.size()); i++) {
        if(i < this->data.size())
            res->data[i] += this->data[i];
        if(i < b.data.size())
            res->data[i] += b.data[i];
    }
    for(size_t i = 0; i < res->data.size(); i++) {
        if(res->data[i] >= BigIntBase) {
            res->data[i] -= BigIntBase;
            res->data[i+1]++;
        }
    }
    if(res->data.back() == 0)
        res->data.pop_back();
    return *res;
}


std::istream& operator>>(std::istream &in, BigInt &a) {
    std::string s;
    in >> s;
    while(s.size() % BigIntLen)
        s = "0" + s;
    a.data.clear();
    for(size_t i = 0; i < s.size(); i += BigIntLen)
        a.data.push_back(atoi(s.substr(i, BigIntLen).c_str()));
    std::reverse(a.data.begin(),a.data.end());
    return in;
}

std::ostream& operator<<(std::ostream &out, BigInt &a) {
    out << a.data.back();
    if(a.data.size() >= 2) {
        for(int i = (int)a.data.size() - 2; i >= 0; i--) {
            out << std::setfill('0') << std::setw(BigIntLen) << a.data[i];
        }
    }
    return out;
}

int main() {
    BigInt a, b;
    std::cin >> a >> b;
    std::cout << a + b << std::endl;

    return 0;
}
