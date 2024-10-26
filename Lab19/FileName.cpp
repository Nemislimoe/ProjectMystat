#include <iostream>
#include <Windows.h> // ��� ��������� ������
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// ����� ��������� ���:
// ��������� ���������� ��� �����������
struct User {
    int id;
    string name;
    string password;

    User(int id, string name, string password)
        : id(id), name(name), password(password) {}
};

// ��������� ���������� ��� ������ ��������
struct Homework {
    string name;
    string description;
    bool submitted;

    Homework(string name, string description)
        : name(name), description(description), submitted(false) {}
};

// ��������� ���������� ��� �������
struct Schedule {
    string subject;
    string day;
    string time;

    Schedule(string subject, string day, string time)
        : subject(subject), day(day), time(time) {}
};

class Mystat {
private:
    vector<User> users; // �����������
    vector<Homework> homeworkList; // �������
    vector<Schedule> scheduleList; // �������
    int userIdCounter = 1;

    // ����� ����� ��� ���������:
    const string userFileName = "users.txt";
    const string homeworkFileName = "homework.txt";
    const string scheduleFileName = "schedule.txt";

public:

    Mystat() { // �����������
        loadData(); // ������������ ������ � �����
    }

    ~Mystat() { // ����������
        saveData(); // ���������� ������ � ����
    }

    // ��������� ������ �����������
    void registerUser() {
        string name, password;
        cout << "������ ��'� �����������: ";
        cin >> name;
        cout << "������ ������: ";
        cin >> password;

        // ��������� ���� � ������
        users.push_back(User(userIdCounter++, name, password));
        cout << "���������� " << name << " �������������." << endl;
    }
    // ���� ����������� 
    User* loginUser() {
        string name, password;
        cout << "������ ��'� �����������: ";
        cin >> name;
        cout << "������ ������: ";
        cin >> password;

        // �������� ���� ��������
        for (auto& user : users) {
            if (user.name == name && user.password == password) {
                cout << "���� ������� ��� " << name << ".\n";
                return &user;
            }
        }
        cout << "���������� ���� � ������." << endl;
        return 0;
    }

    // � ������� ����� � authorization ����� �� �����������
    User* Authentication() {
        int choice;
        User* currentUser = 0;

        while (true) {
            cout << "1. ���������\n2. ����\n0. �����\n";
            cin >> choice;

            if (choice == 1) {
                registerUser(); // ���������
            }
            else if (choice == 2) {
                currentUser = loginUser(); // ����
                if (currentUser) break;
            }
            else if (choice == 0) {
                cout << "����� � ��������.\n";
                return 0; // ����� � ���������
            }
            else {
                cout << "������� ����. ��������� �� ���.\n";
            }
        }
        return currentUser;
    }

    // ��������� ������� 
    void addHomework() {
        string name, description;
        cout << "����� ���������� ��������: ";
        cin.ignore();
        getline(cin, name);
        cout << "����: ";
        getline(cin, description);
        homeworkList.push_back(Homework(name, description));
        cout << "������ �������� ������." << endl;
    }

    // ����� ������� 
    void submitHomework() {
        int index;
        viewHomework(); // ������ �� �������
        cout << "������� ����� ���������� �������� ��� �����: ";
        cin >> index;
        if (index > 0 && index <= homeworkList.size()) {
            homeworkList[index - 1].submitted = true;
            cout << "������ �������� �����." << endl;
        }
        else {
            cout << "������������ ����." << endl;
        }
    }

    // ������ �� �������
    void viewHomework() {
        if (homeworkList.empty()) {
            cout << "������� ������� ����." << endl;
            return;
        }
        cout << "������ ������� �������:\n";
        for (size_t i = 0; i < homeworkList.size(); ++i) {
            cout << i + 1 << ". " << homeworkList[i].name
                << " (" << (homeworkList[i].submitted ? "�����" : "�� �����") << ")\n";
        }
    }

    // ���� ������� � �������  
    void addLesson() {
        string subject, day, time;
        cout << "����� ��������: ";
        cin.ignore();
        getline(cin, subject);
        cout << "����: ";
        getline(cin, day);
        cout << "���: ";
        getline(cin, time);
        scheduleList.push_back(Schedule(subject, day, time));
        cout << "������� ������." << endl;
    }

    // ������� ������� � ��������
    void removeLesson() {
        int index;
        viewSchedule();
        cout << "������� ����� ������� ��� ���������: ";
        cin >> index;
        if (index > 0 && index <= scheduleList.size()) {
            scheduleList.erase(scheduleList.begin() + index - 1);
            cout << "������� ��������." << endl;
        }
        else {
            cout << "������������ ����." << endl;
        }
    }

