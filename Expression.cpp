#include <string>
#include <stack>
#include <cctype>
using namespace std;

int islemOnceligi(char op) {    //Operatörleri kontrol ederken iþlem önceliði sýrasýný daha rahat kontrol etmek için
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
        if ((s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') && postFix.empty()) { //stack boþsa ve operatör eklemek istiyorsan, operatörü pushla.
            postFix.push(s[i]);
        }
        else if ((s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') && !postFix.empty()) {//Stack boþ deðilse, stack'teki operatör ile stringdeki operatörü karþýlaþtýr. Stack'teki operatörün iþlem önceliðinde daha önde veya eþit olduðu sürece, stack'ten result'a at. Stack boþalýrsa stringdeki operatörü stack'e pushla.
            while (!postFix.empty() && islemOnceligi(s[i]) <= islemOnceligi(postFix.top())) {
                result += postFix.top();
                postFix.pop();
                result += ' ';  // Operatörden sonra boþluk býrak
            }
            postFix.push(s[i]);
        }
        else if (s[i] == '(') { // parantez aç görürsen sadece pushla.
            postFix.push(s[i]);
        }
        else if (s[i] == ')') { //parantez kapatma iþareti görürsen stackte '(' iþareti görene kadar pop'la.
            while (postFix.top() != '(') {
                result += postFix.top();
                postFix.pop();
                result += ' ';
            }
            postFix.pop(); // Stackte kalan parantez açma iþaretini pop'la
        }
        else if (isdigit(s[i])) { // Sayý görürsen
            while (i < s.size() && isdigit(s[i])) {
                result += s[i];
                i++;
            }
            result += ' '; // Tüm basamaklarý yazdýktan sonra boþluk býrak.
            i--; // Döngü sonunda i'yi artýrmamak için geri al
        }
    }

    // Stack'teki operatörleri boþalt
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
// Postfix ifadesini deðerlendiren fonksiyon
int EvaluatePostfixExpression(string& s) {
    stack<int> evalStack;
    int i = 0;

    while (i < s.size()) {
        if (isdigit(s[i])) {  // Sayýysa
            int num = 0;
            while (i < s.size() && isdigit(s[i])) { // Tam sayýyý oluþtur
                num = num * 10 + (s[i] - '0');
                i++;
            }
            evalStack.push(num);  // Yýðýna ekle
        }
        else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') {  // Operatörse
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