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
	long long int& operator[](int index) {
		while (index >= size) {
			vector.push_back(0);
			++size;
		}
		return vector[index];
	}
	long long int operator[](int index) const {
		if (index >= size || index < 0) {
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
		/*for (int i = 0; i < vec.size; ++i) {
			(*this)[i] = vec.vector[i];
		}*/
		vector = vec.vector;
		size = vec.size;
	}
};

void reverse(vector_wrapper& arr) {
	for (unsigned int i = 0; i < arr.size / 2; ++i) {
		std::swap(arr[i], arr[arr.size - 1 - i]);
	}
}

class BigInteger {
private:
#ifdef VS_10
	int base;
#else
	int base = 10;
#endif

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

	void multiply_by_digit(int N) {
		//it shouldn't be called if N >= base
		if (N == 0) {
			nullify();
			return;
		}
		long long int addendum;
		int carry = 0;
		for (int i = 0; (i < digits.size) || carry; ++i) {
			addendum = digits[i] * N + carry;
			carry = addendum / base;
			digits[i] = addendum % base;
		}
	}
	BigInteger multiplied_by_digit(int N) const {
		//same goes for this one
		BigInteger bint(*this);
		bint.multiply_by_digit(N);
		return bint;
	}
	void multiply_by_base_power(int N) {
		if (N == 0) {
			return;
		}
		int size = digits.size;
		for (int i = 0; i < size; ++i) {
			digits[size - 1 + N - i] = (const_cast<const vector_wrapper&>(digits))[size - 1 - i];
		}
		for (int i = 0; i < N; ++i) {
			digits[i] = 0;
		}
	}
	BigInteger multiplied_by_digit_with_shift_by(int digit, int N) {
		//and for this one...
		BigInteger bint(*this);
		bint.multiply_by_digit(digit);
		bint.multiply_by_base_power(N);
		return bint;
	}
	/*void multiply_by_digit_with_shift_by(int digit, int N) {
		multiply_by_digit(digit);
		multiply_by_base_power(N);
	}*/
	void checkless_multiply_by_number(const BigInteger& bint) {
		//only called from *= for (const int&)s
		BigInteger res;
		for (int i = 0; i < bint.digits.size; ++i) {
			res += multiplied_by_digit_with_shift_by(bint.digits[i], i);
		}
		*this = res;
		if (bint.negative) {
			negative = !negative;
		}
	}

	BigInteger n_digit_prefix(int N) {
		if (N >= digits.size) {
			return *this;
		}
		BigInteger res;
		for (int i = 0; i < N; ++i) {
			res.digits[N - 1 - i] = digits[digits.size - 1 - i];
		}
		res.digits.size = N;
		res.zero = false;
		return res;
	}

	void add_one_digit_to_the_end(int N) {
		int size = digits.size;
		for (int i = 0; i < size; ++i) {
			digits[size - i] = const_cast <const vector_wrapper&>(digits)[size - 1 - i];
		}
		digits[0] = N;
	}

	void add_n_digits_from_mth_of(const BigInteger& bint, int n, int m) {
		//Theta(new length of number)
		if (n <= 0) {
			return;
		}
		/*if (n > bint.digits.size - m) {
			n = bint.digits.size - m;
		}*/

		// m is 0 if you want to copy from the "bint.digits.size - 1" index
		int size = digits.size;
		//there's a chance that n might be too big, thus we'll have to adjust it
		for (int i = 0; i < size; ++i) {
			digits[size - 1 - i + n] = const_cast <const vector_wrapper&>(digits)[size - 1 - i];
		}
		// 1 2 3 4 5; 2, 2
		// bint.digits = (5, 4, 3, 2, 1); *this.digits= (2, 2) => (k1 = ?, k2 = ?, 2, 2)
		//"bint.digits.size - 1 - m" is the last index we need to get in [] => the 1st one should be "bint.digits.size - 1 - m - n"
		//now m = 1. 

		//if m 
		for (int i = 0; i < n; ++i) {
			digits[i] = bint.digits[bint.digits.size - m - n + i];
		}
	}

public:
	void assign_zero() {
		nullify();
	}
	BigInteger(int N = 0) {
		//digits.push_back(N); if base is bigger than any int
#ifdef VS_10
		base = 10;
#endif 
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
		//reverse(digits);
	}

	BigInteger(const BigInteger& bint) {
		zero = bint.zero;
		negative = bint.negative;
		base = bint.base;
		digits = bint.digits;
	}

	BigInteger(vector_wrapper& vec) {
		digits = vec;
		zero = false;
		negative = false;
	}

