#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_PATIENTS = 500;   
const int MAX_NAME_LENGTH = 50;  

int patientIDs[MAX_PATIENTS];
string patientNames[MAX_PATIENTS];
int patientAges[MAX_PATIENTS];
string patientDiseases[MAX_PATIENTS];
int roomNumbers[MAX_PATIENTS];
int totalPatients = 0; 

void displayMenu();
void addPatient();
void searchPatient();
void displayAllPatients();
void updatePatient();
void savePatientsToFile();
void loadPatientsFromFile();
bool isPatientIDExists(int id);
int getPatientIndexByID(int id);
void displayPatient(int index);
void deletePatient();


int main() {
    loadPatientsFromFile();
    int choice;

    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: 
                addPatient();
                break;
            case 2: 
                searchPatient();
                break;
            case 3: 
                displayAllPatients();
                break;
            case 4: 
                updatePatient();
                break;
            case 5: 
                deletePatient();
                break;
            case 6: 
                savePatientsToFile();
                cout << "Patient records saved successfully!" << endl;
                break;
            case 7: 
                cout << "Exiting Hospital Management System. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 7); 

    return 0;
}


void displayMenu() {
    cout << "\n--- Hospital Patient Management System ---\n";
    cout << "1. Add a New Patient\n";
    cout << "2. Search for a Patient\n";
    cout << "3. Display All Patients\n";
    cout << "4. Update Patient Information\n";
    cout << "5. Delete a Patient\n";
    cout << "6. Save Patient Records to File\n";
    cout << "7. Exit\n";
}


void loadPatientsFromFile() {
    ifstream file("hospital_patients.txt");

    if (!file) {
        cout << "No previous data found. Starting fresh.\n";
        return;
    }

    while (file >> patientIDs[totalPatients]) {
        file.ignore();
        getline(file, patientNames[totalPatients]);
        file >> patientAges[totalPatients];
        file.ignore();
        getline(file, patientDiseases[totalPatients]);
        file >> roomNumbers[totalPatients];
        totalPatients++;

        if (totalPatients >= MAX_PATIENTS) {
            cout << "Patient limit reached. Cannot load more patients.\n";
            break;
        }
    }
    file.close();
    cout << "Patient records loaded successfully!\n";
}


void savePatientsToFile() {
    ofstream file("hospital_patients.txt");

    for (int i = 0; i < totalPatients; ++i) {
        file << patientIDs[i] << "\n";
        file << patientNames[i] << "\n";
        file << patientAges[i] << "\n";
        file << patientDiseases[i] << "\n";
        file << roomNumbers[i] << "\n";
    }

    file.close();
}


void addPatient() {
    if (totalPatients >= MAX_PATIENTS) {
        cout << "Cannot add more patients, hospital is full!\n";
        return;
    }

    int patientID;
    cout << "Enter Patient ID: ";
    cin >> patientID;

    if (isPatientIDExists(patientID)) {
        cout << "A patient with this ID already exists. Try a different ID.\n";
        return;
    }

    cin.ignore(); 
    cout << "Enter Patient Name: ";
    getline(cin, patientNames[totalPatients]);

    cout << "Enter Patient Age: ";
    cin >> patientAges[totalPatients];

    cin.ignore(); 
    cout << "Enter Patient Disease: ";
    getline(cin, patientDiseases[totalPatients]);

    cout << "Enter Room Number: ";
    cin >> roomNumbers[totalPatients];

    patientIDs[totalPatients] = patientID;
    totalPatients++;

    cout << "Patient added successfully!\n";
}


bool isPatientIDExists(int patientID) {
    for (int i = 0; i < totalPatients; ++i) {
        if (patientIDs[i] == patientID) {
            return true;
        }
    }
    return false;
}


void searchPatient() {
    cin.ignore(); 
    cout << "Enter Patient ID or Name to search: ";
    string query;
    getline(cin, query);

    bool found = false;
    for (int i = 0; i < totalPatients; ++i) {
        
        if (to_string(patientIDs[i]) == query || patientNames[i] == query) {
            displayPatient(i);
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "No patient found with the given ID or Name.\n";
    }
}


void displayPatient(int index) {
    cout << "\n--- Patient Found ---\n";
    cout << "Patient ID: " << patientIDs[index] << endl;
    cout << "Name: " << patientNames[index] << endl;
    cout << "Age: " << patientAges[index] << endl;
    cout << "Disease: " << patientDiseases[index] << endl;
    cout << "Room Number: " << roomNumbers[index] << endl;
    cout << "-----------------------\n";
}


void displayAllPatients() {
    if (totalPatients == 0) {
        cout << "No patients to display.\n";
        return;
    }

    cout << "\n--- Displaying All Patients ---\n";
    for (int i = 0; i < totalPatients; ++i) {
        displayPatient(i);
    }
}


void updatePatient() {
    int id;
    cout << "Enter the Patient ID to update: ";
    cin >> id;

    int index = getPatientIndexByID(id);
    if (index == -1) {
        cout << "No patient found with the provided ID.\n";
        return;
    }

    cout << "Updating details for Patient ID: " << id << endl;

    cin.ignore(); 
    cout << "Enter new Name: ";
    getline(cin, patientNames[index]);

    cout << "Enter new Age: ";
    cin >> patientAges[index];

    cin.ignore(); 
    cout << "Enter new Disease: ";
    getline(cin, patientDiseases[index]);

    cout << "Enter new Room Number: ";
    cin >> roomNumbers[index];

    cout << "Patient details updated successfully!\n";
}

int getPatientIndexByID(int id) {
    for (int i = 0; i < totalPatients; ++i) {
        if (patientIDs[i] == id) {
            return i;
        }
    }
    return -1;
}


void deletePatient() {
    int id;
    cout << "Enter the Patient ID to delete: ";
    cin >> id;

    int index = getPatientIndexByID(id);
    if (index == -1) {
        cout << "No patient found with the provided ID.\n";
        return;
    }

    for (int i = index; i < totalPatients - 1; ++i) {
        patientIDs[i] = patientIDs[i + 1];
        patientNames[i] = patientNames[i + 1];
        patientAges[i] = patientAges[i + 1];
        patientDiseases[i] = patientDiseases[i + 1];
        roomNumbers[i] = roomNumbers[i + 1];
    }

    totalPatients--;
    cout << "Patient deleted successfully!\n";
}