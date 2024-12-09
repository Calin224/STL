#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<fstream>
#include <queue>
using namespace std;

#define WORK 9;

class Problem {
public:
    string name;
    string speciality;
    int prioritate;
    int time;

    Problem(string a, string b, int c, int d): name(a), speciality(b), time(c), prioritate(d) {};
};

class Doctor {
public:
    string id;
    string speciality;
    int time_worked = 0;
    vector<Problem> problems_solved;

    Doctor(string a, string b): id(a), speciality(b) {};
};

struct ProblemCompare {
    bool operator()(const Problem& p1, const Problem& p2) const {
        return p1.prioritate < p2.prioritate;
    }
};

int main() {
    ifstream inFile("input.txt");

    int no_problems, no_doctors, time_per_problem, prioritate;
    string name, speciality, id;

    vector<Doctor> doctors;

    priority_queue<Problem, vector<Problem>, ProblemCompare> pq;

    inFile >> no_problems;

    for (int i = 0; i < no_problems; i++)
    {
        inFile >> name;
        inFile >> speciality;
        inFile >> time_per_problem;
        inFile >> prioritate;

        Problem problem(name, speciality, time_per_problem, prioritate);
        pq.push(problem);
    }

    inFile >> no_doctors;

    for (int i = 0; i < no_doctors; i++)
    {
        inFile >> id;
        inFile >> speciality;

        Doctor doctor(id, speciality);
        doctors.push_back(doctor);
    }

    while(!pq.empty()) {
        Problem problem = pq.top();
        auto doctor = find_if(doctors.begin(), doctors.end(), [&](const Doctor& doctor) {
            return doctor.speciality == problem.speciality and doctor.time_worked + problem.time < WORK;
        });

        if(doctor != doctors.end()) {
            doctor->time_worked += problem.time;
            doctor->problems_solved.push_back(problem);
        }

        pq.pop();
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