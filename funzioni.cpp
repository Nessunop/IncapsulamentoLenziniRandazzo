#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <bitset>
#include "funzioni.h"

struct headerIp
{
	string version = "0100"; // ipv4
	string hlen = "0101";	 // 5 perche' nessuna opzione (20 x 8) / 32
	string tos = "00000000";
	string totLenght;
	string id = "0000000000000000"; // 16 bit
	string flags = "010";
	string offset = "0000000000000"; // 13 bit
	string ttl = "00000000";
	string protocol = "00010001";						  // UDP
	string checksum = "0000000000000000";				  // inizialmente 0
	string ipSource = "11000000101010000011100000000001"; // 192.168.56.1
	string ipDest = "11000000101010000011100000000101";	  // 192.168.56.5
};

headerIp ipv4;

// MENU
// MENU

void menuStart()
{
	cout << "<---------------------------------------->\n";
	cout << "benvenuto nell'incapsulamento di randazzo\n";
	cout << "<---------------------------------------->\n";
	menuScelta();
}

void menuScelta()
{
	bool continua = true;
	while (continua)
	{
		int scelta;

		cout << "1) Opzioni Messaggio\n2) Opzioni Livello Rete\n4) Crea frame\n0) Esci\n\nCosa vuoi fare?: ";
		cin >> scelta;

		switch (scelta)
		{
		case 1:
			menuMessaggio();
			break;

		case 2:
			menuRete();
			break;

			// case 3:
			// 	menuDatalink();
			// 	break;

		case 4:
			creaFrame();
			break;

		default:
			continua = false;
			cout << "Uscita";
		}
	}
}

void menuMessaggio()
{
	int scelta;
	bool continua = true;

	while (continua)
	{
		cout << "1) Mostra Messaggio\n2) Scrivi Messaggio\n0) Esci\n\nCosa vuoi fare?: ";
		cin >> scelta;

		switch (scelta)
		{
		case 1:
			cout << leggiMsg() << endl;
			break;

		case 2:
			scriviMsg();
			break;

		default:
			continua = false;
			break;
		}
	}
}

void menuRete()
{
	int scelta;
	bool continua = true;

	cout << "1) Modifica campo Protocol\n2)\n3) Modifica TOS\n0) Esci\n\nCosa vuoi fare?: ";
	cin >> scelta;

	switch (scelta)
	{
	case 1:
		menuProtocol();
		break;

		// case 2:
		// 	modifIP();
		// 	break;

	case 3:
		menuTOS();

	default:
		continua = false;
	}
}

void menuProtocol()
{
	int scelta;
	bool continua = true;

	while (continua)
	{
		cout << "1) Utilizza TCP \n2) Utilizza UDP\n3)Mostra protocollo corrente\n0) Esci\n\nCosa vuoi fare?: ";
		cin >> scelta;

		switch (scelta)
		{
		case 1:
			modifProtocol("00000110"); // binario di tcp
			cout << "Protocollo aggiornato\n";
			break;

		case 2:
			modifProtocol("00010001"); // binario di udp
			cout << "Protocollo aggiornato\n";
			break;

		case 3:
			cout << "Il protocollo utilizzato ha codice: " << ipv4.protocol << endl;
			break;
		default:
			continua = false;
		}
	}
}

void menuTOS()
{
	int scelta;
	bool continua = true;

	while (continua)
	{
		cout << "1) Delay\n2) Throughput\n3) Reliability\n4) Monetary Cost\n5) Stampa campo TOS\n0) Esci\n\nCosa vuoi fare?: ";
		cin >> scelta;

		switch (scelta)
		{
		case 1:
			modifTOS(3);
			break;

		case 2:
			modifTOS(4);
			break;

		case 3:

			modifTOS(5);
			break;

		case 4:
			modifTOS(6);
			break;

		case 5:
			cout << "bit 1-3 : precedenza, 4 : delay, 5 : throughput, 6 : reliability, 7 : monetary cost, 8 : unused\n"
				 << ipv4.tos << "\n";
			break;

		default:
			continua = false;
		}
	}
}

