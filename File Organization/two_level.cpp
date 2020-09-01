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

class UFD
{
    // User File Directory
private:
    File *fp_start;
    File *fp_end;
    int file_count;

public:
    UFD()
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
};

struct User
{
    int id;
    string name;
    UFD dir;
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
    cout << "Two Level File Organization Technique Simulation" << endl;
    MFD mfd;
    User *user;

    string ch;
    while (1)
    {
        cout << endl;
        show_MFD_options();
        show_UFD_options();
        cout << "[Q] Quit" << endl;

        cin >> ch;
        transform(ch.begin(), ch.end(), ch.begin(), ::toupper);

        if (ch == "CU")
            mfd.create_user();
        else if (ch == "RU")
            mfd.remove_user();
        else if (ch == "SU")
            mfd.show_users();
        else if (ch == "CF" || ch == "RF" || ch == "SF" || ch == "SFD")
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
                    user->dir.touch();
                else if (ch == "RF")
                    user->dir.rm();
                else if (ch == "SF")
                    user->dir.ls();
                else if (ch == "SFD")
                    user->dir.ls_la();
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
    cout << "[SF] Show all files | ";
    cout << "[SFD] Show all files in detail" << endl;
}

bool UFD::file_exists(string file_name)
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

void UFD::touch()
{
    string file_name;
    cout << "Enter file name : ";
    cin.ignore();
    getline(cin, file_name);

    if (!file_exists(file_name))
    {
        File *new_file = new File;
        new_file->name = file_name;
        cout << endl
             << "Enter file size : ";
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

void UFD::rm()
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

void UFD::ls()
{
    if (file_count == 0)
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
}

void UFD::ls_la()
{
    if (file_count == 0)
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