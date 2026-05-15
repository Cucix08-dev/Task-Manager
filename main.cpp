#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <fstream>
#include <filesystem>
using namespace std;

string toLowerCase(const string &str);
int searchIndex(const vector<string>& titleArr, const string& searchStr);

class Task{
    private:
        string name;
        string desc;
        int priority;

        string creationDate;
        int creationDay;
        int creationMonth;
        int creationYear;
        int creationDateSum;

        string expirationDate;
        int expirationDay;
        int expirationMonth;
        int expirationYear;
        int expirationDateSum;

    public:
        Task(
            string n, string d, int p, 
            int cDay, int cMonth, int cYear,
            int eDay, int eMonth, int eYear
        ){
            name = n;
            desc = d;
            priority = p;
            
            creationDay = cDay;
            creationMonth = cMonth;
            creationYear = cYear;
            creationDate = 
                to_string(cDay) + "-" + 
                to_string(cMonth) + "-" +
                to_string(cYear);
            creationDateSum = cDay + cMonth + cYear;

            expirationDay = eDay;
            expirationMonth = eMonth;
            expirationYear = eYear;
            expirationDate = 
                to_string(eDay) + "-" + 
                to_string(eMonth) + "-" + 
                to_string(eYear);
            expirationDateSum = eDay + eMonth + eYear;
        }

        /* GET E SET */

        //GETS
        string getName(){return name;}
        string getDesc(){return desc;}
        int getPriority(){return priority;}

        string getCreationDate(){
            creationDate =
                to_string(creationDay) + "-" +
                to_string(creationMonth) + "-" +
                to_string(creationYear);

            return creationDate;
        }
        int getCreationDateSum(){
            creationDateSum = creationDay + creationMonth + creationYear;
            return creationDateSum;
        }
        int getCreationDay(){return creationDay;}
        int getCreationMonth(){return creationMonth;}
        int getCreationYear(){return creationYear;}

        string getExpirationDate(){
            expirationDate = 
                to_string(expirationDay) + 
                to_string(expirationMonth) + 
                to_string(expirationYear);

            return expirationDate;
        }
        int getExpirationDay(){return expirationDay;}
        int getExpirationMonth(){return expirationMonth;}
        int getExpirationYear(){return expirationYear;}
        int getExpirationDateSum(){
            expirationDateSum = expirationDay + expirationMonth + expirationYear;
            return expirationDateSum;
        }

        //SETS
        void setName(string x){name=x;}
        void setDesc(string x){desc=x;}
        void setPriority(int x){priority=x;}

        void setCreationDate(string x){creationDate=x;}
        void setCreationDay(int x){creationDay=x;}
        void setCreationMonth(int x){creationMonth=x;}
        void setCreationYear(int x){creationYear=x;}
        void setCreationDateSum(int x){creationDateSum=x;}

        void setExpirationDate(string x){expirationDate=x;}
        void setExpirationDay(int x){expirationDay=x;}
        void setExpirationMonth(int x){expirationMonth=x;}
        void setExpirationYear(int x){expirationYear=x;}
        void setExpirationDateSum(int x){expirationDateSum=x;}

};

class TaskManager{
    private:
        vector<Task> tasks;

    public:
        void addTask(const Task& t){
            tasks.emplace_back(t);
        }

        void modify(int index){
            string action;
            
            cout << "\n-- MODIFY -- \n"
                 << "\nPossibles commands: \n"
                 << "name \n"
                 << "desc \n"
                 << "priority \n"
                 << "expirationdate \n"
                 << "\nInput: ";
            cin >> action;

            action = toLowerCase(action);

            if (action == "name"){
                string name;
                cout << "\nInsert name: ";
                cin.ignore();
                getline(cin,name);
                tasks.at(index).setName(name);
            }

            else if (action == "desc") {
                string desc;
                cout << "\nInsert description: ";
                cin.ignore();
                getline(cin,desc);
                tasks.at(index).setDesc(desc);
            }

            else if (action == "priority") {
                int priority;
                cout << "\nInsert priority: ";
                cin >> priority;
                tasks.at(index).setPriority(priority);
            }

            else if (action == "expirationdate"){
                int month;
                do {
                    cout << "\nInsert month: ";
                    cin >> month;
                } while (month < 1 || month > 12);

                int maxDay = 31;
                if (month == 4 || month == 6 || month == 9 || month == 11)
                    maxDay = 30;
                else if (month == 2)
                    maxDay = 28;


                int day;

                do {
                    cout << "\nInsert day: ";
                    cin >> day;
                } while (day < 1 || day > maxDay);


                int year;
                cout << "\nInsert year: ";
                cin >> year;

                int sum = day + month + year;
                bool valid = sum > tasks.at(index).getCreationDateSum();
                
                if (valid){
                    tasks.at(index).setExpirationDay(day);
                    tasks.at(index).setExpirationMonth(month);
                    tasks.at(index).setExpirationYear(year);
                    tasks.at(index).setExpirationDateSum(sum);
                    tasks.at(index).setExpirationDate(to_string(day) + "-" + to_string(month) + "-" + to_string(year));
                }
            }
        }

        void modifyTask(string task){
            int index = searchIndex(getTitleArr(),task);
            bool exist = (index >= 0);

            if (exist){
                modify(index);
            }
        }
        
        vector<string> getTitleArr() {
            vector<string> tasksTitles;

            for (int i = 0; i < tasks.size(); i++) {
                tasksTitles.push_back(tasks.at(i).getName());
            }

            return tasksTitles;
        }

