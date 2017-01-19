#include "schokoprod_structs.cpp"

/********************************************************
*************** FUNKTIONEN: DEKLARATION *****************
*********************************************************/

/*void 	print_zutaten(zutat_t *array);
void 	print_pralinen(schokolade_t *array, zutat_t *array2);
void 	berechnung_rohstoff(schokolade_t *array, zutat_t *array2);
void	berechnung_rohstoff_pro_tafel(schokolade_t *array, zutat_t *array2);
void 	berechnung_preis(schokolade_t *array, zutat_t *array2);
int 	get_uint();

void 	press_enter();
void 	help();
*/
/********************************************************
*********** DEFINITION DER HILFSFUNKTIONEN **************
*********************************************************/

// Fordert Nutzer auf Enter zu drücken
void press_enter() {
	cout << "\nEnter drücken um fortzufahren.";
	cin.ignore();
	
	return;
}

// Hilfe & Credits
void help() {
	cout << "\n-- Hilfe\n";
	cout << "Das Programm gibt Auskunft über Kosten und Preise einer Schokoladenproduktion.\n";
	cout << "Notwendig für die Berechnung sind zwei Dateien: zutaten.txt (beeinhaltet Zutaten\n";
	cout << "und deren Preise pro 100g und schoki.txt (beeinhaltet Name der Praline, Gewicht,\n";
	cout << "Anzahl an Zutaten sowie eine Auflistung der einzelnen Zutaten und deren Prozentanteil\n";
	cout << "am Gesamtrezept). Bei Anpassungen in den .txt Datein bitte das Format beibehalten\n";
	cout << "und die entsprechenden Konstanten im Quelltext verändern.\n";

	press_enter();
	return;
}

// Rückgabe eines positiven Integerwertes
int get_uint() {
	while (true) {
		string input;
		int temp;

		getline(cin, input);
		stringstream inputStream(input);
		if (inputStream >> temp) {
			if (temp >= 0) {
				return temp;
			}
		}
		cout << "Ungültiger Wert, bitte erneut versuchen: ";
	}	
}


// Auflisten aller Zutaten und ihrem Preisen pro 100g
void print_zutaten(zutat_t *array) {
	cout << "\n-- Zutaten\n";
	cout << "Folgende " << ANZAHL_ZUTATEN << " Zutaten stehen zur Verfügung:\n";
	
	for (int i = 0; i < ANZAHL_ZUTATEN; i++) {
		cout << "\t- " << array[i].name << " (" << array[i].preis_pro_100gramm << "€/100g)\n";
	}
	cout << endl;

	press_enter();
	return;
}

// Auflisten aller Schokoladenrezepte
void print_pralinen(schokolade_t	*praline, zutat_t *zutaten) {
	cout << "\n-- Rezepte\n";
	cout << "Folgende Pralinen können produziert werden:\n";
	
	for (int i = 0; i < ANZAHL_PRALINEN; i++) {
		cout << (i + 1) << ": " << praline[i].name << " (" << praline[i].gewicht << "g)" << endl;
		
		for (int j = 0; j < ANZAHL_ZUTATEN_PRO_PRALINE; j++) {
			if (praline[i].zutat[j].id != -1) {
				cout << "\t- "<< praline[i].zutat[j].menge_in_prozent << "% " << zutaten[praline[i].zutat[j].id].name << endl;
				}
		}

		cout << endl;
	}

	press_enter();
	return;
}

/********************************************************
************ BERECHNUNG DER ROHSTOFFKOSTEN **************
*********************************************************/

