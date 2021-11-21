#ifndef REAL_TEST
#define REAL_TEST
#include <iostream>
#include <vector>
#include <string>
#endif

class vector_wrapper {
private:
	std::vector <long long int> vector;
public:
	long long int size;
	vector_wrapper(int N = 0) : size(N) {

	}
	void push_back(long long int N) {
		vector.push_back(N);
		++size;
	}
	long long int& operator[](unsigned int index) {
		if (index == size) {
			vector.push_back(0);
			++size;
		}
		return vector[index];
	}
	long long int operator[](unsigned int index) const {
		if (index >= size) {
			return 0;
		}
		return vector[index];
	}
	void remove_leading_zeroes() {
		while (size && !vector[size - 1]) {
			vector.pop_back();
			--size;
		}
	}
	void clear() {
		size = 0;
		vector.clear();
	}

	void operator=(const vector_wrapper& vec) {
		for (int i = 0; i < vec.size; ++i) {
			(*this)[i] = vec.vector[i];
		}
		size = vec.size;
	}
};

void reverse(vector_wrapper& arr) {
	for (unsigned int i = 0; i < arr.size; ++i) {
		std::swap(arr[i], arr[arr.size - 1 - i]);
	}
}

class BigInteger {
private:
	int base = 10;
	bool negative;
	bool zero;
	vector_wrapper digits;

	int compare(const BigInteger& bint) const {
		if (negative) {
			if (bint.negative) {
				// both < 0
				if (digits.size - bint.digits.size) {
					return bint.digits.size - digits.size;
				}
				//now they have equal number of digits
				for (int i = digits.size - 1; i >= 0; --i) {
					if (digits[i] - bint.digits[i]) {
						return bint.digits[i] - digits[i];
					}
				}
				return 0;
			}
			else {
				return -1;
			}
		}
		else {
			if (bint.negative) {
				return 1;
			}
			else {
				// both >= 0
				if (digits.size - bint.digits.size) {
					return digits.size - bint.digits.size;
				}
				//now they have equal number of digits
				for (int i = digits.size - 1; i >= 0; --i) {
					if (digits[i] - bint.digits[i]) {
						return digits[i] - bint.digits[i];
					}
				}
				//if they are both zero, this cycle won't happen
				return 0;
			}
		}
	}
	int compare_by_abs(const BigInteger& bint) const {
		if (zero) {
			if (bint.zero) {
				return 0;
			}
			return -1;
		}
		if (bint.zero) {
			return 1;
		}
		// both > 0
		if (digits.size - bint.digits.size) {
			return digits.size - bint.digits.size;
		}
		//now they have equal number of digits
		for (int i = digits.size - 1; i >= 0; --i) {
			if (digits[i] - bint.digits[i]) {
				return digits[i] - bint.digits[i];
			}
		}
		return 0;
	}

	void nullify() {
		zero = true;
		negative = false;
		digits.clear();
	}

	void carry_add(const BigInteger& bint) {
		long long int carry = 0;
		int k = (bint.digits.size > digits.size ? bint.digits.size : digits.size);
		for (int i = 0; (i < k) || carry; ++i) {
			if (bint.digits[i] + digits[i] + carry >= base) {
				(digits[i] += bint.digits[i] + carry) %= base;
				carry = 1;
			}
			else {
				digits[i] += bint.digits[i] + carry;
				carry = 0;
			}
		}
	}
	void carry_substr(const BigInteger& bint) {
		long long int carry = 0;
		int k = (bint.digits.size > digits.size ? bint.digits.size : digits.size);
		for (int i = 0; i < k; ++i) {
			if (digits[i] < bint.digits[i] + carry) {
				digits[i] += (base - bint.digits[i] - carry);
				carry = 1;
			}
			else {
				digits[i] -= bint.digits[i] + carry;
				carry = 0;
			}
		}
		digits.remove_leading_zeroes();
	}
	void carry_reverse_substr(const BigInteger& bint) {
		long long int carry = 0;
		int k = (bint.digits.size > digits.size ? bint.digits.size : digits.size);
		for (int i = 0; (i < k) || carry; ++i) {
			if (bint.digits[i] < digits[i] + carry) {
				digits[i] = base + bint.digits[i] - digits[i] - carry;
				carry = 1;
			}
			else {
				digits[i] = bint.digits[i] - digits[i] - carry;
				carry = 0;
			}
		}
		digits.remove_leading_zeroes();
	}
public:
	BigInteger(int N = 0) {
		//digits.push_back(N); if base is bigger than any int

		if (N < 0) {
			negative = true;
			zero = false;
			N *= -1;
		}
		else {
			negative = false;
			if (N == 0) {
				zero = true;
			}
			else {
				zero = false;
			}
		}

		while (N) {
			digits.push_back(N % base);
			N /= base;
		}
		reverse(digits);
	}

