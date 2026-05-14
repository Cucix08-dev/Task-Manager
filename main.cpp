#include <iostream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

string toLowerCase(const string &str);
int searchIndex(const vector<string>& titleArr, const string& searchStr);

class Task{
    private:
        string name;
        string desc;
        int priority;
        string creationDate;
        int creationDateSum;
        string expirationDate;
        int expirationDateSum;

    public:
        Task(string t, string d, int p, string cD, int cDS, string eD, int eDS){
            name = t;
            desc = d;
            priority = p;
            creationDate = cD;
            creationDateSum = cDS;
            expirationDate = eD;
            expirationDateSum = eDS;
        }

        /* GET E SET */

        //GETS
        string getName(){return name;}
        string getDesc(){return desc;}
        int getPriority(){return priority;}
        string getCreationDate(){return creationDate;}
        int getCreationDateSum(){return creationDateSum;}
        string getExpirationDate(){return expirationDate;}
        int getExpirationDateSum(){return expirationDateSum;}

        //SETS
        void setName(string x){name=x;}
        void setDesc(string x){desc=x;}
        void setPriority(int x){priority=x;}
        void setCreationDate(string x){creationDate=x;}
        void setCreationDateSum(int x){creationDateSum=x;}
        void setExpirationDate(string x){expirationDate=x;}
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
                    tasks.at(index).setExpirationDateSum(sum);
                    tasks.at(index).setExpirationDate(to_string(day) + " - " + to_string(month) + " - " + to_string(year));
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

};

int main(){
    TaskManager tasks;

    bool running = true;

    while (running){
        time_t now = time(nullptr);
        tm* t = localtime(&now);

        int scelta;

        cout << "--- Insert the choise ---\n";
        cout << "1) Add task\n";
        cout << "2) Modify task\n";
        cout << "3) Remove task\n";        
        cout << "4) Print all tasks\n";
        cout << "5) Exit\n";

        cin >> scelta;
        string task;

        string name, desc, creationDate, expirationDate;
        int priority, day, month, year;

        switch (scelta){
            case 1:
                cout << "\n--- ADD ---\n";

                cout << "\nInsert name: ";
                cin.ignore();
                getline(cin,name);

                cout << "\nInsert description: ";
                getline(cin,desc);

                cout << "\nInsert priority: ";
                cin >> priority;

                int creationDateSum = t->tm_mday + t->tm_mon + t->tm_year;
                creationDate = to_string(t->tm_mday) + " - " + to_string(t->tm_mon) + " - " + to_string(t->tm_year);

                do{
                    cout << "\nInsert month number: ";
                    cin >> month;
                } while (month < 1 || month > 12);

                int maxDay = 31;
                if (month == 4 || month == 6 || month == 9 || month == 11)
                    maxDay = 30;
                else if (month == 2)
                    maxDay = 28;

                do{
                    cout << "\nInsert day: ";
                    cin >> day;
                } while (day < 1 || day > maxDay);

                cout << "\nInsert year: ";
                cin >> year;

                int expirationDateSum = day + month + year;
                bool valid = expirationDateSum > creationDateSum;
                
                if (valid){
                    expirationDate = to_string(day) + " - " + 
                                     to_string(month) + " - " + 
                                     to_string(year);
                }
                else{
                    expirationDate = creationDate;
                }

                tasks.addTask(Task(
                    name,
                    desc,
                    priority,
                    creationDate,
                    creationDateSum,
                    expirationDate,
                    expirationDateSum
                ));
                
                break;
            
            case 2:
                cout << "\n--- MODIFY ---\n";
                cout << "Insert the name of task: ";
                cin.ignore();
                getline(cin, task);
                tasks.modifyTask(task);
                break;

            case 3:
                cout << "\n--- REMOVE ---\n";
                cout << "Insert the name of task: ";
                cin.ignore();
                getline(cin, task);
                tasks.removeTask(task);
                break;

            case 4:
                cout << "\n--- TASKS ---\n";
                tasks.toString();
                break;
            
            default:
                running = false;
                break;
        }
    }
    
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
