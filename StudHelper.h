#ifndef STUDHELPER_H
#define STUDHELPER_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cctype>
#include <vector>
#include <cstdio>
#include <stdexcept>
#include <ctime>
#include <chrono>
#include <climits>
#include <algorithm>
#include <locale>
#include <filesystem>

#include <termios.h>
#include <unistd.h>

#include "libxl.h"

using namespace std;
using namespace filesystem;
using namespace chrono;
using namespace libxl;

//Using Singleton to create object
class StudHelper;

class StudHelperDestroyer {
private:
    StudHelper* m_instance;

public:
    ~StudHelperDestroyer();

    void initialize(StudHelper* studh);
};

class StudHelper {
private:
    static StudHelper* m_instance;
    static StudHelperDestroyer m_destroyer;

    string m_path;
    Book* m_book;
    Sheet* m_sheet;

//Functions-helpers
    static string get_all_to_uppercase(string str);
    static Sheet* get_sheet_by_name(Book* book, const char* name);

public:
//Block assignment & copying
    StudHelper(const StudHelper&) = delete;
    StudHelper& operator=(StudHelper&) = delete;

    static StudHelper& get_instance();

    string get_path() { return m_path; }

    void create_file(const string& filename);

    void open_file(const string& path);

    void read_file();

    void write_data(vector<double>& marks, const string& subj, bool has_subj);

    vector<unsigned> get_subject(const string& subj, bool get_sum);

    void get_useful_information(const string& subj, bool has_exam, bool is_12_system);

protected:
//Protect constructor & destructor from client
    StudHelper() : m_path(""), m_book(nullptr), m_sheet(nullptr) {}

    ~StudHelper() { m_book->save(m_path.c_str()); m_book->release(); }

    friend class StudHelperDestroyer;
};

int getch();

#endif // STUDHELPER_H