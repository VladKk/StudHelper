#include "StudHelper.h"

//Initialize field for Singleton
StudHelper* StudHelper::m_instance = nullptr;
StudHelperDestroyer StudHelper::m_destroyer;

//Delete StudHelper object
StudHelperDestroyer::~StudHelperDestroyer() { delete m_instance; }

//Initialize StudHelper object
void StudHelperDestroyer::initialize(StudHelper* studh) { m_instance = studh; }

//Create StudHelper object
StudHelper& StudHelper::get_instance(const string& dbname, const string& name, const string& password,
        const string& hostaddr = "127.0.0.1", const string& port = "5432") {
//If object wasn't created, make new
    if(!m_instance) {
        m_instance = new StudHelper(dbname, name, password, hostaddr, port);

        m_destroyer.initialize(m_instance);
    }

    return* m_instance;
}

//Check connection to database
void StudHelper::check_connection() {
    try {
//Create connection object and initialize it
        connection conn("dbname = " + m_dbname + " user = " + m_name + " password = " + m_password +
            " hostaddr = " + m_hostaddr + " port = " + m_port);

//Basic check if connection is opened
        if(!conn.is_open()) {
            cerr << "Can't open database" << endl;

            exit(1);
        }

        conn.close();
    }
    catch(const exception& exc) {
        cerr << exc.what() << endl;

        exit(1);
    }
}

//Check if table exists
bool StudHelper::check_table() {
    string sql;
    bool is_tbl = false;

    try {
//Create connection object and initialize it
        connection conn("dbname = " + m_dbname + " user = " + m_name + " password = " + m_password +
                        " hostaddr = " + m_hostaddr + " port = " + m_port);

//Basic check if connection is opened
        if(!conn.is_open())
            exit(1);

//Write SQL query
        sql = "SELECT EXISTS ("
                "SELECT * "
                "FROM information_schema.tables "
                "WHERE table_schema = 'public' "
                "AND table_name = 'marks'"
                ");";

//Create non-transactional query
        nontransaction nontrans(conn);
        result res(nontrans.exec(sql));

//If table exists, return true
        if(res[0][0].as<bool>())
            is_tbl = true;

        conn.close();

        return is_tbl;
    }
    catch(const exception& exc) {
        cerr << exc.what() << endl;

        exit(1);
    }
}

//Create table
void StudHelper::create_table() {
    string sql;

    try {
//Create connection object and initialize it
        connection conn("dbname = " + m_dbname + " user = " + m_name + " password = " + m_password +
                        " hostaddr = " + m_hostaddr + " port = " + m_port);

//Basic check if connection is opened
        if(!conn.is_open())
            exit(1);

//Write SQL query
        sql = "CREATE TABLE Marks("
              "ID INT PRIMARY KEY NOT NULL, "
              "SUBJECT TEXT NOT NULL, "
              "MARK INT NOT NULL"
              ");";

//Create and execute transactional query
        work wrk(conn);

        wrk.exec(sql);
        wrk.commit();

        conn.close();
    }
    catch(const exception& exc) {
        cerr << exc.what() << endl;

        exit(1);
    }
}

//Get data from table
void StudHelper::get_data() {
    string sql;

    try {
//Create connection object and initialize it
        connection conn("dbname = " + m_dbname + " user = " + m_name + " password = " + m_password +
                        " hostaddr = " + m_hostaddr + " port = " + m_port);

//Basic check if connection is opened
        if(!conn.is_open())
            exit(1);

//Write SQL query
        sql = "SELECT * FROM Marks "
                "GROUP BY id, subject "
                "ORDER BY subject ASC;";

//Create non-transactional query
        nontransaction nontrans(conn);
        result res(nontrans.exec(sql));

//Print all data in table
        for(const auto& val : res) {
            cout << "ID = " << val[0].as<int>() << '\t';
            cout << "Subject = " << val[1].as<string>() << '\t';
            cout << "Mark = " << val[2].as<int>() << endl;
        }

        conn.close();
    }
    catch(const exception& exc) {
        cerr << exc.what() << endl;

        exit(1);
    }
}

//Get certain subject
void StudHelper::get_subject(const string& subject) {
    string sql;
    int marks_total = 0;

    try {
//Create connection object and initialize it
        connection conn("dbname = " + m_dbname + " user = " + m_name + " password = " + m_password +
                        " hostaddr = " + m_hostaddr + " port = " + m_port);

//Basic check if connection is opened
        if(!conn.is_open())
            exit(1);

//Write SQL query
        sql = "SELECT * FROM marks "
                "WHERE subject = '" + subject + "' "
                "GROUP BY id, subject "
                "ORDER BY subject ASC;";

//Create non-transactional query
        nontransaction nontrans(conn);
        result res(nontrans.exec(sql));

//Print all data about given subject
        for(const auto& val : res) {
            cout << "ID = " << val[0].as<int>() << '\t';
            cout << "Subject = " << val[1].as<string>() << '\t';
            cout << "Mark = " << val[2].as<int>() << endl;

//Get and print sum of marks
            marks_total += val[2].as<int>();
        }

        cout << "Sum of " << subject << " points: " << marks_total << endl;

        conn.close();
    }
    catch(const exception& exc) {
        cerr << exc.what() << endl;

        exit(1);
    }
}

