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
#include <string>
#include "funzioni.h"


using namespace std;

struct headerIp
{
	string version = "0100"; // ipv4
	string hlen = "0101";	 // 5 perche' nessuna opzione (20 x 8) / 32
	string tos = "01100110";
	string totLenght = "0000010111011100"; // 1500
	string id = "0000000000000001";		   // 16 bit
	string flags = "000";
	string offset = "0000000000000";					 // 13 bit
	string ttl = "01000000";							 // 64
	string protocol = "00000110";						 // TCP
	string checksum = "0000000000000000";				 // inizialmente 0
	string ipSource = "1100000010101000110010011001000"; // 192.168.100.200
	string ipDest = "11000000101010000000000100000001";	 // 192.168.1.1
};

struct headerDataLink{
	string dsap = "111111110000100000000000110000100101010001111011"; //ff0800c2547b
	string ssap = "000000001111111110000000101011000101001011101011"; //00ff80ac52eb
	string headertype = "1000000000000000";							//0x8000		
};

headerIp ipv4;
headerDataLink dataLink;

string leggiMsg();
void scriviFrame(string frame);

string charInBin(char carattere); //prende il carattere e lo traduce in codice ascii
string stringInBin(string msg);// prende la stringa e restituisce una stringa di 0 e 1

void creaFrame();

string headerIpv4();
string ipChecksum(string bits);

string calcolaCRC(const string &payload);
string headerData();

int main()
{
	creaFrame();
}


// FILE
// FILE

string leggiMsg()
{ // prendo la prima riga del file msg.txt e la ritorno
	string msg;
		
	ifstream fin("msg.txt");

	if (!fin)
	{
		cerr << "Errore nell'apertura del file in lettura\n";
		return "ciao";
	}
	getline(fin, msg);

	fin.close();

	return msg;
}

void scriviFrame(string frame)
{ // creo il frame
	ofstream fout("frame.txt");

	if (!fout)
	{
		cerr << "Errore nell'apertura del file in scrittura\n";
		exit;
	}
	fout << frame;

	fout.close();
}

// CONVERSIONE
// CONVERSIONE

string charInBin(char carattere)
{
	string charToBin;
	int i = 0;

	while (carattere >= 1)
	{
		if (carattere % 2)
		{ // se modulo =1 aggiungop 1 alla stringa
			charToBin = "1" + charToBin;
		}
		else
		{
			charToBin = "0" + charToBin;
		}
		carattere /= 2;
		i++;
	}

	for (i; i < 8; i++)
	{ // se non ho raggiunto 8 bit aggiungo 0 finche' non arrivo a 8
		charToBin = "0" + charToBin;
	}

	return charToBin;
}

string stringInBin(string msg)
{
	string stringInBin;

	for (int i = 0; i < msg.size(); i++)
	{ // scorro la string, converto ogni carattere e lo aggiungo ad una stringa che poi ritorno
		stringInBin = stringInBin + charInBin(msg[i]);
	}

	return stringInBin;
}

// CREA FRAME
// CREA FRAME

void creaFrame()
{
	string frame = leggiMsg(); // prendo il messaggio da file

	frame = stringInBin(frame); // lo traduco in binario
	
	string preChecksum = headerIpv4() + frame; // per calcolare il checksum creo il frame

	ipv4.checksum = ipChecksum(preChecksum);   //calcolo il checksum 
	
	frame = headerIpv4() + frame;   //creo frame con il campo checksum compilato

	frame = headerData() + frame;
	
	scriviFrame(frame); // scrivo in file
}

// HEADER IPV4
// HEADER IPV4

string headerIpv4()
{
	string frame;

	frame = ipv4.version; // aggiungo tutti i campi dell'header a una stringa che ritorno
	frame += ipv4.hlen;
	frame += ipv4.tos;
	frame += ipv4.totLenght;
	frame += ipv4.id;
	frame += ipv4.flags;
	frame += ipv4.offset;
	frame += ipv4.ttl;
	frame += ipv4.protocol;
	frame += ipv4.checksum;
	frame += ipv4.ipSource;
	frame += ipv4.ipDest;
	// frame = ipv4.padding + frame;

	return frame;
}

string ipChecksum(string bits) {
    unsigned int sum = 0;
    for (size_t i = 0; i < bits.size(); i += 16) {
        unsigned short block = 0;
        for (int j = 0; j < 16; j++) {
            block = (block << 1) | (bits[i + j] - '0');
        }
        sum += block;
        if (sum & 0x10000) sum = (sum & 0xFFFF) + 1;
    }
    unsigned short crc = ~sum & 0xFFFF;
    string scrc = to_string(crc);
    return scrc;
}

//collegamento

string headerData(){
	string frame;
	frame = dataLink.dsap;
	frame += dataLink.ssap;
	frame += dataLink.headertype;
	return frame;
}

