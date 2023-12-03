/*
Author: Kenneth Guillont
Course: CSCI-136
Instructor: Brandon Foster
Assignment: Lab 11 Task A. Class Profile
*/

#include <iostream>
using namespace std;

class Profile {
private:
    string username;
    string displayname;
public:
    Profile(string usrn, string dspn) {
        username = usrn;
        displayname = dspn;
    }

    Profile() {
        username = "";
        displayname = "";
    }

    string getUsername() {
        return username;
    }

    string getFullName() {
        return displayname + " (@" + username + ")";
    }

    void setDisplayName(string dspn) {
        displayname = dspn;
    }
};

int main() {
    Profile p1("marco", "Marco");    
    cout << p1.getUsername() << endl; // marco
    cout << p1.getFullName() << endl; // Marco (@marco)

    p1.setDisplayName("Marco Rossi"); 
    cout << p1.getUsername() << endl; // marco
    cout << p1.getFullName() << endl; // Marco Rossi (@marco)
    
    Profile p2("tarma1", "Tarma Roving");    
    cout << p2.getUsername() << endl; // tarma1
    cout << p2.getFullName() << endl; // Tarma Roving (@tarma1)
}