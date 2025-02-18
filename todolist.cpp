#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Task {
    int id;
    string description;
    bool completed;
};

vector<Task> tasks;
const string FILE_NAME = "todo_list.txt";

void loadTasks() {
    ifstream file(FILE_NAME);
    tasks.clear();
    Task task;
    while (file >> task.id >> task.completed) {
        file.ignore();
        getline(file, task.description);
        tasks.push_back(task);
    }
    file.close();
}

void saveTasks() {
    ofstream file(FILE_NAME);
    for (const auto& task : tasks) {
        file << task.id << " " << task.completed << " " << task.description << endl;
    }
    file.close();
}

void addTask() {
    Task task;
    task.id = tasks.size() + 1;
    task.completed = false;
    cout << "Enter task description: ";
    cin.ignore();
    getline(cin, task.description);
    tasks.push_back(task);
    saveTasks();
    cout << "Task added successfully!\n";
}

void viewTasks() {
    cout << "\nTo-Do List:\n";
    for (const auto& task : tasks) {
        cout << task.id << ". " << (task.completed ? "[Done] " : "[Pending] ") << task.description << endl;
    }
}

void markTaskAsDone() {
    int id;
    cout << "Enter task ID to mark as done: ";
    cin >> id;
    if (id > 0 && id <= tasks.size()) {
        tasks[id - 1].completed = true;
        saveTasks();
        cout << "Task marked as completed!\n";
    } else {
        cout << "Invalid task ID!\n";
    }
}

void deleteTask() {
    int id;
    cout << "Enter task ID to delete: ";
    cin >> id;
    if (id > 0 && id <= tasks.size()) {
        tasks.erase(tasks.begin() + id - 1);
        for (int i = 0; i < tasks.size(); i++) {
            tasks[i].id = i + 1;
        }
        saveTasks();
        cout << "Task deleted successfully!\n";
    } else {
        cout << "Invalid task ID!\n";
    }
}

int main() {
    loadTasks();
    int choice;
    do {
        cout << "\nTo-Do List Menu:\n";
        cout << "1. Add Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Mark Task as Done\n";
        cout << "4. Delete Task\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addTask(); break;
            case 2: viewTasks(); break;
            case 3: markTaskAsDone(); break;
            case 4: deleteTask(); break;
            case 5: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice, try again!\n";
        }
    } while (choice != 5);
    return 0;
}
