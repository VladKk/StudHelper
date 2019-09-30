#include "StudHelper.h"

int main() {
    system("clear");

    cout << "\t\tWelcome to StudHelper!\t\t" << endl;
    cout << "Enter data to connect to database:" << endl;

    string dbname, name, password,
            hostaddr = "127.0.0.1",
            port = "5432";

    cout << "Enter username: ";
    cin >> name;
    cout << "Enter password: ";
    cin >> password;
    cout << "Enter database name: ";
    cin >> dbname;

//Create StudHelper object
    StudHelper& stud_helper = StudHelper::get_instance(dbname, name, password, hostaddr, port);

//PreMenu
    preMenu:
    system("clear");

    cout << "Press certain button to select function:" << endl;
    cout << "'c' - check connection" << endl;
    cout << "'h' - print help information" << endl;
    cout << "'e' - exit the program" << endl;

//Make choice depending on pressed button
    switch(getch()) {
//Check connection to database
        case static_cast<int>('c'): {
            system("clear");

            stud_helper.check_connection();

            if (stud_helper.check_table())
                goto menu;
            else
                goto createTable;
        }
//Print helpful information
        case static_cast<int>('h'): {
            system("clear");

//Get current date and time
            time_t time = system_clock::to_time_t(system_clock::now());

            cout << "The program works with PostgreSQL" << endl;
            cout << "If you have suggestions, write: mrvlad008@gmail.com" << endl;
            cout << "Developer: Vladislav Koliadenko" << endl;
            cout << "Current date/time: " << ctime(&time) << endl;
            cout << "Press 'm' to go to the menu or any other button to exit the program" << endl;

            int ch = getch();

            if (ch == static_cast<int>('m'))
                goto preMenu;

            break;
        }
//Exit the program
        case static_cast<int>('e'):
            exit(0);
//If needed button wasn't pressed, return to the pre menu
        default:
            goto preMenu;
    }

//Create table (if needed)
createTable:
    system("clear");

    cout << "Press certain button to select function:" << endl;
    cout << "'t' - create table (the table is missing)" << endl;
    cout << "'h' - print help information" << endl;
    cout << "'e' - exit the program" << endl;

//Make choice depending on pressed button
    switch(getch()) {
//Create table
        case static_cast<int>('t'): {
            system("clear");

            stud_helper.create_table();

            goto menu;
        }
//Print helpful information
        case static_cast<int>('h'): {
            system("clear");

//Get current date and time
            time_t time = system_clock::to_time_t(system_clock::now());

            cout << "The program works with PostgreSQL" << endl;
            cout << "If you have suggestions, write: mrvlad008@gmail.com" << endl;
            cout << "Developer: Vladislav Koliadenko" << endl;
            cout << "Current date/time: " << ctime(&time) << endl;
            cout << "Press 'm' to go to the menu or any other button to exit the program" << endl;

            int ch = getch();

            if (ch == static_cast<int>('m'))
                goto createTable;

            break;
        }
//Exit the program
        case static_cast<int>('e'):
            exit(0);
//If needed button wasn't pressed, return to the pre menu
        default:
            goto createTable;
    }

//Menu
    menu:
    system("clear");

    cout << "Press certain button to select function:" << endl;
    cout << "'d' - get data from table" << endl;
    cout << "'s' - get certain subject" << endl;
    cout << "'z' - delete certain subject" << endl;
    cout << "'a' - add marks to the table" << endl;
    cout << "'x' - delete mark from the table" << endl;
    cout << "'c' - change mark in the table" << endl;
    cout << "'p' - get progress information" << endl;
    cout << "'i' - get connection information" << endl;
    cout << "'h' - print help information" << endl;
    cout << "'e' - exit the program" << endl;

//Make choice depending on pressed button
    switch(getch()) {
//Create table
        case static_cast<int>('d'): {
            system("clear");

            stud_helper.get_data();

            cout << "Press 'm' to go to the menu or any other button to exit the program" << endl;

            int ch = getch();

            if (ch == static_cast<int>('m'))
                goto menu;

            break;
        }
        case static_cast<int>('s'): {
            system("clear");

            string subj;

            cout << "Enter subject name (use '_' instead of space): ";
            cin >> subj;

            stud_helper.get_subject(subj);

            cout << "Press 'm' to go to the menu or any other button to exit the program" << endl;

            int ch = getch();

            if (ch == static_cast<int>('m'))
                goto menu;

            break;
        }
        case static_cast<int>('z'): {
            system("clear");

            string subj;

            cout << "Enter subject name (use '_' instead of space): ";
            cin >> subj;

            stud_helper.delete_subject(subj);

            goto menu;
        }
        case static_cast<int>('a'): {
            system("clear");

            string subj;
            list<int> marks;

            cout << "Enter subject name (use '_' instead of space): ";
            cin >> subj;

            cout << "Enter marks (enter 'd' when you done):" << endl;

            while(true) {
                int temp = 0;

                cout << "-> ";
                cin >> temp;

                marks.push_back(temp);

                if(int ch = getchar(); ch == static_cast<int>('d'))
                    break;
            }

            marks.pop_back();

            stud_helper.insert_data(marks, subj);

            goto menu;
        }
        case static_cast<int>('x'): {
            system("clear");

            int id = 0;

            cout << "Enter mark ID: ";
            cin >> id;

            stud_helper.delete_data(id);

            goto menu;
        }
        case static_cast<int>('c'): {
            system("clear");

            int id = 0,
                mark = 0;

            cout << "Enter mark ID: ";
            cin >> id;
            cout << "Enter mark you want to change with: ";
            cin >> mark;

            stud_helper.change_data(id, mark);

            goto menu;
        }
        case static_cast<int>('p'): {
            system("clear");

            string subj;

            cout << "Enter subject name (use '_' instead of space): ";
            cin >> subj;

            retryChoise:
            system("clear");

            cout << "Press certain button to select function:" << endl;
            cout << "'h' - get progress information of given subject (exam is present)" << endl;
            cout << "'w' - get progress information of given subject (exam isn't present)" << endl;
            cout << "'m' - go to the menu" << endl;
            cout << "'e' - exit the program" << endl;

            switch(getch()) {
                case static_cast<int>('h'): {
                    system("clear");

                    stud_helper.get_adv_info(subj, true);

                    cout << "Press 'm' to go to the menu or any other button to exit the program" << endl;

                    int ch = getch();

                    if (ch == static_cast<int>('m'))
                        goto menu;

                    break;
                }
                case static_cast<int>('w'): {
                    system("clear");

                    stud_helper.get_adv_info(subj, false);

                    cout << "Press 'm' to go to the menu or any other button to exit the program" << endl;

                    int ch = getch();

                    if (ch == static_cast<int>('m'))
                        goto menu;

                    break;
                }
                case static_cast<int>('m'):
                    goto menu;
                case static_cast<int>('e'):
                    exit(0);
                default:
                    goto retryChoise;
            }

            break;
        }
        case static_cast<int>('i'): {
            system("clear");

            stud_helper.get_info();

            cout << "Press 'm' to go to the menu or any other button to exit the program" << endl;

            int ch = getch();

            if (ch == static_cast<int>('m'))
                goto menu;

            break;
        }
//Print helpful information
        case static_cast<int>('h'): {
            system("clear");

//Get current date and time
            time_t time = system_clock::to_time_t(system_clock::now());

            cout << "The program works with PostgreSQL" << endl;
            cout << "If you have suggestions, write: mrvlad008@gmail.com" << endl;
            cout << "Developer: Vladislav Koliadenko" << endl;
            cout << "Current date/time: " << ctime(&time) << endl;
            cout << "Press 'm' to go to the menu or any other button to exit the program" << endl;

            int ch = getch();

            if (ch == static_cast<int>('m'))
                goto menu;

            break;
        }
//Exit the program
        case static_cast<int>('e'):
            exit(0);
//If needed button wasn't pressed, return to the pre menu
        default:
            goto menu;
    }

    return 0;
}