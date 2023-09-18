/////////////////////////////////////////////////////////////////////
//
// Laboratorio 3: calcolo di semplici espressioni numeriche 
//                mediante pile e code
//
// vengono accettati dall'esterno solo numeri positivi.
// Per trattare anche numeri negativi occorre modificare
// l'analizzatore lessicale.
//
///////////////////////////////////////////////////////////////////


#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

#include "token.h"

using std::cout;
using std::cin;
using std::string;
using std::istringstream;
using std::ostringstream;

/////////////////////////////////////////////////////////////////////
// Funzioni ausiliarie su tipi di dato semplici
/////////////////////////////////////////////////////////////////////

// da stringa a numero
int str2int(const string &s) {
  // DA IMPLEMENTARE
  return 0;
}

// da numero a stringa
string int2str(int n) {
  // DA IMPLEMENTARE
  return "";
}

// ritorna false se e solo se non si può leggere un token dall'input stream;
// inserisce in t il token letto
bool prossimoToken(istringstream &iss, token &t) {
  // DA IMPLEMENTARE
  return false;
}

