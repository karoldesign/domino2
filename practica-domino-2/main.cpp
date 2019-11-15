//
//  main.cpp
//  practica-1-domino
//
//  Created by Carolina Chamorro on 12/10/2019.
//  Copyright © 2019 Carolina Chamorro. All rights reserved.
//

#include <time.h>
#include <cstdlib>
#include <list>
#include <iostream>
#include <fstream>

using namespace std;
const int numToken = 28;
typedef short int tArray[numToken];

string toStr(int n) {
    switch (n) {
        case 0:
            return "0";
        case 1:
            return "1";
        case 2:
            return "2";
        case 3:
            return "3";
        case 4:
            return "4";
        case 5:
            return "5";
        case 6:
            return "6";
        case 7:
            return "7";
        case 8:
            return "8";
        case 9:
            return "9";
        default:
            return "ERROR";
    }
}

// Token
string tokenToStr(short int left, short int right) {
    string str = "|" + toStr(left) + "-" + toStr(right) + "|";
    return str;
}

// painting pool
string poolToStr(tArray pool1, tArray pool2, int numPlayerToken) {
    string str;
    
    for ( int i = 0; i < numPlayerToken; i++ ) {
        str = str + tokenToStr(pool1[i], pool2[i]);

    }
    return str;
}

bool canPutLeft(string board, short int tokenN1, short int tokenN2) {
    return (board[1]-0x30==tokenN2);
}

bool canPutRight(string board, short int tokenN1, short int tokenN2) {
    return (board[board.size()-2]-0x30==tokenN1);
}


string putTokenLeft(string board, short int tokenN1, short int tokenN2) {
    return tokenToStr(tokenN1, tokenN2) + board;
}

string putTokenRight(string board, short int tokenN1, short int tokenN2) {
    return board + tokenToStr(tokenN1, tokenN2);
}


void deleteToken (tArray tokenN1, tArray tokenN2, short int& numPlayerToken, short int numToken) {
    for(int i = numToken; i < numPlayerToken; i++) {
        tokenN1[i] = tokenN1[i+1];
        tokenN2[i] = tokenN2[i+1];
    }
    numPlayerToken--;
}

void drawTokens (tArray pool1, tArray pool2, short int cont, short int& tokenN1, short int& tokenN2) {
    for (int i = 0; i < 1; i++) {
        tokenN1 = pool1[cont-1];
        tokenN2 = pool2[cont-1];
        cont--;
    }
}

// Tablero
void showBoard(tArray tokenN1, tArray tokenN2, string board, int numCounter, int numStolen, int numPlayerToken) {
    cout << " -------------------- " << endl;
    cout << "|       TABLERO      |" << endl;
    cout << " -------------------- " << endl;
    cout << board << endl;
    cout << "Fichas colocadas: " << numCounter << " - Fichas robadas: " << numStolen << endl;
    cout << "Fichas del jugador: " << poolToStr(tokenN1, tokenN2, numPlayerToken) << endl;
    return;
}

// Menú
int showMenu() {
    int chooseOption = 0;
    
    while (chooseOption < 1 || chooseOption > 4) {
        cout << " -------------------- " << endl;
        cout << "|  MENÚ DE OPCIONES  |" << endl;
        cout << " -------------------- " << endl;
        cout << "1. Poner ficha por la izquierda" << endl;
        cout << "2. Poner ficha por la derecha" << endl;
        cout << "3. Robar ficha nueva" << endl;
        cout << "4. Salir" << endl;
        
        cout << "Elija opción: ";
        cin >> chooseOption;
    }
    
    return chooseOption;
}

// aleat
short int aleat(int n) {
    return rand()%(n+1);
}

short int chooseToken(tArray tokenN1, tArray tokenN2, int numPlayerToken) {
    int chooseToken = 0;

    for(int i = 0; i < numPlayerToken; i++) {
        cout << "(" << i+1 << ") " << tokenToStr(tokenN1[i], tokenN2[i]) << endl;
    }
    
    while (chooseToken < 1 || chooseToken > numPlayerToken) {
        cout << "Elije ficha: ";
        cin >> chooseToken;
    }
    return chooseToken;
}

short int chooseMax() {
    int chooseMax = 0;
    
    while (chooseMax < 6 || chooseMax > 9) {
        cout << "Variante del juego (entre 6 y 9): ";
        cin >> chooseMax;
    }
    return chooseMax;
}

bool chooseSave() {
    char option = ' ';
    
    while (option != 'S' && option != 'N') {
        cout << "¿Quiéres guardar antes de salir? (S/N)";
        cin >> option;
    }
    
    return option == 'S';
}

bool openFile() {
    char option = ' ';
    
    while (option != 'S' && option != 'N') {
        cout << "¿Quiéres abrir un archivo anterior? (S/N)";
        cin >> option;
    }
    
    return option == 'S';
}

void generatePool(tArray pool1, tArray pool2, int max) {
    int k = 0;
    for ( int i = 0; i <= max; i++ ) {
        for ( int j = 0; j <= i; j++ ) {
            pool1[ k ] = i;
            pool2[ k ] = j;
            k++;
        }
    }
}

void disorderPool(tArray pool1, tArray pool2) {
    int idx;
    short int tmp1, tmp2;
        for (int i = numToken - 1; i >= 0; i--) {
            idx = rand() % (i + 1);
            if (i != idx) {
            tmp1 = pool1[i];
            tmp2 = pool2[i];
            pool1[i] = pool1[idx];
            pool2[i] = pool2[idx];
            pool1[idx] = tmp1;
            pool2[idx] = tmp2;
        }
    }
}

