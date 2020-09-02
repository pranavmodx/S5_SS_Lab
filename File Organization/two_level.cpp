#include <iostream>
#include <vector>

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
    void show_MFD_options();

    bool user_exists(int id);
    int user_count();

    void create_user();
    void remove_user();
    void show_users();

    User *get_user();
};

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
        mfd.show_MFD_options();
        show_UFD_options();
        cout << "[q] Quit" << endl;

        cin.ignore();
        getline(cin, ch);

        if (ch == "cu")
            mfd.create_user();
        else if (ch == "ru")
            mfd.remove_user();
        else if (ch == "su")
            mfd.show_users();
        else if (ch == "touch" || ch == "rm" || ch == "ls" || ch == "ls_la")
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
                if (ch == "touch")
                    user->dir.touch();
                else if (ch == "rm")
                    user->dir.rm();
                else if (ch == "ls")
                    user->dir.ls();
                else if (ch == "ls_la")
                    user->dir.ls_la();
            }
        }
        else if (ch == "q")
            break;
        else
            cout << "Please enter the correct choice!" << endl;
    }
}

void show_UFD_options()
{
    cout << "[touch] Create file | ";
    cout << "[rm] Remove file | ";
    cout << "[ls] Show all files | ";
    cout << "[ls_la] Show all files in detail" << endl;
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

void UFD::rm()
{
    if (file_count == 0)
    {
        cout << "There are no files to delete!" << endl;
        return;
    }

    File *fp = fp_start, *fp2 = fp_start;
    string file_name;

    cout << "Enter the name of the file to delete : ";
    cin.ignore();
    getline(cin, file_name);

    // If first file matches
    if (fp->name.compare(file_name) == 0)
    {
        file_count--;
        fp_start = fp->next;
        delete fp;
        file_count--;
        cout << "Deleted file successfully!" << endl;
        return;
    }

    // Backup fp previous to file to be deleted
    while (fp && fp->name.compare(file_name) != 0)
    {
        fp2 = fp;
        fp = fp->next;
    }

    // If file found, then it won't be null
    if (fp)
    {
        fp2->next = fp->next;
        delete fp;
        file_count--;
        cout << "Deleted file successfully!" << endl;
        return;
    }

    cout << "No file of that name exists" << endl;
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

void MFD::show_MFD_options()
{
    cout << "[cu] Create user | ";
    cout << "[ru] Remove user | ";
    cout << "[su] Show users" << endl;
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