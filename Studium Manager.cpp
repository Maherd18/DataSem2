#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct Student {
    string vorname;
    string nachname;
    string studiengang;
};

vector<Student> loadStudents(const string& filename) {
    vector<Student> students;
    ifstream file(filename);
    string line, vorname, nachname, studiengang;
    
    getline(file, line); // Header überspringen
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, vorname, ',');
        getline(ss, nachname, ',');
        getline(ss, studiengang, ',');
        students.push_back({vorname, nachname, studiengang});
    }
    return students;
}

void saveStudents(const string& filename, const vector<Student>& students) {
    ofstream file(filename);
    file << "Vorname,Nachname,Studiengang\n";
    for (const auto& student : students) {
        file << student.vorname << "," << student.nachname << "," << student.studiengang << "\n";
    }
}

void printStudents(const vector<Student>& students) {
    cout << "Vorname | Nachname | Studiengang\n";
    cout << "--------------------------------\n";
    for (const auto& student : students) {
        cout << student.vorname << " | " << student.nachname << " | " << student.studiengang << "\n";
    }
}

void changeStudyProgram(vector<Student>& students, const string& vorname, const string& nachname, const string& newProgram) {
    for (auto& student : students) {
        if (student.vorname == vorname && student.nachname == nachname) {
            student.studiengang = newProgram;
            cout << "Studiengang geändert!\n";
            return;
        }
    }
    cout << "Student nicht gefunden!\n";
}

int main() {
    string filename = "studium.csv";
    vector<Student> students = loadStudents(filename);
    printStudents(students);
    
    // Beispiel: Ändern des Studiengangs
    changeStudyProgram(students, "Max", "Müller", "Physik");
    saveStudents(filename, students);
    return 0;
}
