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

//Method-helper to check if ID generator exists in DB
bool StudHelper::check_generator() {
    string sql;
    bool is_gnrtr = false;

    try {
//Create connection object and initialize it
        connection conn("dbname = " + m_dbname + " user = " + m_name + " password = " + m_password +
                        " hostaddr = " + m_hostaddr + " port = " + m_port);

//Basic check if connection is opened
        if(!conn.is_open())
            exit(EXIT_FAILURE);

//Write SQL query
        sql = "select p.oid::regprocedure "
                    "from pg_proc p "
                    "join pg_namespace n "
                    "on p.pronamespace = n.oid "
                    "where n.nspname not in ('pg_catalog', 'information_schema');";

//Create non-transactional query
        nontransaction nontrans(conn);
        result res(nontrans.exec(sql));

//Start searching for needed functions
        for(const auto& val1 : res) {
//If first needed function was found
            if (val1[0].as<string>() == "id_generator(integer)") {
//Look for another one
                for (const auto &val2 : res) {
//If all the functions were found, stop searching and return true
                    if(val2[0].as<string>() == "get_id(integer, integer, integer)") {
                        is_gnrtr = true;

                        break;
                    }
                }

                break;
            }
        }

        conn.close();

        return is_gnrtr;
    }
    catch(const exception& exc) {
        cerr << exc.what() << endl;

        exit(EXIT_FAILURE);
    }
}

void StudHelper::create_generator() {
    string sql;

    try {
//Create connection object and initialize it
        connection conn("dbname = " + m_dbname + " user = " + m_name + " password = " + m_password +
                        " hostaddr = " + m_hostaddr + " port = " + m_port);

//Basic check if connection is opened
        if(!conn.is_open())
            exit(EXIT_FAILURE);

//Write SQL query
        sql = "create or replace function id_generator(value integer) returns integer "
                "immutable "
                "strict "
                "language plpgsql "
              "as "
              "$$ "
              "declare "
              "l1 int; "
              "l2 int; "
              "r1 int; "
              "r2 int; "
              "i int := 0; "
              "begin "
                "l1:= (value >> 12) & (4096-1); "
                "r1:= value & (4096-1); "
                "while i < 3 loop "
                    "l2 := r1; "
                    "r2 := l1 # ((((1366 * r1 + 150889) % 714025) / 714025.0) * (4096-1))::int; "
                    "l1 := l2; "
                    "r1 := r2; "
                    "i := i + 1; "
                "end loop; "
                "return ((l1 << 12) + r1); "
              "end; "
              "$$;";

//Create and execute transactional query
        work wrk(conn);

        wrk.exec(sql);
        wrk.commit();

        conn.close();
    }
    catch(const exception& exc) {
        cerr << exc.what() << endl;

        exit(EXIT_FAILURE);
    }
}

void StudHelper::create_id() {
    string sql;

    try {
//Create connection object and initialize it
        connection conn("dbname = " + m_dbname + " user = " + m_name + " password = " + m_password +
                        " hostaddr = " + m_hostaddr + " port = " + m_port);

//Basic check if connection is opened
        if(!conn.is_open())
            exit(EXIT_FAILURE);

//Write SQL query
        sql = "create or replace function get_id(value integer, max integer, min integer) returns integer "
                    "immutable "
                    "strict "
                    "language plpgsql "
              "as "
              "$$ "
              "begin "
                "loop "
                    "value := id_generator(value); "
                    "exit when value <= max and value >= min; "
                    "if value = (select id from marks) then "
                        "value := get_id(value, min, max); "
                    "end if; "
                    "end loop; "
                    "return value; "
              "end "
              "$$;";

//Create and execute transactional query
        work wrk(conn);

        wrk.exec(sql);
        wrk.commit();

        conn.close();
    }
    catch(const exception& exc) {
        cerr << exc.what() << endl;

        exit(EXIT_FAILURE);
    }
}

