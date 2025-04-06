#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

class LargeInteger {
public:
    std::string value;

    // Constructor to initialize with a string
    LargeInteger(const std::string& val) : value(removeLeadingZeros(val)) {}

    // Method to add another LargeInteger and return the result as a new LargeInteger
    LargeInteger add(const LargeInteger& other) const {
        std::string num1 = value;
        std::string num2 = other.value;

        // Handle both numbers being negative
        if (num1[0] == '-' && num2[0] == '-') {
            return LargeInteger("-" + addStrings(num1.substr(1), num2.substr(1)));
        }
        // Handle one number being negative
        else if (num1[0] == '-' || num2[0] == '-') {
            if (num1[0] == '-') {
                // num1 is negative, num2 is positive
                return subtractStrings(num2, num1.substr(1));
            } else {
                // num2 is negative, num1 is positive
                return subtractStrings(num1, num2.substr(1));
            }
        }
        // Both numbers are positive
        else {
            return LargeInteger(addStrings(num1, num2));
        }
    }

    // Method to subtract another LargeInteger and return the result as a new LargeInteger
    LargeInteger subtract(const LargeInteger& other) const {
        std::string num1 = value;
        std::string num2 = other.value;

        // Handle both numbers being negative
        if (num1[0] == '-' && num2[0] == '-') {
            return subtractStrings(num2.substr(1), num1.substr(1));
        }
        // Handle one number being negative
        else if (num1[0] == '-' || num2[0] == '-') {
            if (num1[0] == '-') {
                // num1 is negative, num2 is positive
                return LargeInteger("-" + addStrings(num1.substr(1), num2));
            } else {
                // num2 is negative, num1 is positive
                return addStrings(num1, num2.substr(1));
            }
        }
        // Both numbers are positive
        else {
            if (num1 < num2) {
                return LargeInteger("-" + subtractStrings(num2, num1));
            }
            return LargeInteger(subtractStrings(num1, num2));
        }
    }

private:
    // Helper function to remove leading zeros
    static std::string removeLeadingZeros(const std::string& str) {
        size_t nonZero = str.find_first_not_of('0');
        if (nonZero == std::string::npos) return "0";
        return str.substr(nonZero);
    }

    // Helper function to add two positive large integers
    static std::string addStrings(const std::string& num1, const std::string& num2) {
        int i = num1.size() - 1;
        int j = num2.size() - 1;
        int carry = 0;
        std::string result;

        while (i >= 0 || j >= 0 || carry) {
            int sum = carry;
            if (i >= 0) sum += num1[i--] - '0';
            if (j >= 0) sum += num2[j--] - '0';

            carry = sum / 10;
            result.push_back((sum % 10) + '0');
        }

        std::reverse(result.begin(), result.end());
        return result;
    }

    // Helper function to subtract two positive large integers
    static std::string subtractStrings(const std::string& num1, const std::string& num2) {
        std::string larger, smaller;
        bool negativeResult = false;
        
        // Determine which number is larger
        if (num1.size() > num2.size() || (num1.size() == num2.size() && num1 >= num2)) {
            larger = num1;
            smaller = num2;
        } else {
            larger = num2;
            smaller = num1;
            negativeResult = true;
        }

        std::string result;
        int borrow = 0;
        int i = larger.size() - 1;
        int j = smaller.size() - 1;

        while (i >= 0 || j >= 0) {
            int diff = (larger[i--] - '0') - borrow;
            if (j >= 0) diff -= (smaller[j--] - '0');

            if (diff < 0) {
                diff += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }

            result.push_back(diff + '0');
        }

        if (negativeResult) {
            result.push_back('-');
        }
        
        std::reverse(result.begin(), result.end());
        return removeLeadingZeros(result);
    }
};

// Function to count pairs with difference equal to target
int countPairs(const std::vector<LargeInteger>& data, const LargeInteger& target) {
    int result = 0;
    std::unordered_map<std::string, int> hash_map;

    for (const auto& item : data) {
        std::string itemStr = item.value;
        LargeInteger targetSum = item.add(target);

        if (hash_map.find(targetSum.value) != hash_map.end()) {
            result += hash_map[targetSum.value];
        }

        hash_map[itemStr]++;
    }

    return result;
}
extern "C" {
    int count_pairs_from_file(const char* filename);
}

int count_pairs_from_file(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        std::cerr << "Error opening file" << std::endl;
        return -1; // Error opening file
    }

    // Read target
    char targetStr[1000];
    fscanf(file, "%s", targetStr);
    LargeInteger target(targetStr);

    // Read number of integers
    unsigned long long int n;
    fscanf(file, "%d", &n);

    // Read integers
    std::vector<LargeInteger> data;
    data.reserve(n);
    for (int i = 0; i < n; i++) {
        char number[1000];
        fscanf(file, "%s", number);
        data.emplace_back(number);
    }

    fclose(file);

    // Count pairs
    return countPairs(data, target);
}

int main() {
    // Define large integer data
    // std::vector<LargeInteger> data = {
    //     LargeInteger("400000000000000000000"),
    //     LargeInteger("-100000000000000000000"),
    //     LargeInteger("-200000000000000000000"),
    //     LargeInteger("300000000000000000000")
    // };

    // Define result
    unsigned long long int result = count_pairs_from_file("inputs.txt");

    // Print result
    std::cout << "Number of pairs: " << result << std::endl;
    // LargeInteger target("100000000000000000000");

    return 0;
}
