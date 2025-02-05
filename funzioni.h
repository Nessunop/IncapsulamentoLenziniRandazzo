#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <stdlib.h>


using namespace std;

string leggiMsg();
void scriviMsg();
void scriviFrame(string frame);

void menuStart();
void menuScelta();
void menuMessaggio();
void menuRete();
void menuProtocol();
void menuTOS();
void menuDatalink();

string charInBin(char carattere); //prende il carattere e lo traduce in codice ascii
string stringInBin(string msg);// prende la stringa e restituisce una stringa di 0 e 1
string decInBin(int decimale);

void creaFrame();

string headerIpv4();
void completaIpv4();
void modifTOS(int i);
void modifProtocol(string newProtocol);
void modifIP();
int binToInt(const string& bin);
int calculateChecksum(int headerWords[], int size);


