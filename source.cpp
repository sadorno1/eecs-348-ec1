#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>

using namespace std;

// function to extract a numeric value from the input string
double extractNumeric(const string& input) {
    bool hasSign = false, hasDecimal = false, hasDigits = false;
    int signCount = 0, decimalCount = 0;
    size_t length = input.length();
    
    // check for an empty string
    if (length == 0) {
        return -999999.99;
    }

    // validate the input string
    for (size_t i = 0; i < length; ++i) {
        char ch = input[i];

        // check for valid characters
        if (ch == '+' || ch == '-') {
            if (i > 0) { 
                return -999999.99;
            }
            hasSign = true;
            signCount++;
        } else if (ch == '.') {
            if (hasDecimal) { 
                return -999999.99;
            }
            hasDecimal = true;
            decimalCount++;
        } else if (isdigit(ch)) {
            hasDigits = true; 
        } else {
            return -999999.99;
        }
    }

    // at least one digit should be present
    if (!hasDigits || signCount > 1 || decimalCount > 1) {
        return -999999.99;
    }

    // convert to double manually
    double result = 0.0;
    double decimalMultiplier = 0.1;
    bool isNegative = false;
    bool processingDecimal = false;

    for (size_t i = 0; i < length; ++i) {
        char ch = input[i];

        if (ch == '+' || ch == '-') {
            isNegative = (ch == '-');
        } else if (ch == '.') {
            processingDecimal = true;
        } else if (isdigit(ch)) {
            if (processingDecimal) {
                result += (ch - '0') * decimalMultiplier;
                decimalMultiplier /= 10.0;
            } else {
                result = result * 10.0 + (ch - '0');
            }
        }
    }

    return isNegative ? -result : result;
}

int main() {
    string input;

    cout << "Enter a string (type 'END' to quit):" << endl;
    while (true) {
        cout << "Input: ";
        getline(cin, input);

        if (input == "END") {
            break;
        }

        double result = extractNumeric(input);

        if (result == -999999.99) {
            cout << "The input is invalid." << endl;
        } else {
            cout << "The input is: " << fixed << setprecision(4) << result << endl;
        }
    }

    cout << "Program terminated." << endl;
    return 0;
}
