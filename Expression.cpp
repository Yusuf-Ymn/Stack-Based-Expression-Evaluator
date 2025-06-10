#include <string>
#include <stack>
#include <cctype>
using namespace std;

int islemOnceligi(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}


string Infix2Postfix(string& s) {
    string result;
    stack<char> postFix;
    int resultIndex = 0;

    for (int i = 0; i < s.size(); i++) {
        if ((s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') && postFix.empty()) { 
            postFix.push(s[i]);
        }
        else if ((s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') && !postFix.empty()) {
                result += postFix.top();
                postFix.pop();
                result += ' ';
            }
            postFix.push(s[i]);
        }
        else if (s[i] == '(') {
            postFix.push(s[i]);
        }
        else if (s[i] == ')') {
            while (postFix.top() != '(') {
                result += postFix.top();
                postFix.pop();
                result += ' ';
            }
            postFix.pop();
        }
        else if (isdigit(s[i])) { // Sayý görürsen
            while (i < s.size() && isdigit(s[i])) {
                result += s[i];
                i++;
            }
            result += ' ';
            i--;
        }
    }

    
    while (!postFix.empty()) {
        result += postFix.top();
        postFix.pop();
        result += ' ';
    }

    return result;
}


int EvaluatePostfixExpression(string& s) {
    stack<int> evalStack;
    int i = 0;

    while (i < s.size()) {
        if (isdigit(s[i])) {
            int num = 0;
            while (i < s.size() && isdigit(s[i])) {
                num = num * 10 + (s[i] - '0');
                i++;
            }
            evalStack.push(num);
        }
        else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') {
            int b = evalStack.top(); evalStack.pop();
            int a = evalStack.top(); evalStack.pop();

            int result;
            if (s[i] == '+') result = a + b;
            else if (s[i] == '-') result = a - b;
            else if (s[i] == '*') result = a * b;
            else if (s[i] == '/') result = a / b;

            evalStack.push(result);  // Sonucu yýðýna ekle
        }
        i++;  // Ýlerle
    }

    return evalStack.top();  // Yýðýnýn tepesindeki deðer sonucu verir
}
