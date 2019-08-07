#include "StudHelper.h"

void StudHelper::create_file(const string& filename) {
    m_book = xlCreateXMLBook();

    Sheet* sheet = m_book->addSheet("Marks");

    Font* textFont = m_book->addFont();
    textFont->setSize(12);
    textFont->setName("Arial");

    Format* textFormat = m_book->addFormat();
    textFormat->setFont(textFont);
    textFormat->setAlignH(ALIGNH_CENTER);
    textFormat->setAlignV(ALIGNV_CENTER);

    sheet->insertRow(0, 255);
    sheet->insertCol(0, 255);
    sheet->setDisplayGridlines(true);
    sheet->setCol(sheet->firstCol(), sheet->lastCol(), -1, textFormat);
    sheet->setRow(sheet->firstRow(), -1, textFormat);

    char username[LOGIN_NAME_MAX];
    getlogin_r(username, LOGIN_NAME_MAX);

    if(string lang = locale("").name(); lang.find("ru"))
        m_path = m_path + "/home/" + username + "/Документы/" + filename + "SH.xlsx";
    else if (lang.find("en"))
        m_path = m_path + "/home/" + username + "/Documents/" + filename + "SH.xlsx";
    else
        m_path = "";

    m_book->save(m_path.c_str());
}

void StudHelper::open_file(const string& path) {
    m_path = path;

    m_book = xlCreateXMLBook();

    m_book->load(m_path.c_str());
}

void StudHelper::read_file() {
    Sheet* sheet = get_sheet_by_name(m_book, "Marks");

    if(sheet) {
        for(int row = sheet->firstRow(); row < sheet->lastRow(); ++row) {
            for(int col = sheet->firstCol(); col < sheet->lastCol(); ++col) {
                CellType cellType = sheet->cellType(row, col);

                switch(cellType) {
                    case CELLTYPE_NUMBER: {
                        double d = sheet->readNum(row, col);

                        cout << d;

                        break;
                    }
                    case CELLTYPE_STRING: {
                        const char* s = sheet->readStr(row, col);

                        cout << (s ? s : "null");

                        break;
                    }
                    case CELLTYPE_BOOLEAN: {
                        bool b = sheet->readBool(row, col);

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
    else
        return;
}

void StudHelper::write_data(vector<double>& marks, const string& subj, bool has_subj = false) {
    Sheet* sheet = get_sheet_by_name(m_book, "Marks");

    if(sheet) {
        const int row = sheet->firstRow();

        for (int col = sheet->firstCol(), i = (int) marks.size() - 1; col < sheet->lastCol() || i >= 0; ++col, --i) {
            CellType cellType = sheet->cellType(row, col);

            if (has_subj) {
                if (cellType == CELLTYPE_STRING) {
                    const char *str = sheet->readStr(row, col);

                    if (get_all_to_uppercase(str) == get_all_to_uppercase(subj)) {
                        for (int sub_row = row; sub_row < sheet->lastRow(); ++sub_row) {
                            CellType sub_cellType = sheet->cellType(sub_row, col);

                            if (sub_cellType == CELLTYPE_BLANK || sub_cellType == CELLTYPE_EMPTY)
                                sheet->writeNum(sub_row, col, marks[i]);
                        }

                        break;
                    }
                }
            } else {
                if (cellType == CELLTYPE_EMPTY || cellType == CELLTYPE_BLANK) {
                    sheet->writeStr(row, col, subj.c_str());

                    for (int sub_row = row; sub_row < sheet->lastRow(); ++sub_row)
                        sheet->writeNum(sub_row, col, marks[i]);

                    break;
                }
            }
        }

        m_book->save(m_path.c_str());
    }
    else
        return;
}

vector<unsigned> StudHelper::get_subject(const string& subj, bool get_sum = false) {
    Sheet* sheet = get_sheet_by_name(m_book, "Marks");
    vector<unsigned> marks;

    if(sheet) {
        unsigned sum = 0;

        for (int row = sheet->firstRow(); row < sheet->lastRow(); ++row) {
            for (int col = sheet->firstCol(); col < sheet->lastCol(); ++col) {
                CellType cellType = sheet->cellType(row, col);

                if (cellType == CELLTYPE_STRING) {
                    const char *s = sheet->readStr(row, col);

                    if (get_all_to_uppercase(s) == get_all_to_uppercase(subj)) {
                        for (int sub_row = sheet->firstRow(); sub_row < sheet->lastRow(); ++sub_row) {
                            CellType sub_cellType = sheet->cellType(sub_row, col);

                            if (sub_cellType == CELLTYPE_NUMBER) {
                                double d = sheet->readNum(sub_row, col);

                                marks.push_back(static_cast<unsigned>(d));

                                if (get_sum)
                                    sum += static_cast<unsigned>(d);
                            }
                        }

                        break;
                    }
                }
            }
        }

        if (get_sum)
            cout << "Sum of all " << subj << " marks: " << sum << endl;

        return marks;
    }
    else
        return marks;
}

void StudHelper::get_useful_information(const string& subj, bool has_exam = false, bool is_12_system = false) {
    vector<unsigned> marks = get_subject(subj, true);
    unsigned sum = 0;

    for(const auto& a: marks)
        cout << a << '\t';

    cout << endl;

    for(const auto& a : marks) {
        sum += a;

        if(is_12_system && a < 4) {
            cout << a << " should be retaken!" << endl;
        }
        else if(!is_12_system && a == 0)
            cout << a << " should be retaken!" << endl;
    }

    if (sum < 60)
        cout << "You have to get " << 60 - sum << " points to get credit!" << endl;

    if(has_exam && sum < 21) {
        cout << "You have to get " << 21 - sum << " points to be allowed to the exam!" << endl;
    }
    else if(!has_exam && sum < 30)
        cout << "You have to get " << 30 - sum << " points to be allowed to the credit!" << endl;
}

string StudHelper::get_all_to_uppercase(string str) {
    for(auto& a : str)
        a = toupper(a);

    return str;
}

Sheet* StudHelper::get_sheet_by_name(Book* book, const char* name) {
    for(int i = 0; i < book->sheetCount(); ++i) {
        if(strcmp(book->getSheet(i)->name(), name) == 0)
            return book->getSheet(i);
    }

    return nullptr;
}

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