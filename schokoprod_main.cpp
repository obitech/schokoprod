/* schokoprod.cpp
**********************************************************
* Das folgende Programm erlaubt Berechnungen über eine fiktive Schokoladenproduktion.
* Als Eingabe müssen zwei Datein vorliegen: schoki.txt, welches die Rezepte der Pralinen enthält
* und zutaten.txt, welche die Zutaten und deren Preis pro 100gm enthält. Im vorliegenden Beispiel
* sind 3 Pralinen, 7 Zutaten und 5 maximale Zutaten pro Praline gegeben. Diese Werte und die 
* Textdatein können aber angepasst werden (es müssen aber noch die jeweiligen #defines geändert)
* werden.
* Nun können die Rohstoffkosten für eine oder mehrer Tafeln berechnet werden, sowie
* eine Matrix zum Berechnen des Verkaufspreises. Für die Berechnung des Verkaufspreises kommen
* zusätliche Kosten wie Personal, Betrieb, etc. hinzu, welche auch angepasst werden können.
* Für dieses Programm habe ich mehrer structs genutzt, welche über Funktionen angepasst werden können.
* Sämtliche Berechnung die eine Ausgabe liefern wurden in extra Funktionen ausgelagert, so dass man
* das Programm modular erweitern kann. Desweiteren habe ich versucht möglichst alle falsche Inputwerte
* vom User abzufangen (siehe Hilfsfunktionen in der Mitte des Quelltexts). Ich habe versucht die User Experience
* so angenehm wie möglich zu gestalten und alle Ausageben anschaulich formatiert. Über ein Hauptmenü kann der 
* der Nutzer verschiedene Berechnungen und Ausgaben durchführen. Das Programm kann im Menü mit der Eingabe 0 
* oder normal mit Strg + C beendet werden.
**********************************************************/

// Header file
#include "schokoprod_functions.cpp"

/********************************************************
*************** FUNKTIONEN: DEKLARATION *****************
*********************************************************/
/*
extern void 	print_zutaten(zutat_t *array);
extern void 	print_pralinen(schokolade_t *array, zutat_t *array2);
extern void 	berechnung_rohstoff(schokolade_t *array, zutat_t *array2);
extern void		berechnung_rohstoff_pro_tafel(schokolade_t *array, zutat_t *array2);
extern void 	berechnung_preis(schokolade_t *array, zutat_t *array2);
extern int 		get_uint();

extern void 	press_enter();
extern void 	help();*/

/********************************************************
********************* START OF MAIN *********************
*********************************************************/

int main() {

/********************************************************
**************** EINLESEN DER ZUTATEN *******************
*********************************************************/

	int i = 0;

	// Variablen für Zutaten
	zutat_t zutaten[ANZAHL_ZUTATEN];
	char fname[20];
	float fpreis;

	// Zutaten file öffnen
	ifstream zutatenFile;
	zutatenFile.open(DATEI_ZUTATEN_NAME);

	if (!zutatenFile) {
		cout << "zutaten.txt konnte nicht geöffnet werden.\n";
		press_enter();
		return 1;
	}

	// Struct befüllen
	while(zutatenFile >> fname >> fpreis) {
		strcpy(zutaten[i].name, fname);
		zutaten[i].preis_pro_100gramm = fpreis;
		i++;
	}

	zutatenFile.close();

/********************************************************
************** EINLESEN DER SCHOKOLADE  *****************
*********************************************************/

	// Variablen für Pralinen
	schokolade_t praline[ANZAHL_PRALINEN];
	char input[20];

	// Schokoladen-file öffnen
	ifstream schokoFile;
	schokoFile.open(DATEI_REZEPTE_NAME);

	if (!schokoFile) {
		cout << "schoki.txt konnte nicht geöffnet werden.\n";
		press_enter();
		return 1;
	}

	// Loop über 3 Pralinen
	for (int i = 0; i < ANZAHL_PRALINEN; i++ ) {
		int j = 0;

		schokoFile >> input;
		strcpy(praline[i].name, input);
		schokoFile >> praline[i].gewicht;
		
		// Anzahl der Zutaten für diese Praline
		schokoFile >> j;

		// Wenn Anzahl < 5, setze rest auf -1
		if (j < ANZAHL_ZUTATEN_PRO_PRALINE) 	{
			for (int p = j; p < ANZAHL_ZUTATEN_PRO_PRALINE; p++) {
				praline[i].zutat[p].id = -1;
			}
		}

		// Loop über die einzelnen Zutaten
		for (int k = 0; k < j; k++) {
			schokoFile >> input;
			
			// ID finden & in Pralinenarray packen
			for (int z = 0; z < ANZAHL_ZUTATEN; z++) {
				if (strcmp(zutaten[z].name, input) == 0) {
					praline[i].zutat[k].id = z;
				}
			}

			schokoFile >> praline[i].zutat[k].menge_in_prozent;
		}
	}

	schokoFile.close();

	// Allgemeine Rohstoffkosten für eine Tafel werden ermitteln und structs entsprechend befüllt
	berechnung_rohstoff(praline, zutaten);

/********************************************************
************************* MENU **************************
*********************************************************/	

	string choice;

	while (true) {
		cout << "\n-- Hauptmenü\n";
		cout << "Willkommen im Programm zur Berechnung einer Schokoladenproduktion. Bitte wählen Sie:\n";
		cout << "1 - STANDARDAUSGABE FÜR BELEG\n";
		cout << "2 - Hilfe\n";
		cout << "3 - Anzeige von Zutaten & Rezepten\n";
		cout << "4 - Berechnung der Produktionskosten (Rohstoffe)\n";
		cout << "5 - Berechnung des Verkaufspreises\n";
		cout << "\n0 - Exit\n";
		cout << "\nBitte Nummer eingeben:\n> ";

		getline(cin, choice);


		if (choice == "0") {
			return 0;
		}

		else if (choice == "1") {
			berechnung_rohstoff_pro_tafel(praline, zutaten);
			berechnung_preis(praline, zutaten);
		}

		else if (choice == "2") {
			help();
		}

		else if (choice == "3") {
			print_zutaten(zutaten);
			print_pralinen(praline, zutaten);
		}

		else if (choice == "4") {
			berechnung_rohstoff_pro_tafel(praline, zutaten);
		}

		else if (choice == "5") {
			berechnung_preis(praline, zutaten);
		}

		else {
			cout << "Falsche Eingabe.\n";
		}
	}	

	return 0;
}

