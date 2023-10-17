//Solution

//
// Created by Stefan Andonov on 5.4.23.
//

#include<iostream>
#include<cstring>

using namespace std;

class DeliveryPerson {
private:
    char ID[6];
    char *name;
    int location;
    int deliveries;

    void copy(const DeliveryPerson &other) {
        this->location = other.location;
        this->deliveries = other.deliveries;
        strcpy(this->ID, other.ID);
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
    }

public:
    DeliveryPerson(char *id = "", char *name = "", int location = 0, int deliveries = 0) : location(location),
                                                                                           deliveries(deliveries) {
        strcpy(this->ID, id);
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    }

    DeliveryPerson(const DeliveryPerson &other) {
        copy(other);
    }

    DeliveryPerson &operator=(const DeliveryPerson &other) {
        if (this != &other) {
            delete[] name;
            copy(other);
        }
        return *this;
    }

    ~DeliveryPerson() {
        delete[] name;
    }

    void print() {
        cout << "ID: " << ID << " Name: " << name << " Current location: " << location << " # of deliveries: "
             << deliveries << endl;
    }

    bool isSame(const DeliveryPerson &d) {
        return strcmp(this->ID, d.ID) == 0;
    }

    int distance(int area) {
        return abs(location - area);
    }

    int getDeliveries() const {
        return deliveries;
    }

    void setLocation(int location) {
        DeliveryPerson::location = location;
    }

    void setDeliveries(int deliveries) {
        DeliveryPerson::deliveries = deliveries;
    }

    void increaseDeliveries() {
        ++deliveries;
    }

    char * getName() {
        return name;
    }

    bool compare (DeliveryPerson & dp, int area){
        if (this->distance(area) < dp.distance(area)){
            return true;
        } else if (this->distance(area) == dp.distance(area)) {
            return this->deliveries < dp.deliveries;
        } else {
            return false;
        }
    }
};

class DeliveryApp {
private:
    char name[20];
    DeliveryPerson * drivers;
    int count;

    void copy(const DeliveryApp &other) {
        strcpy(this->name, other.name);
        count = other.count;
        drivers = new DeliveryPerson[count];
        for (int i = 0; i < count; i++) {
            drivers[i] = other.drivers[i];
        }
    }

public:
    DeliveryApp(char *name = "") {
        strcpy(this->name, name);
        drivers = new DeliveryPerson [0];
        count = 0;
    }

//    DeliveryApp (const DeliveryApp & other){
//        copy(other);
//    }
//
//    DeliveryApp & operator = (const DeliveryApp & other){
//        if (this!=&other){
//            delete [] drivers;
//            copy(other);
//        }
//        return *this;
//    }

    ~DeliveryApp() {
        delete[] drivers;
    }

    void print() {
        cout << name << endl;
        if (count == 0) {
            cout << "EMPTY" << endl;
        }
        for (int i = 0; i < count; ++i) {
            drivers[i].print();
        }
    }

    void addDeliveryPerson(const DeliveryPerson &driver) {
        for (int i = 0; i < count; ++i) {
            if (drivers[i].isSame(driver)) {
                return;
            }
        }

        DeliveryPerson *tmp = new DeliveryPerson[count + 1];
        for (int i = 0; i < count; ++i) {
            tmp[i] = drivers[i];
        }
        tmp[count++] = driver;
        delete[] drivers;
        drivers = tmp;
    }

    void assignDelivery(int restaurantArea, int customerArea) {
        int idx = 0;
        for (int i=1;i<count;i++){
            if (drivers[i].compare(drivers[idx], restaurantArea)){
                idx = i;
            }
        }

        drivers[idx].increaseDeliveries();
        drivers[idx].setLocation(customerArea);
    }


};

void readAppData(DeliveryApp &app) {

}

int main() {

    int testCase;
    cin >> testCase;

    if (testCase == 1) {
        cout << "CONSTRUCTOR DeliveryPerson" << endl;
        DeliveryPerson person("12345", "Stefan", 5);
        person.print();
        cout << "CONSTRUCTOR DeliveryPerson OK" << endl;
    } else if (testCase == 2) {
        cout << "COPY-CONSTRUCTOR DeliveryPerson" << endl;
        DeliveryPerson person = DeliveryPerson("12345", "Stefan", 5);
        person.print();
        cout << "COPY-CONSTRUCTOR DeliveryPerson OK" << endl;
    } else if (testCase == 3) {
        cout << "DEFAULT CONSTRUCTOR AND OPERATOR = DeliveryPerson" << endl;
        DeliveryPerson person;
        DeliveryPerson person2("12345", "Stefan", 5);
        person = person2;
        person.print();
        cout << "DEFAULT CONSTRUCTOR AND OPERATOR = DeliveryPerson OK" << endl;
    } else if (testCase == 4) {
        cout << "CONSTRUCTOR DeliveryApp" << endl;
        char appName[50];
        cin >> appName;
        DeliveryApp app(appName);
        app.print();
        cout << "CONSTRUCTOR DeliveryApp OK" << endl;
    } else if (testCase == 5) {
        cout << "DeliveryApp addDeliveryPerson test" << endl;
        char appName[50];
        cin >> appName;
        DeliveryApp app(appName);
        int n;
        cin >> n;
        char ID[6];
        char name[20];
        int location;
        for (int i = 0; i < n; i++) {
            cin >> ID >> name >> location;
            app.addDeliveryPerson(DeliveryPerson(ID, name, location));
        }
        app.print();
    } else if (testCase == 6) {
        cout << "DeliveryApp addDeliveryPerson test" << endl;
        char appName[50];
        cin >> appName;
        DeliveryApp app(appName);
        int n;
        cin >> n;
        char ID[6];
        char name[20];
        int location;
        for (int i = 0; i < n; i++) {
            cin >> ID >> name >> location;
            app.addDeliveryPerson(DeliveryPerson(ID, name, location));
        }
        cin >> n; //read assign deliveries
        for (int i = 0; i < n; i++) {
            int restaurantArea, customerArea;
            cin >> restaurantArea >> customerArea;
            app.assignDelivery(restaurantArea, customerArea);
        }
        app.print();
    }
    return 0;
}