// Berechnung der allgemeinen Rohstoffkosten & befüllen der structs. Diese Funktion muss in main aufgerufen werden!
void berechnung_rohstoff(schokolade_t *praline, zutat_t *zutaten) {

	// Hier werden die individuellen Rohstoffkosten jeder Zutat, sowie die Rohstoffkosten der gesamten Praline ermittelt
	for (int i = 0; i < ANZAHL_PRALINEN; i++) {
		double sum = 0;	

		// Wenn nicht alle Zutaten vorkommen, setze restliche id's auf 0
		for (int j = 0; j < ANZAHL_ZUTATEN_PRO_PRALINE; j++) {
			if (praline[i].zutat[j].id == -1) {
				praline[i].zutat[j].rohstoffkosten = 0;
			}
			else {
				// Bsp: 34% Anteil Kakao je 0.82€/100g; 150g Schokolade = 34 * (150 * 0.82 / 100) / 100;
				praline[i].zutat[j].rohstoffkosten = (praline[i].zutat[j].menge_in_prozent * ((praline[i].gewicht * zutaten[praline[i].zutat[j].id].preis_pro_100gramm) / 100) /100);
			}
			sum += praline[i].zutat[j].rohstoffkosten;
		}

		praline[i].kosten.rohstoff_einheit = sum;

		// Dieses Element ist abhänging von der zu produzierenden Anzahl und wird später nach der Nutzereingabe definiert
		praline[i].kosten.rohstoff_gesamt = 0;

	}	
}

// Berechnung der Rohstoffkosten für x-Tafeln
void berechnung_rohstoff_pro_tafel(schokolade_t *praline, zutat_t *zutaten) {

	// Speichert die Anzahl der zu produzierenden Tafeln für jede Praline
	int n_schoko[ANZAHL_PRALINEN];

	cout << "\n-- Berechnung der Rohstoffkosten\n";

	// Gibt die Zutaten und deren Rohstoffkosten für eine Tafel Schokolade aus
	cout << "Folgende Pralinen können produziert werden:\n";
	for (int i = 0; i < ANZAHL_PRALINEN; i++) {
		cout << "\n" << (i + 1) << ": " << praline[i].name << " (" << praline[i].gewicht << "g)" << endl;

		for (int j = 0; j < ANZAHL_ZUTATEN_PRO_PRALINE; j++) {
			if (praline[i].zutat[j].id != -1) {
				cout << "\t- "<< praline[i].zutat[j].menge_in_prozent << "% " << zutaten[praline[i].zutat[j].id].name;
				cout << " (" << zutaten[praline[i].zutat[j].id].preis_pro_100gramm << "€/100g) \t-> " << praline[i].zutat[j].rohstoffkosten << "€\n";
			}	
		}

		cout << "\tRohstoffkosten pro Einheit:\t--> " << praline[i].kosten.rohstoff_einheit << "€\n";
	}

	cout << "\nWie viele Einheiten sollen produziert werden?\n> ";
	for (int i = 0; i < ANZAHL_PRALINEN; i++) {
		cout << praline[i].name << ": ";
		n_schoko[i] = get_uint();
	}	

	// Gibt die Gesamtkosten der einzelnen Rohstoffe und die Gesamtrohstoffkosten der Schokolade aus
	for (int i = 0; i < ANZAHL_PRALINEN; i++) {
		double sum = 0;
		cout << "\n" << n_schoko[i] << "x " << praline[i].name << " (insg. " << (praline[i].gewicht * n_schoko[i]) << "g)" << endl;

		for (int j = 0; j < ANZAHL_ZUTATEN_PRO_PRALINE; j++) {
			if (praline[i].zutat[j].id != -1) {
				cout << "\t- "<< praline[i].zutat[j].menge_in_prozent << "% " << zutaten[praline[i].zutat[j].id].name;
				cout << " (" << zutaten[praline[i].zutat[j].id].preis_pro_100gramm << "€/100g) \t-> " << (praline[i].zutat[j].rohstoffkosten * n_schoko[i]) << "€\n";
				sum += praline[i].zutat[j].rohstoffkosten * n_schoko[i];
			}	
		}

		praline[i].kosten.rohstoff_gesamt = sum;
		cout << "\tGesamte Rohstoffkosten:\t\t--> " << (praline[i].kosten.rohstoff_gesamt) << "€\n";
	}

	press_enter();
	return;
}

/********************************************************
********************* PREISMATRIX ***********************
*********************************************************/

