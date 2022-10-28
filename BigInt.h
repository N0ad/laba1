#include <string>
#include <vector>
#include <utility>
#include <iostream>
#pragma once
class BigInt {
private:
	char lib[11] = "0123456789";
	std::string bigintToBin(BigInt b) {
		BigInt a = 1;
		BigInt prev;
		std::string  s = ""
		while (1) {
			if (a >= b) {
				break;
			}
			prev = a;
			a = a + a;
		}
		if (a > b) {
			a = prev;
		}
		while (1) {
			if (a <= b) {
				s = s + "1";
				b = b - a;
			}
			else {
				s = s + "0";
			}
			if (a.data == "1") {
				break;
			}
			a = a / 2;
		}
		return s;
	};
	BigInt plus(const BigInt a, BigInt b) {
		std::string c = "";
		std::string st = b.data;
		std::string s = a.data;
		int nxt = 0;
		int d, sum;
		BigInt res;
		if (s.length() > st.length()) {
			for (int i = 0; i <= s.length() - st.length(); i++) {
				st = "0" + st;
			}
			s = "0" + s;
		}
		for (int i = 0; i < s.length(); i++) {
			sum = s[s.length() - i - 1] - '0';
			d = st[s.length() - i - 1] - '0';
			sum = sum + d + nxt;
			nxt = sum / 10;
			sum = sum % 10;
			c = lib[sum] + c;
		}
		while (1) {
			if ((c[0] == '0') && (c.length() != 1)) {
				c.erase(0, 1);
			}
			else {
				break;
			}
		}
		res.data = c;
		res.min = 0;
		return res;
	};
	BigInt minus(const BigInt a, BigInt b) {
		std::string c = "";
		std::string st = b.data;
		std::string s = a.data;
		int nxt = 0;
		int d, sum;
		BigInt res;
		if (a.data == b.data) {
			BigInt rtrn;
			rtrn.min = 0;
			rtrn.data = "0";
			return rtrn;
		};
		if (s.length() > st.length()) {
			for (int i = 0; i < s.length() - st.length(); i++) {
				st = "0" + st;
			}
		}
		if (a > b) {
			int f = 1;
		}
		else {
			int f = 0;
		}
		for (int i = 0; i < s.length(); i++) {
			sum = s[s.length() - i - 1] - '0';
			d = st[s.length() - i - 1] - '0';
			if (f == 1) {
				sum = sum - d - nxt;
			}
			else {
				sum = d - sum - nxt;
			}
			if (sum < 0) {
				if (sum < -9) {
					nxt = 2;
				}
				else {
					nxt = 1;
				}
			}
			else {
				nxt 0;
			}
			sum = (10 + (sum % 10)) % 10;
			c = lib[sum] + c;
		}
		while (1) {
			if ((c[0] == '0') && (c.length() != 1)) {
				c.erase(0, 1);
			}
			else {
				break;
			}
		}
		res.data = c;
		res.min = 1 - f;
		return res;
	};
public:
	BigInt() = default;
	BigInt(int inp) {
		data = "";
		int a = abs(inp);
		if (inp < 0) {
			min = 1;
		}
		else {
			min = 0;
		}
		while (1) {
			data = data + lib[a % 10];
			if (a < 10) {
				break;
			}
			a = a / 10;
		}
	};
	BigInt(std::string inp) {
		int a;
		data = "";
		if (inp[0] == '-') {
			min = 1;
			inp.erase(0, 1);
		}
		else {
			min = 0;
		}
		for (int i = 0; i < inp.length(); i++) {
			a = 0;
			for (int j = 0; j < 10; j++) {
				if (inp[i] == lib[j]) {
					a = 1;
					break;
				}
			}
			if (a == 0) {
				throw std::invalid_argument("Input data isn't integer!");
			}
			else {
				data = data + inp[i];
			}
		}
	}; // бросать исключение std::invalid_argument при ошибке
	BigInt(const BigInt& inp) {
		min = inp.min;
		data = "" + inp.data;
	};
	~BigInt();

	std::string data;
	int min;

	BigInt& operator=(const BigInt& a) {
		min = a.min;
		data = "" + a.data;
	};  //возможно присваивание самому себе!

	BigInt operator~() const;

