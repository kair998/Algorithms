//����5λС���ļӼ��˳���
#include<iostream>
#include<string>

#include<algorithm>

using namespace std;

class Myadd {
private:
	int a[106] = { 0 }, b[106] = { 0 }, c[106] = { 0 };
public:

	void init(int num[], string& str) {
		int len = str.size();  
		bool hasDot = false;  //�Ƿ����С����
		int dotpos = 0;  //С�������ַ����е�λ��

		//����С�����λ��
		for (int i = 0; i < len; i++) {
			if (str[i] == '.') {
				dotpos = i;
				hasDot = true;
				break;
			}
		}

		//������������
		int index = 0;
		for (int i = dotpos - 1; i >= 0; i--) {
			num[index++] = str[i] - '0';
		}

		//����С������
		if (hasDot) {
			//С������ռ�������100�±�֮��
			index = 100;
			for (int i = dotpos + 1; i < len; i++) {
				num[index++] = str[i] - '0';
			}
		}
		
	}

	string add(string& str1, string& str2) {
		init(a, str1);
		init(b, str2);

		//����carry�������λ�����ڹ�ϵ����
		int carry = 0;

		//����С������
		for (int i = 105; i >= 100; i--) {
			c[i] = a[i] + b[i] + carry;
			carry = c[i] / 10;
			c[i] %= 10;
		}

		for (int i = 0; i < 100; i++) {
			c[i] = a[i] + b[i] + carry;
			carry = c[i] / 10;
			c[i] %= 10;
		}

		int zeroInt = 0;
		for (int i = 99; i >=0; i--) {
			if (c[i] == 0) {
				zeroInt++;
			}
			else {
				break;
			}
		}

		int zeroFloat = 0;
		for (int i = 104; i >= 100; i--) {
			if (c[i] == 0) {
				zeroFloat++;
			}
			else {
				break;
			}
		}
		string result;
		if (carry > 0) {
			result += to_string(carry);
		}

		//�����������
		for (int i = 99 - zeroInt; i >= 0; i--) {
			result += to_string(c[i]);
		}

		if (result.empty()) {
			result = "0";
		}

		//���С������
		result += ".";
		for (int i = 100; i < 105 - zeroFloat; i++) {
			result += to_string(c[i]);
		}

		return result;
	}
};

class Mysub {
private:
	int a[105] = { 0 }, b[105] = { 0 }, c[105] = { 0 };

public:
	void init(int num[], const std::string& str) {
		int len = str.size();
		bool hasDot = false;  // �Ƿ����С����
		int dotpos = 0;      // С�������ַ����е�λ��

		// ����С�����λ��
		for (int i = 0; i < len; i++) {
			if (str[i] == '.') {
				dotpos = i;
				hasDot = true;
				break;
			}
		}

		// ������������
		int index = 0;
		for (int i = dotpos - 1; i >= 0; i--) {
			num[index++] = str[i] - '0';
		}

		// ����С������
		if (hasDot) {
			// С������ռ�������100�±�֮��
			index = 100;
			for (int i = dotpos + 1; i < len; i++) {
				num[index++] = str[i] - '0';
			}
		}
	}

	bool isGreaterOrEqual(const std::string& str1, const std::string& str2) {
		// ȥ��С����
		std::string s1 = str1, s2 = str2;
		s1.erase(std::remove(s1.begin(), s1.end(), '.'), s1.end());
		s2.erase(std::remove(s2.begin(), s2.end(), '.'), s2.end());

		// ���볤��
		while (s1.size() < s2.size()) s1 = "0" + s1;
		while (s2.size() < s1.size()) s2 = "0" + s2;

		return s1 >= s2;
	}

	std::string sub(const std::string& str1, const std::string& str2) {
		bool isNegetive = false;

		if (!isGreaterOrEqual(str1, str2)) {
			isNegetive = true;
			init(a, str2);
			init(b, str1);
		}
		else {
			init(a, str1);
			init(b, str2);
		}
		
		// �ж��Ƿ��λ
		bool borrow = false;

		// ����С������
		for (int i = 104; i >= 100; i--) {
			c[i] = a[i] - b[i] - borrow;
			if (c[i] < 0) {
				c[i] += 10;
				borrow = true;
			}
			else {
				borrow = false;
			}
		}

		// ������������
		for (int i = 0; i < 100; i++) {
			c[i] = a[i] - b[i] - borrow;
			if (c[i] < 0) {
				c[i] += 10;
				borrow = true;
			}
			else {
				borrow = false;
			}
		}

		// ȥ����������ǰ����
		int zeroInt = 0;
		for (int i = 99; i >= 0; i--) {
			if (c[i] == 0) {
				zeroInt++;
			}
			else {
				break;
			}
		}

		// ȥ��С�����ֺ���
		int zeroFloat = 0;
		for (int i = 104; i >= 100; i--) {
			if (c[i] == 0) {
				zeroFloat++;
			}
			else {
				break;
			}
		}

		std::string result;

		if (isNegetive) {
			result += "-";
		}

		// �����������
		for (int i = 99 - zeroInt; i >= 0; i--) {
			result += to_string(c[i]);
		}

		if (result.empty()) {
			result = "0";
		}

		// ���С������
		result += ".";
		for (int i = 100; i < 105 - zeroFloat; i++) {
			result += to_string(c[i]);
		}

		return result;
	}
};

