//22520201
//Vo Thanh Danh
//Session 03 
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

// Function prototypes for each exercise
int binarySearchFirst(int arr[], int size, int target);
int binarySearchLast(int arr[], int size, int target);
int countOccurrences(int arr[], int size, int target);

int jumpSearch(int arr[], int size, int target);

int interpolationSearch(string arr[], int size, const string& target);

int findMissingNumber(int arr[], int size);

int bidirectionalBinarySearch(int arr[], int size, int target);

void swap(int &a, int &b);
int partition(int arr[], int low, int high);
int quickSelect(int arr[], int low, int high, int k);
int kthSmallest(int arr[], int size, int k);

void linearSearch(int arr[], int size, int target, int &comparisons);
void binarySearch(int arr[], int size, int target, int &comparisons);

int main() {
    int choice;

    do {
        cout << "\nMenu:\n";
        cout << "1. Count Occurrences Using Binary Search\n";
        cout << "2. Dynamic Step Size Jump Search\n";
        cout << "3. Interpolation Search for Strings\n";
        cout << "4. Find Missing Number Using Binary Search\n";
        cout << "5. Multi-Search System (Linear and Binary)\n";
        cout << "6. Bidirectional Binary Search\n";
        cout << "7. Kth Smallest Element Using Binary Search\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int size, target;
                cout << "Enter the size of the array: ";
                cin >> size;
                int arr[size];
                cout << "Enter " << size << " sorted elements: ";
                for (int i = 0; i < size; i++) cin >> arr[i];
                cout << "Enter target to count occurrences: ";
                cin >> target;
                int count = countOccurrences(arr, size, target);
                cout << "Count of " << target << " is: " << count << "\n";
                break;
            }
            case 2: {
                int size, target;
                cout << "Enter the size of the array: ";
                cin >> size;
                int arr[size];
                cout << "Enter " << size << " sorted elements: ";
                for (int i = 0; i < size; i++) cin >> arr[i];
                cout << "Enter target to find using Jump Search: ";
                cin >> target;
                int index = jumpSearch(arr, size, target);
                if (index != -1)
                    cout << "Found at index: " << index << "\n";
                else
                    cout << "Not found\n";
                break;
            }
            case 3: {
                int size;
                cout << "Enter the number of strings: ";
                cin >> size;
                string arr[size];
                cout << "Enter " << size << " lexicographically sorted strings: ";
                for (int i = 0; i < size; i++) cin >> arr[i];
                string target;
                cout << "Enter target string to search: ";
                cin >> target;
                int index = interpolationSearch(arr, size, target);
                if (index != -1)
                    cout << "Found at index: " << index << "\n";
                else
                    cout << "Not found\n";
                break;
            }
            case 4: {
                int size;
                cout << "Enter the size of the array (excluding missing number): ";
                cin >> size;
                int arr[size];
                cout << "Enter " << size << " sorted elements with one missing (0 to n): ";
                for (int i = 0; i < size; i++) cin >> arr[i];
                int missing = findMissingNumber(arr, size);
                cout << "Missing number is: " << missing << "\n";
                break;
            }
            case 5: {
                int size, target;
                cout << "Enter the size of the array: ";
                cin >> size;
                int arr[size];
                cout << "Enter " << size << " sorted elements: ";
                for (int i = 0; i < size; i++) cin >> arr[i];
                cout << "Enter target to search: ";
                cin >> target;

                int linearComparisons = 0, binaryComparisons = 0;
                linearSearch(arr, size, target, linearComparisons);
                binarySearch(arr, size, target, binaryComparisons);

                cout << "Linear Search Comparisons: " << linearComparisons << "\n";
                cout << "Binary Search Comparisons: " << binaryComparisons << "\n";
                break;
            }
            case 6: {
                int size, target;
                cout << "Enter the size of the array: ";
                cin >> size;
                int arr[size];
                cout << "Enter " << size << " sorted elements: ";
                for (int i = 0; i < size; i++) cin >> arr[i];
                cout << "Enter target to find using Bidirectional Binary Search: ";
                cin >> target;
                int index = bidirectionalBinarySearch(arr, size, target);
                if (index != -1)
                    cout << "Found at index: " << index << "\n";
                else
                    cout << "Not found\n";
                break;
            }
            case 7: {
                int size, k;
                cout << "Enter the size of the array: ";
                cin >> size;
                int arr[size];
                cout << "Enter " << size << " unsorted elements: ";
                for (int i = 0; i < size; i++) cin >> arr[i];
                cout << "Enter k to find kth smallest element: ";
                cin >> k;
                if (k > 0 && k <= size) {
                    int result = kthSmallest(arr, size, k);
                    cout << "The " << k << "th smallest element is: " << result << "\n";
                } else {
                    cout << "Invalid k\n";
                }
                break;
            }
            case 8:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 8);

    return 0;
}

