Betting Management System – POO Tema 3

Proiect realizat în C++ pentru gestionarea și simularea pariurilor sportive.

Funcționalități
    -gestionarea mai multor tipuri de pariuri:
        #pariu simplu
        #pariu multiplu
        #pariu sistem
    -calcularea câștigurilor
    -citirea și afișarea datelor
    -tratarea excepțiilor
    -utilizarea moștenirii și polimorfismului
    -clonarea obiectelor folosind Prototype Pattern
    -crearea obiectelor folosind Factory Pattern
    -utilizarea șabloanelor (templates)
Concepte OOP utilizate
    -clase și obiecte
    -moștenire
    -polimorfism
    -funcții virtuale
    -suprascriere de operatori
    -excepții
    -design patterns:
        #Prototype
        #Factory
    -template class
    -template function
Fișierele proiectului
    -poo tema 3.cpp – fișier principal
    -pariuri.h – declarațiile claselor
    -pariuri.cpp – implementarea claselor
    -rezultate.h – gestionarea rezultatelor
    -exceptii.h – excepții personalizate
    -sabloane.h – templates și Factory Pattern
    -date.in – date de intrare


REVIEW PROIECTUL 3 POO

Am realizat acest proiect deoarece mi-am dorit să construiesc o aplicație mai complexă în C++, care să îmbine conceptele de programare orientată pe obiect cu o temă care mi se pare 
interesantă și actuală, și anume pariurile sportive. Nu am vrut să fac un proiect foarte simplu sau doar ceva făcut ca să bifez niște cerințe, ci am încercat să creez un sistem cât mai bine organizat, 
care să demonstreze că înțeleg conceptele importante din C++ și că pot să le aplic într-un program real.

Proiectul meu este un sistem de gestionare a pariurilor sportive. Ideea principală a fost să permit existența mai multor tipuri de pariuri și să gestionez diferit fiecare tip, folosind moștenirea 
și polimorfismul. Mi s-a părut o alegere bună deoarece domeniul pariurilor sportive permite foarte multe idei și multe concepte OOP pot fi aplicate natural fără să pară forțate.

La început am gândit structura proiectului și am încercat să îl organizez cât mai bine. Nu am vrut să pun tot codul într-un singur fișier deoarece ar fi devenit foarte greu de urmărit și modificat. 
Din acest motiv am separat proiectul în mai multe fișiere precum pariuri.h, pariuri.cpp, exceptii.h, rezultate.h, sabloane.h și fișierul principal poo tema 3.cpp. Consider că această organizare 
face proiectul mult mai curat și mai ușor de întreținut.

Una dintre cele mai importante părți ale proiectului este utilizarea programării orientate pe obiect. Am creat o clasă de bază pentru pariuri și mai multe clase derivate, fiecare reprezentând 
un tip diferit de pariu. De exemplu, există pariu simplu, pariu multiplu și pariul de tip sistem. Fiecare dintre acestea are propriile caracteristici și propriul mod de calcul al câștigului. Mi s-a 
părut important să folosesc moștenirea deoarece toate tipurile de pariuri au anumite elemente comune, dar în același timp au și comportamente diferite.

Prin folosirea funcțiilor virtuale și a polimorfismului, programul poate trata toate tipurile de pariuri într-un mod unitar. Acest lucru mi se pare unul dintre cele mai mari avantaje ale OOP-ului 
deoarece codul devine mai flexibil și mai ușor de extins. Dacă în viitor aș vrea să adaug un nou tip de pariu, aș putea face asta fără să modific foarte mult restul proiectului.

Un alt aspect important este faptul că am folosit excepții pentru tratarea erorilor. Nu am vrut ca programul să accepte date invalide sau să se oprească brusc atunci când utilizatorul 
introduce ceva greșit. Din acest motiv am creat excepții personalizate și am tratat diferite situații care pot apărea în timpul rulării programului. Consider că asta face proiectul mai 
robust și mai apropiat de o aplicație reală.

