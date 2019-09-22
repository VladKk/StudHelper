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