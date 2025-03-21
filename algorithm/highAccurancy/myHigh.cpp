//保留5位小数的加减乘除法
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
		bool hasDot = false;  //是否存在小数点
		int dotpos = 0;  //小数点在字符串中的位置

		//查找小数点的位置
		for (int i = 0; i < len; i++) {
			if (str[i] == '.') {
				dotpos = i;
				hasDot = true;
				break;
			}
		}

		//处理整数部分
		int index = 0;
		for (int i = dotpos - 1; i >= 0; i--) {
			num[index++] = str[i] - '0';
		}

		//处理小数部分
		if (hasDot) {
			//小数部分占用数组的100下标之后
			index = 100;
			for (int i = dotpos + 1; i < len; i++) {
				num[index++] = str[i] - '0';
			}
		}
		
	}

	string add(string& str1, string& str2) {
		init(a, str1);
		init(b, str2);

		//设置carry，处理进位，便于关系处理
		int carry = 0;

		//处理小数部分
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

		//添加整数部分
		for (int i = 99 - zeroInt; i >= 0; i--) {
			result += to_string(c[i]);
		}

		if (result.empty()) {
			result = "0";
		}

		//添加小数部分
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
		bool hasDot = false;  // 是否存在小数点
		int dotpos = 0;      // 小数点在字符串中的位置

		// 查找小数点的位置
		for (int i = 0; i < len; i++) {
			if (str[i] == '.') {
				dotpos = i;
				hasDot = true;
				break;
			}
		}

		// 处理整数部分
		int index = 0;
		for (int i = dotpos - 1; i >= 0; i--) {
			num[index++] = str[i] - '0';
		}

		// 处理小数部分
		if (hasDot) {
			// 小数部分占用数组的100下标之后
			index = 100;
			for (int i = dotpos + 1; i < len; i++) {
				num[index++] = str[i] - '0';
			}
		}
	}

	bool isGreaterOrEqual(const std::string& str1, const std::string& str2) {
		// 去掉小数点
		std::string s1 = str1, s2 = str2;
		s1.erase(std::remove(s1.begin(), s1.end(), '.'), s1.end());
		s2.erase(std::remove(s2.begin(), s2.end(), '.'), s2.end());

		// 补齐长度
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
		
		// 判断是否借位
		bool borrow = false;

		// 处理小数部分
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

		// 处理整数部分
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

		// 去除整数部分前导零
		int zeroInt = 0;
		for (int i = 99; i >= 0; i--) {
			if (c[i] == 0) {
				zeroInt++;
			}
			else {
				break;
			}
		}

		// 去除小数部分后导零
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

		// 添加整数部分
		for (int i = 99 - zeroInt; i >= 0; i--) {
			result += to_string(c[i]);
		}

		if (result.empty()) {
			result = "0";
		}

		// 添加小数部分
		result += ".";
		for (int i = 100; i < 105 - zeroFloat; i++) {
			result += to_string(c[i]);
		}

		return result;
	}
};

class Mymul {
private:
    int a[105] = { 0 }; // 存储第一个数的整数和小数部分
    int b[105] = { 0 }; // 存储第二个数的整数和小数部分
    int c[211] = { 0 }; // 存储乘法结果，c[0]-c[200] 是整数部分，c[201]-c[210] 是小数部分

public:
    // 初始化函数，将字符串转换为数组
    void init(int num[], const std::string& str) {
        int len = str.size();
        bool hasDot = false;  // 是否存在小数点
        int dotpos = 0;       // 小数点在字符串中的位置

        // 查找小数点的位置
        for (int i = 0; i < len; i++) {
            if (str[i] == '.') {
                dotpos = i;
                hasDot = true;
                break;
            }
        }

        // 处理整数部分（从低位到高位存储）
        int index = 0;
        for (int i = dotpos - 1; i >= 0; i--) {
            num[index++] = str[i] - '0';
        }

        // 处理小数部分（从高位到低位存储）
        if (hasDot) {
            index = 100; // 小数部分从下标 100 开始存储
            for (int i = dotpos + 1; i < len; i++) {
                num[index++] = str[i] - '0';
            }
        }
    }

