#include <iostream>
#include <string>
#include <algorithm> 
using namespace std;

int hammingDistance(const string& str1, const string& str2) {
    // Determine the maximum length
    size_t maxLength = max(str1.length(), str2.length());

    // Pad the shorter string with leading zeros
    string paddedStr1 = string(maxLength - str1.length(), '0') + str1;
    string paddedStr2 = string(maxLength - str2.length(), '0') + str2;

    int distance = 0;

    // Calculate the Hamming distance
    for (size_t i = 0; i < maxLength; ++i) {
        if (paddedStr1[i] != paddedStr2[i]) {
            distance++;
        }
    }

    return distance;
}

int main() {
    string str1, str2;

    // Input binary strings
    cout << "str1: ";
    cin >> str1;
    cout << "str2: ";
    cin >> str2;

    // Calculate Hamming distance
    int hammingD = hammingDistance(str1, str2);

    // Output the result
    cout << "hamming distance between " << str1 << " and " << str2 << " is: " << hammingD << endl;

    return 0;
}


//00010 - 001110 hamming distance is 1