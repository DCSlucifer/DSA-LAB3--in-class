//Full Name: Võ Thành Danh
//MSSV     : 22520201
//Lab 03
//Notes or Remarks:
#include <iostream>
#include <vector>
#include <string>

// Hàm để tạo bảng LPS (Longest Prefix Suffix)
std::vector<int> computeLPSArray(const std::string& pattern) {
    int m = pattern.length();
    std::vector<int> lps(m, 0);
    int len = 0; // độ dài của tiền tố dài nhất
    int i = 1;

    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

// Hàm KMP để tìm kiếm chuỗi con
void KMPSearch(const std::string& text, const std::string& pattern) {
    int n = text.length();
    int m = pattern.length();

    std::vector<int> lps = computeLPSArray(pattern);

    int i = 0; // chỉ số cho text
    int j = 0; // chỉ số cho pattern

    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == m) {
            std::cout << "Pattern found at index " << i - j << std::endl;
            j = lps[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
}

int main() {
    std::string text;
    std::string pattern;

    std::cout << "Enter the text: ";
    std::getline(std::cin, text);

    std::cout << "Enter the pattern to search: ";
    std::getline(std::cin, pattern);

    KMPSearch(text, pattern);

    return 0;
}
