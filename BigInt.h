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
	BigInt binToBigint(std::string s) {
		BigInt a = 1;
		BigInt res = 0;
		for (int i = s.length() - 1; i >= 0; i--) {
			if (s[i] == '1') {
				res = plus(res, a);
			}
			a = plus(a, a);
		}
		return res;
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

	BigInt operator~() const {
		min = 1 - min;
		BigInt a;
		a.data = data;
		a.min = 0;
		std::string s = bigintToBin(a);
		for (int i = s.length() - 1; i >= 0; i--) {
			if (s[i] == "1") {
				s[i] = "0";
			}
			else {
				s[i] = "1";
			}
		}
		a = binToBigint(s);
		data = a.data;
		a.min = min;
		return a;
	};

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
		BigInt a, bb;
		a.data = data;
		a.min = 0;
		if (b.min == min) {
			res = plus(a, b);
			res.min = min;
		}
		else {
			bb.data = b.data;
			bb.min = 1 - b.min;
			res = minus(a, bb);
		}
		if (res.data == 0) {
			res.min = 0;
		}
		data = res.data;
		min = res.min;
		return res;
	};
	BigInt& operator*=(const BigInt& b) {
		BigInt a, bb, res;
		if ((data == "0") || (b.data == "0")) {
			res = 0;
			data = res.data;
			min = res.min;
			return res;
		}
		std::string s = "";
		a.min = 0;
		bb.min = 0;
		res = 0;
		int l, o;
		if (data.length() > b.data.length()) {
			a.data = data;
			s = s + b.data;
			l = b.data.length();
		}
		else {
			a.data = b.data;
			s = s + data;
			l = data.length();
		}
		for (int i = l - 1; i >= 0; i--) {
			o = s[i] - '0';
			bb = 0;
			for (int j = 0; j < o; j++) {
				bb = plus(bb, a);
			}
			for (int j = 0; j < l - i - 1; j++) {
				bb.data = bb.data + "0";
			}
			res = plus(res, bb);
		}
		res.min = (b.min + min) % 2;
		data = res.data;
		min = res.min;
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
			res.min = (min + res.min) % 2;
		}
		else {
			BigInt y;
			res.min = 0;
			res.data = data;
			y.min = 0;
			y.data = b.data;
			res = plus(res, y);
			res.min = min;
		}
		if (res.data == 0) {
			res.min = 0;
		}
		data = res.data;
		min = res.min;
		return res;
	};
	BigInt& operator/=(const BigInt& b) {
		if (b.data == "0") {
			throw std::invalid_argument("Dividing by zero!");
		}
		BigInt bb, res, c;
		std::string s;
		if (data == "0") {
			res = 0;
			data = res.data;
			min = res.min;
			return res;
		}
		bb.min = 0;
		c.min = 0;
		res.data = "";
		int l, o;
		if (data.length() > b.data.length()) {
			s = data;
			c.data = b.data;
			l = data.length();
		}
		else {
			s = b.data;
			c.data = data;
			l = b.data.length();
		}
		bb.data = s;
		bb.data.erase(l);
		s.erase(0, l);
		o = 0;
		while (1) {
			if (bb >= c) {
				bb = minus(bb, c);
				o = o + 1;
			}
			else {
				res.data = res.data + lib[o];
				if (s == "") {
					break;
				}
				o = 0;
				bb.data = bb.data + s[0];
				s.erase(0, 1);
			}
		}
		if ((min + b.min) % 2 == 1) {
			res = res + 1;
			res.min = 1;
		}
		else {
			res.min = 0;
		}
		data = res.data;
		min = res.min;
		return res;
	};
	BigInt& operator^=(const BigInt& b) {
		std::string as, bs, s;
		BigInt abi, bbi;
		abi.data = data;
		bbi.data = b.data;
		abi.min = 0;
		bbi.min = 0;
		as = bigintToBin(abi);
		bs = bigintToBin(bbi);
		int al = as.length();
		int bl = bs.lenght();
		int l;
		if (al != bl) {
			if (al < bl) {
				for (int i = 0; i < bl - al; i++) {
					as = "0" + as;
				}
				l = bl;
			}
			else {
				for (int i = 0; i < al - bl; i++) {
					bs = "0" + bs;
				}
				l = al;
			}
		}
		s = "";
		for (int i = l - 1; i >= 0; i--) {
			if (as[i] == bs[i]) {
				s = "0" + s;
			}
			else {
				s = "1" + s;
			}
		}
		BigInt res = binToBigint(s);
		res.min = (min + b.min) % 2;
		min = res.min;
		data = rs.data;
		return res;
	};
	BigInt& operator%=(const BigInt&) {
		if (b.data == "0") {
			throw std::invalid_argument("Dividing by zero!");
		}
		BigInt bb, res, c;
		std::string s;
		if (data == "0") {
			res = 0;
			data = res.data;
			min = res.min;
			return res;
		}
		bb.min = 0;
		c.min = 0;
		int l, o;
		if (data.length() > b.data.length()) {
			s = data;
			c.data = b.data;
			l = data.length();
		}
		else {
			s = b.data;
			c.data = data;
			l = b.data.length();
		}
		bb.data = s;
		bb.data.erase(l);
		s.erase(0, l);
		o = 0;
		while (1) {
			if (bb >= c) {
				bb = minus(bb, c);
				o = o + 1;
			}
			else {
				if (s == "") {
					break;
				}
				o = 0;
				bb.data = bb.data + s[0];
				s.erase(0, 1);
			}
		}
		if ((min + b.min) % 2 == 1) {
			res = c - bb;
			data = res.data;
			min = res.min;
			return res;
		}
		else {
			data = bb.data;
			min = bb.min;
			return bb;
		}
	};
	BigInt& operator&=(const BigInt&) {
		std::string as, bs, s;
		BigInt abi, bbi;
		abi.data = data;
		bbi.data = b.data;
		abi.min = 0;
		bbi.min = 0;
		as = bigintToBin(abi);
		bs = bigintToBin(bbi);
		int al = as.length();
		int bl = bs.lenght();
		int l;
		if (al != bl) {
			if (al < bl) {
				for (int i = 0; i < bl - al; i++) {
					as = "0" + as;
				}
				l = bl;
			}
			else {
				for (int i = 0; i < al - bl; i++) {
					bs = "0" + bs;
				}
				l = al;
			}
		}
		s = "";
		for (int i = l - 1; i >= 0; i--) {
			if ((as[i] == "1") && (bs[i] == "1")) {
				s = "0" + s;
			}
			else {
				s = "1" + s;
			}
		}
		BigInt res = binToBigint(s);
		res.min = (min + b.min) % 2;
		min = res.min;
		data = rs.data;
		return res;
	};
	BigInt& operator|=(const BigInt&) {
		std::string as, bs, s;
		BigInt abi, bbi;
		abi.data = data;
		bbi.data = b.data;
		abi.min = 0;
		bbi.min = 0;
		as = bigintToBin(abi);
		bs = bigintToBin(bbi);
		int al = as.length();
		int bl = bs.lenght();
		int l;
		if (al != bl) {
			if (al < bl) {
				for (int i = 0; i < bl - al; i++) {
					as = "0" + as;
				}
				l = bl;
			}
			else {
				for (int i = 0; i < al - bl; i++) {
					bs = "0" + bs;
				}
				l = al;
			}
		}
		s = "";
		for (int i = l - 1; i >= 0; i--) {
			if ((as[i] == "1") || (bs[i] == "1")) {
				s = "0" + s;
			}
			else {
				s = "1" + s;
			}
		}
		BigInt res = binToBigint(s);
		res.min = (min + b.min) % 2;
		min = res.min;
		data = rs.data;
		return res;
	};

	BigInt operator+() const {
		BigInt res;
		res.min = min;
		res.data = data;
		return res;
	};  // unary +
	BigInt operator-() const {
		BigInt res;
		res.min = 1 - min;
		res.data = data;
		return res;
	};  // unary -

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

	operator int() const {
		if (((data > "2147483648") && (min == 1)) || ((data > "2147483647") && (min == 0))) {
			throw std::invalid_argument("Argument bigger than max value of int.");
		}
		else {
			int res = 0;
			int a;
			if (min == 1) {
				for (int i = data.length() - 1; i >= 0; i--) {
					a = data[i] - '0';
					res = res - a;
				}
			}
			else {
				for (int i = data.length() - 1; i >= 0; i--) {
					a = data[i] - '0';
					res = res + a;
				}
			}
			return res;
		}
	};
	operator std::string() const {
		std::string s = "";
		if (i.min == 1) {
			s = s + "-";
		}
		s = s + i.data;
		return s;
	};

	size_t size() const {
		int res = sizeof(char) * data.length();
		res = res + sizeof(int);
		return res;
	};  // size in bytes	
};

