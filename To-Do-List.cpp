#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    int Id;
    string title;
    string description;
    bool iscomplete;
    Node* next;
    Node* previous;

    Node(int I, string Title, string Description) {
        Id = I;
        title = Title;
        description = Description;
        iscomplete = false;
        next = nullptr;
        previous = nullptr;
    }
};

class ToDoList {
private:
    Node* head;

public:
    ToDoList() {
        head = nullptr;
    }

    void addTask(int I, string Title, string Description) {
        Node* newNode = new Node(I, Title, Description);
        if (head == nullptr) {
            head = newNode;
        }
        else {
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->previous = temp;
        }
        cout << "Task added successfully." << endl;
    }

    void editTask(int id, string newTitle, string newDescription) {
        if (head == nullptr) {
            cout << "No task available to edit." << endl;
            return;
        }
        Node* temp = head;
        while (temp) {
            if (temp->Id == id) {
                temp->title = newTitle;
                temp->description = newDescription;
                cout << "Task updated successfully." << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Task not found." << endl;
    }

    void markdone(int id)
    {
        Node* temp = head;
        while (temp) {
            if (temp->Id == id) {
                temp->iscomplete = true;
                cout << "Task marked as completed." << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Task not found." << endl;
    }

    void deleteTask(int id)
    {
        Node* temp = head;
        while (temp) {
            if (temp->Id == id) {
                if (temp->previous)
                {
                    temp->previous->next = temp->next;
                }
                else
                {
                    head = temp->next;
                }
                if (temp->next)
                {
                    temp->next->previous = temp->previous;
                }
                delete temp;
                cout << "Task deleted." << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Task not found." << endl;
    }

    void filterTasks(bool showCompleted)
    {
        Node* temp = head;
        bool found = false;
        while (temp) {
            if (temp->iscomplete == showCompleted) {
                cout << "ID: " << temp->Id << " | Title: " << temp->title << endl;
                found = true;
            }
            temp = temp->next;
        }
        if (!found)
        {
            cout << "No matching tasks found." << endl;
        }
    }

    void searchTask(int id) {
        if (head == nullptr) {
            cout << "No task available to edit." << endl;
            return;
        }
        Node* temp = head;
        while (temp) {
            if (temp->Id == id) {
                cout << "Title: " << temp->title << endl;
                cout << "Discription: " << temp->description << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Task not found." << endl;
    }

    void viewTasks() {
        if (head == nullptr) {
            cout << "No tasks available." << endl;
            return;
        }
        Node* temp = head;
        cout << "\n--- List of All Tasks ---\n";
        while (temp != nullptr) {
            cout << "---------------------------" << endl;
            cout << "Id: " << temp->Id << endl;
            cout << "Title: " << temp->title << endl;
            cout << "Description: " << temp->description << endl;
            cout << "Status: " << (temp->iscomplete ? "Completed" : "Pending") << endl;

            temp = temp->next;
        }
    }
};

int main() {
    ToDoList todo;
    string title, description;
    int choice, id;

    cout << "--------------- To-Do List Menu ---------------" << endl;

    while (true) {
        cout << "\n1. Add Task" << endl;
        cout << "2. Edit Task" << endl;
        cout << "3. Mark done task" << endl;
        cout << "4. Delete task" << endl;
        cout << "5. Filter task" << endl;
        cout << "6. Search task" << endl;
        cout << "7. View Tasks" << endl;
        cout << "0. Exit Program" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear newline from buffer

        switch (choice) {
        case 1:
            cout << "Enter task ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter task title: ";
            getline(cin, title);
            cout << "Enter task description: ";
            getline(cin, description);
            todo.addTask(id, title, description);
            break;

        case 2:
            cout << "Enter task ID to edit: ";
            cin >> id;
            cin.ignore();
            cout << "Enter new task title: ";
            getline(cin, title);
            cout << "Enter new task description: ";
            getline(cin, description);
            todo.editTask(id, title, description);
            break;

        case 3:
            cout << "Enter task ID to mark as completed: ";
            cin >> id;
            todo.markdone(id);
            break;

        case 4:
            cout << "Enter task ID to delete: ";
            cin >> id;
            todo.deleteTask(id);
            break;

        case 5:
            cout << "Enter 1 for completed tasks, 0 for pending tasks: ";
            cin >> id;
            todo.filterTasks(id);
            break;

        case 6:
            cout << "Enter task id: ";
            cin >> id;
            todo.searchTask(id);
            break;

        case 7:
            todo.viewTasks();
            break;

        case 0:
            cout << "----- Program Ended -----" << endl;
            return 0;

        default:
            cout << "Invalid choice. Try again." << endl;
        }
    }

    return 0;
}