void berechnung_preis(schokolade_t *praline, zutat_t *zutaten) {

	// Variablen für Preisberechnung
	string 	choice, choice_format, choice_produkt;
	int 		prozent_gewinn, start_prozent_gewinn, end_prozent_gewinn, schritt_prozent_gewinn; 
	int 		produkt = 0;
	int 		anzahl, start_anzahl, end_anzahl, schritt_anzahl;
	double	gewinn, vpreis_gesamt, vpreis_einheit, vpreis_format;	

	
	// Abfrage des Produktes
	cout << "\nFür welches Produkt soll der Verkaufspreis berechnet werden?\n";
	for (int i = 0; i < ANZAHL_PRALINEN; i++) {
		cout << (i + 1) << ": " << praline[i].name << endl;
	}
	cout<< "\n0 - Zurück zum Hauptmenü\n";

	// Interne Auswahl des Produkts
	while(true) {
		cout << "\nBitte Nummer eingeben:\n> ";
		getline(cin, choice_produkt);
		
		// Umwandlung vom string input in integer
		stringstream strToInt(choice_produkt);
		if (strToInt >> produkt) {
			// Lässt nur Zahlen zwischen 0 und max. Anzahl der Pralinen zu
			if (produkt > 0 && produkt <= ANZAHL_PRALINEN) {
				produkt -= 1;
				break;
			}

			else if (produkt == 0) {
				return;
			} 
		}

		cout << "Falsche Eingabe.\n";
	}

	// Abfrage der Werte
	cout << "\n-- Berechnung des Verkaufspreises\n";
	cout << "Bitte auswählen:\n";
	cout << "1 - Standardwerte\n";
	cout << "2 - Benutzerdefinierte Werte\n";
	cout << "\n0 - Zurück zum Hauptmenü\n> ";

	getline(cin, choice);

	// Standardwerte nach Aufgabenstellung
	if (choice == "1") {
		
		praline[produkt].kosten.personal = 42800;
		praline[produkt].kosten.betrieb = 19200;
		praline[produkt].kosten.sonstige = 13500;
		praline[produkt].kosten.rohstoff_gesamt = 0;

		start_anzahl = 10000;
		end_anzahl = 250000;
		schritt_anzahl = 10000;

		start_prozent_gewinn = 1;
		end_prozent_gewinn = 10;
		schritt_prozent_gewinn = 1;

		cout << "\n-- Standardwerte\n";
		cout << "\t- Personalkosten:\t42 800€\n";
		cout << "\t- Betriebskosten:\t19 200€\n";
		cout << "\t- Sonstige Kosten:\t13 500€\n";
		cout << "\t- Stückzahl:\t10 000 - 250 000 (+10 000/Zeile)\n";
		cout << "\t- Gewinnspanne:\t1% - 10% (+1%/Spalte)\n";

	}

	// Benutzerdefinierte Werte
	else if (choice == "2") {
		cout << "\n-- Benutzerdefinierte Werte\n";
		cout << "- Produkt: " << praline[produkt].name << endl;
		praline[produkt].kosten.rohstoff_gesamt = 0;

		cout << "- Personalkosten: ";
		praline[produkt].kosten.personal = get_uint();

		cout << "- Betriebskosten: ";
		praline[produkt].kosten.betrieb = get_uint();

		cout << "- Sonstige Kosten: ";
		praline[produkt].kosten.sonstige = get_uint();

		cout << "- Zu produzierende Stückzahl (Start): ";
		start_anzahl = get_uint();

		while (true) {
			cout << "- Zu produzierende Stückzahl (Ende): ";
			end_anzahl = get_uint();

			if (end_anzahl >= start_anzahl) {
				break;
			}
			cout << "Ungültiger Wert.";
		}	
		

		while (true) {
			cout << "- Wachstum der Stückzahl pro Zeile: ";
			schritt_anzahl = get_uint();

			if (schritt_anzahl <= end_anzahl) {
				break;
			}
			cout << "Ungültiger Wert.";			
		}

		cout << "- Gewinnspanne in % (Start): ";
		start_prozent_gewinn = get_uint();

		while (true) {
			cout << "- Gewinnspanne in % (Ende): ";
			end_prozent_gewinn = get_uint();

			if (end_prozent_gewinn >= start_prozent_gewinn) {
				break;
			}
			cout << "Ungültiger Wert.";			
		}

		while (true) {
			cout << "- Wachstum der Gewinnspanne pro Spalte: ";

			schritt_prozent_gewinn = get_uint();
			if (schritt_prozent_gewinn <= end_prozent_gewinn) {
				break;
			}
			cout << "Ungültiger Wert.";
		}

		cout << "\nFolgende Werte wurden eingegeben:\n";
		cout << "\t- Personalkosten:\t"	<< praline[produkt].kosten.personal << "€" << endl;
		cout << "\t- Betriebskosten:\t"	<< praline[produkt].kosten.betrieb << "€" << endl;
		cout << "\t- Sonstige Kosten:\t"	<< praline[produkt].kosten.sonstige << "€" << endl;
		cout << "\t- Stückzahl:\t" << start_anzahl << " - " << end_anzahl << " (+" << schritt_anzahl << "/Zeile)\n";
		cout << "\t- Gewinnspanne in %:\t" << start_prozent_gewinn << "% - " << end_prozent_gewinn << "% (+" << schritt_prozent_gewinn <<  "%/Spalte)\n";

		press_enter();

	}

	// Zurück zum Hauptmenü
	else if (choice == "0") {
		return;
	}

	else {
		cout << "Falsche Eingabe.";
		press_enter();
		return;
	}

	// Ausgabe des Preises
	cout << "\nAusgabeformat des Verkaufspreises:\n";
	cout << "1 - Verkaufspreis pro Tafel\n";
	cout << "2 - Verkaufspreis gesamt\n";
	cout << "\n0 - Zurück zum Hauptmenü\n";
	cout << "\nBitte Nummer eingeben:\n> ";

	getline(cin, choice_format);

	// Ausgabe pro Tafel
	if (choice_format == "1") {
		vpreis_format = 1;
	}

	// Ausgabe gesamt
	else if (choice_format == "2") {
		vpreis_format = 2;
	}

	// Zurück zum Hauptmenü
	else if (choice_format == "0") {
		return;
	}

	else {
		cout << "Falsche Eingabe.";
		press_enter();
		return;
	}

	// Legende & Beginn der Matrix
	cout << "\n-- Legende\nZeilen:\t\tStückzahl n an zu produzierenden Pralinen\n";
	cout << "Spalten:\tGewinn p in %\n";
	cout << "Felder:\t\tVerkaufspreis pro Tafel in €\n";

	// Kopf der Matrix
	cout << "\nn\t";
	for (int p = start_prozent_gewinn; p <= end_prozent_gewinn; p = p + schritt_prozent_gewinn) {
		cout << "p = " << p << "%\t";
	}

	cout << endl;

	// Y-Achse: Stückzahl an Tafeln steigt um 10 000 von 10 000 auf 250 000
	for (anzahl = start_anzahl; anzahl <= end_anzahl; anzahl = anzahl + schritt_anzahl) {
		cout << anzahl << "\t";
		praline[produkt].kosten.rohstoff_gesamt = anzahl * praline[produkt].kosten.rohstoff_einheit;

		// X-Achse: Gewinn steigt um 1% von 1% bis 10%
		for (prozent_gewinn = start_prozent_gewinn; prozent_gewinn <= end_prozent_gewinn; prozent_gewinn = prozent_gewinn + schritt_prozent_gewinn) {
			praline[produkt].kosten.gesamt = praline[produkt].kosten.personal + praline[produkt].kosten.betrieb + praline[produkt].kosten.sonstige + praline[produkt].kosten.rohstoff_gesamt;
			gewinn = (prozent_gewinn * praline[produkt].kosten.gesamt) / 100;
			vpreis_gesamt = praline[produkt].kosten.gesamt + gewinn;
			vpreis_einheit = vpreis_gesamt / anzahl;

			if (vpreis_format == 1) {
				cout << setprecision(5) <<vpreis_einheit << "\t";
			}
			else {
				cout << vpreis_gesamt << "\t";
			}
		}
		cout << endl;
	}

	press_enter();
	return;
}