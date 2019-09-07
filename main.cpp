#include "StudHelper.h"

int main() {
//Create object of StudHelper
    StudHelper& stud_helper = StudHelper::get_instance();

//Pre menu
preMenu:
    system("clear");

    cout << "\tWelcome to StudHelper!" << endl;
    cout << "Press certain button to select function:" << endl;
    cout << "'n' - create new file" << endl;
    cout << "'o' - open existing file (with SH.xlsx extension only)" << endl;
    cout << "'h' - print help information" << endl;
    cout << "'e' - exit the program" << endl;

//Make choice depending on pressed button
    switch(getch()) {
//Creating new file
        case static_cast<int>('n'): {
            system("clear");

            string filename;

//Get name of file
            cout << "Enter here name of file: ";
            getline(cin, filename);

//Create new file
            stud_helper.create_file(filename);

            system("clear");

//If file couldn't be created, exit the program
            if(stud_helper.get_path().empty() || stud_helper.get_path().find("SH.xlsx") == string::npos) {
                cerr << "Couldn't create file!" << endl;

                exit(0);
            }
//Otherwise show file path
            else
                cout << "File path: " << stud_helper.get_path() << endl;

//Get to the menu or exit the program
            cout << "Press 'm' to go to the menu or any other button to exit the program" << endl;

            if (int ch = getch(); ch == static_cast<int>('m'))
                goto menu;

            break;
        }
//Open existing file
        case static_cast<int>('o'): {
            system("clear");

            string path;

//Get path to file
            cout << "Enter here path to file: ";
            getline(cin, path);

//Open file
            stud_helper.open_file(path);

            system("clear");

//If file couldn't be created, exit the program
            if(stud_helper.get_path().empty() || stud_helper.get_path().find("SH.xlsx") == string::npos) {
                cerr << "Couldn't open file!" << endl;

                exit(0);
            }
//Otherwise notify about successful opening
            else
                cout << "File was opened successfully!" << endl;

//Go to the menu or exit the program
            cout << "Press 'm' to go to the menu or any other button to exit the program" << endl;

            if (int ch = getch(); ch == static_cast<int>('m'))
                goto menu;

            break;
        }
//Print helpful information
        case static_cast<int>('h'): {
            system("clear");

//Get current date and time
            time_t time = system_clock::to_time_t(system_clock::now());

//Print helpful information
            cout << "The program works only with MS Excel files" << endl;
            cout << "If you have suggestions, write: mrvlad008@gmail.com" << endl;
            cout << "Developer: Vladislav Koliadenko" << endl;
            cout << "Current date/time: " << ctime(&time) << endl;
//Go to the menu or exit the program
            cout << "Press 'm' to go to the menu or any other button to exit the program" << endl;

            if (int ch = getch(); ch == static_cast<int>('m'))
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

//Menu
menu:
    system("clear");

    cout << "Press certain button to select function:" << endl;
    cout << "'f' - show file content" << endl;
    cout << "'w' - add subject with marks/marks to given subject" << endl;
    cout << "'s' - get all marks of given subject" << endl;
    cout << "'i' - get useful information about given subject" << endl;
    cout << "'p' - get file path" << endl;
    cout << "'h' - print help information" << endl;
    cout << "'e' - exit the program" << endl;

    switch(getch()) {
//Show file content
        case static_cast<int>('f'): {
            system("clear");

//Read file
            stud_helper.read_file();

//Go to the menu or exit the program
            cout << "Press 'm' to go to the menu or any other button to exit the program" << endl;

            if (int ch = getch(); ch == static_cast<int>('m'))
                goto menu;

            break;
        }
//Write data into the file
        case static_cast<int>('w'): {
        retryWrite:
            system("clear");

            cout << "Press certain button to select function:" << endl;
            cout << "'s' - add marks to existing subject" << endl;
            cout << "'n' - add new subject with marks" << endl;
            cout << "'m' - go to menu" << endl;
            cout << "'e' - exit the program" << endl;

            switch(getch()) {
//Add marks to existing subject
                case static_cast<int>('s'): {
                    system("clear");

                    vector<double> marks;
                    string subj;

//Get name of subject
                    cout << "Enter name of subject to be modified: ";
                    cin.ignore();
                    getline(cin, subj);
                    cout << "Now enter marks to be added (press 'd' when you've done):" << endl;

//Get marks to be added
                    while(true) {
                        int num = 0;

                        cout << "-> ";
                        cin >> num;

                        marks.push_back(num);

//If 'd' was pressed, exit the cycle
                        if(int ch = getch(); ch == static_cast<int>('d'))
                            break;
                    }

//Reverse marks for easier filling
                    reverse(marks.begin(), marks.end());

//Write data into the file
                    stud_helper.write_data(marks, subj, true);

//Go to the menu or exit the program
                    cout << "Press 'm' to go to the menu or any other button to exit the program" << endl;

                    if (int ch = getch(); ch == static_cast<int>('m'))
                        goto menu;

                    break;
                }
//Add new subject with marks
                case static_cast<int>('n'): {
                    system("clear");

                    vector<double> marks;
                    string subj;

//Get name of the subject
                    cout << "Enter name of subject to be added: ";
                    getline(cin, subj);
                    cout << "Now enter marks to be added (enter 'd' when you've done):" << endl;

//Get marks to be added
                    while(true) {
                        int num = 0;

                        cout << "-> ";
                        cin >> num;

                        marks.push_back(num);

//If 'd' button was pressed, exit the cycle
                        if(int ch = getch(); ch == static_cast<int>('d'))
                            break;
                    }

//Reverse marks for easier filling
                    reverse(marks.begin(), marks.end());

//Write data into the file
                    stud_helper.write_data(marks, subj, false);

//Go to the menu or exit the program
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
                    exit(0);
//If needed button wasn't pressed, retry
                default:
                    goto retryWrite;
            }

            goto menu;
        }
//Get marks of given subject
        case static_cast<int>('s'): {
            retrySum:
            system("clear");

            string subj;

//Get name of subject
            cout << "Enter name of subject to be shown: ";
            getline(cin, subj);

//If subject doesn't exist, go to the menu or exit the program
            if(stud_helper.get_subject(subj, false).empty()) {
                cerr << "Couldn't find given subject!" << endl;
                retryErr1:
                cout << "Press 'm' to go to the menu 'e' to exit the program" << endl;

                switch(getch()) {
                    case static_cast<int>('m'):
                        goto menu;
                    case static_cast<int>('e'):
                        exit(0);
                    default:
                        system("clear");

                        cerr << "Invalid input!" << endl;

                        goto retryErr1;
                }
            }

            cout << "Press certain button to select function:" << endl;
            cout << "'s' - print sum of marks of " << subj << endl;
            cout << "'o' - get only marks" << endl;
            cout << "'m' - go to menu" << endl;
            cout << "'e' - exit the program" << endl;

            switch (getch()) {
//Print marks with sum of them
                case static_cast<int>('s'): {
                    system("clear");

                    cout << "Marks of " << subj << ':' << endl;

                    for (const auto &a : stud_helper.get_subject(subj, true))
                        cout << a << '\t';

                    cout << endl;
//Go to the menu or exit the program
                    cout << "Press 'm' to go to the menu or any other button to exit the program" << endl;

                    if (int ch = getch(); ch == static_cast<int>('m'))
                        goto menu;

                    break;
                }
//Get only marks without sum of them
                case static_cast<int>('o'): {
                    system("clear");

                    cout << "Marks of " << subj << ':' << endl;

                    for (const auto &a : stud_helper.get_subject(subj, false))
                        cout << a << '\t';


                    cout << endl;
//Go to the menu ot exit the program
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
                    exit(0);
//If needed button wasn't pressed, retry
                default:
                    goto retrySum;
            }
        }
//Get useful information about given subject
        case static_cast<int>('i'): {
            retryInfo:
            system("clear");

            string subj;

//Get name of subject
            cout << "Enter name of subject to be shown: ";
            getline(cin, subj);

//If subject doesn't exist, go to the menu or exit the program
            if(stud_helper.get_subject(subj, false).empty()) {
                cerr << "Couldn't find given subject!" << endl;
                retryErr2:
                cout << "Press 'm' to go to the menu 'e' to exit the program" << endl;

                switch(getch()) {
                    case static_cast<int>('m'):
                        goto menu;
                    case static_cast<int>('e'):
                        exit(0);
                    default:
                        system("clear");

                        cerr << "Invalid input!" << endl;

                        goto retryErr2;
                }
            }

            cout << "Press  certain button to select function:" << endl;
            cout << "'b' - get useful information (using 12 pts system & exam is present)" << endl;
            cout << "'s' - get useful information (using 12 pts system & exam isn't present)" << endl;
            cout << "'p' - get useful information (using 100 pts system & exam is present)" << endl;
            cout << "'n' - get useful information (using 100 pts system & exam isn't present)" << endl;
            cout << "'m' - go to menu" << endl;
            cout << "'e' - exit the program" << endl;

//Get useful information for different cases (12/100 pts system, exam is/isn't present)
            switch (getch()) {
                case static_cast<int>('b'): {
                    system("clear");

                    stud_helper.get_useful_information(subj, true, true);

                    cout << "Press 'm' to go to the menu or any other button to exit the program" << endl;

                    if (int ch = getch(); ch == static_cast<int>('m'))
                        goto menu;

                    break;
                }
                case static_cast<int>('s'): {
                    system("clear");

                    stud_helper.get_useful_information(subj, false, true);

                    cout << "Press 'm' to go to the menu or any other button to exit the program" << endl;

                    if (int ch = getch(); ch == static_cast<int>('m'))
                        goto menu;

                    break;
                }
                case static_cast<int>('p'): {
                    system("clear");

                    stud_helper.get_useful_information(subj, true, false);

                    cout << "Press 'm' to go to the menu or any other button to exit the program" << endl;

                    if (int ch = getch(); ch == static_cast<int>('m'))
                        goto menu;

                    break;
                }
                case static_cast<int>('n'): {
                    system("clear");

                    stud_helper.get_useful_information(subj, false, false);

                    cout << "Press 'm' to go to the menu or any other button to exit the program" << endl;

                    if (int ch = getch(); ch == static_cast<int>('m'))
                        goto menu;

                    break;
                }
                case static_cast<int>('m'):
                    system("clear");

                    goto menu;
                case static_cast<int>('e'):
                    exit(0);
                default:
                    goto retryInfo;
            }
        }
//Get path to working file
        case static_cast<int>('p'): {
            system("clear");

            cout << "File path: " << stud_helper.get_path() << endl;
            cout << "Press 'm' to go to the menu or any other button to exit the program" << endl;

            if (int ch = getch(); ch == static_cast<int>('m'))
                goto menu;

            break;
        }
//Get help info for this program
        case static_cast<int>('h'): {
            system("clear");

            time_t time = system_clock::to_time_t(system_clock::now());

            cout << "The program works only with MS Excel files" << endl;
            cout << "If you have suggestions, write: mrvlad008@gmail.com" << endl;
            cout << "Developer: Vladislav Koliadenko" << endl;
            cout << "Current date/time: " << ctime(&time) << endl;
            cout << "Press 'm' to go to the menu or any other button to exit the program" << endl;

            if (int ch = getch(); ch == static_cast<int>('m'))
                goto menu;

            break;
        }
//Exit the program
        case static_cast<int>('e'):
            exit(0);
//If needed button wasn't pressed, retry
        default:
            goto menu;
    }

    return 0;
}