	BigInteger(const BigInteger& bint) {
		zero = bint.zero;
		negative = bint.negative;
		//base = bint.base;
		digits = bint.digits;
	}
	BigInteger& operator=(const BigInteger& bint) {
		if (this == &bint) {
			return *this;
		}
		zero = bint.zero;
		negative = bint.negative;
		//base = bint.base;
		digits = bint.digits;
	}

	bool operator==(const BigInteger& bint) const {
		if ((negative != bint.negative) || (zero != bint.zero) || (digits.size - bint.digits.size)) {
			return false;
		}
		for (int i = 0; i < digits.size; ++i) {
			if (digits[i] - bint.digits[i]) {
				return false;
			}
		}
		return true;
	}

	bool operator>(const BigInteger& bint) const {
		if (zero) {
			return bint.negative;
		}
		if (!negative) {
			// now it is > 0
			//if bint is <= 0, we return
			if (bint.zero || bint.negative) {
				return true;
			}
			//now they're both positive
			if (digits.size - bint.digits.size) {
				return digits.size > bint.digits.size;
			}
			//now they have the same number of digits
			for (int i = digits.size - 1; i >= 0; --i) {
				if (digits[i] - bint.digits[i]) {
					return digits[i] > bint.digits[i];
				}
			}
			//equal
			return false;
		}
		else {
			// now it's negative
			if (bint.zero || !bint.negative) {
				return false;
			}
			//both negative
			//let's forget about that silly flag and compare them as usual
			if (digits.size - bint.digits.size) {
				return digits.size < bint.digits.size;
			}
			//now they have the same number of digits
			for (int i = digits.size - 1; i >= 0; --i) {
				if (digits[i] - bint.digits[i]) {
					return digits[i] < bint.digits[i];
				}
			}
			//equal
			return false;
		}
	}

	bool operator<(const BigInteger& bint) const {
		return bint > *this;
	}

	bool operator<= (const BigInteger& bint) const {
		return !(*this > bint);
	}

	bool operator>= (const BigInteger& bint) const {
		if (zero) {
			return bint.zero || bint.negative;
		}
		if (!negative) {
			if (bint.zero || bint.negative) {
				return true;
			}
			//now they're both positive
			if (digits.size - bint.digits.size) {
				return digits.size > bint.digits.size;
			}
			//now they have the same number of digits
			for (int i = digits.size - 1; i >= 0; --i) {
				if (digits[i] - bint.digits[i]) {
					return digits[i] > bint.digits[i];
				}
			}
			//equal
			return true;
		}
		else {
			if (!bint.negative) {
				return false;
			}
			if (digits.size - bint.digits.size) {
				return digits.size < bint.digits.size;
			}
			//now they have the same number of digits
			for (int i = digits.size - 1; i >= 0; --i) {
				if (digits[i] - bint.digits[i]) {
					return digits[i] < bint.digits[i];
				}
			}
			//equal
			return true;
		}
	}

	bool operator!= (const BigInteger& bint) const {
		return !(*this == bint);
	}

	BigInteger& operator+=(const BigInteger& bint) {
		if (bint.zero) {
			return *this;
		}
		if (!negative) {
			if (!bint.negative) {
				carry_add(bint);
				zero = false;
			}
			else {
				int sign = compare_by_abs(bint);
				if (sign > 0) {
					carry_substr(bint);
				}
				else {
					if (sign == 0) {
						nullify();
					}
					else {
						carry_reverse_substr(bint);
						negative = true;
						zero = false;
					}
				}
			}
		}
		else {
			if (bint.negative) {
				carry_add(bint);
			}
			else {
				int sign = compare_by_abs(bint);
				if (sign > 0) {
					carry_substr(bint);
				}
				else {
					if (sign == 0) {
						nullify();
					}
					else {
						carry_reverse_substr(bint);
						negative = false;
					}
				}
			}
		}
		return *this;
	}

