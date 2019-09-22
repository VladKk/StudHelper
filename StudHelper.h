#ifndef STUDHELPER_H
#define STUDHELPER_H

#include <iostream>

#include <termios.h>
#include <unistd.h>

#include <pqxx/pqxx>

using namespace std;
using namespace pqxx;

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

public:
//Block assignment & copying
    StudHelper(const StudHelper&) = delete;
    StudHelper& operator=(StudHelper&) = delete;

    static StudHelper& get_instance();

protected:
//Protect constructor & destructor from client
    StudHelper() = default;

    ~StudHelper() = default;

    friend class StudHelperDestroyer;
};

int getch();

#endif // STUDHELPER_H