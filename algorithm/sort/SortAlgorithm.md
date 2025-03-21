
# 详解 C++ 比较器、对数器与排序算法

## 1. 比较器

比较器是 C++ `<algorithm>` 库中 `std::sort` 的最后一个参数。它接受一个返回值为 `bool` 的函数或函数对象（如 lambda 表达式、函数指针、仿函数等），用于实现用户自定义的排序规则。

比较器遵循以下规则：
- 返回值为 `true` 时，不交换比较对象的第 1 和第 2 个元素。
- 返回值为 `false` 时，交换这两个元素。

### 1.1 函数实现

```cpp
bool compare(int a, int b) {
    return a > b;  // 降序排序
}

bool compare2(int a, int b) {
    return a < b;  // 升序排序
}

std::vector<int> vec = {4, 2, 5, 3, 1};

// 使用自定义比较函数进行排序
std::sort(vec.begin(), vec.end(), compare);
```

看起来很容易让人摸不着头脑，这啥？

其实带入数字计算一下还是很好理解的。理解之后觉得也挺不错的，只要把a , b理解我我们待排序的元素（第一个和第二个），a < b第一个比第二个小，那就是升序嘛，a > b同理。

### 1.2 Lambda 表达式实现

```cpp
std::vector<int> vec = {4, 2, 5, 3, 1};

// 使用 lambda 表达式作为比较器
std::sort(vec.begin(), vec.end(), [](int a, int b) {
    return a > b;  // 降序排序
});
```

### 1.3 仿函数实现

仿函数是一个重载了 `operator()` 的类或结构体对象。你可以定义一个仿函数并将其传递给 `std::sort`。

```cpp
struct Compare {
    bool operator()(int a, int b) const {
        return a > b;  // 降序排序
    }
};

std::sort(vec.begin(), vec.end(), Compare());
```

### 1.4 自定义对象排序

为了巩固理解，这里提供一段用类重载自定义数据对象排序的代码：

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

// 学生类
class Student {
public:
    struct Info {
        std::string name;
        int ID;
        int age;
    };
};

typedef Student::Info StudentInfo;

// 用于比较学生ID的类（升序）
class AscendingIDComparator {
public:
    // 重载 operator() 用于升序排序
    bool operator()(const StudentInfo& std1, const StudentInfo& std2) const {
        return std1.ID < std2.ID;
    }
};

// 用于比较学生ID的类（降序）
class DescendingIDComparator {
public:
    // 重载 operator() 用于降序排序
    bool operator()(const StudentInfo& std1, const StudentInfo& std2) const {
        return std1.ID > std2.ID;
    }
};

// 主逻辑类
class Compare {
public:
    void main() {
        // 创建学生数组
        std::vector<StudentInfo> students = {
            {"Alice", 2, 28},
            {"Bob", 1, 23},
            {"Charlie", 3, 29}
        };

        // 使用升序比较器进行排序
        AscendingIDComparator ascComp;
        std::sort(students.begin(), students.end(), ascComp);

        std::cout << "Sorted by ID (ascending):" << std::endl;
        for (const auto& student : students) {
            std::cout << "Name: " << student.name << ", ID: " << student.ID << ", Age: " << student.age << std::endl;
        }

        // 使用降序比较器进行排序
        DescendingIDComparator descComp;
        std::sort(students.begin(), students.end(), descComp);

        std::cout << "\nSorted by ID (descending):" << std::endl;
        for (const auto& student : students) {
            std::cout << "Name: " << student.name << ", ID: " << student.ID << ", Age: " << student.age << std::endl;
        }
    }
};

int main() {
    Compare comp;
    comp.main();
    return 0;
}