BigInt operator+(const BigInt& a, const BigInt& b) {
	std::string c = "";
	std::string st = b.data;
	int nxt = 0;
	int d, sum;
	BigInt res;
	BigInt aa, bb;
	aa.data = a.data;
	aa.min = 0;
	if (b.min == a.min) {
		res = plus(aa, b);
		res.min = a.min;
	}
	else {
		bb.data = b.data;
		bb.min = 1 - b.min;
		res = minus(aa, bb);
	}
	if (res.data == 0) {
		res.min = 0;
	}
	return res;
};
BigInt operator-(const BigInt& a, const BigInt& b) {
	BigInt aa, bb, res;
	if ((a.data == "0") || (b.data == "0")) {
		res = 0;
		return res;
	}
	std::string s = "";
	aa.min = 0;
	bb.min = 0;
	res = 0;
	int l, o;
	if (a.data.length() > b.data.length()) {
		aa.data = a.data;
		s = s + b.data;
		l = b.data.length();
	}
	else {
		aa.data = b.data;
		s = s + a.data;
		l = a.data.length();
	}
	for (int i = l - 1; i >= 0; i--) {
		o = s[i] - '0';
		bb = 0;
		for (int j = 0; j < o; j++) {
			bb = plus(bb, aa);
		}
		for (int j = 0; j < l - i - 1; j++) {
			bb.data = bb.data + "0";
		}
		res = plus(res, bb);
	}
	res.min = (b.min + a.min) % 2;
	return res;
};
BigInt operator*(const BigInt& a, const BigInt& b) {
	std::string c = "";
	std::string st = b.data;
	int nxt = 0;
	int d, sum;
	BigInt res;
	BigInt aa, bb;
	aa.data = a.data;
	bb.data = b.data
		aa.min = 0;
	bb.data = 0;
	if (b.min == a.min) {
		res = minus(aa, bb);
		res.min = (a.min + res.min) % 2;
	}
	else {
		BigInt y;
		res.min = 0;
		res.data = a.data;
		y.min = 0;
		y.data = b.data;
		res = plus(res, y);
		res.min = a.min;
	}
	if (res.data == 0) {
		res.min = 0;
	}
	return res;
};
BigInt operator/(const BigInt& a, const BigInt& b) {
	if (b.data == "0") {
		throw std::invalid_argument("Dividing by zero!");
	}
	BigInt bb, res, c;
	std::string s;
	if (a.data == "0") {
		res = 0;
		return res;
	}
	bb.min = 0;
	c.min = 0;
	res.data = "";
	int l, o;
	if (a.data.length() > b.data.length()) {
		s = a.data;
		c.data = b.data;
		l = a.data.length();
	}
	else {
		s = b.data;
		c.data = a.data;
		l = b.data.length();
	}
	bb.data = s;
	bb.data.erase(l);
	s.erase(0, l);
	o = 0;
	while (1) {
		if (bb >= c) {
			bb = minus(bb, c);
			o = o + 1;
		}
		else {
			res.data = res.data + lib[o];
			if (s == "") {
				break;
			}
			o = 0;
			bb.data = bb.data + s[0];
			s.erase(0, 1);
		}
	}
	if ((a.min + b.min) % 2 == 1) {
		res = res + 1;
		res.min = 1;
	}
	else {
		res.min = 0;
	}
	return res;
};
BigInt operator^(const BigInt& a, const BigInt& b) {
	std::string as, bs, s;
	BigInt abi, bbi;
	abi.data = a.data;
	bbi.data = b.data;
	abi.min = 0;
	bbi.min = 0;
	as = bigintToBin(abi);
	bs = bigintToBin(bbi);
	int al = as.length();
	int bl = bs.lenght();
	int l;
	if (al != bl) {
		if (al < bl) {
			for (int i = 0; i < bl - al; i++) {
				as = "0" + as;
			}
			l = bl;
		}
		else {
			for (int i = 0; i < al - bl; i++) {
				bs = "0" + bs;
			}
			l = al;
		}
	}
	s = "";
	for (int i = l - 1; i >= 0; i--) {
		if (as[i] == bs[i]) {
			s = "0" + s;
		}
		else {
			s = "1" + s;
		}
	}
	BigInt res = binToBigint(s);
	res.min = (a.min + b.min) % 2;
	return res;
};
BigInt operator%(const BigInt& a, const BigInt& b) {
	if (b.data == "0") {
		throw std::invalid_argument("Dividing by zero!");
	}
	BigInt bb, res, c;
	std::string s;
	if (a.data == "0") {
		res = 0;
		return res;
	}
	bb.min = 0;
	c.min = 0;
	int l, o;
	if (a.data.length() > b.data.length()) {
		s = a.data;
		c.data = b.data;
		l = a.data.length();
	}
	else {
		s = b.data;
		c.data = a.data;
		l = b.data.length();
	}
	bb.data = s;
	bb.data.erase(l);
	s.erase(0, l);
	o = 0;
	while (1) {
		if (bb >= c) {
			bb = minus(bb, c);
			o = o + 1;
		}
		else {
			if (s == "") {
				break;
			}
			o = 0;
			bb.data = bb.data + s[0];
			s.erase(0, 1);
		}
	}
	if ((a.min + b.min) % 2 == 1) {
		res = c - bb;
		return res;
	}
	else {
		return bb;
	}
};
BigInt operator&(const BigInt& a, const BigInt& b) {
	std::string as, bs, s;
	BigInt abi, bbi;
	abi.data = a.data;
	bbi.data = b.data;
	abi.min = 0;
	bbi.min = 0;
	as = bigintToBin(abi);
	bs = bigintToBin(bbi);
	int al = as.length();
	int bl = bs.lenght();
	int l;
	if (al != bl) {
		if (al < bl) {
			for (int i = 0; i < bl - al; i++) {
				as = "0" + as;
			}
			l = bl;
		}
		else {
			for (int i = 0; i < al - bl; i++) {
				bs = "0" + bs;
			}
			l = al;
		}
	}
	s = "";
	for (int i = l - 1; i >= 0; i--) {
		if ((as[i] == "1") && (bs[i] == "1")) {
			s = "0" + s;
		}
		else {
			s = "1" + s;
		}
	}
	BigInt res = binToBigint(s);
	res.min = (a.min + b.min) % 2;
	return res;
};
BigInt operator|(const BigInt& a, const BigInt& b) {
	std::string as, bs, s;
	BigInt abi, bbi;
	abi.data = a.data;
	bbi.data = b.data;
	abi.min = 0;
	bbi.min = 0;
	as = bigintToBin(abi);
	bs = bigintToBin(bbi);
	int al = as.length();
	int bl = bs.lenght();
	int l;
	if (al != bl) {
		if (al < bl) {
			for (int i = 0; i < bl - al; i++) {
				as = "0" + as;
			}
			l = bl;
		}
		else {
			for (int i = 0; i < al - bl; i++) {
				bs = "0" + bs;
			}
			l = al;
		}
	}
	s = "";
	for (int i = l - 1; i >= 0; i--) {
		if ((as[i] == "1") || (bs[i] == "1")) {
			s = "0" + s;
		}
		else {
			s = "1" + s;
		}
	}
	BigInt res = binToBigint(s);
	res.min = (a.min + b.min) % 2;
	return res;
};

std::ostream& operator<<(std::ostream& o, const BigInt& i) {
	std::string s = "";
	if (i.min == 1) {
		s = s + "-";
	}
	s = s + i.data;
	o << s;
	return o;
};