În proiect am folosit și două design patterns. Primul este Prototype Pattern. Acesta este implementat prin metoda clone(). Mi s-a părut potrivit deoarece permite copierea obiectelor fără să 
cunosc exact tipul lor concret. Practic, fiecare clasă derivată își poate crea o copie proprie. Acest pattern demonstrează că înțeleg concepte mai avansate de OOP și că pot folosi idei 
moderne de proiectare software.

Al doilea design pattern utilizat este Factory Pattern. Am creat o clasă specială care are rolul de a crea diferite tipuri de pariuri în funcție de parametrii primiți. Mi-a plăcut ideea acestui 
pattern deoarece separă logica de creare a obiectelor de restul aplicației. Astfel, codul devine mai organizat și mai ușor de modificat. În plus, este un pattern foarte folosit în aplicațiile reale 
și cred că este important să știu cum funcționează.

Pe lângă design patterns, am folosit și template-uri. Am realizat o clasă template pentru statistici legate de pariuri. Aceasta poate fi utilizată pentru diferite tipuri de date precum int 
sau double. De exemplu, poate calcula statistici pentru număr de goluri, cote, mize sau alte valori numerice. Mi s-a părut o soluție bună deoarece evită duplicarea codului și demonstrează 
flexibilitatea limbajului C++.

De asemenea, am implementat și o funcție template care compară două valori și returnează valoarea mai mare. Chiar dacă este ceva simplu, arată că înțeleg conceptul de generic programming și 
că pot crea funcții reutilizabile pentru mai multe tipuri de date.

Consider că unul dintre punctele forte ale proiectului este organizarea codului. Am încercat să scriu cât mai clar și să separ responsabilitățile între clase. De exemplu, logica principală a 
pariurilor este separată de tratarea excepțiilor și de partea de template-uri. Acest lucru face proiectul mai ușor de înțeles și mai ușor de modificat pe viitor.

Pe parcursul realizării proiectului am întâlnit și dificultăți. Unele dintre cele mai complicate părți au fost gestionarea corectă a moștenirii și a pointerilor către clasa de bază. La început 
am avut probleme legate de funcțiile virtuale și de copierea obiectelor, însă după mai multe teste și modificări am reușit să rezolv aceste probleme. Consider că aceste dificultăți m-au ajutat să 
înțeleg mai bine limbajul C++ și modul în care funcționează memoria și polimorfismul.

Un alt lucru important pe care l-am învățat a fost organizarea unui proiect mai mare. Înainte obișnuiam să scriu programe mai mici, dar acest proiect m-a făcut să gândesc mai atent structura 
codului și relațiile dintre clase. Cred că experiența aceasta m-a ajutat mult și mă va ajuta și pe viitor în alte proiecte.

Din punctul meu de vedere, proiectul este unul reușit deoarece îndeplinește toate cerințele și în același timp are o logică clară și realistă. Nu este doar un exemplu teoretic, ci un program 
care poate fi extins și îmbunătățit foarte ușor. De exemplu, în viitor aș putea adăuga o interfață grafică, salvarea datelor în fișiere sau chiar conectarea la baze de date.

Un alt motiv pentru care consider că proiectul este bun este faptul că folosește multe concepte importante din C++ într-un mod natural. Nu am introdus elemente inutile doar pentru a bifa cerințe. 
Fiecare componentă are un rol și contribuie la funcționarea aplicației. Cred că asta face diferența dintre un proiect făcut doar pentru notă și unul realizat cu atenție.

În concluzie, sunt mulțumit de acest proiect și consider că reprezintă foarte bine nivelul meu actual de cunoștințe în C++. Prin acest proiect am reușit să aplic noțiuni importante precum moștenirea, 
polimorfismul, excepțiile, design patterns și template-urile într-o aplicație organizată și funcțională. De asemenea, proiectul m-a ajutat să îmi dezvolt gândirea logică și modul de organizare a codului. 
Chiar dacă mai există multe lucruri pe care le pot îmbunătăți, cred că rezultatul final este unul foarte bun și demonstrează că pot realiza aplicații complexe folosind programarea orientată pe obiect.
