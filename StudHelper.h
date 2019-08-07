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

#include <termios.h>
#include <unistd.h>

#include "libxl.h"

using namespace std;
using namespace chrono;
using namespace libxl;

class StudHelper {
private:
    string m_path;
    Book* m_book;
    Sheet* m_sheet;

    static string get_all_to_uppercase(string str);
    static Sheet* get_sheet_by_name(Book* book, const char* name);

public:
    StudHelper() : m_path(""), m_book(nullptr), m_sheet(nullptr) {}

    ~StudHelper() { m_book->save(m_path.c_str()); m_book->release(); }

    string get_path() { return m_path; }

    void create_file(const string& filename);

    void open_file(const string& path);

    void read_file();

    void write_data(vector<double>& marks, const string& subj, bool has_subj);

    vector<unsigned> get_subject(const string& subj, bool get_sum);

    void get_useful_information(const string& subj, bool has_exam, bool is_12_system);
};

int getch();

#endif // STUDHELPER_H