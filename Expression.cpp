#include <string>
#include <stack>
#include <cctype>
using namespace std;

int islemOnceligi(char op) {    //Operat�rleri kontrol ederken i�lem �nceli�i s�ras�n� daha rahat kontrol etmek i�in
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Infix to Postfix fonksiyonu
string Infix2Postfix(string& s) {
    string result;
    stack<char> postFix;
    int resultIndex = 0;

    for (int i = 0; i < s.size(); i++) {
        if ((s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') && postFix.empty()) { //stack bo�sa ve operat�r eklemek istiyorsan, operat�r� pushla.
            postFix.push(s[i]);
        }
        else if ((s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') && !postFix.empty()) {//Stack bo� de�ilse, stack'teki operat�r ile stringdeki operat�r� kar��la�t�r. Stack'teki operat�r�n i�lem �nceli�inde daha �nde veya e�it oldu�u s�rece, stack'ten result'a at. Stack bo�al�rsa stringdeki operat�r� stack'e pushla.
            while (!postFix.empty() && islemOnceligi(s[i]) <= islemOnceligi(postFix.top())) {
                result += postFix.top();
                postFix.pop();
                result += ' ';  // Operat�rden sonra bo�luk b�rak
            }
            postFix.push(s[i]);
        }
        else if (s[i] == '(') { // parantez a� g�r�rsen sadece pushla.
            postFix.push(s[i]);
        }
        else if (s[i] == ')') { //parantez kapatma i�areti g�r�rsen stackte '(' i�areti g�rene kadar pop'la.
            while (postFix.top() != '(') {
                result += postFix.top();
                postFix.pop();
                result += ' ';
            }
            postFix.pop(); // Stackte kalan parantez a�ma i�aretini pop'la
        }
        else if (isdigit(s[i])) { // Say� g�r�rsen
            while (i < s.size() && isdigit(s[i])) {
                result += s[i];
                i++;
            }
            result += ' '; // T�m basamaklar� yazd�ktan sonra bo�luk b�rak.
            i--; // D�ng� sonunda i'yi art�rmamak i�in geri al
        }
    }

    // Stack'teki operat�rleri bo�alt
    while (!postFix.empty()) {
        result += postFix.top();
        postFix.pop();
        result += ' ';
    }

    return result;
}



///----------------------------------------------------------------------------------
/// Given a string in post-fix notation, evaluates it and returns the result
/// 
// Postfix ifadesini de�erlendiren fonksiyon
int EvaluatePostfixExpression(string& s) {
    stack<int> evalStack;
    int i = 0;

    while (i < s.size()) {
        if (isdigit(s[i])) {  // Say�ysa
            int num = 0;
            while (i < s.size() && isdigit(s[i])) { // Tam say�y� olu�tur
                num = num * 10 + (s[i] - '0');
                i++;
            }
            evalStack.push(num);  // Y���na ekle
        }
        else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') {  // Operat�rse
            int b = evalStack.top(); evalStack.pop();
            int a = evalStack.top(); evalStack.pop();

            int result;
            if (s[i] == '+') result = a + b;
            else if (s[i] == '-') result = a - b;
            else if (s[i] == '*') result = a * b;
            else if (s[i] == '/') result = a / b;

            evalStack.push(result);  // Sonucu y���na ekle
        }
        i++;  // �lerle
    }

    return evalStack.top();  // Y���n�n tepesindeki de�er sonucu verir
}