
#ifndef FILEUTILS_H
#define FILEUTILS_H
#include <string>
#include <vector>
#include "FileSystem.H"
using namespace std;

class FileUtils
{
  public:

    enum
    {
        COPY = 0,
        MOVE = 1,
        RENAME = 2,
        CREATE_FILE = 3,
        CREATE_DIR = 4,
        DELETE_FILE = 5,
        DELETE_DIR = 6,
        DELETE = 7,
        GOTO = 8,
        SEARCH = 9,
        SNAPSHOT = 10,
        CLEAR_TRASH = 11,
    };

    // Constructor/Destructor
    FileUtils(FileSystem* p);
    ~FileUtils();

    // Public methods
    void init(string cmdString, string mFxPath);
    int execute();

    int fxCopy();
    int fxMove();
    int fxRename();
    int fxCreateFile();
    int fxCreateDir();
    int fxDeleteFile();
    int fxDeleteDir();
    int fxDelete(bool isForce=false);
    int fxGoto();
    int fxSearch();
    int fxSnapshot();
    int fxClearTrash();

  private:
    void tokenize(string cmdString);
    int copyDirectory(string sourceDirPath, string destDirPath);
    int deleteFolderTree(string dirPath);
    int searchFolderTree(string sEntry, string dirPath = "");
    void displaySearchResults();
    bool isDirectory(string path);
    string getUserHome();
    int evaluateDirectoryArg(string arg, string& sPath);
    int scanAndDumpResults(ofstream& dump, string dirPath, int formatDepth);
    void evaluateArrowKeysInSearchResults(string buff);
    void evaluateEnterKeyInSearchResults();
    string getTimeStamp();

  private:
    FileSystem* pFx;
    string mCmd;
    string mFxPath;
    vector<string> mArgs;
    vector<string> mCmdsList; // List of commands supported.
    vector<string> mFoundList;
};



#endif /* FILEUTILS_H */

