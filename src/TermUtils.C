#include <iostream>
#include <string>
#include <termios.h>
#include <unistd.h>
#include "TermUtils.H"
using namespace std;

struct termios orig_term_settings;
struct termios new_term_settings;

int setup_alternate_terminal()
{
    int rc = SUCCESS;
    tcgetattr(STDIN_FILENO, &orig_term_settings);

    new_term_settings = orig_term_settings;
    new_term_settings.c_lflag &= ~ECHO;
    new_term_settings.c_lflag &= ~ICANON;
    new_term_settings.c_cc[VMIN] = 1;
    new_term_settings.c_cc[VTIME] = 0;

    // Save the cursor and switch to alternate screen buffer
    cout << SWITCH_ALT_SCREEN_BUFFER << flush;
    cout << ENABLE_ALT_SCREEN_SCROLL << flush;

    rc = tcsetattr(STDIN_FILENO, TCSANOW, &new_term_settings);

    if (rc != SUCCESS)
    {
        cerr << "Could Not Set New Terminal Attributes" << endl;
        rc = FAILURE;
    }
    return rc;
}


int restore_terminal()
{
    int rc = SUCCESS;
    // Switch back from the alternate screen buffer
    cout << CLEAR_ALT_SCREEN_BUFFER << flush;
    cout << SWITCH_NORM_SCREEN_BUFFER << flush;

    // Restore the original terminal
    rc = tcsetattr(STDIN_FILENO, TCSANOW, &orig_term_settings);

    if (rc != SUCCESS)
    {
        cerr << "Could Not Restore the Terminal Attributes" << endl;
        rc = FAILURE;
    }
    return rc;
}


int fetch_cursor_position()
{
    char buff[8];
    string s;
    int start_pos, end_pos;
    int sCursorPos;

    if (isatty(STDIN_FILENO))
    {
        write (STDOUT_FILENO, FETCH_CURSOR_POSITION, 4);
        read (STDIN_FILENO ,buff ,sizeof(buff));

        s = string(buff);
        start_pos = s.find_last_of("[")+1;
        end_pos = s.find_last_of(";");
        s = s.substr(start_pos, end_pos-start_pos);
        sCursorPos = atoi(s.c_str());
    }
    else
    {
        sCursorPos = -1;
    }
    cin.clear();
    return sCursorPos;
}

void fetch_terminal_size(int& height, int& width)
{
    char buff[16];
    string s;
    int pos, start_pos, end_pos;

    if (isatty(STDIN_FILENO))
    {
        write (STDOUT_FILENO, FETCH_TERMINAL_SIZE, 5);
        read (STDIN_FILENO ,buff ,sizeof(buff));

        s = string(buff);
        start_pos = s.find("[8;")+3;
        end_pos = s.find_last_of("t");
        s = s.substr(start_pos, end_pos-start_pos);

        pos = s.find(";");
        height = atoi(s.substr(0,pos).c_str());
        width = atoi(s.substr(pos+1).c_str());
    }
    else
    {
        height = 0; width = 0;
    }
    cin.clear();
    return;
}


void setup_command_mode()
{
    new_term_settings.c_lflag |= ECHO;
    new_term_settings.c_lflag |= ICANON;
    tcsetattr(STDIN_FILENO, TCSANOW, &new_term_settings);
}


void setup_normal_mode()
{
    new_term_settings.c_lflag &= ~ECHO;
    new_term_settings.c_lflag &= ~ICANON;
    tcsetattr(STDIN_FILENO, TCSANOW, &new_term_settings);
}


