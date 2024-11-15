#include<bits/stdc++.h>
#include<fstream>
using namespace std;

#define WORK 9;

class Problem {
public:
    string name;
    string speciality;
    int time;

    Problem(string a, string b, int c): name(a), speciality(b), time(c) {};
};

class Doctor {
public:
    string id;
    string speciality;
    int time_worked = 0;
    vector<Problem> problems_solved;

    Doctor(string a, string b): id(a), speciality(b) {};
};

int main() {
    ifstream inFile("input4_bonus.txt");

    int no_problems, no_doctors, time_per_problem;
    string name, speciality, id;

    vector<Problem> problems;
    vector<Doctor> doctors;

    inFile >> no_problems;

    for (int i = 0; i < no_problems; i++)
    {
        inFile >> name;
        inFile >> speciality;
        inFile >> time_per_problem;

        Problem problem(name, speciality, time_per_problem);
        problems.push_back(problem);
    }

    inFile >> no_doctors;

    for (int i = 0; i < no_doctors; i++)
    {
        inFile >> id;
        inFile >> speciality;

        Doctor doctor(id, speciality);
        doctors.push_back(doctor);
    }

    for(auto& problem: problems) {
        auto doctor = find_if(doctors.begin(), doctors.end(), [problem](const Doctor& doctor) {
            return doctor.speciality == problem.speciality and doctor.time_worked + problem.time < WORK;
        });

        if(doctor != doctors.end()) {
            doctor->time_worked += problem.time;
            doctor->problems_solved.push_back(problem);
        }
    }

    for(auto& doctor: doctors) {
        if(!doctor.problems_solved.empty()) {
            cout<<doctor.id<<" "<<doctor.problems_solved.size()<<" ";
            for(auto& problem: doctor.problems_solved) {
                cout<<problem.name<<" ";
            }
            cout<<"\n";
        }
    }

    return 0;
}
