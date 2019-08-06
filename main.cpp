#include "StudHelper.h"

int main() {
    StudHelper stud_helper;

preMenu:
    system("clear");

    cout << "\tWelcome to StudHelper!" << endl;
    cout << "Press certain button to select function:" << endl;
    cout << "'n' - create new file" << endl;
    cout << "'o' - open existing file (with SH.xlsx extension only)" << endl;
    cout << "'h' - print help information" << endl;
    cout << "'e' - exit the program" << endl;

    switch(getch()) {
        case static_cast<int>('n'): {
            system("clear");

            string filename;

            cout << "Enter here name of file: ";
            getline(cin, filename);

            stud_helper.create_file(filename);

            system("clear");

            if(stud_helper.get_path().empty() || stud_helper.get_path().find("SH.xlsx") == string::npos) {
                cerr << "Couldn't create file!" << endl;

                exit(0);
            }
            else
                cout << "File path: " << stud_helper.get_path() << endl;

            cout << "Press 'm' to go to the menu or any other button to exit the program" << endl;

            if (int ch = getch(); ch == static_cast<int>('m'))
                goto menu;

            break;
        }
        case static_cast<int>('o'): {
            system("clear");

            string path;

            cout << "Enter here path to file: ";
            getline(cin, path);

            stud_helper.open_file(path);

            system("clear");

            if(stud_helper.get_path().empty() || stud_helper.get_path().find("SH.xlsx") == string::npos) {
                cerr << "Couldn't open file!" << endl;

                exit(0);
            }
            else
                cout << "File was opened successfully!" << endl;

            cout << "Press 'm' to go to the menu or any other button to exit the program" << endl;

            if (int ch = getch(); ch == static_cast<int>('m'))
                goto menu;

            break;
        }
        case static_cast<int>('h'): {
            system("clear");

            time_t time = system_clock::to_time_t(system_clock::now());

            cout << "The program works only with MS Excel files" << endl;
            cout << "If you have suggestions, write: mrvlad008@gmail.com" << endl;
            cout << "Developer: Vladislav Koliadenko" << endl;
            cout << "Current date/time: " << ctime(&time) << endl;
            cout << "Press 'm' to go to the menu or any other button to exit the program" << endl;

            if (int ch = getch(); ch == static_cast<int>('m'))
                goto preMenu;

            break;
        }
        case static_cast<int>('e'):
            exit(0);
        default:
            goto preMenu;
    }

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
        case static_cast<int>('f'): {
            system("clear");

            stud_helper.read_file();

            cout << "Press 'm' to go to the menu or any other button to exit the program: ";

            if (int ch = getch(); ch == static_cast<int>('m'))
                goto menu;

            break;
        }
        case static_cast<int>('w'): {
        retryWrite:
            system("clear");

            cout << "Press certain button to select function:" << endl;
            cout << "'s' - add marks to existing subject" << endl;
            cout << "'n' - add new subject with marks" << endl;
            cout << "'m' - go to menu" << endl;
            cout << "'e' - exit the program" << endl;

            switch(getch()) {
                case static_cast<int>('s'): {
                    system("clear");

                    vector<double> marks;
                    string subj;

                    cout << "Enter name of subject to be modified: ";
                    getline(cin, subj);
                    cout << "Now enter marks to be added (press 'd' when you've done):" << endl;

                    while(true) {
                        int num = 0;

                        cout << "-> ";
                        cin >> num;

                        marks.push_back(num);

                        if(int ch = getch(); ch == static_cast<int>('d'))
                            break;
                    }

                    reverse(marks.begin(), marks.end());

                    stud_helper.write_data(marks, subj, true);

                    cout << "Press 'm' to go to the menu or any other button to exit the program: ";

                    if (int ch = getch(); ch == static_cast<int>('m'))
                        goto menu;

                    break;
                }
                case static_cast<int>('n'): {
                    system("clear");

                    vector<double> marks;
                    string subj;

                    cout << "Enter name of subject to be added: ";
                    getline(cin, subj);
                    cout << "Now enter marks to be added (press 'd' when you've done):" << endl;

                    while(true) {
                        int num = 0;

                        cout << "-> ";
                        cin >> num;

                        marks.push_back(num);

                        if(int ch = getch(); ch == static_cast<int>('d'))
                            break;
                    }

                    reverse(marks.begin(), marks.end());

                    stud_helper.write_data(marks, subj, false);

                    cout << "Press 'm' to go to the menu or any other button to exit the program: ";

                    if (int ch = getch(); ch == static_cast<int>('m'))
                        goto menu;

                    break;
                }
                case static_cast<int>('m'):
                    goto menu;
                case static_cast<int>('e'):
                    exit(0);
                default:
                    goto retryWrite;
            }

            break;
        }
        case static_cast<int>('s'): {
            retrySum:
            system("clear");

            string subj;

            cout << "Enter name of subject to be shown: ";
            getline(cin, subj);

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
                case static_cast<int>('s'): {
                    system("clear");

                    cout << "Marks of " << subj << ':' << endl;

                    for (const auto &a : stud_helper.get_subject(subj, true))
                        cout << a << '\t';

                    cout << endl;
                    cout << "Press 'm' to go to the menu or any other button to exit the program" << endl;

                    if (int ch = getch(); ch == static_cast<int>('m'))
                        goto menu;

                    break;
                }
                case static_cast<int>('o'): {
                    system("clear");

                    cout << "Marks of " << subj << ':' << endl;

                    for (const auto &a : stud_helper.get_subject(subj, false))
                        cout << a << '\t';


                    cout << endl;
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
                    goto retrySum;
            }
        }
        case static_cast<int>('i'): {
            retryInfo:
            system("clear");

            string subj;

            cout << "Enter name of subject to be shown: ";
            getline(cin, subj);

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
        case static_cast<int>('p'): {
            system("clear");

            cout << "File path: " << stud_helper.get_path() << endl;
            cout << "Press 'm' to go to the menu or any other button to exit the program" << endl;

            if (int ch = getch(); ch == static_cast<int>('m'))
                goto menu;

            break;
        }
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
        case static_cast<int>('e'):
            exit(0);
        default:
            goto menu;
    }

    return 0;
}