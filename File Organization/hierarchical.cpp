#include <iostream>
#include <vector>
#include <ctype.h>
#include <algorithm>

using namespace std;

struct File
{
    string name;
    int size;
    File *next;
};

class Directory
{
private:
    File *fp_start;
    File *fp_end;
    int file_count;

    string name;
    vector<Directory *> dirs;

public:
    Directory()
    {
        fp_start = nullptr;
        fp_end = nullptr;
        file_count = 0;
    }

    bool file_exists(string file_name);
    void touch();
    void rm();
    void ls();
    void ls_la();

    bool dir_exists(string dir_name);
    Directory *get_dir(string dir_name);
    void mkdir();
    void rmdir();
};

struct User
{
    int id;
    string name;
    Directory ufd; // User file directory
};

class MFD
{
    // Main File Directory
private:
    vector<User *> users;

public:
    bool user_exists(int id);
    void create_user();
    void remove_user();
    void show_users();
    int user_count();
    User *get_user();
};

void show_MFD_options();
void show_UFD_options();

int main()
{
    cout << "Hierarchical File Organization Technique Simulation" << endl;
    MFD mfd;
    User *user;

    string ch;
    while (1)
    {
        cout << endl;
        show_MFD_options();
        show_UFD_options();
        cout << "[Q] Quit" << endl
             << endl;

        cin >> ch;
        transform(ch.begin(), ch.end(), ch.begin(), ::toupper);

        if (ch == "CU")
            mfd.create_user();
        else if (ch == "RU")
            mfd.remove_user();
        else if (ch == "SU")
            mfd.show_users();
        else if (ch == "CF" || ch == "RF" || ch == "CD" || ch == "RD" || ch == "SFD" || ch == "SFDD")
        {
            if (mfd.user_count() == 0)
            {
                cout << "No users exist! Create one first." << endl;
                continue;
            }

            user = mfd.get_user();
            if (!user)
                cout << "No user of that id exists" << endl;
            else
            {
                cout << "ID : " << user->id << " | Name : " << user->name << endl;
                if (ch == "CF")
                    user->ufd.touch();
                else if (ch == "RF")
                    user->ufd.rm();
                else if (ch == "CD")
                    user->ufd.mkdir();
                else if (ch == "RD")
                    user->ufd.rmdir();
                else if (ch == "SFD")
                    user->ufd.ls();
                else if (ch == "SFDD")
                    user->ufd.ls_la();
            }
        }
        else if (ch == "Q")
            break;
        else
            cout << "Please enter the correct choice!" << endl;
    }
}

void show_UFD_options()
{
    cout << "[CF] Create file | ";
    cout << "[RF] Remove file | ";
    cout << "[CD] Create directory | ";
    cout << "[RD] Remove directory | ";
    cout << "[SFD] Show files & directories | " << endl;
    cout << "[SFDD] Show files & directories in detail" << endl;
}

bool Directory::file_exists(string file_name)
{
    File *fp = fp_start;

    if (file_count > 0)
    {
        while (fp)
        {
            if (fp->name.compare(file_name) == 0)
                return true;
            fp = fp->next;
        }
    }

    return false;
}

void Directory::touch()
{
    string file_name;
    cout << "Enter file name : ";
    cin.ignore();
    getline(cin, file_name);

    if (!file_exists(file_name))
    {
        File *new_file = new File;
        new_file->name = file_name;
        cout << "Enter file size : ";
        cin >> new_file->size;
        if (file_count == 0)
        {
            fp_start = new_file;
            fp_start->next = nullptr;
        }
        else if (file_count == 1)
        {
            fp_end = new_file;
            fp_end->next = nullptr;
            fp_start->next = fp_end;
        }
        else
        {
            fp_end->next = new_file;
            fp_end = new_file;
            fp_end->next = nullptr;
        }
        file_count++;
        cout << "File created successfully!" << endl;
    }
    else
    {
        cout << "File with the same name already exists!" << endl;
    }
}

void Directory::rm()
{
    if (file_count == 0)
    {
        cout << "There are no files to remove!" << endl;
        return;
    }

    File *fp = fp_start;
    string file_name;
    cout << "Enter the name of file to remove : ";
    cin.ignore();
    getline(cin, file_name);
    int found = 0;

    File *temp;
    while (fp)
    {
        if (fp->name.compare(file_name) == 0)
        {
            found = 1;
            file_count--;
            temp = fp;
            cout << "File removed successfully!" << endl;
        }
        fp = fp->next;
    }
    if (!found)
        cout << "No file of that name exists" << endl;
    else
        delete temp;

    if (file_count == 0)
        fp_start = fp_end = nullptr;
}

bool Directory::dir_exists(string dir_name)
{
    int i;
    for (i = 0; i < dirs.size(); i++)
    {
        if (dirs[i]->name.compare(dir_name) == 0)
            return true;
    }
    return false;
}

Directory *Directory::get_dir(string dir_name)
{
    int i;
    for (i = 0; i < dirs.size(); i++)
    {
        if (dirs[i]->name.compare(dir_name) == 0)
            return dirs[i];
    }
    return nullptr;
}