void linearSearch(int arr[], int size, int target, int &comparisons) {
    for (int i = 0; i < size; i++) {
        comparisons++;
        if (arr[i] == target) {
            cout << "Linear Search: Found at index " << i << "\n";
            return;
        }
    }
    cout << "Linear Search: Not found\n";
}

void binarySearch(int arr[], int size, int target, int &comparisons) {
    int low = 0, high = size - 1;
    while (low <= high) {
        comparisons++;
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) {
            cout << "Binary Search: Found at index " << mid << "\n";
            return;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    cout << "Binary Search: Not found\n";
}

int binarySearchFirst(int arr[], int size, int target) {
    int low = 0, high = size - 1, result = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) {
            result = mid;
            high = mid - 1;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return result;
}

int binarySearchLast(int arr[], int size, int target) {
    int low = 0, high = size - 1, result = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) {
            result = mid;
            low = mid + 1;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return result;
}

int countOccurrences(int arr[], int size, int target) {
    int first = binarySearchFirst(arr, size, target);
    if (first == -1) return 0;
    int last = binarySearchLast(arr, size, target);
    return last - first + 1;
}

int jumpSearch(int arr[], int size, int target) {
    int step = sqrt(size);
    int prev = 0;
    while (arr[min(step, size) - 1] < target) {
        prev = step;
        step += sqrt(size);
        if (prev >= size) return -1;
    }
    for (int i = prev; i < min(step, size); i++) {
        if (arr[i] == target) return i;
    }
    return -1;
}

int interpolationSearch(string arr[], int size, const string& target) {
    int low = 0, high = size - 1;
    while (low <= high && target >= arr[low] && target <= arr[high]) {
        if (low == high) return (arr[low] == target) ? low : -1;
        int pos = low + (target.compare(arr[low]) * (high - low)) / (arr[high].compare(arr[low]));
        if (arr[pos] == target) return pos;
        if (arr[pos] < target) low = pos + 1;
        else high = pos - 1;
    }
    return -1;
}

int findMissingNumber(int arr[], int size) {
    int low = 0, high = size - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == mid) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return low;
}

int bidirectionalBinarySearch(int arr[], int size, int target) {
    int low = 0, high = size - 1;
    while (low <= high) {
        if (arr[low] == target) return low;
        if (arr[high] == target) return high;
        low++;
        high--;
    }
    return -1;
}

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            swap(arr[i], arr[j]);
            i++;
        }
    }
    swap(arr[i], arr[high]);
    return i;
}

int quickSelect(int arr[], int low, int high, int k) {
    if (low <= high) {
        int pivotIndex = partition(arr, low, high);
        
        if (pivotIndex == k - 1)
            return arr[pivotIndex];
        else if (pivotIndex > k - 1)
            return quickSelect(arr, low, pivotIndex - 1, k);
        else
            return quickSelect(arr, pivotIndex + 1, high, k);
    }
    return -1;
}

int kthSmallest(int arr[], int size, int k) {
    return quickSelect(arr, 0, size - 1, k);
}
