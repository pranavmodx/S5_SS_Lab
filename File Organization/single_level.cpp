#include <iostream>

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
};

void display_options();

int main()
{
    cout << "Single Level File Organization Technique Simulation" << endl;
    Directory dir;

    int ch = 100;
    while (ch)
    {
        display_options();
        cin >> ch;
        switch (ch)
        {
        case 1:
            dir.ls();
            break;
        case 2:
            dir.ls_la();
            break;
        case 3:
            dir.touch();
            break;
        case 4:
            dir.rm();
            break;
        case 5:
            ch = 0;
            break;
        default:
            cout << "Please enter the correct choice" << endl;
        }
    }
}

void display_options()
{
    cout << endl
         << "1. Show files" << endl;
    cout << "2. Show files in detail" << endl;
    cout << "3. Create file" << endl;
    cout << "4. Remove file" << endl;
    cout << "5. Quit" << endl
         << endl;
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

void Directory::ls()
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

void Directory::ls_la()
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
