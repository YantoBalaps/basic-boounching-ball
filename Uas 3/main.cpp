#include <iostream>
#include <windows.h>
#include <string>
#include <ctime>
#include <cmath>

using namespace std;

void setConsoleSize(int width, int height) {
    COORD coord;
    coord.X = width;
    coord.Y = height;

    SMALL_RECT Rect;
    Rect.Top = 0;
    Rect.Left = 0;
    Rect.Bottom = height - 1;
    Rect.Right = width - 1;

    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleScreenBufferSize(console, coord);
    SetConsoleWindowInfo(console, TRUE, &Rect);
}

void showMenu() {
    cout << "Menu:" << endl;
    cout << "1. Start game" << endl;
    cout << "2. Nama kelompok" << endl;
    cout << "3. Petunjuk" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter your choice (1/2/3/4): ";
}

void displayGroupInfo() {
    const HANDLE oh = GetStdHandle(STD_OUTPUT_HANDLE);
    do {
        system("CLS"); // Clear the screen
        SetConsoleTextAttribute(oh, 4);
        cout << "\tNAMA KELOMPOK\n";
        cout << "+----+-----------------------------------+--------------+\n";
        cout << "| NO |"
            << "               Nama                |"
            << "     NIM      |" << endl;
        cout << "+----+-----------------------------------+--------------+\n";
        SetConsoleTextAttribute(oh, 13);
        cout << "| 1. |"
            << "            Adi Vesadeo            |"
            << "  23.11.5774  |" << endl;
        cout << "+----+-----------------------------------+--------------+\n";
        SetConsoleTextAttribute(oh, 12);
        cout << "| 2. |"
            << "       Ibnu Setiyanto Nugroho      |"
            << "  23.11.5787  |" << endl;
        cout << "+----+-----------------------------------+--------------+\n";
        SetConsoleTextAttribute(oh, 10);
        cout << "| 3. |"
            << "        Desfa Hafidh Abiyyu        |"
            << "  23.11.5775  |" << endl;
        cout << "+----+-----------------------------------+--------------+\n";
        SetConsoleTextAttribute(oh, 6);
        cout << "| 4. |"
            << "   Nathan Farros Kusuma Barracuda  |"
            << "  23.11.5780  |" << endl;
        cout << "+----+-----------------------------------+--------------+\n";
        SetConsoleTextAttribute(oh, 7);

        cout << "Press 0 to return to the main menu: ";
        int subChoice;
        cin >> subChoice;

        if (subChoice == 0) {
            system("CLS");
            return; // Kembali ke menu utama
        }
        else {
            system("CLS");
            cout << "Tolong masukkan 0, jangan yang lain!!" << endl;
        }
    } while (true);
}

void displayInstructions() {
    system("CLS");
    cout << "PETUNJUK PERMAINAN\n";
    cout << "===================\n";
    // Tambahkan petunjuk permainan sesuai kebutuhan
    cout << "1. Tekan panah kanan untuk bergerak ke kanan.\n";
    cout << "2. Tekan panah kiri untuk bergerak ke kiri.\n";
    cout << "3. Cari Skor sebanyak-banyak nya\n";

    cout << "\nPress 0 to return to the main menu: ";
    int subChoice;
    cin >> subChoice;

    if (subChoice == 0) {
        system("CLS");
        return; // Kembali ke menu utama
    }
    else {
        system("CLS");
        cout << "Tolong masukkan 0, jangan yang lain!!" << endl;
    }
}
    

int main() {
    const HANDLE oh = GetStdHandle(STD_OUTPUT_HANDLE);
    const int RADIUS = 4;
    const int TOLERANCE = 6;
    int cirX = 0, cirY = 0, CIRBOUNDX = 50, CIRBOUNDY = 20;
    int cirXDir = 1, cirYDir = 1;
    int playerX = 5;
    int score = 0;

    bool hasCollided = false;

    // Set console window size to 60x30
        setConsoleSize(60, 30);


    int choice;
    do {
        showMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            system("CLS");
            while (true) {
                if (GetAsyncKeyState(VK_RIGHT)) {
                    playerX += 3;
                }
                else if (GetAsyncKeyState(VK_LEFT)) {
                    playerX -= 3;
                }

                system("CLS");

                for (int j = 0; j < cirY; j++) {
                    cout << endl;
                }

                for (int xCir = -RADIUS; xCir <= RADIUS; xCir++) {
                    for (int dx = 0; dx < cirX; dx++) {
                        SetConsoleTextAttribute(oh, 9);
                        cout << " ";
                    }
                    for (int yCir = -RADIUS; yCir <= RADIUS; yCir++) {
                        int eq = xCir * xCir + yCir * yCir - RADIUS * RADIUS;
                        cout << ((abs(eq) < TOLERANCE) ? "*" : " ");
                    }
                    cout << endl;
                }

                for (int extend = CIRBOUNDY; extend > cirY + RADIUS - 1; extend--) {
                    cout << endl;
                }

                for (int dx = 0; dx < playerX; dx++) {
                    SetConsoleTextAttribute(oh, 9);
                    cout << " ";
                }

                for (int width = 0; width < 10; width++) {
                    SetConsoleTextAttribute(oh, 10);
                    cout << "=";
                }
                cout << endl;

                cirX += cirXDir;
                cirY += cirYDir;

                if (cirX <= 0 || cirX >= CIRBOUNDX) {
                    cirXDir = -cirXDir;
                }

                if (cirY <= 0) {
                    cirYDir = 1;
                }
                else if (cirY >= CIRBOUNDY) {
                    if (cirX >= playerX - RADIUS && cirX <= playerX + 10 + RADIUS) {
                        if (!hasCollided) {
                            cirYDir = -1;
                            score++;
                            Beep(440, 200);
                            hasCollided = true;
                        }
                    }
                    else {
                        system("CLS");
                        SetConsoleTextAttribute(oh, 12);
                        cout << "Yahaha kalah! Total score mu: " << score << endl;
                        SetConsoleTextAttribute(oh, 7);
                        system("pause");

                        system("CLS");

                        cirX = 0;
                        cirY = 0;
                        cirXDir = 1;
                        cirYDir = 1;
                        playerX = 5;
                        score = 0;
                        hasCollided = false;
                        break;
                    }
                }

                SetConsoleCursorPosition(oh, { 50, 0 });
                SetConsoleTextAttribute(oh, 10);
                cout << "Score: ";
                SetConsoleTextAttribute(oh, 10);
                cout << score << ' ';

                if (cirX >= playerX - RADIUS && cirX <= playerX + 10 + RADIUS && cirY >= CIRBOUNDY - 2) {
                    hasCollided = false;
                }

                Sleep(30);
            }

            break;

        case 2:
            system("CLS");
            displayGroupInfo();
            break;

        case 3:
            system("CLS");
            displayInstructions();
            break;

        case 4:
            return 0;

        default:
            system("CLS");
            cout << "Pilihan tidak valid. Silakan pilih 1, 2, atau 3." << endl;
        }
    } while (true);

    return 0;
}