	BigInteger& operator-=(const BigInteger& bint) {
		if (bint.zero) {
			return *this;
		}
		if (!negative) {
			if (!bint.negative) {
				int sign = compare_by_abs(bint);
				if (sign > 0) {
					carry_substr(bint);
				}
				else {
					if (sign == 0) {
						nullify();
					}
					else {
						carry_reverse_substr(bint);
						negative = true;
						zero = false;
					}
				}
			}
			else {
				carry_add(bint);
				zero = false;
			}
		}
		else {
			if (!bint.negative) {
				carry_add(bint);
			}
			else {
				int sign = compare_by_abs(bint);
				if (sign > 0) {
					carry_substr(bint);
				}
				else {
					if (sign == 0) {
						nullify();
					}
					else {
						carry_reverse_substr(bint);
						negative = false;
					}
				}
			}
		}
	}

	BigInteger& operator++() {
		if (!negative) {
			carry_add(1);
			zero = false;
		}
		else {
			int sign = compare_by_abs(1);
			if (sign > 0) {
				carry_substr(1);
			}
			else {
				nullify();
			}
		}
		return *this;
	}
	BigInteger operator++(int) {
		if (!negative) {
			carry_add(1);
			zero = false;
		}
		else {
			int sign = compare_by_abs(1);
			if (sign > 0) {
				carry_substr(1);
			}
			else {
				nullify();
			}
		}
		return *this;
	}
	BigInteger& operator--() {
		if (!negative) {
			int sign = compare_by_abs(1);
			if (sign > 0) {
				carry_substr(1);
			}
			else {
				if (sign == 0) {
					nullify();
				}
				else {
					carry_reverse_substr(1);
					negative = true;
					zero = false;
				}
			}
		}
		else {
			carry_add(1);
		}
		return *this;
	}
	BigInteger operator--(int) {
		if (!negative) {
			int sign = compare_by_abs(1);
			if (sign > 0) {
				carry_substr(1);
			}
			else {
				if (sign == 0) {
					nullify();
				}
				else {
					carry_reverse_substr(1);
					negative = true;
					zero = false;
				}
			}
		}
		else {
			carry_add(1);
		}
		return *this;
	}
	/*
	BigInteger& operator*=(const BigInteger& bint) {
		
	}
	BigInteger& operator/=(const BigInteger& bint) {

	}
	BigInteger& operator%=(const BigInteger& bint) {

	}
	*/

	std::string toString() const{
		std::string str;
		if (zero) {
			return "0";
		}
		if (negative) {
			str += "-";
		}
		for (int i = digits.size - 1; i >= 0 ; --i) {
			str += std::to_string(digits[i]);
		}
		return str;
	}
	//~BigInteger() {
	//	digits.~vector();
	//}
};

BigInteger operator+(const BigInteger& bint1, const BigInteger& bint2) {
	BigInteger temp(bint1);
	temp += bint2;
	return temp;
}

BigInteger operator-(const BigInteger& bint1, const BigInteger& bint2) {
	BigInteger temp(bint1);
	temp -= bint2;
	return temp;
}

//BigInteger operator*(const BigInteger& bint1, const BigInteger& bint2) {
//
//}
//BigInteger operator*(const BigInteger& bint, int N) {
//
//}
//BigInteger operator*(int N, const BigInteger& bint) {
//
//}
//
//BigInteger operator/(const BigInteger& bint1, const BigInteger& bint2) {
//
//}
//BigInteger operator/(const BigInteger& bint, int N) {
//
//}
//BigInteger operator/(int N, const BigInteger& bint) {
//
//}
//
//BigInteger operator%(const BigInteger& bint1, const BigInteger& bint2) {
//
//}
//BigInteger operator%(const BigInteger& bint, int N) {
//
//}
//BigInteger operator%(int N, const BigInteger& bint) {
//
//}
//
//
//
//std::istream& operator>>(std::istream stream, BigInteger bint) {
//
//}
std::ostream& operator<<(std::ostream& stream, const BigInteger& bint) {
	return stream << bint.toString();
}