        void toString(){
            for (int i = 0; i < tasks.size(); i++){
                cout << endl 
                     << tasks.at(i).getName() << " "
                     << tasks.at(i).getDesc() << " "
                     << tasks.at(i).getPriority() << " "
                     << tasks.at(i).getCreationDate() << " "
                     << tasks.at(i).getExpirationDate() 
                     << endl;
            }
        }

        void removeTask(string task){
            int index = searchIndex(getTitleArr(),task);
            bool exist = (index >= 0);

            if (exist){
                tasks.erase(tasks.begin() + index);
            }
            
        }

        void generateCSV(ofstream& out){
            string csvStr = "";

            for (int i = 0; i < tasks.size(); i++){
                csvStr += 
                    tasks.at(i).getName() + ";" + 
                    tasks.at(i).getDesc() + ";" + 
                    to_string(tasks.at(i).getPriority()) + ";" + 

                    to_string(tasks.at(i).getCreationDay()) + ";" +
                    to_string(tasks.at(i).getCreationMonth()) + ";" +
                    to_string(tasks.at(i).getCreationYear()) + ";" +

                    to_string(tasks.at(i).getExpirationDay()) + ";" +
                    to_string(tasks.at(i).getExpirationMonth()) + ";" +
                    to_string(tasks.at(i).getExpirationYear()) + "\n";
            }

            out << csvStr;
        }

};

int main(){
    TaskManager tasks;

    ifstream taskIn("tasks.csv");
    ofstream taskOut("tasks.csv", ios::app);


    bool exist = true;

    if (!taskOut){
        cerr << "The file tasks.csv doesn't exist.\n";
        exist = false;
    }
    if (!taskIn){
        cerr << "The file tasks.csv doesn't exist.\n";
        exist = false;
    }
    else{
        string line;

        while (getline(taskIn, line)) {
            vector<string> camp;
            stringstream ss(line);
            string campo;

            while (getline(ss, campo, ';')) {
                camp.push_back(campo);
            }

            if (camp.size() == 9) {
                tasks.addTask(Task(
                    camp[0],
                    camp[1],
                    stoi(camp[2]),
                    stoi(camp[3]),
                    stoi(camp[4]),
                    stoi(camp[5]),
                    stoi(camp[6]),
                    stoi(camp[7]),
                    stoi(camp[8])
                ));
            }
        }


    }

    bool running = true;

    while (running){
        time_t now = time(nullptr);
        tm* t = localtime(&now);

        int scelta;

        cout << "--- Insert the choise ---\n"
             << "1) Add task\n"
             << "2) Modify task\n"
             << "3) Remove task\n"
             << "4) Print all tasks\n"
             << "5) Exit\n"
             << "\nInput:";

        cin >> scelta;
        string task;

        string name, desc, creationDate, expirationDate;
        int priority, eDay, eMonth, eYear;

        switch (scelta){
            case 1: {
                cout << "\n--- ADD ---\n";

                cout << "\nInsert name: ";
                cin.ignore();
                getline(cin,name);

                cout << "\nInsert description: ";
                getline(cin,desc);

                cout << "\nInsert priority: ";
                cin >> priority;

                int cDay = t->tm_mday;
                int cMonth = t->tm_mon;
                int cYear = t->tm_year;
                int creationDateSum = cDay + cMonth + cYear;
                creationDate = 
                    to_string(cDay) + "-" + 
                    to_string(cMonth) + "-" + 
                    to_string(cYear);

                do{
                    cout << "\nInsert month number: ";
                    cin >> eMonth;
                } while (eMonth < 1 || eMonth > 12);

                int maxDay = 31;
                if (eMonth == 4 || eMonth == 6 || eMonth == 9 || eMonth == 11)
                    maxDay = 30;
                else if (eMonth == 2)
                    maxDay = 28;

                do{
                    cout << "\nInsert day: ";
                    cin >> eDay;
                } while (eDay < 1 || eDay > maxDay);

                cout << "\nInsert year: ";
                cin >> eYear;

                int expirationDateSum = eDay + eMonth + eYear;
                bool valid = expirationDateSum > creationDateSum;
                
                if (valid){
                    expirationDate = to_string(eDay) + "-" + 
                                     to_string(eMonth) + "-" + 
                                     to_string(eYear);
                }
                else{
                    expirationDate = creationDate;
                }

                tasks.addTask(Task(
                    name,
                    desc,
                    priority,
                    cDay,
                    cMonth,
                    cYear,
                    eDay,
                    eMonth,
                    eYear
                ));
                
                break;
            }

            case 2: {
                cout << "\n--- MODIFY ---\n";
                cout << "Insert the name of task: ";
                cin.ignore();
                getline(cin, task);
                tasks.modifyTask(task);
                break;
            }

            case 3: {
                cout << "\n--- REMOVE ---\n";
                cout << "Insert the name of task: ";
                cin.ignore();
                getline(cin, task);
                tasks.removeTask(task);
                break;
            }

            case 4: {
                cout << "\n--- TASKS ---\n";
                tasks.toString();
                break;
            }

            default: {
                running = false;
                break;
            }
        }
    }
    
    tasks.generateCSV(taskOut);

    return 0;
}


string toLowerCase(const string &str) {
    string s = str;
    for (char &c : s) c = tolower(c);
    return s;
}


int searchIndex(const vector<string>& titleArr, const string& searchStr) {
    string target = toLowerCase(searchStr);

    for (size_t i = 0; i < titleArr.size(); i++) {
        if (toLowerCase(titleArr[i]) == target)
            return static_cast<int>(i);
    }

    return -1;
}