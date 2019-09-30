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

void StudHelper::check_connection() {
    try {
        connection conn("dbname = " + m_dbname + " user = " + m_name + " password = " + m_password +
            " hostaddr = " + m_hostaddr + " port = " + m_port);

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

bool StudHelper::check_table() {
    string sql;
    bool is_tbl = false;

    try {
        connection conn("dbname = " + m_dbname + " user = " + m_name + " password = " + m_password +
                        " hostaddr = " + m_hostaddr + " port = " + m_port);

        if(!conn.is_open())
            exit(1);

        sql = "SELECT EXISTS ("
                "SELECT * "
                "FROM information_schema.tables "
                "WHERE table_schema = 'public' "
                "AND table_name = 'marks'"
                ");";

        nontransaction nontrans(conn);
        result res(nontrans.exec(sql));

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

void StudHelper::create_table() {
    string sql;

    try {
        connection conn("dbname = " + m_dbname + " user = " + m_name + " password = " + m_password +
                        " hostaddr = " + m_hostaddr + " port = " + m_port);

        if(!conn.is_open())
            exit(1);

        sql = "CREATE TABLE Marks("
              "ID INT PRIMARY KEY NOT NULL, "
              "SUBJECT TEXT NOT NULL, "
              "MARK INT NOT NULL"
              ");";

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

void StudHelper::get_data() {
    string sql;

    try {
        connection conn("dbname = " + m_dbname + " user = " + m_name + " password = " + m_password +
                        " hostaddr = " + m_hostaddr + " port = " + m_port);

        if(!conn.is_open())
            exit(1);

        sql = "SELECT * FROM Marks "
                "GROUP BY id, subject "
                "ORDER BY subject ASC;";

        nontransaction nontrans(conn);
        result res(nontrans.exec(sql));

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

void StudHelper::get_subject(const string& subject) {
    string sql;
    int marks_total = 0;

    try {
        connection conn("dbname = " + m_dbname + " user = " + m_name + " password = " + m_password +
                        " hostaddr = " + m_hostaddr + " port = " + m_port);

        if(!conn.is_open())
            exit(1);

        sql = "SELECT *, sum(mark) AS marks_total FROM marks "
                "WHERE subject = '" + subject + "' "
                "GROUP BY id, subject "
                "ORDER BY subject ASC;";

        nontransaction nontrans(conn);
        result res(nontrans.exec(sql));

        for(const auto& val : res) {
            cout << "ID = " << val[0].as<int>() << '\t';
            cout << "Subject = " << val[1].as<string>() << '\t';
            cout << "Mark = " << val[2].as<int>() << endl;

            marks_total += val[3].as<int>();
        }

        cout << "Sum of " << subject << " points: " << marks_total << endl;

        conn.close();
    }
    catch(const exception& exc) {
        cerr << exc.what() << endl;

        exit(1);
    }
}

void StudHelper::insert_data(const list<int>& marks, const string& subject) {
    string sql;

    try {
        connection conn("dbname = " + m_dbname + " user = " + m_name + " password = " + m_password +
                        " hostaddr = " + m_hostaddr + " port = " + m_port);

        if(!conn.is_open())
            exit(1);

        for(const auto& val : marks) {
            sql.append("INSERT INTO marks(id, subject, mark) VALUES((SELECT floor(random() * 900000 + 100000)::int)")
                    .append(", '").append(subject).append("', ").append(to_string(val)).append(");");
        }

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

void StudHelper::delete_data(const int &id) {
    string sql;

    try {
        connection conn("dbname = " + m_dbname + " user = " + m_name + " password = " + m_password +
                        " hostaddr = " + m_hostaddr + " port = " + m_port);

        if(!conn.is_open())
            exit(1);

        sql = "DELETE FROM marks "
                "WHERE id = " + to_string(id) + ';';

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

void StudHelper::delete_subject(const string &subject) {
    string sql;

    try {
        connection conn("dbname = " + m_dbname + " user = " + m_name + " password = " + m_password +
                        " hostaddr = " + m_hostaddr + " port = " + m_port);

        if(!conn.is_open())
            exit(1);

        sql = "DELETE FROM marks "
              "WHERE subject = '" + subject + "';";

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

void StudHelper::change_data(const int &id, const int& mark) {
    string sql;

    try {
        connection conn("dbname = " + m_dbname + " user = " + m_name + " password = " + m_password +
                        " hostaddr = " + m_hostaddr + " port = " + m_port);

        if(!conn.is_open())
            exit(1);

        sql = "UPDATE marks "
                "SET mark = " + to_string(mark) + ' ' +
                "WHERE id = " + to_string(id) + ';';

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

void StudHelper::get_info() {
    cout << "Database name: " << StudHelper::get_dbname() << endl;
    cout << "Username: " << StudHelper::get_name() << endl;
    cout << "Password: " << StudHelper::get_password() << endl;
    cout << "Host address: " << StudHelper::get_hostaddr() << endl;
    cout << "Port: " << StudHelper::get_port() << endl;
}

void StudHelper::get_adv_info(const string &subject, bool has_exam = false) {
    string sql;
    int marks_total = 0;

    try {
        connection conn("dbname = " + m_dbname + " user = " + m_name + " password = " + m_password +
                        " hostaddr = " + m_hostaddr + " port = " + m_port);

        if(!conn.is_open())
            exit(1);

        sql = "SELECT id, sum(mark) AS marks_total FROM marks "
                "WHERE subject = '" + subject + "' "
                "GROUP BY id;";

        nontransaction nontrans(conn);
        result res(nontrans.exec(sql));

        for(const auto& val : res) {
            marks_total += val[1].as<int>();

            if(val[1].as<int>() == 0)
                cout << val[1].as<string>() << " (ID: " << val[0].as<string>() << ") should be retaken!" << endl;
        }

        cout << "Sum of " << subject << " points: " << marks_total << endl;

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
