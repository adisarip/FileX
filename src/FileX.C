#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/stat.h>
#include "TermUtils.H"
#include "FileSystem.H"
using namespace std;


int getDirectoryPath(string dirName, string& dirPath)
{
    int rc = SUCCESS;
    char* pDir = getenv(dirName.c_str());
    if (pDir != NULL)
    {
        dirPath = string(pDir) + "/";
    }
    else
    {
        rc = FAILURE;
    }
    return rc;
}


bool isDirectoryPresent(string dirPath)
{
    struct stat fileStat;
    stat(dirPath.c_str(), &fileStat);
    return (S_ISDIR(fileStat.st_mode));
}


int evaluateDirPath(string& dirPath)
{
    int rc = SUCCESS;
    string sHomeDir;
    string sCurrentDir;

    rc = getDirectoryPath("HOME", sHomeDir);
    if (rc == SUCCESS)
    {
        rc = getDirectoryPath("PWD", sCurrentDir);
    }

    if (rc == SUCCESS)
    {
        if (dirPath.back() != '/')
        {
            dirPath = dirPath + "/";
        }

        if (dirPath.find("/") == 0)
        {
            // Absolute path
        }
        else if (dirPath.find("./") == 0)
        {
            dirPath = sCurrentDir + dirPath.substr(2);
        }
        else if (dirPath.find("../") == 0)
        {
            while (dirPath.find("../") == 0 && sCurrentDir.size() >= 1)
            {
                if (sCurrentDir.back() == '/')
                {
                    sCurrentDir.pop_back();
                }
                int pos = sCurrentDir.find_last_of("/");
                sCurrentDir = sCurrentDir.substr(0, pos+1);
                dirPath = dirPath.substr(3);
            }
            dirPath = sCurrentDir + dirPath;
        }
        else if (dirPath.find("~") == 0 || dirPath.find("~/") == 0)
        {
            // path w.r.t user home directory
            int pos = (dirPath.size() > 1) ? 2 : 1;
            dirPath = sHomeDir + dirPath.substr(pos);
        }
        else
        {
            // a directory in the current folder w/o starting with "./"
            dirPath = sCurrentDir + dirPath;
        }
    }

    if (!isDirectoryPresent(dirPath))
    {
        rc = FAILURE;
    }

    return rc;
}

int main(int argc, char* argv[])
{
    char c;
    char in_buff[8];
    string sDirPath;

    if (argc > 2)
    {
        cerr << "ERROR: Invalid Command" << endl;
        return FAILURE;
    }
    else if (argc == 2)
    {
        sDirPath = string(argv[1]);
    }
    else
    {
        sDirPath = ".";
    }

    if (evaluateDirPath(sDirPath) != SUCCESS)
    {
        return FAILURE;
    }


    FileSystem fs(sDirPath);

    // Switch to alternate screen buffer
    setup_alternate_terminal();

    // Save the terminal dimensions
    int height, width;
    fetch_terminal_size(height, width);
    fs.setTermDimensions(height, width);
    fs.setDisplayDimensions();

    // Display directory listing
    fs.run();

    // Read each character in non-cannonical mode
    // Infinite loop - press 'q' or Ctrl-C to break.
    while(1)
    {
        cin.clear();
        read (STDIN_FILENO, &c, 1);
        if (c == CTRL_C || c == QUIT)
        {
            cout << CLEAR_ALT_SCREEN_BUFFER << flush;
            break;
        }
        else if (c == KEY_ESC)
        {
            cin.clear();
            read (STDIN_FILENO, &in_buff, 8);
            fs.evaluateArrowKeys(string(in_buff));
        }
        else if (c == KEY_ENTER)
        {
            fs.evaluateEnterKey();
        }
        else if (c == BACKSPACE)
        {
            // Move up a directory
            fs.moveUp();
        }
        else if (c == 'h' || c == 'H')
        {
            fs.restart();
        }
        else if (c == ':')
        {
            fs.processCommandMode();
        }
        else
        {
            // Do nothing
        }
    }

    // Revert from the alternate screen buffer and restore the Terminal
    restore_terminal();
    return 0;
}
