#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

using namespace std;

struct Student {
    string id;
    string vorname;
    string nachname;
};

struct Studiengang {
    string id;
    string name;
};

vector<Student> loadStudents(const string& filename) {
    vector<Student> students;
    ifstream file(filename);
    string line, id, vorname, nachname;
    
    getline(file, line); // Header überspringen
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, id, ',');
        getline(ss, vorname, ',');
        getline(ss, nachname, ',');
        students.push_back({id, vorname, nachname});
    }
    return students;
}

unordered_map<string, string> loadStudiengaenge(const string& filename) {
    unordered_map<string, string> studiengaenge;
    ifstream file(filename);
    string line, id, name;
    
    getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, id, ',');
        getline(ss, name, ',');
        studiengaenge[id] = name;
    }
    return studiengaenge;
}

unordered_map<string, vector<string>> loadStudentPrograms(const string& filename) {
    unordered_map<string, vector<string>> studentPrograms;
    ifstream file(filename);
    string line, studentId, programId;
    
    getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, studentId, ',');
        getline(ss, programId, ',');
        studentPrograms[studentId].push_back(programId);
    }
    return studentPrograms;
}

void printStudentData(const vector<Student>& students, unordered_map<string, string>& studiengaenge, unordered_map<string, vector<string>>& studentPrograms) {
    cout << "Vorname | Nachname | Studiengang\n";
    cout << "-----------------------------------\n";
    for (const auto& student : students) {
        string student_id = student.id;
        if (studentPrograms.find(student_id) != studentPrograms.end()) {
            for (const auto& progId : studentPrograms[student_id]) {
                cout << student.vorname << " | " << student.nachname << " | " << studiengaenge[progId] << "\n";
            }
        } else {
            cout << student.vorname << " | " << student.nachname << " | Kein Studiengang\n";
        }
    }
}

int main() {
    vector<Student> students = loadStudents("Studierende.csv");
    unordered_map<string, string> studiengaenge = loadStudiengaenge("studiengaenge.csv");
    unordered_map<string, vector<string>> studentPrograms = loadStudentPrograms("zugeordnete_studiengaenge.csv");
    
    printStudentData(students, studiengaenge, studentPrograms);
    return 0;
}