void Directory::mkdir()
{
    int exit = 0;
    string ch, dir_name;

    while (!exit)
    {
        cout << endl;
        cout << "You are inside ";
        name.size() == 0 ? cout << "root user" : cout << name;
        cout << " directory" << endl;
        cout << "[SFD] Show files and directories | ";
        cout << "[SFDD] Show files and directories (in detail) | ";
        cout << "[CD] Create directory | ";
        cout << "[SWD] Switch to another directory | ";
        cout << "[B] Go back" << endl;
        cin >> ch;
        transform(ch.begin(), ch.end(), ch.begin(), ::toupper);

        if (ch == "CD")
        {
            cout << "Enter name of directory to create : ";
            cin.ignore();
            getline(cin, dir_name);
            if (!dir_exists(dir_name))
            {
                Directory *new_dir = new Directory;
                new_dir->name = dir_name;
                dirs.push_back(new_dir);
                cout << "Directory created successfully!" << endl;
            }
            else
                cout << "Directory of that name already exists" << endl;
        }
        else if (ch == "SWD")
        {
            cout << "Enter the name of the directory you want to switch to : ";
            cin.ignore();
            getline(cin, dir_name);
            if (dir_exists(dir_name))
            {
                Directory *switched_dir = get_dir(dir_name);
                switched_dir->mkdir();
            }
            else
                cout << "No directory of that name exists" << endl;
        }

        else if (ch == "SFD")
            ls();
        else if (ch == "SFDD")
            ls_la();
        else if (ch == "B")
            exit = 1;
        else
        {
            cout << "Please enter the correct choice" << endl;
        }
    }
}

void Directory::rmdir()
{
    int i, exit = 0, found;
    string ch, dir_name;

    while (!exit)
    {
        cout << endl;
        cout << "You are inside ";
        name.size() == 0 ? cout << "root user" : cout << name;
        cout << " directory" << endl;
        cout << "[SFD] Show files and directories | ";
        cout << "[SFDD] Show files and directories (in detail) | ";
        cout << "[RD] Remove directory | ";
        cout << "[SWD] Switch to another directory | ";
        cout << "[B] Go back" << endl;
        cin >> ch;
        transform(ch.begin(), ch.end(), ch.begin(), ::toupper);

        if (ch == "RD")
        {
            Directory *new_dir = new Directory;
            cout << "Enter name of directory to remove : ";
            cin.ignore();
            getline(cin, dir_name);
            for (i = 0; i < dirs.size(); i++)
            {
                if (dirs[i]->name.compare(dir_name) == 0)
                {
                    found = 1;
                    dirs.erase(dirs.begin() + i);
                }
            }
            if (found = 1)
            {
                cout << "No directory of that name exists" << endl;
                found = 0;
            }
        }
        else if (ch == "SWD")
        {
            cout << "Enter name of directory you want to switch to : ";
            cin.ignore();
            getline(cin, dir_name);
            if (dir_exists(dir_name))
            {
                Directory *switched_dir = get_dir(dir_name);
                switched_dir->rmdir();
            }
            else
                cout << "No directory of that name exists" << endl;
        }
        else if (ch == "SFD")
            ls();
        else if (ch == "SFDD")
            ls_la();
        else if (ch == "B")
            exit = 1;
        else
            cout << "Please enter the correct choice" << endl;
    }
}

void Directory::ls()
{
    int i;
    if (file_count + dirs.size() == 0)
    {
        cout << "Empty directory" << endl;
        return;
    }
    File *fp = fp_start;
    while (fp)
    {
        cout << fp->name << endl;
        fp = fp->next;
    }
    for (i = 0; i < dirs.size(); i++)
    {
        cout << dirs.size() << endl;
        cout << dirs[i]->name << endl;
    }
}

void Directory::ls_la()
{
    int i;
    if (file_count + dirs.size() == 0)
    {
        cout << "Empty directory" << endl;
        return;
    }
    File *fp = fp_start;
    while (fp)
    {
        cout << fp->name << "  --  " << fp->size << "kb" << endl;
        fp = fp->next;
    }
    for (i = 0; i < dirs.size(); i++)
    {
        cout << dirs[i]->name << endl;
        dirs[i]->ls_la();
    }
}

void show_MFD_options()
{
    cout << "[CU] Create user | ";
    cout << "[RU] Remove user | ";
    cout << "[SU] Show users" << endl;
}

bool MFD::user_exists(int id)
{
    int i;
    for (i = 0; i < users.size(); i++)
    {
        if (users[i]->id == id)
        {
            return true;
        }
    }
    return false;
}

void MFD::create_user()
{
    int id;
    cout << "Enter id of user : ";
    cin >> id;
    if (!user_exists(id))
    {
        User *new_user = new User;
        new_user->id = id;
        cout << "Enter name of user : ";
        cin.ignore();
        getline(cin, new_user->name);
        users.push_back(new_user);
        cout << "User created successfully!" << endl;
    }
    else
        cout << "User with that id already exists!" << endl;
}

void MFD::remove_user()
{
    int i, id;
    cout << "Enter the id of user to remove : ";
    cin >> id;
    for (i = 0; i < users.size(); i++)
    {
        if (users[i]->id == id)
        {
            users.erase(users.begin() + i);
            cout << "User removed successfully!" << endl;
            return;
        }
    }
    cout << "No user of that id exists" << endl;
}

void MFD::show_users()
{
    int i;
    for (i = 0; i < users.size(); i++)
    {
        cout << "ID : " << users[i]->id << " | Name : " << users[i]->name << endl;
    }
}

int MFD::user_count()
{
    return users.size();
}

User *MFD::get_user()
{
    int i, id, found = 0;
    cout << "Enter user id : ";
    cin >> id;
    for (i = 0; i < users.size(); i++)
    {
        if (users[i]->id == id)
        {
            return users[i];
        }
    }
    return nullptr;
}