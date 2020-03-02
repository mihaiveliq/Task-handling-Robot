// Copyright 2018 Mihai Velicu

#ifndef COADA_H_
#define COADA_H_

template <typename T>
struct Node {
    T data;
    Node<T> *next;
    Node<T> *prev;

    explicit Node(T data) {
        this -> data = data;
        next = nullptr;
        prev = nullptr;
    }
};

template <typename T>
class Coada {
 private:
    Node<T> *head;
    Node<T> *tail;
    int numElements;

 public:
    // Constructor
    Coada() {
        head = nullptr;
        tail = nullptr;
        numElements = 0;
    }

    // Alt constructor
    explicit Coada(Node<T> *head) {
        this -> head = head;
        while ( head != nullptr ) {
            numElements++;
            head = head->next;
        }
    }

    // Destructor
    ~Coada() {
		Node<T> *temp = head;
		while ( head != nullptr ) {
			temp = head;
			head = head->next;
			delete temp;
		}
		numElements = 0;
    }

    // Adaug un nod la finalul cozii
    void addRear(T data) {
         Node<T>* nod = new Node<T>(data);

		if (numElements == 0) {
			head = nod;
			tail = nod;
		} else {
			tail->next = nod;
			nod->prev = tail;
		}

		tail = nod;
		numElements++;
    }

    // Adaug un nod la inceputul cozii
    void addFront(T data) {
        Node<T>* nod = new Node<T>(data);

        if (numElements == 0) {
			head = nod;
			tail = nod;
		} else {
			nod->next = head;
			head->prev = nod;
		}

		head = nod;
		numElements++;
    }

    // Elimin ultimul nod din coada
    T removeRear() {
    	T val = tail -> data;
        if (head == nullptr) {
            return val;
        }
		Node<T>* nod = tail;
		tail = tail->prev;
		if (tail == nullptr) {
            head = tail = nullptr;
		} else {
			tail->next = nullptr;
		}
		delete nod;
		numElements--;
        return val;
    }

    // Elimin primul nod din coada
    T removeFront() {
    	T val = head->data;

		Node<T>* nod = head;
        if (nod == nullptr) {
            return val;
        }
		head = head->next;
		if(head == nullptr) {
			tail = head = nullptr;
		} else {
			head->prev = nullptr;
		}
		delete nod;
		numElements--;

        return val;
    }

    // Verific daca exista noduri in coada
    bool isEmpty() {
        if (numElements == 0) {
        	return 1;
        } else {
        	return 0;
        }
    }

    // Returnez numarul nodurilor din coada
    int size() {
        return numElements;
    }

    // Returnez primul nod
    Node<T> *getHead() {
        return head;
    }

    // Returnez ultimul nod
    Node<T> *getTail() {
        return tail;
    }
};

#endif  // COADA_H_