void menuDatalink()
{
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

void scriviMsg()
{ // scrivo un nuovo messaggio
	string newMsg;
	cout << "Inserisci il messaggio: ";
	cin >> newMsg;

	ofstream fout("msg.txt");

	if (!fout)
	{
		cerr << "Errore nell'apertura del file in scrittura\n";
		return;
	}
	fout << newMsg;

	fout.close();
	cout << "Messaggio aggiornato\n";
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

string decInBin(int decimale)
{
	string decToBin;
	int i = 0;

	while (decimale >= 1)
	{
		if (decimale % 2)
		{ // se modulo =1 aggiungop 1 alla stringa
			decToBin = "1" + decToBin;
		}
		else
		{
			decToBin = "0" + decToBin;
		}
		decimale /= 2;
		i++;
	}

	return decToBin;
}

int binToInt(const string &bin)
{
	return stoi(bin, nullptr, 2);
}

// CREA FRAME
// CREA FRAME

void creaFrame()
{
	completaIpv4(); // completo la struct dell'header ipv4

	string frame = leggiMsg(); // prendo il messaggio da file

	frame = stringInBin(frame);	  // lo traduco in binario
	frame = headerIpv4() + frame; // aggiungo tutti i campi dell'header in binario

	scriviFrame(frame); // scrivo in file
}

// HEADER IPV4
// HEADER IPV4

string headerIpv4()
{
	string frame;

	frame = ipv4.version; // aggiungo tutti i campi dell'header a una stringa che ritorno
	frame = ipv4.hlen + frame;
	frame = ipv4.tos + frame;
	frame = ipv4.totLenght + frame;
	frame = ipv4.id + frame;
	frame = ipv4.flags + frame;
	frame = ipv4.offset + frame;
	frame = ipv4.ttl + frame;
	frame = ipv4.protocol + frame;
	// frame = ipv4.checksum + frame;
	frame = ipv4.ipSource + frame;
	frame = ipv4.ipDest + frame;
	// frame = ipv4.padding + frame;

	return frame;
}

void completaIpv4()
{
	// prendere lunghezza della stringa, lunghezza dell'header, converto in binario stringa
	string msg = leggiMsg();

	int lenghtMsg = msg.size(); // lunghezza del messaggio (array di char)

	lenghtMsg += 20; // aggiungo lunghezza dell header

	string campo = decInBin(lenghtMsg); // converto da decimale in binario stringa

	ipv4.totLenght = campo;

	int headerWords[10] = {
		(binToInt(ipv4.version + ipv4.hlen) << 8) | binToInt(ipv4.tos),
		binToInt(ipv4.totLenght),
		binToInt(ipv4.id),
		(binToInt(ipv4.flags) << 13) | binToInt(ipv4.offset),
		(binToInt(ipv4.ttl) << 8) | binToInt(ipv4.protocol),
		0,
		binToInt(ipv4.ipSource.substr(0, 16)),
		binToInt(ipv4.ipSource.substr(16, 16)),
		binToInt(ipv4.ipDest.substr(0, 16)),
		binToInt(ipv4.ipDest.substr(16, 16))};

	int checksum = calculateChecksum(headerWords, 10);
	ipv4.checksum = bitset<16>(checksum).to_string();
}

int calculateChecksum(int headerWords[], int size)
{
	int sum = 0; // sum accumula la somma delle parole da 16 bit.
	for (int i = 0; i < size; i++)
	{ // Scorre tutte le parole dell'header e le somma.
		sum += headerWords[i];
		if (sum > 0xFFFF)
		{										// Se la somma supera 0xFFFF = overflow.
			sum = (sum & 0xFFFF) + (sum >> 16); // sum & 0xFFFF → Tiene solo i 16 bit meno significativi della somma.
			sum >> 16;							// Prende il riporto(carry), cioè i bit in eccesso.
					  							 // Li somma di nuovo per ottenere il valore corretto.
		}
	}
	return ~sum & 0xFFFF;
}

void modifProtocol(string newProtocol)
{
	ipv4.protocol = newProtocol;
}

void modifIP()
{
	cout << "Inserisci l'ip:";
}

void modifTOS(int i)
{
	if (ipv4.tos[i] == '0')
	{
		ipv4.tos[i] = '1'; // se flag e' 0 lo mette a 1 e viceversa,
	}
	else
	{
		ipv4.tos[i] = '0';
	}
}
