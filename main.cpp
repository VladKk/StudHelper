#include "StudHelper.h"

int main() {
    system("clear");

//Connection to the database
    cout << "\t\tWelcome to StudHelper!\t\t" << endl;
    cout << "Enter data to connect to database:" << endl;

    string dbname, name, password, hostaddr, port;

//Enter needed information
    cout << "Enter username: ";
    getline(cin, name);

//Get password (is hidden)
    password = getpass("Enter password: ");

    cout << "Enter database name: ";
    getline(cin, dbname);

//Enter IPv4 + check if it's right
    do {
        cout << "Enter host IPv4 address (enter 'd' to use localhost): ";
        getline(cin, hostaddr);

        if (hostaddr == "d")
            hostaddr = "127.0.0.1";
    } while(!is_ip(hostaddr));

//Eneter port + check if it's opened
    do {
        cout << "Enter port (enter 'd' to use default port): ";
        getline(cin, port);

        if (port == "d")
            port = "5432";
    } while(!is_port(hostaddr, port));

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

            if (int ch = getch(); ch == static_cast<int>('m'))
                goto preMenu;

            break;
        }
//Exit the program
        case static_cast<int>('e'):
            exit(EXIT_SUCCESS);
//If needed button wasn't pressed, retry
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

            if (int ch = getch(); ch == static_cast<int>('m'))
                goto createTable;

            break;
        }
//Exit the program
        case static_cast<int>('e'):
            exit(EXIT_SUCCESS);
//If needed button wasn't pressed, retry
        default:
            goto createTable;
    }

//Menu
    menu:
    system("clear");

    cout << "Press certain button to select function:" << endl;
    cout << "'d' - get data" << endl;
    cout << "'a' - add data" << endl;
    cout << "'x' - delete data" << endl;
    cout << "'c' - change data" << endl;
    cout << "'i' - get information (academic performance/connection/developer)" << endl;
    cout << "'e' - exit the program" << endl;