```

## 对数器

对数器可以理解为你本地的 OJ 系统，它能帮助你验证代码的正确性。以排序算法为例，我们可以用内置库函数生成随机数组，对比我们写的排序算法和 `std::sort` 的结果是否相同。

### 2.1 对数器结构

```cpp
void runTest() {
    int c_times, c_size, c_value;
    std::cout << "Please choose test times: ";
    std::cin >> c_times;
    std::cout << "Please choose test array max size: ";
    std::cin >> c_size;
    std::cout << "Please choose test array max value: ";
    std::cin >> c_value;

    for (int i = 0; i < c_times; i++) {
        int size;
        // 生成随机数组
        int* ori_arr = generateRandomArray(c_size, c_value, size);
        // 复制一份随机数组
        int* ori_arr2 = copyArray(ori_arr, size);

        你的排序方法(ori_arr, size);
        comparator(ori_arr2, size);

        bool are_equal = true;
        for (int j = 0; j < size; j++) {
            if (ori_arr[j] != ori_arr2[j]) {
                are_equal = false;
                break;
            }
        }
        if (!are_equal) {
            std::cout << "False\n";
            break;
        }
        delete[] ori_arr;
        delete[] ori_arr2;
    }
    std::cout << "All rights\n";
}
```

### 2.2 生成随机数组

为了生成随机数组，我查阅菜鸟教程：[C++ 标准库  | 菜鸟教程](https://www.runoob.com/cplusplus/cpp-libs-random.html)

这里详细介绍了<random> 库的使用方法，这里我们引入random，使用随机设备创建一个随机种子，使用随机种子初始化 Mersenne Twister 随机数生成器，查阅得知，std::uniform_int_distribution函数可以用于生成在某个整数范围内的均匀分布的整数。我们以maxvalue代表数组元素最大值，maxsize代表数组大小：

这个out_size是什么玩意呢，它的作用是帮我偷懒，为了记录数组长度到底是多少（之后无论是复制，还是实际排序中要用到相关长度参数就可以直接调用！）而设置的输出参数。

```cpp
int* generateRandomArray(int maxsize, int maxvalue, int& out_size) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist_value(0, maxvalue);
    std::uniform_int_distribution<int> dist_size(1, maxsize);
    out_size = dist_size(gen);
    int* num = new int[out_size];  // 动态分配数组
    for (int i = 0; i < out_size; i++) {
        num[i] = dist_value(gen);
    }
    return num;
}
```

### 2.3 数组复制

```cpp
int* copyArray(const int* ori_arr, int size) {
    int* new_arr = new int[size];
    for (int i = 0; i < size; i++) {
        new_arr[i] = ori_arr[i];
    }
    return new_arr;
}
```

---

到此对数器讲完，我们终于可以开始排序啦！（正经人谁会在排序之前写上面那一坨。。。）

## 3. 排序算法

### 3.1 排序的稳定性

排序的稳定性是指**该排序方法在做交换操作时，是否可能越过和它大小相等的数字**。如果不会，则该排序方法稳定；反之则不稳定。

### 3.2 选择排序

- 时间复杂度：O(N²)
- 空间复杂度：O(1)
- 不稳定
- 第一个是时间复杂度O(N²)，空间复杂度O(1)，不稳定的选择排序：

  选择排序的核心思想就是先将数组的第一个元素视为最小（min_index = 0），然后依次遍历每个数组元素，比较数组元素和数组min_index位置的元素的大小，迭代min_index，最后交换第一个元素和min_index元素。之后就是把第二个元素视为最小。。。

```cpp
void select(int* ori_arr, int size) {
    for (int i = 0; i < size; i++) {
        int min_index = i; // 记录最小值的索引
        for (int j = i + 1; j < size; j++) {
            if (ori_arr[j] < ori_arr[min_index]) {
                min_index = j; // 更新最小值的索引
            }
        }
        // 交换当前位置和最小值位置
        std::swap(ori_arr[i], ori_arr[min_index]);
    }
}
```

### 3.3 冒泡排序

- 时间复杂度：O(N²)
- 空间复杂度：O(1)
- 稳定
- 第二个是时间复杂度O(N²)，空间复杂度O(1)，稳定的冒泡排序：

  冒泡排序的核心思想是先自第一个元素起，从左至右比较其相邻元素，将其较大的一个移向右边，这样做一轮，可以确定该数组的最大元素。那么进行n - 1轮之后，就能完成排序。这里加入了flag优化，如果一轮下来没有交换操作，就代表排序已经完成，直接结束即可：

```cpp
void bubble(int* ori_arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        bool flag = true;
        for (int j = 0; j < size - i - 1; j++) {
            if (ori_arr[j] > ori_arr[j + 1]) {
                std::swap(ori_arr[j], ori_arr[j + 1]);
                flag = false;
            }
        }
        if (flag) break;
    }
}
```

~~（现在你可以去bilibiliUP主户晨风的直播间装程序员了。）~~

### 3.4 插入排序

- 时间复杂度：O(N²)
- 空间复杂度：O(1)
- 稳定
- 第三个是时间复杂度O(N²)，空间复杂度O(1)，稳定的插入排序：

  插入的核心思想是将第一个元素视为已经有序，我们通过对下一个元素和有序部分的元素进行大小比较，一步步扩展有序部分的大小，最终让数组有序：

```cpp
void insert(std::vector<int>& ori_arr, int n) {
    if (ori_arr.empty() || ori_arr.size() <= 2) {
        return;
    }

    for (int i = 1; i < n; i++) {
        for (int j = i - 1; j >= 0; j--) {
            if (ori_arr[j + 1] < ori_arr[j]) {
                std::swap(ori_arr[j], ori_arr[j + 1]);
            }
        }
    }
}
```

### 3.5 归并排序

- 时间复杂度：O(N*log(N))
- 空间复杂度：O(N)
- 稳定
- 第四个是时间复杂度O(N*log(N))，空间复杂度O(N)，稳定的归并排序：

  归并排序的核心思想在于二分，以减少数据量便于使之有序化，最后递归进行两个被切分的数组的merge操作，只要保证左侧元素在相等时优先进入整合数组，就能保证稳定性。**相关问题：逆序对，小和**

  注释部分为小和的解决代码。

```cpp
void merge(int* ori_arr, int size) {
    if (ori_arr == NULL || size < 2) {
        return;
    }
    process(ori_arr, 0, size - 1);
}