class Mymul {
private:
    int a[105] = { 0 }; // �洢��һ������������С������
    int b[105] = { 0 }; // �洢�ڶ�������������С������
    int c[211] = { 0 }; // �洢�˷������c[0]-c[200] ���������֣�c[201]-c[210] ��С������

public:
    // ��ʼ�����������ַ���ת��Ϊ����
    void init(int num[], const std::string& str) {
        int len = str.size();
        bool hasDot = false;  // �Ƿ����С����
        int dotpos = 0;       // С�������ַ����е�λ��

        // ����С�����λ��
        for (int i = 0; i < len; i++) {
            if (str[i] == '.') {
                dotpos = i;
                hasDot = true;
                break;
            }
        }

        // �����������֣��ӵ�λ����λ�洢��
        int index = 0;
        for (int i = dotpos - 1; i >= 0; i--) {
            num[index++] = str[i] - '0';
        }

        // ����С�����֣��Ӹ�λ����λ�洢��
        if (hasDot) {
            index = 100; // С�����ִ��±� 100 ��ʼ�洢
            for (int i = dotpos + 1; i < len; i++) {
                num[index++] = str[i] - '0';
            }
        }
    }

    // �߾��ȳ˷�
    std::string mul(const std::string& str1, const std::string& str2) {
        init(a, str1);
        init(b, str2);

        // ����С�������λ��
        int dot1 = str1.find('.');
        int dot2 = str2.find('.');
        int totalDecimal = 0;
        if (dot1 != std::string::npos) totalDecimal += (str1.size() - dot1 - 1);
        if (dot2 != std::string::npos) totalDecimal += (str2.size() - dot2 - 1);

        // �˷�����
        for (int i = 0; i < 105; i++) {
            for (int j = 0; j < 105; j++) {
                c[i + j] += a[i] * b[j]; // ��λ���
            }
        }

        // �����λ
        for (int i = 0; i < 210; i++) {
            if (c[i] >= 10) {
                c[i + 1] += c[i] / 10;
                c[i] %= 10;
            }
        }

        // ȷ��С�����λ��
        int dotPos = totalDecimal;

        // ȥ����������ǰ����
        int zeroInt = 0;
        for (int i = 200; i >= 0; i--) {
            if (c[i] == 0) {
                zeroInt++;
            } else {
                break;
            }
        }

        // ȥ��С�����ֺ���
        int zeroFloat = 0;
        for (int i = 210; i >= 201; i--) {
            if (c[i] == 0) {
                zeroFloat++;
            } else {
                break;
            }
        }

        // ��������ַ���
        std::string result;

        // �����������
        for (int i = 200 - zeroInt; i >= 0; i--) {
            result += std::to_string(c[i]);
        }

        // �����������Ϊ�գ�����
        if (result.empty()) {
            result = "0";
        }

        // ���С������
        if (dotPos > 0) {
            result += ".";
            for (int i = 201; i <= 201 + dotPos - 1; i++) {
                result += std::to_string(c[i]);
            }
        }

        return result;
    }
};

class Test {
	public:
		int tadd() {
			Myadd myadd;
			string num1, num2;
			cout << "����������100λ������5λС�����������һ����: ";
			cin >> num1;
			cout << "������ڶ�����: ";
			cin >> num2;

			string result = myadd.add(num1, num2);
			cout << "��ӽ��: " << result << endl;

			return 0;
		}
		
		int tsub() {
			Mysub mysub;
			string num1, num2;
			cout << "����������100λ������5λС�����������һ����: ";
			cin >> num1;
			cout << "������ڶ�����: ";
			cin >> num2;

			string result = mysub.sub(num1, num2);
			cout << "������: " << result << endl;

			return 0;

		}

		int tmul() {
			Mymul mymul;
			string num1, num2;
			cout << "����������100λ������5λС�����������һ����: ";
			cin >> num1;
			cout << "������ڶ�����: ";
			cin >> num2;

			string result = mymul.mul(num1, num2);
			cout << "��˽��: " << result << endl;

			return 0;
		}
};

class HighPrecisionDivision {
private:
	int a[100], b, c[100]; // a: ������, b: ����, c: ���
public:
	// ��ʼ�����������ַ���ת��Ϊ��������
	int init(int a[], string& s) {
		int len = s.size();
		for (int i = 0; i < len; i++) {
			a[i] = s[len - i - 1] - '0'; // ��ת�洢��a[0] �����λ
		}
		return len;
	}

	// �߾��ȳ�������
	int hd() {
		string s1;
		cin >> s1 >> b; // ���뱻�����ͳ���
		int lena = init(a, s1); // ��ʼ��������
		int lenc = 0; // �����λ��
		int x = 0; // ����
		// �����λ��ʼ��λ����
		for (int i = lena - 1; i >= 0; i--) {
			x = x * 10 + a[i]; // ��ǰλ��ֵ��������
			c[lenc++] = x / b; // ���㵱ǰλ����
			x %= b; // ��������
		}
		// ȥ��ǰ����
		int start = 0;
		while (start < lenc && c[start] == 0) {
			start++;
		}
		// ������
		if (start == lenc) {
			cout << "0"; // ��������0
		}
		else {
			for (int i = start; i < lenc; i++) {
				cout << c[i];
			}
		}
		cout << endl;
		return 0;
	}
};

int main() {
	Test tc02;
	tc02.tmul();
	return 0;
}