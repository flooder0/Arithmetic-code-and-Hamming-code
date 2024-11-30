#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

std::string toHammingCode(const std::string& code, const std::vector<int>& array) {
    std::string rawHamming(code.length() + array.size(), '0');

    for (int c : array) {
        rawHamming[c - 1] = '_';
    }

    int codeIndex = 0;
    for (int i = 0; i < rawHamming.length(); i++) {
        if (rawHamming[i] == '_') {
            continue;
        }
        rawHamming[i] = code[codeIndex++];
    }

    return rawHamming;
}

int calculator(const std::string& subString) {
    return std::count(subString.begin(), subString.end(), '1') % 2;
}

std::string olderBits(std::string rawHamming, const std::vector<int>& array) {
    for (int p : array) {
        int step = p;
        int start = p - 1;

        std::string temp;
        for (int i = start; i < rawHamming.size(); i += 2 * step) {
            temp += rawHamming.substr(i, step);
        }

        int result = calculator(temp);
        rawHamming[p - 1] = result + '0';
    }

    return rawHamming;
}

int main() {
    std::string code = "000000001110111101001010111101000101100111010101011111110011110100100100000000";
    std::vector<int> array = {1, 2, 4, 8, 16, 32, 64};

    std::string rawHamming = toHammingCode(code, array);
    std::string hamming = olderBits(rawHamming, array);

    std::cout << "Исходный код: " << code << std::endl;
    std::cout << "Сырой Хемминг: " << rawHamming << std::endl;
    std::cout << "Код Хемминга: " << hamming << std::endl;

    return 0;
}
