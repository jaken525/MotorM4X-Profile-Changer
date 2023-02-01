#include <iostream>
#include <sstream>
#include <vector>
#include <boost/filesystem/operations.hpp>
#include <boost/iterator/filter_iterator.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem.hpp>
#include <windows.h>

using namespace std;
namespace bfs = boost::filesystem;

vector<string> Folders;

void CheckGameProfiles() 
{
    Folders.clear();

    cout << "Search all profiles..." << endl;

    if (!bfs::exists("Profiles")) 
        bfs::create_directory("Profiles");

    bfs::directory_iterator begin("Profiles\\");
    bfs::directory_iterator end;
    
    for (; begin != end; ++begin) 
    {
        bfs::path ProfileFolder(*begin);
        bfs::file_status fs = bfs::status(*begin);

        switch (fs.type()) 
        {
        case bfs::directory_file:
            string Folder = ProfileFolder.filename().string();
            Folders.push_back(Folder);
            break;
        }
    }
}

void LoadGameProfile()
{
    cout << endl << "What profile do you want:" << endl;
    cout << "-----------------------------------------" << endl;

    for (int i = 0; i < Folders.size(); i++)
        cout << i + 1 << ". " << Folders[i] << endl;

    cout << "-----------------------------------------" << endl << endl;
   
    int c;
    cin >> c;

    cout << endl << "Old profile data deleting starts." << endl;
    cout << "-----------------------------------------" << endl;
   
    c--;

    if (c < 0) 
        cout << "Data entered incorrectly." << endl;

    if (c >= 0)
    {
        bfs::directory_iterator begin("./");
        bfs::directory_iterator end;

        for (; begin != end; ++begin)
            if (
                bfs::extension(*begin) == ".vhx" ||
                bfs::extension(*begin) == ".xml" ||
                bfs::extension(*begin) == ".hsx"
                )
            {
                bfs::path VHXfile(*begin);
                bfs::remove(VHXfile);
                cout << VHXfile.filename().string() << " delete successfull" << endl;
                Sleep(250);
            }

        cout << "-----------------------------------------" << endl << endl;
        cout << "New profile data copying starts." << endl;
        cout << "-----------------------------------------" << endl;

        string _profileFolder = "Profiles\\" + Folders[c] + "\\";
        stringstream CurrentProfilePath;
        stringstream GamePath;
        string SaveProfilePath;
        string SaveCopyPath;

        for (int i = 0; i < _profileFolder.length(); ++i) 
            if (_profileFolder[i] == '\\') 
                CurrentProfilePath << "\\\\";    
            else 
                CurrentProfilePath << _profileFolder[i];          

        SaveProfilePath = CurrentProfilePath.str();
        SaveCopyPath = GamePath.str();
        bfs::directory_iterator beginp(_profileFolder);
        bfs::directory_iterator endp;

        for (; beginp != endp; ++beginp) 
        {
            bfs::path Newfile(*beginp);
            CurrentProfilePath.str("");
            GamePath.str("");
            GamePath << SaveCopyPath;
            GamePath << Newfile.filename().string();
            CurrentProfilePath << SaveProfilePath;
            CurrentProfilePath << Newfile.filename().string();

            bfs::path profilePath(CurrentProfilePath.str());
            bfs::path gamePath(GamePath.str());

            bfs::copy_file(profilePath, gamePath);
            cout << Newfile.filename().string() << " copy successfull" << endl;

            Sleep(500);
        }

        cout << "-----------------------------------------" << endl << endl;
        cout << "New profile uploaded successfully." << endl;

        system("cls");
    }
}

