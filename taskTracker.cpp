#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Task {
    string description;
    string status;  // "ToDo", "InProgress", "Done"
};


void addTask(vector<Task>& tasks) {
    string description;
    cout << "Enter task description: ";
    cin.ignore();  
    getline(cin, description);  

    Task newTask;
    newTask.description = description;
    newTask.status = "ToDo";  
    tasks.push_back(newTask);

    cout << "Task added successfully!" << endl;
}


void listTasks(const vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "No tasks available." << endl;
        return;
    }
    for (size_t i = 0; i < tasks.size(); ++i) {
        cout << i + 1 << ". " << tasks[i].description << " [" << tasks[i].status << "]" << endl;
    }
}


void markTaskDone(vector<Task>& tasks, int index) {
    if (index <= 0 || index > tasks.size()) {
        cout << "Invalid task number." << endl;
        return;
    }
    tasks[index - 1].status = "Done";
    cout << "Task marked as Done!" << endl;
}


void loadTasks(vector<Task>& tasks, const string& filename) {
    ifstream infile(filename);
    if (!infile) {
        cout << "No previous task file found. Starting fresh." << endl;
        return;
    }

    string description, status;
    while (getline(infile, description)) {
        getline(infile, status);
        Task task;
        task.description = description;
        task.status = status;
        tasks.push_back(task);
    }
    infile.close();
}


void saveTasks(const vector<Task>& tasks, const string& filename) {
    ofstream outfile(filename);
    for (const auto& task : tasks) {
        outfile << task.description << endl;
        outfile << task.status << endl;
    }
    outfile.close();
}

int main() {
    vector<Task> tasks;
    const string filename = "tasks.txt";


    loadTasks(tasks, filename);
    string command;
    while (true) {
        cout << "Enter command (add/list/done/exit): ";
        cin >> command;

        if (command == "add") {
            addTask(tasks);
        } else if (command == "list") {
            listTasks(tasks);
        } else if (command == "done") {
            int index;
            cout << "Enter task number: ";
            cin >> index;
            markTaskDone(tasks, index);
        } else if (command == "exit") {
            saveTasks(tasks, filename);
            cout << "Tasks saved! Exiting..." << endl;
            break;
        } else {
            cout << "Unknown command. Try again." << endl;
        }
    }

    return 0;
}