	BigInteger& operator=(const BigInteger& bint) {
		if (this == &bint) {
			return *this;
		}
		zero = bint.zero;
		negative = bint.negative;
		base = bint.base;
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
		return *this;
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

	BigInteger& operator*=(const BigInteger& bint) {
		if (zero) {
			return *this;
		}
		if (bint.zero) {
			nullify();
			return *this;
		}
		//now none of them == 0
		BigInteger res;
		for (int i = 0; i < bint.digits.size; ++i) {
			res += multiplied_by_digit_with_shift_by(bint.digits[i], i);
		}
		*this = res;
		if (bint.negative) {
			negative = !negative;
		}
		return *this;
	}
	BigInteger& operator*=(const int& N) {
		if (zero || N == 1) {
			return *this;
		}
		if (N == 0) {
			nullify();
			return *this;
		}
		//now neither of us is 0
		if (N == -1) {
			negative = !negative;
			return *this;
		}
		return *this *= BigInteger(N);
	}

	//BigInteger& operator/=(const BigInteger& bint) {
	//	if (zero || bint.zero) {
	//		return *this;
	//	}
	//	//now we start ignoring the sign of *this
	//	//BigInteger temp(*this);
	//	int l = -1, r = base;
	//	BigInteger subtrahend;
	//	int m;
	//	vector_wrapper vec;
	//	while (r - l > 1) {
	//		m = (l+r)/2;
	//		subtrahend = bint;
	//		subtrahend *= m;
	//		if (digits.size < subtrahend.digits.size) {
	//			// subtrahend is too big
	//			// m doesn't fit
	//			r = m;
	//		}
	//		else {
	//			//now subtrahend might fit
	//			subtrahend.multiply_by_base_power(digits.size - subtrahend.digits.size);
	//			//now substraction is possible (in our case we don't substract and compare with zero, instead we just compare)
	//			if (compare_by_abs(subtrahend) >= 0) {
	//				//m fits
	//				l = m;
	//			}
	//			else {
	//				//m doesn't fit
	//				r = m;
	//			}
	//		}
	//	}
	//	vec.push_back(l);
	//	//found the digit, it's equal to l
	//	if (l == 0) {
	//		
	//	}
	//	subtrahend = bint;
	//	subtrahend *= l;
	//	subtrahend.multiply_by_base_power(digits.size - subtrahend.digits.size);
	//	(*this) -= subtrahend;
	//	if (bint.negative) {
	//		negative = !negative;
	//	}
	//	return *this;
	//}
	BigInteger& operator/=(const BigInteger& bint) {
		if (zero || bint.zero) {
			return *this;
		}
		if (digits.size < bint.digits.size) {
			nullify();
			return *this;
		}
		// now *this has at least as many digits as bint
		// 12345 / 222
		BigInteger temp;
		vector_wrapper vec;
		int l, r;
		BigInteger subtrahend;
		int m;
		int k = 0;
		int size;
		bool added_digits;
		bool first = true;
		while (k < digits.size) {
			if (k) {
				first = false;
			}
			added_digits = false;
			if (!temp.digits.size && digits[digits.size - 1 - k] == 0) {
				k++;
				vec.push_back(0);
				//temp.add_one_digit_to_the_end(0);
				continue;
			}
			if (bint.digits.size - temp.digits.size > digits.size - k) {
				temp.add_n_digits_from_mth_of(*this, digits.size - k, k);
				for (int i = 0; i < digits.size - k - 1; ++i) { //only if >= 2 digits were added
					vec.push_back(0);
				}
				k = digits.size;
				added_digits = true;
			}
			else {
				size = bint.digits.size - temp.digits.size;
				if (added_digits) {
					for (int i = 0; i < size - 1; ++i) {
						vec.push_back(0);
					}
				}
				temp.add_n_digits_from_mth_of(*this, size, k);
				if (!first && size) {
					added_digits = true;
				}
				k += size;
			}
			temp.zero = false;
			if (bint.compare_by_abs(temp) > 0) {
				//need next prefix
				if (digits.size == k) {
					//there isn't a bigger one
					if (!vec.size) {
						nullify();
					}
					else {
						vec.push_back(0);
						(*this).digits = vec;
						if (bint.negative) {
							negative = !negative;
						}
					}
					reverse(digits);
					return *this;
				}
				//make temp equal to the next prefix
				temp.add_one_digit_to_the_end(digits[digits.size - 1 - k]);
				if (added_digits) {
					vec.push_back(0);
				}
				added_digits = true;
				k++;
			}
			l = 0, r = base;
			//now temp is what we have to substract from
			//what do we substract?
			//*this = 12345, bint = 222, temp =	1234
			while (r - l > 1) {
				m = (r + l) / 2;
				subtrahend = bint;
				subtrahend.multiply_by_digit(m);
				if (temp.digits.size < subtrahend.digits.size) {
					// subtrahend is too big
					// m doesn't fit
					r = m;
				}
				else {
					if (temp.compare_by_abs(subtrahend) >= 0) {
						// m fits
						l = m;
					}
					else {
						r = m;
					}
				}
			}
			// now l == digit_that_fits
			subtrahend = bint;
			subtrahend.multiply_by_digit(l);
			temp.carry_substr(subtrahend);
			vec.push_back(l);
		}
		//if we're here, result is not 0.
		(*this).digits = vec;
		if (bint.negative) {
			negative = !negative;
		}
		reverse(digits);
		return *this;
	}
	
	BigInteger& operator%=(const BigInteger& bint) {
		if (zero || bint.zero) {
			return *this;
		}
		if (digits.size < bint.digits.size) {
			//negative = bint.negative;
			return *this;
		}
		// now *this has at least as many digits as bint
		BigInteger temp;
		/*
		vector_wrapper vec;
		*/
		int l, r;
		BigInteger subtrahend;
		int m;
		int k = 0;
		int size;
		bool first = true;
		while (k < digits.size) {
			//if (k) {
			//	first = false;
			//}
			/*
			added_digits = false;
			*/
			if (!temp.digits.size && digits[digits.size - 1 - k] == 0) {
				k++;
				/*
				vec.push_back(0);
				*/
				continue;
			}
			if (bint.digits.size - temp.digits.size > digits.size - k) {
				temp.add_n_digits_from_mth_of(*this, digits.size - k, k);
				/*
				for (int i = 0; i < digits.size - k; ++i) {
					vec.push_back(0);
				}
				*/
				k = digits.size;
				/*
				added_digits = true;
				*/
			}
			else {
				size = bint.digits.size - temp.digits.size;
				/*
				if (added_digits) {
					for (int i = 0; i < size - 1; ++i) {
						vec.push_back(0);
					}
				}
				*/
				temp.add_n_digits_from_mth_of(*this, size, k);
				/*
				if (!first && size) {
					added_digits = true;
				}
				*/
				k += size;
			}
			temp.zero = false;
			if (bint.compare_by_abs(temp) > 0) {
				//need next prefix
				if (digits.size == k) {
					if (!temp.digits.size) {
						//is divisible
						nullify();
					}
					else {
						temp.negative = negative;
						*this = temp;
						//negative = bint.negative;
					}
					return *this;
				}
				//make temp equal to the next prefix
				temp.add_one_digit_to_the_end(digits[digits.size - 1 - k]);
				/*
				if (added_digits) {
					vec.push_back(0);
				}
				*/
				//added_digits = true;
				k++;
			}
			l = 0, r = base;
			//now temp is what we have to substract from
			//what do we substract?
			//*this = 12345, bint = 222, temp =	1234
			while (r - l > 1) {
				m = (r + l) / 2;
				subtrahend = bint;
				subtrahend.multiply_by_digit(m);
				if (temp.digits.size < subtrahend.digits.size) {
					// subtrahend is too big
					// m doesn't fit
					r = m;
				}
				else {
					if (temp.compare_by_abs(subtrahend) >= 0) {
						// m fits
						l = m;
					}
					else {
						r = m;
					}
				}
			}
			// now l == digit_that_fits
			subtrahend = bint;
			subtrahend.multiply_by_digit(l);
			temp.carry_substr(subtrahend);
			/*
			vec.push_back(l);
			*/
		}
		if (!temp.digits.size) {
			//is divisible
			nullify();
		}
		else {
			temp.negative = negative;
			*this = temp;
		}
		return *this;
	}

	BigInteger operator-() const {
		if (zero) {
			return *this;
		}
		BigInteger temp(*this);
		temp.negative = !temp.negative;
		return temp;
	}
	
	std::string toString() const {
		std::string str;
		if (zero) {
			return "0";
		}
		if (negative) {
			str += "-";
		}
		for (int i = digits.size - 1; i >= 0; --i) {
			str += std::to_string(digits[i]);
		}
		return str;
	}

	explicit operator bool() {
		return !zero;
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

BigInteger operator*(const BigInteger& bint1, const BigInteger& bint2) {
	BigInteger temp(bint1);
	temp *= bint2;
	return temp;
}

BigInteger operator/(const BigInteger& bint1, const BigInteger& bint2) {
	BigInteger temp(bint1);
	temp /= bint2;
	return temp;
}

BigInteger operator%(const BigInteger& bint1, const BigInteger& bint2) {
	BigInteger temp(bint1);
	temp %= bint2;
	return temp;
}

std::istream& operator>>(std::istream& stream, BigInteger& bint) {
	std::string str;
	stream >> str;
	bint.assign_zero();
	if (str[0] == '0') {
		return stream;
	}
	int i = 0;
	if (str[0] == '-') {
		++i;
	}
	for (; i < str.size(); ++i) {
		//
	}
}
std::ostream& operator<<(std::ostream& stream, const BigInteger& bint) {
	return stream << bint.toString();
}