void SaveGameProfile() 
{
    cout << "What profile name do you want" << endl;
    cout << "-----------------------------------------" << endl;

    string c;
    cin >> c;

    while (c.length() > 15)
    {
        system("cls");
        cout << "The name was entered incorrectly. It must contain no more than 15 characters!" << endl;
        cout << "What profile name do you want" << endl;
        cout << "-----------------------------------------" << endl;
        cin >> c;
    }

    string NewProfileName = "Profiles\\" + c;

    bfs::create_directory(NewProfileName);

    cout << "-----------------------------------------" << endl << endl;
    cout << "New profile data copying starts." << endl;
    cout << "-----------------------------------------" << endl;

        bfs::directory_iterator begin("./");
        bfs::directory_iterator end;

        for (; begin != end; ++begin) 
        {
            if (
                bfs::extension(*begin) == ".vhx" ||
                bfs::extension(*begin) == ".xml" ||
                bfs::extension(*begin) == ".hsx"
                ) 
            {
                string _profileFolder = "Profiles\\" + c + "\\";
                stringstream CurrentProfilePath;
                string SaveProfilePath;

                for (int i = 0; i < _profileFolder.length(); ++i) 
                    if (_profileFolder[i] == '\\')
                        CurrentProfilePath << "\\\\";
                    else 
                        CurrentProfilePath << _profileFolder[i];

                SaveProfilePath = CurrentProfilePath.str();
                bfs::path VHXfile(*begin);
                CurrentProfilePath.str("");
                CurrentProfilePath << SaveProfilePath;
                CurrentProfilePath << VHXfile.filename().string();
                bfs::path profilePath(CurrentProfilePath.str());

                bfs::copy_file(VHXfile, profilePath);
                cout << VHXfile.filename().string() << " copy successfull" << endl;

                Sleep(500);
            }
        }

        cout << "-----------------------------------------" << endl << endl;
        cout << "New profile saved successfully." << endl;

        system("cls");
}

void DeleteGameProfile() 
{
    cout << endl << "What profile do you want:" << endl;
    cout << "-----------------------------------------" << endl;

    for (int i = 0; i < Folders.size(); i++) 
        cout << i + 1 << ". " << Folders[i] << endl;

    cout << "-----------------------------------------" << endl << endl;

    int c;
    cin >> c;

    cout << endl << "Profile data deleted successfully." << endl;

    c--;

    if (c < 0) 
        cout << "Data entered incorrectly." << endl;
    
    if (c >= 0) 
    {
        string RemoveFolder = "Profiles\\" + Folders[c];
        bfs::remove_all(RemoveFolder);
    }

    cout << "-----------------------------------------" << endl << endl;
    cout << "Profile has been successfully deleted." << endl;

    system("cls");
}

void CreateNewGame() 
{
    cout << endl << "Deleting the current profile." << endl;
    cout << "-----------------------------------------" << endl;

    bfs::directory_iterator begin("./");
    bfs::directory_iterator end;

    for (; begin != end; ++begin) 
        if (
            bfs::extension(*begin) == ".vhx" ||
            bfs::extension(*begin) == ".xml" ||
            bfs::extension(*begin) == ".hsx"
            ) 
        {
            bfs::path VHXfile(*begin);
            bfs::remove(VHXfile);

            cout << VHXfile.filename().string() << " delete successfull" << endl;

            Sleep(250);
        }

    cout << "-----------------------------------------" << endl << endl;
    cout << "Profile has been successfully deleted." << endl;
    cout << "To start a new game, go to MotorM4X and start a career." << endl;

    system("cls");
}

int main()
{
    bool programEnd = false;

    while (!programEnd) 
    {
        CheckGameProfiles();

        cout << endl << "You have profiles:" << endl;
        cout << "-----------------------------------------" << endl;

        for (int i = 0; i < Folders.size(); i++)
            cout << i + 1 << ". " << Folders[i] << endl;

        cout << "-----------------------------------------" << endl;
        cout << endl << "What do you want:" << endl;
        cout << "-----------------------------------------" << endl;
        cout <<
            "0. Exit" << endl <<
            "1. Load profile" << endl <<
            "2. Save current profile" << endl <<
            "3. Delete profile" << endl <<
            "4. Create new game" << endl;
        cout << "-----------------------------------------" << endl << endl;
        
        int c;
        cin >> c;

        system("cls");

        switch (c) 
        {
        case 0:
            programEnd = true;
            break;
        case 1:
            LoadGameProfile();
            break;
        case 2:
            SaveGameProfile();
            break;
        case 3:
            DeleteGameProfile();
            break;
        case 4:
            CreateNewGame();
            break;
        }
    }
    return 0;
}