#include<iostream>
#include<string>
using namespace std;

class highAccuracyAlgorithm {

	class hadda {
	private:
		int a[301], b[301], c[301];
	public:
		int init(int a[]) {
			string s;
			cin >> s;
			int len = s.size();
			for (int i = 0; i < len; i++) {
				a[i] = s[len - 1 - i] - '0';
			}
			return len;
		}
		//从低位到高位录入
		int hadd() {
			int lena = init(a);
			int lenb = init(b);
			int lenc = max(lena, lenb);
			for (int i = 0; i < lenc; i++) {
				c[i] += a[i] + b[i];

				if (c[i] >= 10) {
					c[i + 1]++;
					c[i] %= 10;
				}
			}
			//加的时候可能会进位，减的时候只可能会减小。
			while (c[lenc] == 0 && lenc > 0) {
				lenc--;
			}
			for (int i = lenc; i >= 0; i--) {
				cout << c[i];
			}
			return 0;
		}
	};

	class subtraction {
	private:
		int a[301], b[301], c[301];
	public:
		int init(int a[],string &s) {
			cin >> s;
			int len = s.size();
			for (int i = 0; i < len; i++) {
				a[i] = s[len - i - 1] - '0';
			}
			return len;
		}

		int hsub() {
			string s1, s2;
			int lena = init(a, s1);
			int lenb = init(b, s2);
			int lenc = max(lena, lenb);

			if (lena < lenb || (lena == lenb && s1 < s2)) {
				swap(a,b);
				cout<<"-";
			}

			for (int i = 0; i < lenc; i++) {
				c[i] += a[i] - b[i];
				if (c[i] < 0) {
					c[i + 1]--;
					c[i] += 10;
				}
			}
			lenc--;
			while (c[lenc] == 0 && lenc > 0) {
				lenc--;
			}
			for (int i = lenc; i >= 0; i--) {
				cout << c[i];

			}
			return 0;
		}
	};

	class hmutia{
	private:
		int a[301], b[301], c[601];

	public:
		int init(int a[]) {
			string s;
			cin >> s;
			int len = s.size();
			for (int i = 0; i < len; i++) {
				a[i] = s[len - 1 - i] - '0';
			}
			return len;
		}
		int hmuti() {
			int lena = init(a);
			int lenb = init(b);
			int lenc = lena + lenb;
			for (int i = 0; i < lena; i++) {
				for (int j = 0; j < lenb; j++) {
					c[i + j] += a[i] * b[j];
				}
			}
			for (int i = 0; i < lenc; i++) {
				if (c[i] >= 10) {
					c[i + 1] += c[i] / 10;
					c[i] %= 10;
				}
			}
			while (c[lenc] == 0 && lenc > 0) {
				lenc--;
			}
			for (int i = lenc; i >= 0; i--) {
				cout << c[i];
			}
			return 0;
		}
	};

	class hdivisiona {
	public:
		int hd() {
			char str[100];
			int a[100], b, c[100];
			int lena, lenc;
			int x = 0;
			int i;

			memset(a, 0, sizeof(a));
			memset(c, 0, sizeof(c));

			cin >> str;
			cin >> b;

			lena = strlen(str);
			for (i = 0; i < lena; i++) {
				a[i + 1] = str[i] - '0';
			}

			for (i = 1; i <= lena; i++) {
				c[i] = (x * 10 + a[i]) / b;
				x = (x * 10 + a[i]) % b;
			}

			lenc = 1;

			while (c[lenc] == 0 && lenc < lena) {
				lenc++;
			}
			for (i = lenc; i <= lenc; i++) {
				cout << c[i];
			}
			cout << endl;
			return 0;
		}
	};
};

