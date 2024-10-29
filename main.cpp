#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    ifstream inFile("input.txt");

    int no_problems, no_doctors;
    string name, speciality;

    // solve
    vector<string> problems;
    vector<string> names;
    vector<string> doctors;

    inFile>>no_problems;

    for(int i = 0; i < no_problems; ++i) {
        inFile>>name>>speciality;
        problems.push_back(speciality);
        names.emplace_back(name);
    }

    inFile>>no_doctors;

    for(int i = 0; i < no_doctors; ++i) {
        inFile >> name >> speciality;
        doctors.push_back(speciality);
    }

    for(int i = 0; i < problems.size(); ++i) {
        int ok = 0;
        for(int j = 0; j < doctors.size(); ++j) {
            if(problems[i] == doctors[j]) {
                ok = 1;
            }
        }

        if(ok == 1) {
            cout<<names[i]<<" Accept"<<'\n';
        }else {
            cout<<names[i]<<" Reject"<<'\n';
        }
    }

    return 0;
}
