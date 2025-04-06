#ifndef LARGE_INTEGER_H
#define LARGE_INTEGER_H

#include <string>
#include <vector>
#include <unordered_map>

// Class to represent a large integer
class LargeInteger {
public:
    std::string value;

    // Constructor to initialize with a string
    LargeInteger(const std::string& val);

    // Method to add another LargeInteger and return the result as a new LargeInteger
    LargeInteger add(const LargeInteger& other) const;

    // Method to subtract another LargeInteger and return the result as a new LargeInteger
    LargeInteger subtract(const LargeInteger& other) const;

private:
    // Helper function to remove leading zeros
    static std::string removeLeadingZeros(const std::string& str);

    // Helper function to add two positive large integers
    static std::string addStrings(const std::string& num1, const std::string& num2);

    // Helper function to subtract two positive large integers
    static std::string subtractStrings(const std::string& num1, const std::string& num2);
};

// Function to count pairs with a difference equal to the target
int countPairs(const std::vector<LargeInteger>& data, const LargeInteger& target);

// Function to count pairs from a file, exposed to be used in C code
extern "C" {
    int count_pairs_from_file(const char* filename);
}

#endif // LARGE_INTEGER_H
