#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include "observer.h"

class Subject {
private:
    std::vector<Observer*> observers;
public:
    void addObserver(Observer* observer) {
        observers.push_back(observer);
    }

    void notifyObservers() {
        for (Observer* observer : observers) {
            observer->update();
        }
    }
};

#endif // SUBJECT_H
