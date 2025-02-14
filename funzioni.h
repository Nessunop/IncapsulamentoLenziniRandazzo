#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string leggiMsg();
void scriviFrame(string frame);

string charInBin(char carattere); //prende il carattere e lo traduce in codice ascii
string stringInBin(string msg);// prende la stringa e restituisce una stringa di 0 e 1

void creaFrame();

string headerIpv4();
string ipChecksum(string bits);

string calcolaCRC(const string &payload);
string headerData();

