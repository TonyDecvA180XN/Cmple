#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

const int BigIntBase = 1000000000;
const int BigIntLen  = 9;

class BigInt {
public:
    BigInt& operator +(BigInt &b) ;

    friend std::istream& operator>>(std::istream&, BigInt&);
    friend std::ostream& operator<<(std::ostream&, BigInt&);

private:
    std::vector <int> data;
};

std::istream& operator >>(std::istream &in, BigInt &a) ;
std::ostream& operator <<(std::ostream &out, BigInt &a);
