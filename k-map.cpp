#include <iostream>
#include <string>

using namespace std;

const int MAX_VARIABLES = 5;
const int MAX_MINTERMS[3] = {8, 16, 32};

void printHeader() {
    cout << " _____________" << endl
         << "| \"Made By Abdullah khan CSF120222060 \"|" << endl
         << "| \"THE FOOL TALKS AND THE WISE LEARNS\" |" << endl
         << "|______________|" << endl
         << endl;
}

void setExpressionFor3Variables(int a, int b, string* expression) {
    const string values[2][4] = {{"A'B'C'", "A'B'C", "A'BC", "A'BC'"}, {"AB'C'", "AB'C", "ABC", "ABC'"}};
    for (int i = 0; i < 8; i++) {
        if (*(expression + i) == "") {
            *(expression + i) = values[a][b];
            break;
        }
    }
}

void displayBitFor3Variables(int size, int* minterms, int* counter, int i, int j, string* arr) {
    int condition = 0;
    for (int k = 0; k < size; k++) {
        if (*(minterms + k) == *counter) {
            cout << 1;
            condition = 1;
            setExpressionFor3Variables(i, j, arr);
            break;
        }
    }
    cout << (condition ? "" : "0");
    *counter += 1;
}

void setExpression(int a, int b, string* expression, int size) {
    const string values[4][4] = {{"A'B'C'D'", "A'B'C'D", "A'B'CD", "A'B'CD'"},
                                  {"A'BC'D'", "A'BC'D", "A'BCD", "A'BCD'"},
                                  {"ABC'D'", "ABC'D", "ABCD", "ABCD'"},
                                  {"AB'C'D'", "AB'C'D", "AB'CD", "AB'CD'"}};
    int limit = (size == 3) ? MAX_MINTERMS[0] : (size == 4) ? MAX_MINTERMS[1] : MAX_MINTERMS[2];
    for (int i = 0; i < limit; i++) {
        if (*(expression + i) == "") {
            *(expression + i) = values[a][b];
            break;
        }
    }
}

void displayBit(int size, int* minterms, int* counter, int i, int j, string* arr) {
    int condition = 0;
    for (int k = 0; k < size; k++) {
        if (*(minterms + k) == *counter) {
            cout << 1;
            condition = 1;
            setExpression(i, j, arr, size);
            break;
        }
    }
    cout << (condition ? "" : "0");
    *counter += 1;
}

void printExpression(string* expression, int expr) {
    bool first = true;
    for (int i = 0; i < expr; i++) {
        if (*(expression + i) != "") {
            if (!first) cout << " + ";
            cout << *(expression + i);
            first = false;
        }
    }
    cout << endl;
}

void handleCombinations(int* counter, int size, int choice, int i, string* arr, int* minterm) {
    int loop = (choice == 3) ? 8 : 4;
    for (int j = 0; j < loop; j++) {
        if (j == 2 || j == 6) *counter += 1;
        else if (j == 3 || j == 7) *counter -= 1;

        if (choice == 1) displayBitFor3Variables(size, minterm, counter, i, j, arr);
        else displayBit(size, minterm, counter, i, j, arr);

        if (j == 2 || j == 6) *counter -= 1;
        else if (j == 3 || j == 7) *counter += 1;

        cout << "   ";
        if (choice == 3) cout << " ";
    }
}

int main() {
    printHeader();

    int variables, size;
    cout << "Enter the number of variables (3 to 5): ";
    cin >> variables;

    if (variables < 3 || variables > MAX_VARIABLES) {
        cout << "Invalid number of variables. Please enter between 3 to " << MAX_VARIABLES << "." << endl;
        return 1;
    }

    cout << "Enter the number of Minterms: ";
    cin >> size;

    int max_minterms = MAX_MINTERMS[variables - 3];
    if (size < 1 || size > max_minterms) {
        cout << "Invalid number of minterms. Please enter between 1 to " << max_minterms << "." << endl;
        return 1;
    }

    int minterms[size];
    for (int i = 0; i < size; i++) {
        cout << "Enter the value of " << i + 1 << " minterm: ";
        cin >> minterms[i];
    }

    int expr = (variables == 3) ? MAX_MINTERMS[0] : (variables == 4) ? MAX_MINTERMS[1] : MAX_MINTERMS[2];
    string expression[expr] = {""};
    int counter = 0;

    if (variables == 3) {
        cout << "\n BC  00  01  11  10\nA\n\n";
        for (int i = 0; i < 2; i++) {
            cout << i << "     ";
            handleCombinations(&counter, size, 1, i, expression, minterms);
            cout << endl;
        }
    }
    else if (variables == 4) {
        cout << "\n  CD  00  01  11  10\nAB\n\n";
        for (int i = 0; i < 4; i++) {
            if (i == 0) cout << "00     ";
            else if (i == 1) cout << "01     ";
            else if (i == 2) cout << "11     ";
            else if (i == 3) cout << "10     ";

            if (i == 3) counter -= 4;
            else if (i == 2) counter += 4;

            handleCombinations(&counter, size, 2, i, expression, minterms);

            if (i == 3) counter += 4;
            else if (i == 2) counter -= 4;

            cout << endl;
        }
    }
   else if (variables == 5) {
    cout << "\n  CDE  000  001  011  010  100  101  111  110\nAB\n\n";
    for (int i = 0; i < 4; i++) {
        if (i == 0) cout << "00      ";
        else if (i == 1) cout << "01      ";
        else if (i == 2) cout << "11      ";
        else if (i == 3) cout << "10      ";

        if (i == 3) counter -= 4;
        else if (i == 2) counter += 4;

        handleCombinations(&counter, size, 3, i, expression, minterms);

        if (i == 3) counter += 4;
        else if (i == 2) counter -= 4;

        cout << endl;
    }
}

cout << "\nExpression\n";
printExpression(expression, expr);
cout << "\n\n";
return 0;
}
