#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;

template <typename func, typename T>
void print(func name, T&& nums) {
    cout << name << ": ";
    for (const auto& x : nums) {
        cout << x << " ";
    }
    cout << endl;
}

void bubbleSort(vector<int> nums) {
    for (int i = 0; i < n; ++i) {
        bool order = true;
        for (int j = 0; j < n - i - 1; ++j) {
            if (nums[j] > nums[j + 1]) {
                swap(nums[j], nums[j + 1]);
                order = false;
            }
        }
        if (order) {
            break;
        }
    }
    print("bubbleSort", nums);
}

void selectionSort(vector<int> nums) {
    for (int i = 0; i < n; ++i) {
        int min_idx = i;
        for (int j = i; j < n; ++j) {
            if (nums[j] < nums[min_idx]) {
                min_idx = j;
            }
        }
        swap(nums[min_idx], nums[i]);
    }
    print("selectionSort", nums);
}

void insertSort(vector<int> nums) {
    for (int i = 1; i < n; ++i) {
        int pre = i;
        int cur = nums[i];
        while (pre - 1 >= 0 && cur < nums[pre - 1]) {
            nums[pre] = nums[pre - 1];
            --pre;
        }
        nums[pre] = cur;
    }
    print("insertSort", nums);
}

void shellSort(vector<int> nums) {
    // 定义一个增量，将序列分为若干段，每段执行插入排序，直至gap = 1
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; ++i) {
            int pre = i;
            int cur = nums[i];
            while (pre - gap >= 0 && cur < nums[pre - gap]) {
                nums[pre] = nums[pre - gap];
                pre -= gap;
            }
            // 循环判断的是前一位不满足，因此插入点在当前位
            nums[pre] = cur;
        }
    }
    print("shellSort", nums);
}

void merge(vector<int>& nums, int l, int mid, int r) {
    vector<int> temp(r - l + 1);
    // 两个有序序列的起始位置
    int idx = 0;
    int lhs = l, rhs = mid + 1;
    while (lhs <= mid && rhs <= r) {
        if (nums[lhs] < nums[rhs]) {
            temp[idx++] = nums[lhs++];
        }
        else {
            temp[idx++] = nums[rhs++];
        }
    }
    while (lhs <= mid) {
        temp[idx++] = nums[lhs++];
    }
    while (rhs <= r) {
        temp[idx++] = nums[rhs++];
    }
    for (int i = 0; i < r - l + 1; ++i) {
        nums[l + i] = temp[i];
    }
}

void mergeSort(vector<int> nums, int l, int r) {
    if (l == r) {
        return;
    }
    int mid = (l + r) >> 1;
    mergeSort(nums, l, mid);
    mergeSort(nums, mid + 1, r);
    // 对两个有序序列进行归并
    merge(nums, l, mid, r);
    if (r - l + 1 == n) {
        print("mergeSort", nums);
    }
}

int partition(vector<int>& nums, int left, int right) {
    int pivot = nums[left];
    while (left < right) {
        while (left < right && nums[right] > pivot) {
            --right;
        }
        nums[left] = nums[right];
        while (left < right && nums[left] < pivot) {
            ++left;
        }
        nums[right] = nums[left];
    }
    nums[left] = pivot;
    return left;
}

void quickSort(vector<int> nums, int l, int r) {
    if (l < r) {
        int index = partition(nums, l, r);
        quickSort(nums, l, index - 1);
        quickSort(nums, index + 1, r);
        if (r - l + 1 == n) {
            print("quickSort", nums);
        }
    }
}

void adjustHeap(vector<int>& nums, int i, int len) {
    int maxIndex = i;
    if (i * 2 + 1 < len && nums[i * 2 + 1] > nums[maxIndex]) {
        maxIndex = i * 2 + 1;
    }
    if (i * 2 + 2 < len && nums[i * 2 + 2] > nums[maxIndex]) {
        maxIndex = i * 2 + 2;
    }
    if (maxIndex != i) {
        swap(nums[i], nums[maxIndex]);
        adjustHeap(nums, maxIndex, len);
    }
}

void buildHeap(vector<int>& nums, int len) {
    // 注意这里下标从0开始，取len / 2
    for (int i = (len - 1) / 2; i >= 0; --i) {
        adjustHeap(nums, i, len);
    }
}

void heapSort(vector<int> nums) {
    int len = n;
    if (len <= 1) {
        return;
    }
    buildHeap(nums, len);
    while (len) {
        swap(nums[0], nums[len - 1]);
        --len;
        adjustHeap(nums, 0, len);
    }
    print("heapSort", nums);
}

void countSort(vector<int> nums) {
    // 可能数字最小不从0开始，以最小的作为基准
    int min = *min_element(nums.begin(), nums.end());
    int max = *max_element(nums.begin(), nums.end());
    vector<int> bucket(max - min + 1, 0);
    for (const auto& x : nums) {
        ++bucket[x - min];
    }
    int idx = 0;
    for (int i = 0; i < (int)bucket.size(); ++i) {
        for (int j = 0; j < bucket[i]; ++j) {
            nums[idx++] = i + min;
        }
    }
    print("countSort", nums);
}

void radixSort(vector<int> nums) {
    // 计算最大数有多少位
    int bit = 0;
    auto count = [](int num) {
        int cnt = num ? 0 : 1;
        while (num) {
            num /= 10;
            ++cnt;
        }
        return cnt;
    };
    // 取倒数第len位数字
    auto extract = [](int num, int len) {
        while (--len && num) {
            num /= 10;
        }
        return num % 10;
    };
    for (const int x : nums) {
        bit = max(bit, count(x));
    }
    // 循环bit次，每一次对上一次排序的结果进行新一轮基数排序
    for (int i = 1; i <= bit; ++i) {
        // 桶，存储当前位为下标i的数字
        vector<vector<int>> bucket(10);
        for (int x : nums) {
            bucket[extract(x, i)].push_back(x);
        }
        // 遍历每个桶，将其中数字依次取出
        int idx = 0;
        for (int j = 0; j < 10; ++j) {
            for (int digit : bucket[j]) {
                nums[idx++] = digit;
            }
        }
        cout << "第" << i << "轮";
        print("基数排序：", nums);
    }
}

int main() {
    vector<int> arr{ 2, 3, 38, 5, 47, 15, 36, 26, 27, 44, 46, 4, 19, 50, 48 };
    n = static_cast<int>(arr.size());
    bubbleSort(arr);
    selectionSort(arr);
    insertSort(arr);
    shellSort(arr);
    mergeSort(arr, 0, n - 1);
    quickSort(arr, 0, n - 1);
    heapSort(arr);
    countSort(arr);
    radixSort(arr);
    return 0;
}
