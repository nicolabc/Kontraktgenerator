#include <iostream>
#include <fstream>
#include <string>
#include <clocale>
#include <locale>
#include <codecvt>
#include <windows.h>
#include <stdlib.h>
#include <tchar.h>
using namespace std;


//Dette er en latex kode generator. Den lager latex koden ved å lime alt inn i et .txt dokument. Teksten fra dette nye dokumentet må limes inn i en latex kompilator
//for å få den ferdige PDF'en (f.eks sharelatex.com (anbefalt) eller TeXworks). Latex koden er basert på "Kontrakt-ND18 ferdig.tex".
//Foran skråtegn i original latexfil må et skråtegn settes foran (her i koden) når det skrives til txt fil. Ny linje må ha \n som vanlig.
//
//OBS: For at ÆØÅ skal kunne skrives fra konsoll må du på Visual Studio velge File-> Advanced Save Options -> Unicode (UTF8 with signature)
//Vet cout skrives æ = \x91, ø = \x9b, å = \x86, Æ = \x92, Ø = \x9d,	Å = \x8f
//Noe uklart? Kontakt Nicolas Blystad Carbone, nicolabc@stud.ntnu.no
//Våren 2017

int main() {
	//setlocale(LC_ALL, "nb-NO"); //For æøå i console etc
	ofstream myfile;
	locale utf8_locale(locale(), new codecvt_utf8<wchar_t>);
	myfile.imbue(utf8_locale);
	

	cout << "Kopier teksten som genereres i \".txt\" filen \n og lim den inn i en latex generator (f.eks sharelatex). \x92\x9d\x8f virker ikke enda, \n dobbeltsjekk alle navn/adresser i latexfilen. \n" << endl;

	
	myfile.open("kontrakt.txt"); //Lage txt fil
	if(!myfile){
		cout << "Opening file failed" << endl;
	}

	string bedrift; //Bedriftens navn
	cout << "Bedriftens navn: " << endl;
	getline(cin, bedrift); //For bedriftens navn i txt filen, må bruke getline for å få med mellomrom
	
						
	std::string representant;
	cout << "Bedriftens representant (til signatur): " << endl;
	getline(cin, representant);

	std::string adresse;
	cout << "Bedriftens adresse [eks Ullev\x86lsveien 31, Oslo]: " << endl;
	getline(cin, adresse);



	int pakke = 0; // Gull = 1 | Sølv = 2 | Bronse = 3, ( 0 for while-løkke)
	std::string pakkeNavn; //For å sette inn pakkenavnet i Latex-malen
	int pris; //For totalpris 
	char flatskjerm = ' '; //Om bedrift skal ha flatskjerm
	char bedriftpresentasjon = ' '; //Om bedrift skal ha bedpres

	while (pakke != 1 && pakke != 2 && pakke != 3) { //Hvis ingen av pakkene er valgt
		cout << "Hvilken pakke? Gull = 1 | S\x9blv = 2 | Bronse = 3" << endl; //Velge en pakke
		cin >> pakke;

		
		while ((flatskjerm != 'Y' && flatskjerm != 'N') && (pakke == 2 || pakke == 3)) { //Hvis Y/N og (sølv eller bronse)
			cout << "Flatskjerm m/ stativ? [Y/N]" << endl;
			//Ønsker bedriften flatskjerm med stativ?
			cin >> flatskjerm;
		}
		
		
		while ((bedriftpresentasjon != 'Y' && bedriftpresentasjon != 'N')&&(pakke == 1 || pakke == 2)) { //Hvis Y/N og (gull eller sølv)
			cout << "\x9dnsker bedrift bedrifspresentasjon? [Y/N]" << endl;
			cin >> bedriftpresentasjon;
		}
		//bool tilpasset; //For å vite om noen tillegg er lagt til. Brukes i latex-malen.
		
		if (pakke == 1) { //Gull
			pris = 30000; //30 000 NOK
			pakkeNavn = "Gullpakken";

			//Flatskjerm er inkludert

			if (bedriftpresentasjon == 'Y') {
				pris += 7500; //Tillegg for bedpres
				pakkeNavn = "Gullpakken (tilpasset)";
			}

		}
		else if (pakke == 2) { //Sølv
			pris = 22000; //22 000 NOK
			pakkeNavn = "Sølvpakken";
			if (flatskjerm == 'Y') {
				pris += 2000; //Legger til pris på flatskjerm 2000 NOK for sølvpakke
				pakkeNavn = "Sølvpakken (tilpasset)";
			}

			if (bedriftpresentasjon == 'Y') {
				pris += 15000; //Tillegg for bedpres
				pakkeNavn = "Sølvpakken (tilpasset)";
			}
		}
		else if (pakke == 3) { //Bronse
			pris = 16000; //16 000 NOK
			pakkeNavn = "Bronsepakken";
			if (flatskjerm == 'Y') {
				pris += 3000; //Legger til pris på flatskjerm 3000 NOK for bronsepakke
				pakkeNavn = "Bronsepakken (tilpasset)";
			}
		}
		else {
			cout << "Ugyldig pakke" << endl;
		}
	}

	
	std::string prisString = std::to_string(pris); //Pris må konverteres fra int til string for å brukes i malen
	
	//Selve latex-txt filen lages her
	myfile << "\\documentclass[a4paper, 11pt, norsk]{article} \n"
		"\\usepackage{microtype} \n"
		"\\usepackage{graphicx} \n"
		"\\usepackage[T1]{fontenc} \n"
		"\\usepackage{babel, geometry, lmodern} \n"
		"\\usepackage[utf8]{inputenc} \n"
		"\\usepackage{color} \n"
		"\\usepackage{amsmath} \n"
		"\\usepackage{secdot} \n"
		"\n"
		"\\makeatletter \n"
		"\\renewcommand{\\@maketitle}{ \n"
		"\\newpage \n"
		"\\null \n"
		"\\vskip 2em% \n"
		"\\begin{center}% \n"
		"\{\\LARGE \\@title \\par}% \n"
		"\\end{center}% \n"
		"\\par} \\makeatother \n"
		"\ \n"
		"\\graphicspath{ { html / } } \n"
		"\\title{ \\underline{ Kontrakt - Nettverksdagen 2018 } } \n"
		"\\sloppy \n"
		"\\setlength{ \\parindent }{0pt} \n"
		"\ \n"
		"\\begin{document} \n"
		"\\maketitle \n"
		"\ \n"
		"Denne kontrakten inngås mellom\\\\ \\\\ \n"
		"\\textbf{" + bedrift + " } \\\\ \n" 
		"\\textbf{" + adresse + "}  \\\\ \\\\ \n"
		"\\textbf{ Nettverksdagen 2018 } \\\\ \n"
		"\\textbf{ NTNU } \n"
		"\ \n"
		"\\section{ Kontraktens formål } \n"
		"Kontrakten skal avklare representantene fra Nettverksdagen 2018 og bedriften sine forpliktelser og ansvar i samarbeid om utførelse av bedriftsdagen Netttverksdagen 2018. "
		"Nettverksdagen arrangeres torsdag 15. februar 2018 fra kl.10.00 - 15.00 i Glassgården. Med denne kontrakten enes " + bedrift + " og Nettverksdagen 2018 om følgende: \n"
		"\ \n"
		"\\section{ Nettverksdagens forpliktelser }"
		"" + bedrift + " bekrefter med dette å ha valgt " + pakkeNavn + ",  " + prisString + ",- NOK ekskl. mva., til Nettverksdagen 2018.\\\\ \n"
		"\n"
		"I denne pakken inngår: \n"
		"\\begin{itemize} \n";

		//Skal "\\item Strøm, bord, 2 stoler og tilgang på internett. \n" tas med??
		//Legg merke til semikolonet, trengs for at if setning skal kjøres

	//Legger til pakker
	if (pakke == 1) { //Hvis gullpakke er valgt, legger til gullpakkens innhold
		if (bedriftpresentasjon == 'Y') {
			myfile << "\\item Bedriftspresentasjon\n";
		}
		myfile << "\\item Standplass i Glassgården \n" 
			"\\item Flatskjerm m/ stativ\n"
			"\\item Tilgang på intervjurom\n"
			"\\item Bedriftsspotlight\n"
			"\\item Logo på program \n" 
			"\\item Logo på flyers\n"
			"\\item Logo i Kompendium\n"
			"\\item Logo på plakater\n"
			"\\item Logo på banner\n";
			
	}
	else if (pakke == 2) { // Hvis sølvpakke er valgt, legger til sølvpakkens innhold
		if (bedriftpresentasjon == 'Y') {
			myfile << "\\item Bedriftspresentasjon\n";
		}

		myfile <<
			"\\item Standplass i Glassgården \n";

		if (flatskjerm == 'Y') {
			myfile << "\\item Flatskjerm m/ stativ\n";
		}
		
		myfile <<
			"\\item Tilgang på intervjurom\n"
			"\\item Bedriftsspotlight\n"
			"\\item Logo på program \n" 
			"\\item Logo på flyers\n";
	}
	else { //Bronsepakke
		myfile << "\\item Standplass i Glassgården \n";
		if (flatskjerm == 'Y') {
			myfile << "\\item Flatskjerm m/ stativ\n";
		}
		myfile << "\\item Logo på program \n";
	};
	myfile << "\\end{itemize}\n"
		"\n"
		"Nettverksdagen forplikter seg til de avtaler som er gjort i henhold til valg av pakke og tillegg. Nettverksdagen pliktes også å stille med lunsj, kaffe og forfriskninger til bedriften sine representanter gjennom dagen.\n"
		"\\\\ \\\\\n"
		"\\section{ Bedriftens forpliktelser }\\label{ bedfor }\n"
		"" + bedrift + " forplikter seg til å møte opp til avtalt dag og tid. Ved manglende oppmøte vil fullt honorar bli krevet. Hvis bedriften trekker seg mindre enn én måned før Nettverksdagen 2018 regnes dette som manglende oppmøte, og  fullt honorar vil bli krevet."
		" Hvis bedriften trekker seg mer enn én måned før Nettverksdagen 2018 vil halvt honorar bli krevet. Fakturering gjøres etter Nettverksdagen 2018 med betalingsfrist 21 dager etter at bedriften har mottatt faktura.\n"
		"\n"
		"\n"
		"\\section{ Varighet }\n"
		"Kontrakten varer fra signert dato frem tom. 15. februar 2018. Ved avbrytelse av kontrakten, se seksjon \\ref{ bedfor }.\n"
		"\n"
		"\\section{ Underskrifter }\n"
		"Undertegnede samtykker med dette om å overholde denne avtalen på vegne av hans/hennes organisasjon eller bedrift. \\\\\\\\\n"
		"\n"
		"På vegne av " + bedrift + "\\\\\\\\\\\\\n"
		"\\vspace{ .2in }\n"
		"\\makebox[2.5in]{ \\hrulefill } \\hspace{ 1.0in }\\makebox[1.5in]{ Dato:\\hrulefill } \\\\\n"
		"" + representant + " \\\\" + bedrift + " \\makebox[2.5in][r]{} \\\\\\\\\\\\\n"
		"\n"
		"På vegne av Nettverksdagen 2018\\\\\\\\\\\\\n"
		"\\vspace{ .2in }\n"
		"\\makebox[2.5in]{ \\hrulefill } \\hspace{ 1.0in }\\makebox[1.5in]{ Dato:\\hrulefill } \\\\\n"
		"Filip Gornitzka Abelson\\\\Bedriftskontaktleder, Nettverksdagen 2018 \\makebox[2.5in][r]{} \\\\\n"
		"\n"
		"\n"
		"\n"
		"\\end{document}";
	myfile.close();


	cout << "Latex kode generert, se txt fil" << endl;
	return 0;
}