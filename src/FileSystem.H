
#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <string>
#include <vector>
using namespace std;

class FileSystem
{
  public:
    FileSystem(string dirPath);
    ~FileSystem();

    void run(); // traverse the path, clear screen and display
    int  traverse();
    void display();
    void evaluateEnterKey();
    void evaluateArrowKeys(string sBuff);
    void moveUp();
    void restart();
    void processCommandMode();

    // Inline setter/getter functions
    inline void setTermDimensions(int h, int w)
    {
        mTermHeight = h;
        mTermWidth = w;
    };
    inline void setDisplayDimensions()
    {
        mDisplayAreaSize  = (mTermHeight - mFooterSize - 1);
        mDispStartIndex = 0;
        mDispEndIndex = mDisplayAreaSize-1;
    };
    inline void setPath(string dirPath)
    {
        mPath = dirPath;
    };
    inline string getRootPath()
    {
        return mRootPath;
    };
    inline string getTrashPath()
    {
        return mFxTrashPath;
    };

    // other public utilities
    void changeDir(string nextDir,
                   bool isAppend = true,
                   bool isRun = true);

    void createTrashDirectory();

  private:
    void openFile(string fileName);
    void footer();
    int  constructFileData();
    void clearAndDisplay();
    void normalDisplay();
    void extendedDisplay();
    void showCmd(string inputCmd, int rc);

    // inline private helper functions
    inline int min(int x, int y)
    {
        return ((x<y) ? x : y);
    };
    inline int max(int x, int y)
    {
        return ((x>y) ? x : y);
    };

  private:
    int mMaxDispStrSize;
    string mPath;
    string mRootPath;
    int mTermHeight;
    int mTermWidth;
    int mDispStartIndex;
    int mDispEndIndex;
    int mDisplayAreaSize;
    int mFooterSize;
    vector<string> mDirEntries;  // List of all the entries files/directories in the current directory
    vector<string> mDirEntryDetails;
    vector<string> mBackDirStack;    // directory stack for "<-" (Left arrow) key
    vector<string> mFwdDirStack;     // directory stack for "->" (right arrow) key
    string mFxTrashPath;
};

#endif /* FILESYSTEM_H */

