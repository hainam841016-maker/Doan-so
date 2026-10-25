#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    srand(time(0));

    int secret = rand() % 100 + 1;
    int guess;
    int attempts = 7;

    cout << "============================\n";
    cout << "     GAME DOAN SO BI MAT\n";
    cout << "============================\n";
    cout << "May da chon mot so tu 1 den 100.\n";
    cout << "Ban co 7 luot de doan!\n\n";

    for (int i = 1; i <= attempts; i++) {
        cout << "Luot " << i << " - Nhap so ban doan: ";
        cin >> guess;

        if (guess == secret) {
            cout << "\nCHUC MUNG! BAN DA THANG!\n";
            cout << "So bi mat la: " << secret << endl;
            cout << "So luot da dung: " << i << endl;
            return 0;
        }
        else if (guess < secret) {
            cout << "So bi mat LON HON!\n\n";
        }
        else {
            cout << "So bi mat NHO HON!\n\n";
        }
    }

    cout << "GAME OVER! BAN DA THUA!\n";
    cout << "Dap an la: " << secret << endl;

    return 0;
