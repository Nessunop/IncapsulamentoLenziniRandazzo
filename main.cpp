//incapsulamento,

//messaggio dall'alto, salvo in file (ciao mondo) = payload
//prendere messaggio, porta in binario - scelgo tutte le opzioni
//struct livello 3
//	struct ethernet frame
//	tutto in binario


//	poi passo al livello inferiore(datalink)
//	2 mac address, fcs, header type, preamble 0xaa, sfd 0xbb, calcola crc


//	scrivi su un file la stringa di tutto il pacchetto in binario

//	msg.txt(messaggio)

//	main.cpp(main)

//	funzioni.h(dichiarazione prototipi funzioni e struct) (#include "funzioni.h"

//		funzioni.cpp(codici funzioni e struct)

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "funzioni.h"

using namespace std;

int main()
{
	menuStart();
}