void process(int* ori_arr, int L, int R) {
    if (L == R) {
        return;
    }
    int mid = L + ((R - L) >> 1);
    process(ori_arr, L, mid);
    process(ori_arr, mid + 1, R);
    mergesort(ori_arr, L, mid, R);
}

void mergesort(int* ori_arr, int L, int mid, int R) {
    int* help = new int[R - L + 1];
    int p = 0;
    int p1 = L;
    int p2 = mid + 1;

    while (p1 <= mid && p2 <= R) {
        help[p++] = ori_arr[p1] <= ori_arr[p2] ? ori_arr[p1++] : ori_arr[p2++];
    }
    while (p1 <= mid) {
        help[p++] = ori_arr[p1++];
    }
    while (p2 <= R) {
        help[p++] = ori_arr[p2++];
    }
    for (int i = 0; i < R - L + 1; i++) {
        ori_arr[L + i] = help[i];
    }
    delete[] help;
}
```

### 3.6 快速排序

- 时间复杂度：O(N*log(N))
- 空间复杂度：O(log(N))
- 不稳定
- 第五个是时间复杂度O(N*log(N))，空间复杂度O(log(N))，不稳定的快速排序：

  快速排序的核心思想是在数组中随机选取一个数，将数组分为大于此数，小于此数，等于此数的三部分，之后在小于，大于的部分重复此操作，即可完成排序。**相关问题：荷兰国旗**

```cpp
void quick(int* ori_arr, int size) {
    if (ori_arr == NULL || size < 2) {
        return;
    }
    quicksort(ori_arr, 0, size - 1);
}

void quicksort(int* ori_arr, int L, int R) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> rand(L, R);
    int random = rand(gen);
    std::swap(ori_arr[random], ori_arr[R]);

    int* p = partition(ori_arr, L, R);
    if (p[0] - 1 >= L) quicksort(ori_arr, L, p[0] - 1);
    if (p[1] + 1 <= R) quicksort(ori_arr, p[1] + 1, R);
}

int* partition(int* ori_arr, int L, int R) {
    int less = L - 1;
    int more = R;
    while (L < more) {
        if (ori_arr[L] < ori_arr[R]) {
            std::swap(ori_arr[++less], ori_arr[L++]);
        } else if (ori_arr[L] > ori_arr[R]) {
            std::swap(ori_arr[--more], ori_arr[L]);
        } else {
            L++;
        }
    }
    std::swap(ori_arr[more], ori_arr[R]);
    int p[2] = {less + 1, more};
    return p;
}
```

### 3.7 堆排序

- 时间复杂度：O(N*log(N))
- 空间复杂度：O(1)
- 不稳定
- 第六个是堆排序，它涉及到堆结构。堆结构就是一棵完全二叉树，完全二叉树具有如下性质，以至于我们可以用数组模拟完全二叉树。

  1， 一个节点的左子节点下标为其下标 * 2 + 1 ， 右子节点下标为其下标 * 2 + 2

  2， 一个节点的父节点的下标为（其下标 - 1 ）/ 2

  堆结构有两个操作重要的操作，heap_insert和heapify，前者让一个节点上的元素和它的父节点比较大小，如果子节点的值大于父节点，那么将他们交换。循环此过程直到无法交换为止。后者让一个节点上的元素和它的子元素中较大的一个比较大小，如果其值小，则交换，循环此过程直到不能再交换为止。利用这两个操作，我们可以对数组元素依次执行heap_insert操作，构建一个最大堆，然后将堆顶元素和数组末尾元素交换，让heapsize追踪范围-1，再对堆顶元素进行heapify操作，再让堆顶元素和数组末尾元素交换。。。这样下来，我们就得到了升序排列的数组。发明堆排序的人真是个天才。

```cpp
void heap(int* ori_arr, int size) {
    if (ori_arr == NULL || size < 2) {
        return;
    }
    for (int i = 0; i < size; i++) {
        heapinsert(ori_arr, i);
    }
    int heapsize = size;
    std::swap(ori_arr[0], ori_arr[--heapsize]);

    while (heapsize > 0) {
        heapify(ori_arr, 0, heapsize);
        std::swap(ori_arr[0], ori_arr[--heapsize]);
    }
}