bool canDrawToken(string board, tArray tokenN1, tArray tokenN2, int numPlayerToken) {
    bool canPutLeftBool = true;
    bool canPutRightBool = true;
    bool boolToken = (canPutLeftBool && canPutRightBool);

    for (int i = 0; i <= numPlayerToken; i++) {
        canPutLeftBool = canPutLeft(board, tokenN1[i], tokenN2[i]) && canPutLeft(board, tokenN2[i], tokenN1[i]);
        canPutRightBool = canPutRight(board, tokenN1[i], tokenN2[i]) && canPutRight(board, tokenN2[i], tokenN1[i]);

        if (!boolToken) {
            return boolToken;
        }
    }
    return !boolToken;
}

int main(int argc, const char * argv[]) {
    int counter = 0;
    int stolen = 0;
    int max = 0;
    short int numPlayerToken = 0;
    int numPoolToken = 0;
    tArray tokenN1;
    tArray tokenN2;
    string board;
    tArray pool1;
    tArray pool2;
    
    
    srand(time(NULL));
    
    if (openFile()) {
        ifstream archivo;
        archivo.open("domino_save.txt", ios::in);
        if (!archivo.is_open()) {
            cout << "¡No se ha podido abrir el archivo!" << endl;
            
            max = chooseMax();
        
            generatePool(pool1, pool2, max);
            disorderPool(pool1, pool2);
            numPlayerToken = 7;
            numPoolToken = numToken;

            for (int i = 0; i < numPlayerToken; i++) {
                tokenN1[i] = pool1[numPoolToken-1];
                tokenN2[i] = pool2[numPoolToken-1];
                numPoolToken--;
            }

            board = tokenToStr(pool1[numPoolToken-1],pool2[numPoolToken-1]);
            numPoolToken--;
            
        } else {
            archivo >> board;
            // archivo >> pool1;
            // archivo >> pool2;
            // // archivo >> tokenN1;
            // // archivo >> tokenN2;
            archivo >> counter;
            archivo >> stolen;
            archivo >> max;
            archivo >> numPlayerToken;
            archivo >> numPoolToken;
            archivo.close();
        }
    } else {
        
        max = chooseMax();
        
        generatePool(pool1, pool2, max);
        disorderPool(pool1, pool2);
        numPlayerToken = 7;
        numPoolToken = numToken;

        for (int i = 0; i < numPlayerToken; i++) {
            tokenN1[i] = pool1[numPoolToken-1];
            tokenN2[i] = pool2[numPoolToken-1];
            numPoolToken--;
        }

        board = tokenToStr(pool1[numPoolToken-1],pool2[numPoolToken-1]);
        numPoolToken--;
    }
    
    for (int option = 0; option != 4;) {
        showBoard(pool1, pool2, board, counter, stolen, numPlayerToken);
        option = showMenu();
        short int chosen;

        switch(option){
            case 1:
                chosen = chooseToken(tokenN1, tokenN2, numPlayerToken);
                if (canPutLeft(board, tokenN1[chosen], tokenN2[chosen])) {
                    board = putTokenLeft(board, tokenN1[chosen], tokenN2[chosen]);
                    deleteToken(tokenN1, tokenN2, numPlayerToken, chosen);
                    counter++;
                } else if (canPutLeft(board, tokenN2[chosen], tokenN1[chosen])) {
                    board = putTokenLeft(board, tokenN2[chosen], tokenN1[chosen]);
                    deleteToken(tokenN1, tokenN2, numPlayerToken, chosen);
                    counter++;
                } else {
                    cout << " ERROR! :-( " << endl;
                }
                break;
            case 2: 
                chosen = chooseToken(tokenN1, tokenN2, numPlayerToken);
                if (canPutRight(board, tokenN1[chosen], tokenN2[chosen])) {
                    board = putTokenRight(board, tokenN1[chosen], tokenN2[chosen]);
                    deleteToken(tokenN1, tokenN2, numPlayerToken, chosen);
                    counter++;
                } else if (canPutRight(board, tokenN2[chosen], tokenN1[chosen])) {
                    board = putTokenRight(board, tokenN2[chosen], tokenN1[chosen]);
                    deleteToken(tokenN1, tokenN2, numPlayerToken, chosen);
                    counter++;
                } else {
                    cout << " ERROR! :-( " << endl;
                }
                break;
            case 3:
                if (canDrawToken(board, tokenN1, tokenN2, numPlayerToken)) {
                    numPlayerToken = numPlayerToken + 1;
                    drawTokens(pool1, pool2, numPoolToken, tokenN1[numPlayerToken], tokenN2[numPlayerToken]);
                    stolen++;
                } else {
                    cout << ">> Tienes fichas que puedes utilizar! :-) <<" << endl;
                }
                break;
        }
    }
    
    if (chooseSave()) {
        ofstream archivo;
        archivo.open("domino_save.txt", ios::out);
        if (!archivo.is_open()) {
            cout << "¡No se ha podido abrir el archivo!" << endl;
        } else {
            archivo << board << '\n'
            << tokenN1 << '\n'
            << tokenN2 << '\n'
            << counter << '\n'
            << stolen << '\n'
            << max << '\n';
            
            archivo.close();
        }
    }
    return 0;
}
