#include <iostream>
#include <string>
#include <map>
using namespace std;

class TaskManager{
    private:
        map<string,bool>tasks;
    public:
        void addTask(string &task){
            task = toLowerCase(task);
            if (tasks.count(task)){
                cout << "\nTask already exists ✗: " << tasks[task] << endl;
            }
            else{
                tasks[task] = false;
                cout << "\nTask was added successfully ✓ \n";
            }
        }

        void toString(){
            for (const auto& task : tasks){
                char isChecked = (task.second)? '✓':'✗';
                cout << task.first << " " << isChecked << endl;
            }
            cout << endl;
        }

        void removeTask(string task){
            task = toLowerCase(task);
            if (tasks.count(task)){
                tasks.erase(task);
                cout << "Task was removed successfully ✓" << endl;
            }
            else{
                cout << "Task doesn't exist ✗" << endl;
            }
        }

        string toLowerCase(string &str){
            for (char &c : str){
                c = tolower(c);
            }
            return str;
        }

        void checkTask(string task){
            task = toLowerCase(task);
            if (tasks.count(task)){
                tasks[task] = true;
                cout << "Task was checked successfully ✓" << endl;
            }
            else {
                cout << "Task doesn't exist ✗" << endl;
            }
        };

};

int main(){
    TaskManager tasks;

    bool running = true;

    while (running){
        int scelta;

        cout << "--- Insert the choise ---\n";
        cout << "1) Add task\n";
        cout << "2) Remove task\n";
        cout << "3) Visualize all tasks\n";
        cout << "4) Exit\n";

        cin >> scelta;
        string task;
        switch (scelta){
            case 1:
                cout << "\n--- ADD ---\n";
                cout << "Insert the name of task: ";
                cin.ignore();
                getline(cin, task);
                tasks.addTask(task);
                break;

            case 2:
                cout << "\n--- REMOVE ---\n";
                cout << "Insert the name of task: ";
                cin.ignore();
                getline(cin, task);
                tasks.removeTask(task);
                break;

            case 3:
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