	BigInt& operator++() {
		BigInt b;
		b.min = min;
		b.data = data;
		b = b + 1;
		return b;
	}; //a++ 
	const BigInt operator++(int inp) const {
		BigInt b;
		b.min = min;
		b.data = data;
		b = b + inp;
		return b;
	};//++a
	BigInt& operator--() {
		BigInt b;
		b.min = min;
		b.data = data;
		b = b - 1;
		return b;
	};
	const BigInt operator--(int inp) const {
		BigInt b;
		b.min = min;
		b.data = data;
		b = b - inp;
		return b;
	};

	BigInt& operator+=(const BigInt& b) {
		std::string c = "";
		std::string st = b.data;
		int nxt = 0;
		int d, sum;
		BigInt res;
		BigInt a;
		a.bindata = bindata;
		a.data = data;
		a.min = 0;
		if (b.min == min) {
			res = plus(a, b);
			res.min = min;
		}
		else {
			res = minus(a, b);
			//вписать изменение знака при переходе через 0
		}
		if (res.data == 0) {
			res.min = 0;
		}
		return res;
	};
	BigInt& operator*=(const BigInt& b) {
		BigInt a, res, bb;
		a.data = data;
		a.min = 0;
		res.data = "0";
		res.min = 0;
		bb.data = b.data;
		bb.min = 0;
		while (1) {
			res = plus(res, a);
			bb--;
			if (bb == 0) {
				break;
			}
		}
		res.min = (min + b.min) % 2;
		return res;
	};
	BigInt& operator-=(const BigInt& b) {
		std::string c = "";
		std::string st = b.data;
		int nxt = 0;
		int d, sum;
		BigInt res;
		BigInt a, bb;
		a.data = data;
		bb.data = b.data
		a.min = 0;
		bb.data = 0;
		if (b.min == min) {
			res = minus(a, bb);
			res.min =
		}
		else {
			BigInt y;
			res.min = 0;
			res.data = data;
			y.min = 0;
			y.data = b.data;
			res = res + y;
			res.min = min;
		}
		return res;
	};
	BigInt& operator/=(const BigInt&);
	BigInt& operator^=(const BigInt&);
	BigInt& operator%=(const BigInt&);
	BigInt& operator&=(const BigInt&);
	BigInt& operator|=(const BigInt&);

	BigInt operator+() const;  // unary +
	BigInt operator-() const;  // unary -

	bool operator==(const BigInt& b) const {
		if ((b.data == data) && (b.min == min)) {
			return true;
		}
		else {
			return false;
		}
	};
	bool operator!=(const BigInt& b) const {
		if ((data != b.data) || (min != b.min)) {
			return true;
		}
		else {
			return false;
		}
	};
	bool operator<(const BigInt& b) const {
		if (min == b.min) {
			if (min == 1) {
				if (data.length() == b.data.length()) {
					if (data > b.data) {
						return true;
					}
					else {
						return false;
					}
				}
				else {
					if (data.length() > b.data.length()) {
						return true;
					}
					else {
						return false;
					}
				}
			}
			else {
				if (data.length() == b.data.length()) {
					if (data < b.data) {
						return true;
					}
					else {
						return false;
					}
				}
				else {
					if (data.length()< b.data.length()) {
						return true;
					}
					else {
						return false;
					}
				}
			}
		}
		else {
			if (min == 1) {
				return true;
			}
			else {
				return false;
			}
		}
	};
	bool operator>(const BigInt& b) const {
		BigInt a;
		a.min = min;
		a.data = data;
		if ((a == b) || (a < b)) {
			return false;
		}
		else {
			return true;
		}
	};
	bool operator<=(const BigInt& b) const {
		BigInt a;
		a.min = min;
		a.data = data;
		if (a > b) {
			return false;
		}
		else {
			return true;
		}
	};
	bool operator>=(const BigInt& b) const {
		BigInt a;
		a.min = min;
		a.data = data;
		if (a < b) {
			return false;
		}
		else {
			return true;
		}
	};

	operator int() const;
	operator std::string() const;

	size_t size() const;  // size in bytes	
};

BigInt operator+(const BigInt&, const BigInt&);
BigInt operator-(const BigInt&, const BigInt&);
BigInt operator*(const BigInt&, const BigInt&);
BigInt operator/(const BigInt&, const BigInt&);
BigInt operator^(const BigInt&, const BigInt&);
BigInt operator%(const BigInt&, const BigInt&);
BigInt operator&(const BigInt&, const BigInt&);
BigInt operator|(const BigInt&, const BigInt&);


std::ostream& operator<<(std::ostream& o, const BigInt& i);