    // 高精度乘法
    std::string mul(const std::string& str1, const std::string& str2) {
        init(a, str1);
        init(b, str2);

        // 计算小数点的总位数
        int dot1 = str1.find('.');
        int dot2 = str2.find('.');
        int totalDecimal = 0;
        if (dot1 != std::string::npos) totalDecimal += (str1.size() - dot1 - 1);
        if (dot2 != std::string::npos) totalDecimal += (str2.size() - dot2 - 1);

        // 乘法运算
        for (int i = 0; i < 105; i++) {
            for (int j = 0; j < 105; j++) {
                c[i + j] += a[i] * b[j]; // 逐位相乘
            }
        }

        // 处理进位
        for (int i = 0; i < 210; i++) {
            if (c[i] >= 10) {
                c[i + 1] += c[i] / 10;
                c[i] %= 10;
            }
        }

        // 确定小数点的位置
        int dotPos = totalDecimal;

        // 去除整数部分前导零
        int zeroInt = 0;
        for (int i = 200; i >= 0; i--) {
            if (c[i] == 0) {
                zeroInt++;
            } else {
                break;
            }
        }

        // 去除小数部分后导零
        int zeroFloat = 0;
        for (int i = 210; i >= 201; i--) {
            if (c[i] == 0) {
                zeroFloat++;
            } else {
                break;
            }
        }

        // 构建结果字符串
        std::string result;

        // 添加整数部分
        for (int i = 200 - zeroInt; i >= 0; i--) {
            result += std::to_string(c[i]);
        }

        // 如果整数部分为空，补零
        if (result.empty()) {
            result = "0";
        }

        // 添加小数部分
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
			cout << "输入至多有100位整数和5位小数，请输入第一个数: ";
			cin >> num1;
			cout << "请输入第二个数: ";
			cin >> num2;

			string result = myadd.add(num1, num2);
			cout << "相加结果: " << result << endl;

			return 0;
		}
		
		int tsub() {
			Mysub mysub;
			string num1, num2;
			cout << "输入至多有100位整数和5位小数，请输入第一个数: ";
			cin >> num1;
			cout << "请输入第二个数: ";
			cin >> num2;

			string result = mysub.sub(num1, num2);
			cout << "相减结果: " << result << endl;

			return 0;

		}

		int tmul() {
			Mymul mymul;
			string num1, num2;
			cout << "输入至多有100位整数和5位小数，请输入第一个数: ";
			cin >> num1;
			cout << "请输入第二个数: ";
			cin >> num2;

			string result = mymul.mul(num1, num2);
			cout << "相乘结果: " << result << endl;

			return 0;
		}
};

class HighPrecisionDivision {
private:
	int a[100], b, c[100]; // a: 被除数, b: 除数, c: 结果
public:
	// 初始化函数，将字符串转换为整数数组
	int init(int a[], string& s) {
		int len = s.size();
		for (int i = 0; i < len; i++) {
			a[i] = s[len - i - 1] - '0'; // 反转存储，a[0] 是最低位
		}
		return len;
	}

	// 高精度除法函数
	int hd() {
		string s1;
		cin >> s1 >> b; // 输入被除数和除数
		int lena = init(a, s1); // 初始化被除数
		int lenc = 0; // 结果的位数
		int x = 0; // 余数
		// 从最高位开始逐位计算
		for (int i = lena - 1; i >= 0; i--) {
			x = x * 10 + a[i]; // 当前位的值加上余数
			c[lenc++] = x / b; // 计算当前位的商
			x %= b; // 更新余数
		}
		// 去除前导零
		int start = 0;
		while (start < lenc && c[start] == 0) {
			start++;
		}
		// 输出结果
		if (start == lenc) {
			cout << "0"; // 如果结果是0
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