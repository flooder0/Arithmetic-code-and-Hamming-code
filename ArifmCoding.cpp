#include <cmath>
#include <codecvt>
#include <iomanip>
#include <iostream>
#include <limits>
#include <locale>
#include <string>
#include <unordered_map>
#include <vector>

#include "C:/boost_1_86_0/boost/multiprecision/cpp_dec_float.hpp"

using HighPrecision = boost::multiprecision::cpp_dec_float_50;

void print(HighPrecision value) {
    std::cout << std::setprecision(std::numeric_limits<HighPrecision>::max_digits10);
    std::cout << value << std::endl;
}

struct Segment {
    HighPrecision left;
    HighPrecision right;
};

std::unordered_map<wchar_t, Segment> defineSegments(const std::vector<wchar_t>& letters, const std::vector<HighPrecision>& probabilities) {
    std::unordered_map<wchar_t, Segment> segments;
    HighPrecision left = 0.0;

    for (size_t i = 0; i < letters.size(); ++i) {
        Segment segment;
        segment.left = left;
        segment.right = left + probabilities[i];
        segments[letters[i]] = segment;
        left = segment.right;
    }
    return segments;
}

HighPrecision arifmoCode(const std::vector<wchar_t>& letters, const std::vector<HighPrecision>& probabilities, const std::wstring& s) {
    std::unordered_map<wchar_t, Segment> segments = defineSegments(letters, probabilities);
    HighPrecision left = 0.0;
    HighPrecision right = 1.0;

    for (wchar_t symb : s) {
        HighPrecision newRight = left + (right - left) * segments[symb].right;
        HighPrecision newLeft = left + (right - left) * segments[symb].left;
        left = newLeft;
        right = newRight;
    }
    HighPrecision q;
    q = right - left;
    print(q);
    print(right - left);
    return (left + right) / 2.0;
}

int main() {
    setlocale(LC_ALL, "Russian");
    std::vector<wchar_t> letters = {
        L'г',
        L'а',
        L'н',
        L'и',
        L'е',
        L'в',
        L'р',
        L'т',
        L'ё',
        L'м',
        L'у',
        L'с',
        L'о',
        L'ч',
    };
    std::vector<HighPrecision> probabilities = {0.04761904, 0.14285714, 0.04761904, 0.09523809, 0.04761904, 0.09523809, 0.09523809, 0.09523809, 0.04761904, 0.09523809, 0.04761904, 0.04761904, 0.04761904, 0.04761904};
    std::wstring s = L"ганиевартёмрустамович";

    HighPrecision encodedValue = arifmoCode(letters, probabilities, s);

    print(encodedValue * pow(2, 78));

    return 0;
}