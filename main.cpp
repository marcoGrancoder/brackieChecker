#include <iostream>
#include <fstream>
#include <stack>
#include <string>

using namespace std;

bool isBalanced(const string& expression){
    stack<pair<char, int>> brackies;
    bool singleComment = false;
    bool multiComment = false;
    bool quotes = false;
    bool singleQuotes = false;
    int lineNumber = 1;
    for(int i = 0; i < expression.length(); i++){
        char ch = expression[i]; 
        if(ch == '\n') {
            lineNumber++;
            singleComment = false;
            continue;
        }
        char next;
        if (i+1 < expression.length()){
            next = expression[i+1];
        } else {
            next = '\0';
        }
        
        //comments check
        if(!quotes && !singleQuotes){
            //single-line comment checker
            if (!multiComment && !singleComment && ch == '/' && next == '/') {
                singleComment = true;
                i++;
                continue;
            }
            //opening multi-line comment checker
            if (!multiComment && ch == '/' && next == '*'){
                multiComment = true;
                i++;
                continue;
            }
            //closing multi-line comment checker
            if (multiComment && ch == '*' && next == '/'){
                multiComment = false;
                i++;
                continue;
            }
        }
        if (singleComment || multiComment) continue;
        //single
        if (!quotes && ch == '\'' && expression[i-1] != '\\'){
           singleQuotes = !singleQuotes; 
           continue;
        }
        //double
        if (!singleQuotes && ch == '"' && expression[i-1] != '\\'){
            quotes = !quotes;
            continue;
        }

        if ( quotes || singleQuotes) continue;
        if(ch == '(' || ch == '{' || ch == '[') {
            brackies.push({ch, lineNumber});
        } else if(ch == ')' || ch == '}' || ch == ']' ){
            if (brackies.empty()) {
                cout << "Mismatched closing bracket '" << ch << "' at line " << lineNumber << " Contains no opening bracket" << endl;
                return false;
            }
            char top = brackies.top().first;
            int openingLine = brackies.top().second;
            brackies.pop();
            if ((ch == ')' && top != '(') || (ch == '}' && top != '{') || (ch == ']' && top != '[') )
            {
                cout << "Mismatched  bracket '" << top << "' opened at line " <<  openingLine << " But closed with '" << ch << "' at line" << lineNumber << endl;
                return false;
            }
        }
    }
    if (!brackies.empty()){
        cout << "Unmatched opening bracket '" << brackies.top().first << "' at line " << brackies.top().second << endl;
        return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    if (argc < 2){
        cout << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }
    string file = argv[1];
    ifstream infile(file);
    if (!infile){
        cout << "Error: Could not open file" << endl;
        return 1;
    }
    string line, expression;
    while (getline(infile, line)){
        expression += line + "\n";
    }
    infile.close();
    cout << expression;
    if (expression.empty()) {
        cout << "Warning: File is empty. \n";
        return 1;
    }
    if(isBalanced(expression)){
        cout << "BALANCED (:" << endl;
    } else{
        cout << "UNBALANCED ):" << endl;
    }
    return 0;
}