//Check connection to database
void StudHelper::check_connection() {
    try {
//Create connection object and initialize it
        connection conn("dbname = " + m_dbname + " user = " + m_name + " password = " + m_password +
            " hostaddr = " + m_hostaddr + " port = " + m_port);

//Basic check if connection is opened
        if(!conn.is_open())
            exit(EXIT_FAILURE);

        if(!check_generator()) {
            create_generator();
            create_id();
        }

        conn.close();
    }
    catch(const exception& exc) {
        cerr << exc.what() << endl;

        exit(EXIT_FAILURE);
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
            exit(EXIT_FAILURE);

//Write SQL query
        sql = "select exists ("
                "select * "
                "from information_schema.tables "
                "where table_schema = 'public' "
                "and table_name = 'marks'"
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

        exit(EXIT_FAILURE);
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
            exit(EXIT_FAILURE);

//Write SQL query
        sql = "create table marks("
              "id int primary key not null, "
              "subject text not null, "
              "mark int"
              ");";

//Create and execute transactional query
        work wrk(conn);

        wrk.exec(sql);
        wrk.commit();

        conn.close();
    }
    catch(const exception& exc) {
        cerr << exc.what() << endl;

        exit(EXIT_FAILURE);
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
            exit(EXIT_FAILURE);

//Write SQL query
        sql = "select * from marks "
                "group by id, subject "
                "order by subject asc;";

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

        exit(EXIT_FAILURE);
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
            exit(EXIT_FAILURE);

//Write SQL query
        sql = "select * from marks "
                "where subject = '" + subject + "' "
                "group by id, subject "
                "order by subject asc;";

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

        exit(EXIT_FAILURE);
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
            exit(EXIT_FAILURE);

//Automatically write SQL query depending on amount of marks
        for(const auto& val : marks) {
            sql.append("insert into marks(id, subject, mark) values((select floor(random() * 900000 + 100000)::int)")
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

        exit(EXIT_FAILURE);
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
            exit(EXIT_FAILURE);

//Write SQL query
        sql = "delete from marks "
                "where id = " + to_string(id) + ';';

//Create and execute transactional query
        work wrk(conn);

        wrk.exec(sql);
        wrk.commit();

        conn.close();
    }
    catch(const exception& exc) {
        cerr << exc.what() << endl;

        exit(EXIT_FAILURE);
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
            exit(EXIT_FAILURE);

//Write SQL query
        sql = "delete from marks "
              "where subject = '" + subject + "';";

//Create and execute transactional query
        work wrk(conn);

        wrk.exec(sql);
        wrk.commit();

        conn.close();
    }
    catch(const exception& exc) {
        cerr << exc.what() << endl;

        exit(EXIT_FAILURE);
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
            exit(EXIT_FAILURE);

//Write SQL query
        sql = "update marks "
                "set mark = " + to_string(mark) + ' ' +
                "where id = " + to_string(id) + ';';

//Create and execute transactional query
        work wrk(conn);

        wrk.exec(sql);
        wrk.commit();

        conn.close();
    }
    catch(const exception& exc) {
        cerr << exc.what() << endl;

        exit(EXIT_FAILURE);
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
            exit(EXIT_FAILURE);

//Write SQL query
        sql = "select id, mark from marks "
                "where subject = '" + subject + "' "
                "group by id;";

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

//Needed points for certain progress
        const int PTS_EXAM_REQUIRED = 21;
        const int PTS_CREDIT_REQUIRED = 60;
        const int PTS_CREDIT_MIN_REQUIRED = 30;

//Print warnings depending on sum of marks and exam presence
        if(has_exam) {
            if(marks_total < PTS_EXAM_REQUIRED)
                cout << "You should get " << PTS_EXAM_REQUIRED - marks_total << " points to be allowed to the exam!" << endl;

            if(marks_total < PTS_CREDIT_REQUIRED)
                cout << "You should get " << PTS_CREDIT_REQUIRED - marks_total << " points to get credit!" << endl;
        }
        else {
            if(marks_total < PTS_CREDIT_MIN_REQUIRED)
                cout << "You should get " << PTS_CREDIT_MIN_REQUIRED - marks_total << " points to be allowed to get credit!" << endl;

            if(marks_total < PTS_CREDIT_REQUIRED)
                cout << "You should get " << PTS_CREDIT_REQUIRED - marks_total << " points to get credit!" << endl;
        }

        conn.close();
    }
    catch(const exception& exc) {
        cerr << exc.what() << endl;

        exit(EXIT_FAILURE);
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