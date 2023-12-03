/*
Author: Kenneth Guillont
Course: CSCI-136
Instructor: Brandon Foster
Assignment: Lab 11 Task B. Class Network: Adding users
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

class Network {
private:
    static const int MAX_USERS = 20; // max number of user profiles
    int numUsers;                    // number of registered users
    Profile profiles[MAX_USERS];     // user profiles array:
                                     // mapping integer ID -> Profile

    // Returns user ID (index in the 'profiles' array) by their username
    // (or -1 if username is not found)
    int findID(string usrn) {
        for (int i = 0; i < numUsers; i++) {
            if (profiles[i].getUsername() == usrn)
                return i;
        }
        return -1;
    }

public:
    // Constructor, makes an empty network (numUsers = 0)
    Network() {
        numUsers = 0;
    }

    // Attempts to sign up a new user with specified username and displayname
    // return true if the operation was successful, otherwise return false
    bool addUser(string usrn, string dspn) {
        if (usrn.empty() || usrn.length() > 20 || usrn.find(" ") != string::npos || usrn.find("-") != string::npos)
            return false;

        if (findID(usrn) != -1)
            return false;

        if (numUsers == MAX_USERS)
            return false;

        profiles[numUsers] = Profile(usrn, dspn);
        numUsers++;
        return true;
    }
};

int main() {
    Network nw;
    cout << nw.addUser("mario", "Mario") << endl;       // true (1)
    cout << nw.addUser("luigi", "Luigi") << endl;       // true (1)

    cout << nw.addUser("mario", "Mario2") << endl;      // false (0)
    cout << nw.addUser("mario 2", "Mario2") << endl;    // false (0)
    cout << nw.addUser("mario-2", "Mario2") << endl;    // false (0)

    for (int i = 2; i < 20; i++)
        cout << nw.addUser("mario" + to_string(i), "Mario" + to_string(i)) << endl;    // true (1)

    cout << nw.addUser("yoshi", "Yoshi") << endl;       // false (0)
}
