#include <iostream>
#include <ctime>
using namespace std;
const int NUMB = 10;

struct BigInteger{

	static const int base = 10;
	static const int size = 50;
	int digits[size];

	BigInteger() {
		for (int i = 0; i < size; i++) {
			digits[i] = 0;
		}
	}
	BigInteger(int x) {
		for (int i = 0; i < size; i++) {
			digits[i] = 0;
		}
		int i = 0;
		while (x) {
			digits[i++] = x % 10;
			x /= base;
		}
	}
	BigInteger operator+=(const BigInteger other) {
		for (int i = 0; i < size; i++) {
		    digits[i] += other.digits[i];
		}

		for (int i = 0; i < size - 1; i++) {
			if (digits[i] >= base) {
				digits[i] -= base;
				digits[i + 1]++;
			}
		}
		return *this;
	}
	BigInteger operator*(int x) {
		int n;
		BigInteger other = *this;
		for(int i =0; i<size; i++){
			other.digits[i] *= x;
		}
		for (int i = 0; i < size - 1; i++) {
			if (other.digits[i] >= base) {
				n = other.digits[i] / base;
				other.digits[i] -= n*base;
				other.digits[i + 1]+=n;
			}
		}
		return other;
	}
	BigInteger operator=(const BigInteger other) {
		for (int i = 0; i < size; i++) {
			digits[i] = other.digits[i];
		}
		return *this;
	}
	void inc(int k) {
		digits[0] += 1;
		int max = 0;
		for (int i = 0; i <= k; i++) {
			if (digits[i] > 9) {
				digits[i] %= 10;
				digits[i + 1]++;
			}
		}
		for (int i = k; i >= 0; i--) {
			if (digits[i] > max ) {
				max = digits[i];
			}
			if (digits[i] < max) {
				digits[i] = max;
			}
		}
	}
	BigInteger sort(int rank) {
		BigInteger other = *this;
		int c;
		for (int i = 1; i < rank; i++) {
			for (int j = i; j > 0 && other.digits[j - 1] < other.digits[j]; j--) {
				c = other.digits[j - 1];
				other.digits[j - 1] = other.digits[j];
				other.digits[j] = c;
			}
		}
		return other;
	}
};
/*Значение n-го разряда длинного числа*/
int rang_access(const BigInteger, int);
/*Кол-во разрядов неупорядоченного длинного*/
int rang(const BigInteger);
/*Сравнение на равенство длинных чисел*/
bool operator==(const BigInteger, const BigInteger);
/*Вывод длинных чисел*/
ostream& operator<<(ostream&, const BigInteger);

int main() {
	setlocale(0, "ru");
	int n, rank=1, rank1, count = 0;
	BigInteger sum = 0 ,numb, i;
	cout << "Введите максимальный разряд n: ";
	cin >> n;
	/* Создаем двумерный массив степеней(1..n) цифр(1..9)*/
	BigInteger** arr_pow = new BigInteger* [n];
	for (int i = 0; i < n; i++) {
		arr_pow[i] = new BigInteger[NUMB];
	}
	/*Заполняем массив степенями цифр*/
	for (int i = 0; i < NUMB; i++) {
		arr_pow[0][i] = i;
		for (int j = 0; j < n - 1; j++) {
			arr_pow[j + 1][i] = arr_pow[j][i] * i;
		}
	}
	while ((rank-1)!=n) {
		for (i = 0; rang_access(i, rank) != 1; i.inc(rank - 1)) {
			for (int j = 0; j < rank; j++) {
				sum += arr_pow[rank-1][rang_access(i, j)];
			}
			rank1 = rang(sum);
			numb = sum.sort(rank1);
			if ((numb == i) && (rank1 == rank)) {
				cout << ++count << ") " << sum << endl;
			}
			sum = 0;
		}
		rank++;
	}
	cout << '\n' << "Время выполнения: " << (float)clock()/1000 << " секунд";
	/*Высвобождаем память*/
	for (int i = 0; i < n; i++) {
		delete[] arr_pow[i];
	}
	delete[] arr_pow;
	return 0;
}
int rang_access(const BigInteger BigInt, int n) {
	return BigInt.digits[n];
}
int rang(const BigInteger BigInt) {
	int k = BigInteger::size;
	while (BigInt.digits[--k] == 0);
	return k + 1;
}
bool operator==(const BigInteger a, const BigInteger b) {
	for (int i = 0; i < BigInteger::size; i++) {
		if (a.digits[i] != b.digits[i]) {
			return false;
		}
	}
	return true;
}
ostream& operator<<(ostream& out, const BigInteger BigInt) {
	string res;
	bool flag = false;
	for (int i = BigInteger::size-1; i >= 0; i--) {
		if (BigInt.digits[i] != 0 || flag) {
			res += BigInt.digits[i] + '0';
			flag = true;
		}
	}
	if (res.length() == 0) {
		out << "0";
	}
	else {
		out << res;
	}
	return out;
}
