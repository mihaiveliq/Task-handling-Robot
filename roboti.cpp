// Copyright 2018 Mihai Velicu
#include <iostream>
#include <fstream>
#include <string>
#include "./coada.h"
#include "./stiva.h"

// clasa pentru comenzi
class comanda {
 public:
	std::string name;
	int RobotId;
	int Priority;
	int NrBoxes;
	int x;
	int y;
	int deal;
	int clocky;
	bool execution;
	char type;
	comanda() {}
	~comanda() {}

	comanda& operator=(const comanda& other) {
		name = other.name;
		RobotId = other.RobotId;
		Priority = other.Priority;
		NrBoxes = other.NrBoxes;
		x = other.x;
		y = other.y;
		deal = other.deal;
		clocky = other.clocky;
		execution = other.execution;
		type = other.type;

		return *this;
	}
};

// structura pentru roboti
typedef struct {
	Coada <comanda> c;  // coada de comenzi
	int cutii;
}robot;

int main() {
	// creez si deschid fisierul de citire
	std::ifstream in("robots.in");
	// creez si deschid fisierul de afisare
	std::ofstream out("robots.out");

	int RobotId, x, y, NrBoxes, Priority;
	// citire numar de roboti si coordonate harta
	int N, LIN, COL;
	in >> N >> LIN >> COL;

	// citire numar de cutii de pe fiecare pozitie din harta
	int map[LIN][COL];
	for ( int i = 0; i < LIN; ++i ) {
		for ( int j = 0; j < COL; ++j ) {
			in  >> map[i][j];
		}
	}

	// creez un vector de roboti si initializez campul de cutii
	robot r[N];
	for ( int i = 0; i < N; ++i ) {
		r[i].cutii = 0;
	}

	// declar stiva "istoric" pentru a pastra istoricul comenzilor
	// ADD_..._BOX si EXECUTE
	// declar stiva "mixt" pentru a pastra istoricul comenzilor EXECUTE
	// declar comanda mission
	stiva<comanda> istoric, mixt;
	comanda mission;


	// citire, implementare si afisare comenzi
	std::string buffer;
	while ( in >> buffer ) {
		// initializez comanda mission dupa fiecare citire
			mission.RobotId = 0;
			mission.NrBoxes = 0;
			mission.Priority = 0;
			mission.x = 0;
			mission.y = 0;
			mission.deal = 0;
			mission.execution = false;
			mission.clocky = 0;
			mission.type = 'A';
			mission.name = "BOSS";

		/*
		//ADD_GET_BOX
		*/
		if ( buffer == "ADD_GET_BOX" ) {
			in >> RobotId >> x >> y >> NrBoxes >> Priority;

			// particularizez comanda
			mission.RobotId = RobotId;
			mission.NrBoxes = NrBoxes;
			mission.Priority = Priority;
			mission.x = x;
			mission.y = y;
			mission.type = 'G';

			// adaug comanda in coada in functie de prioritate
			if ( Priority == 1 ) {
				r[RobotId].c.addRear(mission);
			} else if ( Priority == 0 ) {
				r[RobotId].c.addFront(mission);
			}
			mixt.push(mission);

		/*
		//ADD_DROP_BOX
		*/

		} else if ( buffer == "ADD_DROP_BOX" ) {
			in >> RobotId >> x >> y >> NrBoxes >> Priority;

			// particularizez comanda
			mission.RobotId = RobotId;
			mission.NrBoxes = NrBoxes;
			mission.Priority = Priority;
			mission.x = x;
			mission.y = y;
			mission.type = 'D';

			// adaug comanda in coada in functie de prioritate
			if ( Priority == 1 ) {
				r[RobotId].c.addRear(mission);
			} else if ( Priority == 0 ) {
				r[RobotId].c.addFront(mission);
			}
			mixt.push(mission);

		/*
		//EXECUTE
		*/

		} else if ( buffer == "EXECUTE" ) {
			in >> RobotId;

			// verific daca coada e goala
			if ( r[RobotId].c.isEmpty() == 1 ) {
				out << "EXECUTE: No command to execute" << std::endl;
			}

			if ( r[RobotId].c.isEmpty() == 0 ) {
				// pun headul intr-o variabila
				comanda head = r[RobotId].c.removeFront();

				if ( head.type == 'G' ) {
					if ( head.NrBoxes > map[head.x][head.y] ) {
						r[RobotId].cutii += map[head.x][head.y];
						head.deal = map[head.x][head.y];
						head.NrBoxes = head.deal;
					} else {
						r[RobotId].cutii += head.NrBoxes;
						map[head.x][head.y] -= head.NrBoxes;
						head.deal = head.NrBoxes;
						head.NrBoxes = head.deal;
					}

				} else if ( head.type == 'D' ) {
					if ( head.NrBoxes > r[RobotId].cutii ) {
						map[head.x][head.y] += r[RobotId].cutii;
						head.deal = r[RobotId].cutii;
						r[RobotId].cutii = 0;
						head.NrBoxes = head.deal;
					} else {
						r[RobotId].cutii -= head.NrBoxes;
						map[head.x][head.y] += head.NrBoxes;
						head.deal = head.NrBoxes;
						head.NrBoxes = head.deal;
					}
				}
				head.execution = true;

				mixt.push(head);
				istoric.push(head);
			}

		/*
		//PRINT_COMMANDS
		*/

		} else if ( buffer == "PRINT_COMMANDS" ) {
			int RobotId;
			in >> RobotId;

			if ( r[RobotId].c.isEmpty() ) {
				out << "PRINT_COMMANDS: No command found" << std::endl;
			} else {
				Node<comanda> *temp = r[RobotId].c.getHead();

				out << "PRINT_COMMANDS: " << RobotId << ": ";

				while ( temp->next != nullptr ) {
					if ( temp->data.type == 'D' ) temp->data.name = "DROP";
					if ( temp->data.type == 'G' ) temp->data.name = "GET";
					out << temp->data.name << " " << temp->data.x << " "
						<< temp->data.y << " " << temp->data.NrBoxes << "; ";
						temp = temp->next;
				}
				if ( temp->data.type == 'D' ) temp->data.name = "DROP";
				if ( temp->data.type == 'G' ) temp->data.name = "GET";
				out << temp->data.name << " " << temp->data.x << " "
					<< temp->data.y << " " << temp->data.NrBoxes;
				out << std::endl;
			}

		/*
		//HOW_MANY_BOXES
		*/

		} else if ( buffer == "HOW_MANY_BOXES" ) {
			in >> RobotId;
			out << "HOW_MANY_BOXES: " << r[RobotId].cutii << std::endl;

		/*
		//LAST_EXECUTED_COMMAND
		*/

		} else if ( buffer == "LAST_EXECUTED_COMMAND" ) {
			if ( istoric.isEmpty() ) {
				out << "No command was executed" << std::endl;
			} else {
				comanda head = istoric.peek();
				if ( head.type == 'D' ) head.name = "DROP";
				if ( head.type == 'G' ) head.name = "GET";

				out << "LAST_EXECUTED_COMMAND: " << head.RobotId << ": "
					<< head.name << " "
					<< head.x << " " << head.y << " "
					<< head.deal << std::endl;
			}

		/*
		//UNDO
		*/

		} else if ( buffer == "UNDO" ) {
			if ( mixt.isEmpty() ) {
				out << "UNDO: " << "No History" << std::endl;
			} else {
				comanda tmp = mixt.peek();
				if ( tmp.execution == 0 ) {
					tmp.clocky = 0;
					if (tmp.Priority) {
						r[tmp.RobotId].c.removeRear();
					} else {
						r[tmp.RobotId].c.removeFront();
					}
					mixt.pop();
				} else if ( tmp.execution == 1 ) {
					if ( tmp.type == 'G' ) {
						map[tmp.x][tmp.y] += tmp.deal;
						r[tmp.RobotId].cutii -= tmp.deal;
					} else if ( tmp.type == 'D' ) {
						map[tmp.x][tmp.y] -= tmp.NrBoxes;
						r[tmp.RobotId].cutii += tmp.NrBoxes;
					}
					tmp.clocky = 0;
					r[tmp.RobotId].c.addFront(tmp);
					mixt.pop();
					istoric.pop();
				}
			}

		/*
		//HOW_MUCH_TIME
		*/

		} else if ( buffer == "HOW_MUCH_TIME" ) {
			if ( istoric.isEmpty() ) {
				out << "HOW_MUCH_TIME: No command was executed" << std::endl;
			} else {
				out << "HOW_MUCH_TIME: " << istoric.peek().clocky
				<< std::endl;
			}
		}

		// incrementarea timpului de stat in coada
		for ( int i = 0; i < N; ++i ) {
			Node<comanda> *tmp = r[i].c.getHead();
			while ( tmp ) {
				tmp->data.clocky++;
				tmp = tmp->next;
			}
		}
	}

	in.close();
	out.close();

	return 0;
}
