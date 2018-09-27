
#ifndef TERMUTILS_H
#define TERMUTILS_H

#define SUCCESS 0
#define FAILURE -1
#define INVALID_COMMAND -2

// Quit terminal
#define CTRL_C    '\x03' // Ctrl-C
#define QUIT      '\x71' // 'q'
#define BACKSPACE '\x7F' // Backspace (DEL in ASCII chart)

#define KEY_ESC   '\x1B'
#define KEY_ENTER '\n'
#define KEY_UP    "[A"
#define KEY_DOWN  "[B"
#define KEY_RIGHT "[C"
#define KEY_LEFT  "[D"

#define CURSOR_START_POS 1
#define SEARCH_CURSOR_START_POS 3

// Escape sequences controlling the termninal
#define SWITCH_ALT_SCREEN_BUFFER  "\e[?1049h"  // save the cursor & switch to alternate screen buffer
#define SWITCH_NORM_SCREEN_BUFFER "\e[?1049l"  // restore the cursor & switch to normal screen buffer
#define CLEAR_ALT_SCREEN_BUFFER   "\e[?2J"     // clear the alternate screen buffer
#define ENABLE_ALT_SCREEN_SCROLL  "\e[?1007h"  // enable cursor up/down in alternate screen buffer
#define DISABLE_ALT_SCREEN_SCROLL "\e[?1007l"  // disable cursor up/down in alternate screen buffer
#define MOVE_CURSOR_TOP           "\e[1;1H"
#define MOVE_CURSOR_UP            "\e[1A"
#define MOVE_CURSOR_UP_5          "\e[5A"
#define MOVE_CURSOR_DOWN          "\e[1B"
#define MOVE_CURSOR_DOWN_2        "\e[2B"
#define MOVE_CURSOR_RIGHT         "\e[1C"
#define MOVE_CURSOR_LEFT          "\e[1D"
#define MOVE_CURSOR_BOTTOM        "\e[1010h"
#define CLEAR_SCREEN              "\e[2J"
#define FETCH_CURSOR_POSITION     "\e[6n"
#define FETCH_TERMINAL_SIZE       "\e[18t" // size is returned in the format "\e[8;H;Wt"

#define EXEC_PATH "/usr/bin/open"
#define EXEC_NAME "open"

int  setup_alternate_terminal();
int  restore_terminal();
int  fetch_cursor_position(); // returns cursor line number
void fetch_terminal_size(int& height, int& width);   // returns height and width in number of characters.
void setup_command_mode();
void setup_normal_mode();

#endif /* TERMUTILS_H */



