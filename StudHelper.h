#ifndef STUDHELPER_H
#define STUDHELPER_H

#include <iostream>
#include <string>
#include <ctime>
#include <chrono>
#include <list>
#include <cstdlib>

#include <termios.h>
#include <unistd.h>

#include <pqxx/pqxx>

#include <arpa/inet.h>

#include <SFML/Network.hpp>

using namespace std;
using namespace chrono;
using namespace pqxx;
using namespace sf;

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
//Singleton fields
    static StudHelper* m_instance;
    static StudHelperDestroyer m_destroyer;

//Main fields
    string m_dbname;
    string m_name;
    string m_password;
    string m_hostaddr;
    string m_port;

//Getters
    string get_dbname() { return m_dbname; }
    string get_name() { return m_name; }
    string get_password() { return m_password; }
    string get_hostaddr() { return m_hostaddr; }
    string get_port() { return m_port; }

public:
//Block assignment & copying
    StudHelper(const StudHelper&) = delete;
    StudHelper& operator=(StudHelper&) = delete;

//Make class instance
    static StudHelper& get_instance(const string& dbname, const string& name, const string& password,
            const string& hostaddr, const string& port);

//Prototypes of main functions
    void check_connection();
    void create_table();
    void get_data();
    void get_subject(const string& subject);
    void insert_data(const list<int>& marks, const string& subject);
    void delete_data(const int& id);
    void delete_subject(const string& subject);
    void change_data(const int& id, const int& mark);
    void get_info();
    void get_adv_info(const string& subject, bool has_exam);
    bool check_table();

protected:
//Protect constructor & destructor from user
    StudHelper(string dbname, string name, string password, string hostaddr, string port)
        : m_dbname(move(dbname)), m_name(move(name)), m_password(move(password)),
          m_hostaddr(move(hostaddr)), m_port(move(port)) {}

    ~StudHelper() = default;

//Make destroyer class as friend
    friend class StudHelperDestroyer;
};

//Prototypes of functions-helpers
int getch();
bool is_port(const string& ip, const string& port);
bool is_ip(const string& ip);

#endif // STUDHELPER_H