void heapinsert(int* arr, int index) {
    while (arr[index] > arr[(index - 1) / 2]) {
        std::swap(arr[index], arr[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

void heapify(int* arr, int index, int heapsize) {
    int left = index * 2 + 1;
    while (left < heapsize) {
        int largest = left + 1 < heapsize && arr[left + 1] > arr[left] ?
            left + 1 : left;
        largest = arr[largest] > arr[index] ? largest : index;
        if (largest == index) {
            break;
        }
        std::swap(arr[largest], arr[index]);
        index = largest;
        left = index * 2 + 1;
    }
}
```

### 3.8 计数排序

- 时间复杂度：O(N)
- 空间复杂度：根据数据情况而定
- 第七个是计数排序时间复杂度为O(N)，空间复杂度要根据数据情况而定：

  发明计数排序的人更是个天才，直接颠覆了惯性思维中对排序的理解，它创建了一个help数组，用来统计待排序数组中每个元素出现的次数，之后遍历help数组，由小到大输出到原数组。乍一看这样很块啊，但如果数组中数据跨度较大，就需要很大的空间去统计，浪费了空间。由于我们不知道数据的分布状况，我们首先确定数据的最小值和最大值，创建等大小的数组，在统计时，让原数组元素减去其最小值（将元素“移动”到由0开始的help数组上），输出到原数组时，只需要加上最小值就能完成排序。

```cpp
void count(int* ori_arr, int size) {
    if (ori_arr == NULL || size < 2) {
        return;
    }
    int max = INT_MIN;
    int min = INT_MAX;

    for (int i = 0; i < size; i++) {
        max = std::max(ori_arr[i], max);
        min = std::min(ori_arr[i], min);
    }

    int* count_arr = new int[max - min + 1]();
    int range = max - min + 1;
    for (int i = 0; i < size; i++) {
        count_arr[ori_arr[i] - min]++;
    }
    int j = 0;
    for (int k = 0; k < range; k++) {
        while (count_arr[k] > 0) {
            ori_arr[j++] = k + min;
            count_arr[k]--;
        }
    }
    delete[] count_arr;
}
```

### 3.9 桶排序

- 时间复杂度：O(N)
- 空间复杂度：O(N)
- 第八个是桶排序，桶排序的底层逻辑是数字每一位的优先级通过桶逐级传递，最终达到有序。由于我们知道数据量的大小，我们会创建一个等大的数组作为桶。其中，我们首先需要创建一个词频数组，统计个位上每个数字出现的频率，为了保证先入桶的数据先出桶，我们计算词频数组的前缀和，之后反向遍历数组，根据各位数字和词频数组的统计入桶。再将结果同步到原数组，如此进行，即可完成排序。

```cpp
void radix(int* ori_arr, int size) {
    if (ori_arr == NULL || size < 2) {
        return;
    }
    radixsort(ori_arr, 0, size, maxbit(ori_arr, size));
}

int maxbit(int* ori_arr, int size) {
    int max = INT_MIN;
    for (int i = 0; i < size; i++) {
        max = std::max(ori_arr[i], max);
    }
    int res = 0;
    while (max != 0) {
        res++;
        max /= 10;
    }
    return res;
}

void radixsort(int* ori_arr, int L, int R, int digit) {
    const int radix = 10;
    int i, j = 0;
    int* bucket = new int[R - L];
    for (int d = 1; d <= digit; d++) {
        int* count = new int[radix]();
        for (i = L; i <= R - 1; i++) {
            j = getDigit(ori_arr[i], d);
            count[j]++;
        }
        for (i = 1; i < radix; i++) {
            count[i] = count[i] + count[i - 1];
        }
        for (i = R - 1; i >= L; i--) {
            j = getDigit(ori_arr[i], d);
            bucket[count[j] - 1] = ori_arr[i];
            count[j]--;
        }
        for (i = L, j = 0; i <= R - 1; i++, j++) {
            ori_arr[i] = bucket[j];
        }
        delete[] count;
    }
    delete[] bucket;
}

int getDigit(int num, int digit) {
    return (((num / ((int)std::pow(10, digit - 1)))) % 10);
}
```

---

未完待续。