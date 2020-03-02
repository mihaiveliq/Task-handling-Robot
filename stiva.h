// Copyright 2018 Mihai Velicu

#ifndef STIVA_H_
#define STIVA_H_
template <typename T>
class stiva {
 private:
    int expandFactor = 2;
    int numElements;
    int maxCapacity;
    T *data;

 public:
    // Constructor
    stiva() {
        numElements = 0;
        maxCapacity = 10;

        data = new T[maxCapacity];
    }

    // Another constructor
    explicit stiva(int initialCapacity) {
        numElements = 0;
        maxCapacity = initialCapacity;
        data = new T[maxCapacity];
    }

    // Destructor
    ~stiva() {
        delete[] data;
    }

    // Adaug element
    void push(T element) {
        if ( isFull() ) {
        	T *data2 = new T[maxCapacity*expandFactor];
            maxCapacity *= expandFactor;
        	for ( int i = 0; i < numElements; ++i ) {
        		data2[i] = data[i];
        	}
        	delete[] data;
        	data = data2;
        }


        data[numElements] = element;

        numElements++;
    }

    // Sterge un element si il returneaza
    T pop() {
        numElements--;
        return data[numElements];
    }

    // Intoarce elementul din varful stivei
    T peek() {
    	return data[numElements-1];
    }

    // Intoarce 1 dacă stiva este goală;
    // 0 dacă are cel puțin un element
    bool isEmpty() {
        if (numElements == 0) {
        	return 1;
    	} else {
    		return 0;
    	}
    }

    bool isFull() {
    	return (numElements == maxCapacity);
	}

    int size() {
        return numElements;
    }

    // Getters & Setters
    T *getData() {
        return data;
    }
};

#endif  // STIVA_H_
