#include "StudHelper.h"

//Initialize field for Singleton
StudHelper* StudHelper::m_instance = nullptr;
StudHelperDestroyer StudHelper::m_destroyer;

//Delete StudHelper object
StudHelperDestroyer::~StudHelperDestroyer() { delete m_instance; }

//Initialize StudHelper object
void StudHelperDestroyer::initialize(StudHelper* studh) { m_instance = studh; }

//Create StudHelper object
StudHelper& StudHelper::get_instance() {
//If object wasn't created, make new
    if(!m_instance) {
        m_instance = new StudHelper();

        m_destroyer.initialize(m_instance);
    }

    return* m_instance;
}

//Create new file
void StudHelper::create_file(const string& filename) {
//Create xlsx book
    m_book = xlCreateXMLBook();

//Set parameters (add sheet, set rows & cols, display grid lines, font & format are default)
    m_sheet = m_book->addSheet("Marks");
    m_sheet->insertRow(0, 255);
    m_sheet->insertCol(0, 255);
    m_sheet->setDisplayGridlines(true);

//Get username to create path
    char username[LOGIN_NAME_MAX];
    getlogin_r(username, LOGIN_NAME_MAX);

//Create path depending on the system language
    if(string lang = locale("").name(); lang.find("ru_") != string::npos)
        m_path.append("/home/").append(username).append("/Документы/").append(filename).append("SH.xlsx");
    else if (lang.find("en_") != string::npos)
        m_path.append("/home/").append(username).append("/Documents/").append(filename).append("SH.xlsx");
    else
        m_path = "";

//Save parameters and open it
    m_book->save(m_path.c_str());

    open_file(m_path);
}

//Open file
void StudHelper::open_file(const string& path) {
//If couldn't find file, return void
    if(!exists(path))
        return;

//Set path, create xlsx book, load file & get needed sheet
    m_path = path;

    m_book = xlCreateXMLBook();

    m_book->load(m_path.c_str());

    m_sheet = get_sheet_by_name(m_book, "Marks");
}

//Show file content
void StudHelper::read_file() {
//If sheet is existing, read it
    if(m_sheet) {
//Walk on every cell
        for(int row = m_sheet->firstRow(); row < m_sheet->lastRow(); ++row) {
            for(int col = m_sheet->firstCol(); col < m_sheet->lastCol(); ++col) {
//Get type of cell
                CellType cellType = m_sheet->cellType(row, col);

//Determine type of cell and print it
                switch(cellType) {
                    case CELLTYPE_NUMBER: {
                        double d = m_sheet->readNum(row, col);

                        cout << d;

                        break;
                    }
                    case CELLTYPE_STRING: {
                        const char* s = m_sheet->readStr(row, col);

                        cout << (s ? s : "null");

                        break;
                    }
                    case CELLTYPE_BOOLEAN: {
                        bool b = m_sheet->readBool(row, col);

                        cout << (b ? "true" : "false");

                        break;
                    }
                    case CELLTYPE_ERROR:
                        cout << "[error]";

                        break;
                    case CELLTYPE_BLANK:
                    case CELLTYPE_EMPTY:
                        continue;
                }

                cout << '\t';
            }

            cout << endl;
        }
    }
//If sheet isn't existing, return void
    else
        return;
}

//Write data into the file (need to be reworked)
void StudHelper::write_data(vector<double>& marks, const string& subj, bool has_subj = false) {
//Write subject names only in second row
        const int row = m_sheet->firstRow() + 1;
//Walk on every column
        for (int col = m_sheet->firstCol(), i = (int)marks.size() - 1; col < m_sheet->lastCol() || i >= 0; ++col, --i) {
//Determine type of cell
            CellType cellType = m_sheet->cellType(row, col);

//If the subject is existing, modify it
            if (has_subj) {
//If type of cell is string, check it
                if (cellType == CELLTYPE_STRING) {
//Read data from cell
                    const char* str = m_sheet->readStr(row, col);

//If data in the cell equals to given subject, modify rows below
                    if (get_all_to_uppercase(str) == get_all_to_uppercase(subj)) {
//Walk on every row below
                        for (int sub_row = row; sub_row < m_sheet->lastRow(); ++sub_row) {
//Get type of cell
                            CellType sub_cellType = m_sheet->cellType(sub_row, col);

//If cell is empty, fill it with give number
                            if (sub_cellType == CELLTYPE_BLANK || sub_cellType == CELLTYPE_EMPTY)
                                m_sheet->writeNum(sub_row, col, marks[i]);
                        }

                        break;
                    }
                }
            }
//If subject isn't existing, create it and fill
            else {
//If cell is empty, write there subject name
                if (cellType == CELLTYPE_EMPTY || cellType == CELLTYPE_BLANK) {
                    m_sheet->writeStr(row, col, subj.c_str());

//Fill cells below with given numbers
                    for (int sub_row = row; sub_row < m_sheet->lastRow(); ++sub_row)
                        m_sheet->writeNum(sub_row, col, marks[i]);

                    break;
                }
            }
        }

//Save the file
        m_book->save(m_path.c_str());
}