//Insert data in table
void StudHelper::insert_data(const list<int>& marks, const string& subject) {
    string sql;

    try {
//Create connection object and initialize it
        connection conn("dbname = " + m_dbname + " user = " + m_name + " password = " + m_password +
                        " hostaddr = " + m_hostaddr + " port = " + m_port);

//Basic check if connection is opened
        if(!conn.is_open())
            exit(1);

//Automatically write SQL query depending on amount of marks
        for(const auto& val : marks) {
            sql.append("INSERT INTO marks(id, subject, mark) VALUES((SELECT floor(random() * 900000 + 100000)::int)")
                    .append(", '").append(subject).append("', ").append(to_string(val)).append(");");
        }

//Create and execute transactional query
        work wrk(conn);

        wrk.exec(sql);
        wrk.commit();

        conn.close();
    }
    catch(const exception& exc) {
        cerr << exc.what() << endl;

        exit(1);
    }
}

//Delete certain mark depending on its ID
void StudHelper::delete_data(const int& id) {
    string sql;

    try {
//Create connection object and initialize it
        connection conn("dbname = " + m_dbname + " user = " + m_name + " password = " + m_password +
                        " hostaddr = " + m_hostaddr + " port = " + m_port);

//Basic check if connection is opened
        if(!conn.is_open())
            exit(1);

//Write SQL query
        sql = "DELETE FROM marks "
                "WHERE id = " + to_string(id) + ';';

//Create and execute transactional query
        work wrk(conn);

        wrk.exec(sql);
        wrk.commit();

        conn.close();
    }
    catch(const exception& exc) {
        cerr << exc.what() << endl;

        exit(1);
    }
}

//Delete certain subject
void StudHelper::delete_subject(const string& subject) {
    string sql;

    try {
//Create connection object and initialize it
        connection conn("dbname = " + m_dbname + " user = " + m_name + " password = " + m_password +
                        " hostaddr = " + m_hostaddr + " port = " + m_port);

//Basic check if connection is opened
        if(!conn.is_open())
            exit(1);

//Write SQL query
        sql = "DELETE FROM marks "
              "WHERE subject = '" + subject + "';";

//Create and execute transactional query
        work wrk(conn);

        wrk.exec(sql);
        wrk.commit();

        conn.close();
    }
    catch(const exception& exc) {
        cerr << exc.what() << endl;

        exit(1);
    }
}

//Change mark depending on its ID
void StudHelper::change_data(const int& id, const int& mark) {
    string sql;

    try {
//Create connection object and initialize it
        connection conn("dbname = " + m_dbname + " user = " + m_name + " password = " + m_password +
                        " hostaddr = " + m_hostaddr + " port = " + m_port);

//Basic check if connection is opened
        if(!conn.is_open())
            exit(1);

//Write SQL query
        sql = "UPDATE marks "
                "SET mark = " + to_string(mark) + ' ' +
                "WHERE id = " + to_string(id) + ';';

//Create and execute transactional query
        work wrk(conn);

        wrk.exec(sql);
        wrk.commit();

        conn.close();
    }
    catch(const exception& exc) {
        cerr << exc.what() << endl;

        exit(1);
    }
}

//Get information about connection
void StudHelper::get_info() {
    cout << "Database name: " << StudHelper::get_dbname() << endl;
    cout << "Username: " << StudHelper::get_name() << endl;
    cout << "Password: " << StudHelper::get_password() << endl;
    cout << "Host address: " << StudHelper::get_hostaddr() << endl;
    cout << "Port: " << StudHelper::get_port() << endl;
}

//Get useful information and advices about certain subject
void StudHelper::get_adv_info(const string& subject, bool has_exam = false) {
    string sql;
    int marks_total = 0;

    try {
//Create connection object and initialize it
        connection conn("dbname = " + m_dbname + " user = " + m_name + " password = " + m_password +
                        " hostaddr = " + m_hostaddr + " port = " + m_port);

//Basic check if connection is opened
        if(!conn.is_open())
            exit(1);

//Write SQL query
        sql = "SELECT id, mark FROM marks "
                "WHERE subject = '" + subject + "' "
                "GROUP BY id;";

//Create non-transactional query
        nontransaction nontrans(conn);
        result res(nontrans.exec(sql));

        for(const auto& val : res) {
//Sum all the marks of given subject
            marks_total += val[1].as<int>();

//If mark = 0, print warning
            if(val[1].as<int>() == 0)
                cout << val[1].as<string>() << " (ID: " << val[0].as<string>() << ") should be retaken!" << endl;
        }

//Print sum of all marks
        cout << "Sum of " << subject << " points: " << marks_total << endl;

//Print warnings depending on sum of marks and exam presence
        if(has_exam) {
            if(marks_total < 21)
                cout << "You should get " << 21 - marks_total << " points to be allowed to the exam!" << endl;

            if(marks_total < 60)
                cout << "You should get " << 60 - marks_total << " points to get credit!" << endl;
        }
        else {
            if(marks_total < 30)
                cout << "You should get " << 30 - marks_total << " points to be allowed to get credit!" << endl;

            if(marks_total < 60)
                cout << "You should get " << 60 - marks_total << " points to get credit!" << endl;
        }

        conn.close();
    }
    catch(const exception& exc) {
        cerr << exc.what() << endl;

        exit(1);
    }
}

//Function-helper to track pressing on buttons
int getch() {
    struct termios oldattr {}, newattr {};
    int ch;

    tcgetattr(STDIN_FILENO, &oldattr);

    newattr = oldattr;
    newattr.c_lflag &= ~(static_cast<unsigned>(ICANON) | static_cast<unsigned>(ECHO));

    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);

    return ch;
}

//Function-helper to check if port is opened
bool is_port(const string& ip, const string& port) { return (TcpSocket().connect(ip, stoi(port)) == Socket::Done); }

//Function-helper to check if IPv4 was entered right
bool is_ip(const string& ip) {
    struct sockaddr_in sa {};

    return inet_pton(AF_INET, ip.c_str(), &(sa.sin_addr)) != 0;
}