    // ������ �������
    void viewSchedule() {
        if (scheduleList.empty()) {
            cout << "�������� ����." << endl;
            return;
        }
        cout << "������ �������:\n";
        for (size_t i = 0; i < scheduleList.size(); ++i) {
            cout << i + 1 << ". " << scheduleList[i].subject
                << " (" << scheduleList[i].day << ", " << scheduleList[i].time << ")\n";
        }
    }
    // ������� �������
    void mainMenu(User* currentUser) {
        int choice;
        while (true) {
            cout << "\n1. ������ ��������\n2. �������\n0. �����\n";
            cout << "������ �����: ";
            cin >> choice;

            switch (choice) {
            case 1:
                homeworkMenu(); // ������� � ���������
                break;
            case 2:
                scheduleMenu(); // ������� � ��������� �������
                break;
            case 0:
                cout << "����� � ��������." << endl;
                return;
            default:
                cout << "������� ����. ��������� �� ���." << endl;
            }
        }
    }
    // ���� ������� �������
    void homeworkMenu() {
        int choice;
        while (true) {
            cout << "\n1. ������ ������ ��������\n2. ����� ������ ��������\n3. ����������� ������ ��������\n0. �����\n";
            cout << "������ �����: ";
            cin >> choice;

            switch (choice) {
            case 1:
                addHomework(); // ��������� �������
                break;
            case 2:
                submitHomework(); // ����� �������
                break;
            case 3:
                viewHomework(); // ������� �������
                break;
            case 0:
                return; // ���������� �� ������� �������
            default:
                cout << "������� ����. ��������� �� ���." << endl;
            }
        }
    }
    // ���� �������� �������
    void scheduleMenu() {
        int choice;
        while (true) {
            cout << "\n1. ������ �������\n2. �������� �������\n3. ����������� �������\n0. �����\n";
            cout << "������ �����: ";
            cin >> choice;

            switch (choice) {
            case 1:
                addLesson(); // ��������� �������
                break;
            case 2:
                removeLesson(); // ��������� �������
                break;
            case 3:
                viewSchedule(); // �������� ��������
                break;
            case 0:
                return; // ���������� �� ������� �������
            default:
                cout << "������� ����. ��������� �� ���." << endl;
            }
        }
    }
    // ������� ��� ���������� ����� � ����� (P.S. � ����� ������ ��� ���� ��� ��� �������� ����������� �������� ���� ���� ���� ���)
    void saveData() {
        ofstream userFile(userFileName);
        ofstream homeworkFile(homeworkFileName);
        ofstream scheduleFile(scheduleFileName);

        // ���������� ������������
        for (const auto& user : users) {
            userFile << user.id << ' ' << user.name << ' ' << user.password << '\n';
        }

        // ���������� ������� �������
        for (const auto& homework : homeworkList) {
            homeworkFile << homework.name << '\n' << homework.description << '\n' << homework.submitted << '\n';
        }

        // ���������� ��������
        for (const auto& schedule : scheduleList) {
            scheduleFile << schedule.subject << '\n' << schedule.day << '\n' << schedule.time << '\n';
        }
    }

    // ������� ��� ������������ ����� �� �����
    void loadData() {
        ifstream userFile(userFileName);
        ifstream homeworkFile(homeworkFileName);
        ifstream scheduleFile(scheduleFileName);

        // ������������ ������������
        int id;
        string name, password;
        while (userFile >> id >> name >> password) {
            users.push_back(User(id, name, password));
            userIdCounter = max(userIdCounter, id + 1); // ��������� ��������� ID
        }

        // ������������ ������� �������
        string homeworkName, description;
        bool submitted;
        while (getline(homeworkFile, homeworkName)) {
            getline(homeworkFile, description);
            homeworkFile >> submitted;
            homeworkFile.ignore();
            homeworkList.push_back(Homework(homeworkName, description));
            homeworkList.back().submitted = submitted;
        }

        // ������������ ��������
        string subject, day, time;
        while (getline(scheduleFile, subject)) {
            getline(scheduleFile, day);
            getline(scheduleFile, time);
            scheduleList.push_back(Schedule(subject, day, time));
        }
    }
};


int main() {
    SetConsoleCP(1251); // ��� ��������� ������
    SetConsoleOutputCP(1251);
    Mystat system; // ������
    User* currentUser = system.Authentication();

    // ������� ������� ���� ���� �� �����������
    if (currentUser) {
        system.mainMenu(currentUser);
    }

    return 0;
}