//Get marks of given subject
vector<unsigned> StudHelper::get_subject(const string& subj, bool get_sum = false) {
//Create vector to contain marks
    vector<unsigned> marks;

//If sheet is existing, read data
    if(m_sheet) {
//Early declaration of sum
        unsigned sum = 0;

//Walk on every cell in sheet
        for (int row = m_sheet->firstRow(); row < m_sheet->lastRow(); ++row) {
            for (int col = m_sheet->firstCol(); col < m_sheet->lastCol(); ++col) {
//Get type of cell
                CellType cellType = m_sheet->cellType(row, col);

//If type of cell is string, check this cell
                if (cellType == CELLTYPE_STRING) {
//Get data in cell
                    const char *s = m_sheet->readStr(row, col);

//If data in cell equals to given subject, read marks below
                    if (get_all_to_uppercase(s) == get_all_to_uppercase(subj)) {
//Walk on every cell below
                        for (int sub_row = m_sheet->firstRow(); sub_row < m_sheet->lastRow(); ++sub_row) {
//Get type of cell
                            CellType sub_cellType = m_sheet->cellType(sub_row, col);

//If type of cell is number, read data in cell
                            if (sub_cellType == CELLTYPE_NUMBER) {
                                double d = m_sheet->readNum(sub_row, col);

//Push mark in vector
                                marks.push_back(static_cast<unsigned>(d));

//If sum is needed, calculate it
                                if (get_sum)
                                    sum += static_cast<unsigned>(d);
                            }
                        }

                        break;
                    }
                }
            }
        }

//If sum is needed, print it
        if (get_sum)
            cout << "Sum of all " << subj << " marks: " << sum << endl;

//Return vector with marks
        return marks;
    }
//If sheet isn't existing, return empty vector
    else
        return marks;
}

//Get all needed information about given subject
void StudHelper::get_useful_information(const string& subj, bool has_exam = false, bool is_12_system = false) {
//Declare vector of marks and sum of them
    vector<unsigned> marks = get_subject(subj, true);
    unsigned sum = 0;

//Print all marks
    for(const auto& a: marks)
        cout << a << '\t';

    cout << endl;

//Get sum of all marks
    for(const auto& a : marks) {
        sum += a;

//Notify about bad marks
//For 12 pts system
        if(is_12_system && a < 4) {
            cout << a << " should be retaken!" << endl;
        }
//For 100 pts system
        else if(!is_12_system && a == 0)
            cout << a << " should be retaken!" << endl;
    }

//If sum of marks is less then is needed for credit, notify it
    if (sum < 60)
        cout << "You have to get " << 60 - sum << " points to get credit!" << endl;

//If exam is present and sum of marks is less than needed, notify it
    if(has_exam && sum < 21) {
        cout << "You have to get " << 21 - sum << " points to be allowed to the exam!" << endl;
    }
//If exam isn't present and sum of marks is less than is needed to be allowed for credit, notify it
    else if(!has_exam && sum < 30)
        cout << "You have to get " << 30 - sum << " points to be allowed to the credit!" << endl;
}

//Function-helper to get all characters in string to uppercase
string StudHelper::get_all_to_uppercase(string str) {
    for(auto& a : str)
        a = toupper(a);

    return str;
}

//Function-helper to get sheet from book by name
Sheet* StudHelper::get_sheet_by_name(Book* book, const char* name) {
    for(int i = 0; i < book->sheetCount(); ++i) {
        if(strcmp(book->getSheet(i)->name(), name) == 0)
            return book->getSheet(i);
    }

    return nullptr;
}

//Function-helper to track pressing on buttons
int getch() {
    struct termios oldattr, newattr;
    int ch;

    tcgetattr(STDIN_FILENO, &oldattr);

    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);

    return ch;
}