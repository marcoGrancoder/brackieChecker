#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

vector<string> isBalanced(const string& expression) {
    vector<string> errors;
    stack<pair<char, int>> brackies;
    bool singleComment = false;
    bool multiComment = false;
    bool quotes = false;
    bool singleQuotes = false;
    int lineNumber = 1;

    for (int i = 0; i < expression.length(); i++) {
        char ch = expression[i];
        if (ch == '\n') {
            lineNumber++;
            singleComment = false;
            continue;
        }

        char next = (i + 1 < expression.length()) ? expression[i + 1] : '\0';

        // Comment check
        if (!quotes && !singleQuotes) {
            if (!multiComment && !singleComment && ch == '/' && next == '/') {
                singleComment = true;
                i++;
                continue;
            }
            if (!multiComment && ch == '/' && next == '*') {
                multiComment = true;
                i++;
                continue;
            }
            if (multiComment && ch == '*' && next == '/') {
                multiComment = false;
                i++;
                continue;
            }
        }

        if (singleComment || multiComment) continue;


        if (!quotes && ch == '\'' && (i == 0 || expression[i - 1] != '\\')) {
            singleQuotes = !singleQuotes;
            continue;
        }
        if (!singleQuotes && ch == '"' && (i == 0 || expression[i - 1] != '\\')) {
            quotes = !quotes;
            continue;
        }

        if (quotes || singleQuotes) continue;

        if (ch == '(' || ch == '{' || ch == '[') {
            brackies.push({ch, lineNumber});
        } else if (ch == ')' || ch == '}' || ch == ']') {
            if (brackies.empty()) {
                errors.push_back("Mismatched closing bracket '" + string(1, ch) +
                                 "' at line " + to_string(lineNumber) +
                                 " — no matching opening bracket.");
                continue;
            }
            char top = brackies.top().first;
            int openingLine = brackies.top().second;
            brackies.pop();
            if ((ch == ')' && top != '(') || (ch == '}' && top != '{') || (ch == ']' && top != '[')) {
                errors.push_back("Mismatched bracket '" + string(1, top) +
                                 "' opened at line " + to_string(openingLine) +
                                 " but closed with '" + string(1, ch) +
                                 "' at line " + to_string(lineNumber) + ".");
            }
        }
    }

    // Check for remaining unmatched opening brackets
    while (!brackies.empty()) {
        errors.push_back("Unmatched opening bracket '" + string(1, brackies.top().first) +
                         "' at line " + to_string(brackies.top().second) + ".");
        brackies.pop();
    }

    return errors;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    string file = argv[1];
    ifstream infile(file);
    if (!infile) {
        cout << "Error: Could not open file" << endl;
        return 1;
    }

    string line, expression;
    while (getline(infile, line)) {
        expression += line + "\n";
    }
    infile.close();

    if (expression.empty()) {
        cout << "Warning: File is empty.\n";
        return 1;
    }

    vector<string> errors = isBalanced(expression);
    if (errors.empty()) {
        cout << "BALANCED (: " << endl;
    } else {
        cout << "UNBALANCED ): Found " << errors.size() << " issue(s):" << endl;
        for (const string& error : errors) {
            cout << " - " << error << endl;
        }
    }

    return 0;
}