//Make choice depending on pressed button
    switch(getch()) {
//Get needed data
        case static_cast<int>('d'): {
            get_data_retry:
            system("clear");

            cout << "Press certain button to select function:" << endl;
            cout << "'a' - get all data" << endl;
            cout << "'s' - get certain subject" << endl;
            cout << "'m' - go to the menu" << endl;
            cout << "'e' - exit the program" << endl;

            switch(getch()) {
//Get all data
                case static_cast<int>('a'): {
                    system("clear");

                    stud_helper.get_data();

                    cout << "Press 'm' to go to the menu or any other button to exit the program" << endl;

                    if (int ch = getch(); ch == static_cast<int>('m'))
                        goto menu;

                    break;
                }
//Get only needed subject
                case static_cast<int>('s'): {
                    system("clear");

                    string subj;

                    cout << "Enter subject name: ";
                    getline(cin, subj);

                    stud_helper.get_subject(subj);

                    cout << "Press 'm' to go to the menu or any other button to exit the program" << endl;

                    if (int ch = getch(); ch == static_cast<int>('m'))
                        goto menu;

                    break;
                }
//Go to the menu
                case static_cast<int>('m'):
                    goto menu;
//Exit the program
                case static_cast<int>('e'):
                    exit(EXIT_SUCCESS);
//If needed button wasn't pressed, retry
                default:
                    goto get_data_retry;
            }

            break;
        }
//Add data to the table
        case static_cast<int>('a'): {
            system("clear");

            string subj;
            list<int> marks;

            cout << "Enter subject name: ";
            getline(cin, subj);

            cout << "Enter marks (enter 'd' when you done):" << endl;

            string temp;

//Add data to the list, as method works with it
            while(cout << "-> " && getline(cin, temp) && temp != "d")
                marks.push_back(stoi(temp));

            stud_helper.insert_data(marks, subj);

            goto menu;
        }
//Delete needed data from the table
        case static_cast<int>('x'): {
            delete_data_retry:
            system("clear");

            cout << "Press certain button to select function:" << endl;
            cout << "'s' - delete certain subject" << endl;
            cout << "'d' - delete certain mark" << endl;
            cout << "'m' - go to the menu" << endl;
            cout << "'e' - exit the program" << endl;

            switch(getch()) {
//Delete whole subject
                case static_cast<int>('s'): {
                    system("clear");

                    string subj;

                    cout << "Enter subject name: ";
                    getline(cin, subj);

                    stud_helper.delete_subject(subj);

                    goto menu;
                }
//Delete certain mark by its ID
                case static_cast<int>('d'): {
                    int id = 0;

                    cout << "Enter mark ID: ";
                    cin >> id;

                    stud_helper.delete_data(id);

                    goto menu;
                }
//Go to the menu
                case static_cast<int>('m'):
                    goto menu;
//Exit the program
                case static_cast<int>('e'):
                    exit(EXIT_SUCCESS);
//If needed button wasn't pressed, retry
                default:
                    goto delete_data_retry;
            }

            break;
        }
//Change mark by its ID
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
//Get needed information
        case static_cast<int>('i'): {
            info_retry:
            system("clear");

            cout << "Press certain button to select function:" << endl;
            cout << "'p' - get information about academic performance" << endl;
            cout << "'c' - get connection information" << endl;
            cout << "'d' - get information about developer" << endl;
            cout << "'m' - go to the menu" << endl;
            cout << "'e' - exit the program" << endl;

            switch(getch()) {
//Get information about yours academic performance
                case static_cast<int>('p'): {
                    system("clear");

                    string subj;

                    cout << "Enter subject name: ";
                    getline(cin, subj);

                    retryChoise:
                    system("clear");

                    cout << "Press certain button to select function:" << endl;
                    cout << "'y' - get progress information of given subject (exam is present)" << endl;
                    cout << "'n' - get progress information of given subject (exam isn't present)" << endl;
                    cout << "'m' - go to the menu" << endl;
                    cout << "'e' - exit the program" << endl;

                    switch(getch()) {
//Get information about yours academic performance considering if exam is presented in the subject
                        case static_cast<int>('y'): {
                           system("clear");

                            stud_helper.get_adv_info(subj, true);

                            cout << "Press 'm' to go to the menu or any other button to exit the program" << endl;

                            if (int ch = getch(); ch == static_cast<int>('m'))
                                goto menu;

                            break;
                        }
//Get information about yours academic performance considering if exam isn't presented in the subject
                        case static_cast<int>('n'): {
                            system("clear");

                            stud_helper.get_adv_info(subj, false);

                            cout << "Press 'm' to go to the menu or any other button to exit the program" << endl;

                            if (int ch = getch(); ch == static_cast<int>('m'))
                                goto menu;

                            break;
                        }
//Go to the menu
                        case static_cast<int>('m'):
                            goto menu;
//Exit the program
                        case static_cast<int>('e'):
                            exit(EXIT_SUCCESS);
//If needed button wasn't pressed, retry
                        default:
                            goto retryChoise;
                    }

                    break;
                }
//Get information about connection to database
                case static_cast<int>('c'): {
                    system("clear");

                    stud_helper.get_info();

                    cout << "Press 'm' to go to the menu or any other button to exit the program" << endl;

                    if (int ch = getch(); ch == static_cast<int>('m'))
                        goto menu;

                    break;
                }
//Get information about daveloper
                case static_cast<int>('d'): {
                    system("clear");

//Get current date and time
                    time_t time = system_clock::to_time_t(system_clock::now());

                    cout << "The program works with PostgreSQL" << endl;
                    cout << "If you have suggestions, write: mrvlad008@gmail.com" << endl;
                    cout << "Developer: Vladislav Koliadenko" << endl;
                    cout << "Current date/time: " << ctime(&time) << endl;
                    cout << "Press 'm' to go to the menu or any other button to exit the program" << endl;

                    if (int ch = getch(); ch == static_cast<int>('m'))
                        goto menu;

                    break;
                }
//Go to the menu
                case static_cast<int>('m'):
                    goto menu;
//Exit the program
                case static_cast<int>('e'):
                    exit(EXIT_SUCCESS);
//If needed button wasn't pressed, retry
                default:
                    goto info_retry;
            }

            break;
        }
//Exit the program
        case static_cast<int>('e'):
            exit(EXIT_SUCCESS);
//If needed button wasn't pressed, retry
        default:
            goto menu;
    }

    return 0;
}