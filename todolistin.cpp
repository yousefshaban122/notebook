#include <iostream>
#include <vector>

#ifdef _WIN32  
    #include <cstdlib>
#endif

using namespace std;

struct ToDoList {
    vector<int> days;
    vector<vector<string>> tasks;  // كل يوم يحتوي على قائمة من المهام
    vector<vector<string>> finish; // المهام المكتملة لكل يوم
} List;

// Function prototypes
void show_result();
void Featuresmenu();
void Search_for_day();
void Delete_a_task();
void View_all_task();
void display_all_task_finish();
void add_a_task();
void display_all_days();

void ShowScreen() {
    cout << "\t\t_____________________________________________________________________________________\n\n";
    cout << "                        \t               To-Do List Manager            \n";
    cout << "\t\t_____________________________________________________________________________________\n\n";
    Featuresmenu();
}

void Featuresmenu() {
    cout << "\n1. Search for day\n";
    cout << "2. Add a task \n";
    cout << "3. Delete a task \n";
    cout << "4. View all tasks \n";
    cout << "5. Display all days \n";
    cout << "6. Display all tasks finished \n";
    cout << "7. Exit\n";

    int choice;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            Search_for_day();
            break;
        case 2:
            add_a_task();
            break;
        case 3:
            Delete_a_task();
            break;
        case 4:
            View_all_task();
            break;
        case 5:
            display_all_days();
            break;
        case 6:
            display_all_task_finish();
            break;
        case 7:
            cout << "Exiting program...\n";
#ifdef _WIN32
            system("cls");  // مسح الشاشة في Windows
#else
            system("clear"); // مسح الشاشة في Linux
#endif
            return;
        default:
            cout << "Invalid choice! Please enter a number between 1 and 7.\n";
            break;
    }

    Featuresmenu();  // Call menu again for another selection
}

void Search_for_day() {
    cout << "Enter the day to search: ";
    int day_search;
    cin >> day_search;

    bool found = false;
    for (size_t i = 0; i < List.days.size(); i++) {
        if (List.days[i] == day_search) {
            found = true;
            cout << "Day: " << List.days[i] << endl;

            cout << "Tasks: \n";
            for (size_t j = 0; j < List.tasks[i].size(); j++) {
                cout << "- " << List.tasks[i][j] << endl;
            }
     
                 //  عرض المهام المكتمله ف نفس اليوم 
            cout << "Finished Tasks: \n"; 
            if ( List.finish[i].size() < 0)
          {  
              cout << " No mission is finished " ; 
          }
            else
        {
            for (size_t j = 0; j < List.finish[i].size(); j++) {
                cout << "- " << List.finish[i][j] << " (Completed)" << endl;
            }
        }

            break;
        }
    }

    if (!found) {
        cout << "That day does not exist!\n";
    }
}

// إضافة مهمة ليوم معين
void add_a_task() {
    cout << "Enter the day to add a task: ";
    int day;
    cin >> day;

    cout << "Enter task description: ";
    string task;
    cin.ignore(); //  عشان ادخل مسافه مع اسم المهمه 
    getline(cin, task);

    bool dayExists = false;
    for (size_t i = 0; i < List.days.size(); i++) {
        if (List.days[i] == day) {
            List.tasks[i].push_back(task);
            dayExists = true;
            break;
        }
    }

    if (!dayExists) {
        List.days.push_back(day);
        List.tasks.push_back({task});
        List.finish.push_back({});
    }

    cout << "Task added successfully!\n";
}

// حذف مهمة من يوم معين
void Delete_a_task() {
    cout << "Enter the day to delete a task from: ";
    int day;
    cin >> day;

    for (size_t i = 0; i < List.days.size(); i++) {
        if (List.days[i] == day) {
            cout << "Select task number to delete:\n";
            for (size_t j = 0; j < List.tasks[i].size(); j++) {
                cout << j + 1 << ". " << List.tasks[i][j] << endl;
            }

            int taskIndex;
            cin >> taskIndex;
            if (taskIndex > 0 && taskIndex <= List.tasks[i].size()) {
                List.tasks[i].erase(List.tasks[i].begin() + (taskIndex - 1));
                cout << "Task deleted successfully!\n";
            } else {
                cout << "Invalid task number.\n";
            }
            return;
        }
    }

    cout << "That day does not exist!\n";
}

// عرض كل المهام
void View_all_task() {
    if (List.days.empty()) {
        cout << "No tasks available.\n";
        return;
    }

    for (size_t i = 0; i < List.days.size(); i++) {
        cout << "Day: " << List.days[i] << endl;
        for (size_t j = 0; j < List.tasks[i].size(); j++) {
            cout << "- " << List.tasks[i][j] << endl;
        }
        cout << endl;
    }
}

// عرض جميع الأيام
void display_all_days() {
    if (List.days.empty()) {
        cout << "No days recorded.\n";
        return;
    }

    cout << "Days with tasks:\n";
    for (int day : List.days) {
        cout << "- " << day << endl;
    }
}

// عرض المهام المكتملة
void display_all_task_finish() {
    if (List.days.empty()) {
        cout << "No completed tasks available.\n";
        return;
    }

    for (size_t i = 0; i < List.days.size(); i++) {
        cout << "Day: " << List.days[i] << endl;
        for (size_t j = 0; j < List.finish[i].size(); j++) {
            cout << "- " << List.finish[i][j] << " (Completed)" << endl;
        }
        cout << endl;
    }
}

int main() {
    ShowScreen();
    return 0;
}
