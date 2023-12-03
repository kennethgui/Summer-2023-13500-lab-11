/*
Author: Kenneth Guillont
Course: CSCI-136
Instructor: Brandon Foster
Assignment: Lab 11 Task D. Class Network: Posting (Bonus)
*/

#include <iostream>
using namespace std;

struct Post {
    string username;
    string message;
};

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
    static const int MAX_USERS = 20;
    int numUsers;
    Profile profiles[MAX_USERS];
    bool following[MAX_USERS][MAX_USERS];
    static const int MAX_POSTS = 100;
    int numPosts;
    Post posts[MAX_POSTS];

    int findID(string usrn) {
        for (int i = 0; i < numUsers; i++) {
            if (profiles[i].getUsername() == usrn)
                return i;
        }
        return -1;
    }

public:
    Network() {
        numUsers = 0;
        for (int i = 0; i < MAX_USERS; i++) {
            for (int j = 0; j < MAX_USERS; j++) {
                following[i][j] = false;
            }
        }
        numPosts = 0; // Initialize the number of posts to 0
    }

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

    bool follow(string usrn1, string usrn2) {
        int id1 = findID(usrn1);
        int id2 = findID(usrn2);

        if (id1 == -1 || id2 == -1)
            return false;

        following[id1][id2] = true;
        return true;
    }

    bool writePost(string usrn, string msg) {
        int id = findID(usrn);

        if (id == -1 || numPosts == MAX_POSTS)
            return false;

        posts[numPosts].username = usrn;
        posts[numPosts].message = msg;
        numPosts++;
        return true;
    }

    bool printTimeline(string usrn) {
        int id = findID(usrn);

        if (id == -1)
            return false;

        for (int i = numPosts - 1; i >= 0; i--) {
            if (posts[i].username == usrn) {
                cout << profiles[id].getFullName() << ": " << posts[i].message << endl;
            } else if (following[id][findID(posts[i].username)]) {
                cout << profiles[findID(posts[i].username)].getFullName() << ": " << posts[i].message << endl;
            }
        }

        return true;
    }

    void printDot() {
        cout << "digraph {" << endl;

        // Print nodes
        for (int i = 0; i < numUsers; i++) {
            cout << "  \"" << "@" << profiles[i].getUsername() << "\"" << endl;
        }

        // Print edges
        for (int i = 0; i < numUsers; i++) {
            for (int j = 0; j < numUsers; j++) {
                if (following[i][j]) {
                    cout << "  \"" << "@" << profiles[i].getUsername() << "\" -> \"" << "@" << profiles[j].getUsername() << "\"" << endl;
                }
            }
        }

        cout << "}" << endl;
    }
};

int main() {
    Network nw;
    // add three users
    nw.addUser("mario", "Mario");
    nw.addUser("luigi", "Luigi");
    nw.addUser("yoshi", "Yoshi");
   
    nw.follow("mario", "luigi");
    nw.follow("luigi", "mario");
    nw.follow("luigi", "yoshi");
    nw.follow("yoshi", "mario");

    // write some posts
    nw.writePost("mario", "It's a-me, Mario!");
    nw.writePost("luigi", "Hey hey!");
    nw.writePost("mario", "Hi Luigi!");
    nw.writePost("yoshi", "Test 1");
    nw.writePost("yoshi", "Test 2");
    nw.writePost("luigi", "I just hope this crazy plan of yours works!");
    nw.writePost("mario", "My crazy plans always work!");
    nw.writePost("yoshi", "Test 3");
    nw.writePost("yoshi", "Test 4");
    nw.writePost("yoshi", "Test 5");

    cout << endl;
    cout << "======= Mario's timeline =======" << endl;
    nw.printTimeline("mario");
    cout << endl;

    cout << "======= Yoshi's timeline =======" << endl;
    nw.printTimeline("yoshi");
    cout << endl;
}
