# Task-handling-Robot

Algoritmul utilizat:

	- Pentru inceput mi-am creeat niste "unelte" 
	de care sa ma folosesc in creearea programului:
  
		->am implementat un model de coada (sub forma de lista dublu 
		inlantuita) si unul de stiva (sub forma de vector resizable);
    
		->am creat o clasa "Comanda" in cadrul careia am 
		creat niste campuri ce definesc structura unei comenzi;
    
		->o structura "Robot" care contine o coada de comenzi (in care
		vor fi introduse comenzi de tip ADD_..._BOX) si numarul de cutii
		aflat in posesia fiecarui robot;
    
		->am creat o harta, un vector de roboti doua stive (utilizarea lor
		este descrisa in comentarii) si alte variabile/obiecte ajutatoare.
    
	- Citirea comenzilor se realizeaza succesiv intr-un while, fiecare comanda 
  fiind prelucrata si daca e cazul afisata in aceeasi secventa a buclei.
  
	- Programul functioneaza, pe scurt, in felul urmator:
  
		->cand sunt citite, comenzile de tipul ADD_..._BOX sunt introduse in
		coada in functie de prioritate si in stiva "mixt" pentru a putea fi
		manipulata in caz ca se da UNDO la ea;
    
		->in cazul comenzilor EXECUTE, acestea trebuie introduse, dupa ce actioneaza 
    asupra primei comenzi din coada, atat in stiva "mixt"
		pentru UNDO, cat si in stiva "istoric" pentru LAST_EXECUTED_COMMAND;
    
		->LAST_EXECUTED_COMMAND afiseaza ultima comanda din stiva "istoric";
    
		->comanda UNDO verifica daca comenzile din stiva "mixt" sunt executate
		(fapt indicat de campul "execution" al comenzii) si in functie de tip,
		fie introduce comanda la sfarsitul cozii, fie in plus anuleaza
		modificarile suferite de harta si de robot(daca este executata);
    
		->in ambele cazuri comanda este eliminata din stiva mixt;
    
		->pentru implementarea comenzii HOW_MUCH_TIME, in bucla while de 
		citire, parcurg de fiecare data vectorul de roboti si fiecarui
		robot ii incrementez campul clocky (care indica timpul cat a 
		stat in coada) al fiecarei comenzi din coada.
