#include <iostream>
#include <string>
#include <stdio.h>
#include <time.h>
#pragma warning(disable : 4996)

using namespace std;
class Date {
public:
	string timeAndDate;
	string getUpdatedDateAndTime() {
		time_t     now = time(0);
		struct tm  tstruct;
		char       buf[80];
		tstruct = *localtime(&now);
		strftime(buf, sizeof(buf), "Date: %Y-%m-%d Time: %X", &tstruct);

		return buf;
	}
	friend ostream& operator<<(ostream& out, const Date& lhs);
	

};
ostream& operator<<(ostream& out, const Date& lhs)
{
	out << lhs.timeAndDate;
	return out;
 }

class File
{
	friend class Folder;
	friend class Filesystem;
	string name;
	string content;
	Date creationDateAndTime;
	Date accessedDateAndTime;
	string linkToParentFolder;
public:
	File()
	{
		name = "unknown";
		content = "";
		creationDateAndTime.timeAndDate=creationDateAndTime.getUpdatedDateAndTime();
		accessedDateAndTime.timeAndDate=creationDateAndTime.getUpdatedDateAndTime();
		linkToParentFolder = "";
	}
};
class Folder
{
	friend Folder* getTargetFolder(string path, string& name, bool& pathCorrect, Filesystem& obj, int turn);
	friend class Filesystem;
public:
	string name;
	Date creationDateAndTime;
	Date accessedDateAndTime;
	int numberOfFiles=0;
	int numberOfSubFolders=0;
	string linkToParentFolder;
	File* collectionOfFiles=nullptr;
	Folder* collectionOfFolder=nullptr;
	int sizeOfCollectionOfFiles=0;
	//constructors and destructor
public:
	Folder() :linkToParentFolder{""}, collectionOfFiles{new File[2]}, name{"Unknown"},sizeOfCollectionOfFiles{2}, numberOfFiles{0}, numberOfSubFolders{0}{
		creationDateAndTime.timeAndDate = creationDateAndTime.getUpdatedDateAndTime();
		accessedDateAndTime.timeAndDate = accessedDateAndTime.getUpdatedDateAndTime();
	
	}
	Folder(string a)
	{
		name = a;
		creationDateAndTime.timeAndDate = creationDateAndTime.getUpdatedDateAndTime();

	}
	~Folder()
	{
		delete[] collectionOfFolder;
		delete[] collectionOfFiles;
	}

	Folder& operator=(const Folder& rhs)
	{
		name = rhs.name;
		linkToParentFolder = rhs.linkToParentFolder;
		creationDateAndTime = rhs.creationDateAndTime;
		accessedDateAndTime = rhs.accessedDateAndTime;
		numberOfFiles = rhs.numberOfFiles;
		numberOfSubFolders = rhs.numberOfSubFolders;
		sizeOfCollectionOfFiles = rhs.sizeOfCollectionOfFiles;
		collectionOfFiles = new File[rhs.numberOfFiles];
		for (int i = 0; i < rhs.sizeOfCollectionOfFiles; ++i)
		{
			collectionOfFiles[i] = rhs.collectionOfFiles[i];
		}
		collectionOfFolder = new Folder[rhs.numberOfSubFolders];
		for (int i = 0; i <rhs.numberOfSubFolders; ++i)
		{
			collectionOfFolder[i] = rhs.collectionOfFolder[i];
		}
		return*this;
	}
	Folder(const Folder& rhs)
	{
		name = rhs.name;
		linkToParentFolder = rhs.linkToParentFolder;
		creationDateAndTime = rhs.creationDateAndTime;
		accessedDateAndTime = rhs.accessedDateAndTime;
		numberOfFiles = rhs.numberOfFiles;
		numberOfSubFolders = rhs.numberOfSubFolders;
		sizeOfCollectionOfFiles = rhs.sizeOfCollectionOfFiles;
		collectionOfFiles = new File[rhs.numberOfFiles];
		for (int i = 0; i < rhs.sizeOfCollectionOfFiles; ++i)
		{
			collectionOfFiles[i] = rhs.collectionOfFiles[i];
		}
		collectionOfFolder = new Folder[rhs.numberOfSubFolders];
		for (int i = 0; i < rhs.numberOfSubFolders; ++i)
		{
			collectionOfFolder[i] = rhs.collectionOfFolder[i];
		}
	}
};
class Filesystem
{
	friend Folder* getTargetFolder(string path, string& name, bool& pathCorrect, Filesystem& obj, int turn);

	Folder root;
public:
	//constructors and destructors
	Filesystem() :root{ "root" } {}
	
	
	//methods


	void createFile(string path, string name, string contents)
	{
		bool pathCorrect = true;
		string name1;

		Folder* currentFolder = getTargetFolder(path,name1,pathCorrect,*this,0);
		
		if (!pathCorrect)
		{
			cout << "Path Dont exist" << endl;
		}
		else
		{

			if (currentFolder->sizeOfCollectionOfFiles >= currentFolder->numberOfFiles)
			{
				File* temp = new File[currentFolder->numberOfFiles*2];
				for (int i = 0; i < currentFolder->sizeOfCollectionOfFiles; ++i)
				{
					temp[i] = currentFolder->collectionOfFiles[i];
				}
				currentFolder->numberOfFiles *= 2;
				delete[] currentFolder->collectionOfFiles;
				currentFolder->collectionOfFiles = temp;
			}
			currentFolder->collectionOfFiles[currentFolder->sizeOfCollectionOfFiles].linkToParentFolder = path;
			currentFolder->collectionOfFiles[currentFolder->sizeOfCollectionOfFiles].name = name;
			currentFolder->collectionOfFiles[currentFolder->sizeOfCollectionOfFiles].content = contents;
			currentFolder->collectionOfFiles[currentFolder->sizeOfCollectionOfFiles].creationDateAndTime.timeAndDate= currentFolder->collectionOfFiles[currentFolder->sizeOfCollectionOfFiles].creationDateAndTime.getUpdatedDateAndTime();
			currentFolder->collectionOfFiles[currentFolder->sizeOfCollectionOfFiles].accessedDateAndTime.timeAndDate = currentFolder->collectionOfFiles[currentFolder->sizeOfCollectionOfFiles].accessedDateAndTime.getUpdatedDateAndTime();
			currentFolder->sizeOfCollectionOfFiles++;
		}
	}
	void createFolder(string path, string name)
	{
		bool pathCorrect = true;
		string name1;
		Folder* currentFolder = getTargetFolder(path,name1,pathCorrect,*this,0);
		
		if (!pathCorrect)
		{
			cout << "Path Dont exist" << endl;
		}
		else
		{
			currentFolder->accessedDateAndTime.timeAndDate = currentFolder->accessedDateAndTime.getUpdatedDateAndTime();

			Folder* temp= new Folder[currentFolder->numberOfSubFolders + 1];
			for (int i = 0; i < currentFolder->numberOfSubFolders; ++i)
			{
				temp[i] = currentFolder->collectionOfFolder[i];
			}
			delete[] currentFolder->collectionOfFolder;
			currentFolder->collectionOfFolder = temp;
			currentFolder->collectionOfFolder[currentFolder->numberOfSubFolders].creationDateAndTime.timeAndDate = currentFolder->collectionOfFolder[currentFolder->numberOfSubFolders].creationDateAndTime.getUpdatedDateAndTime();
			currentFolder->collectionOfFolder[currentFolder->numberOfSubFolders].accessedDateAndTime.timeAndDate = currentFolder->collectionOfFolder[currentFolder->numberOfSubFolders].creationDateAndTime.getUpdatedDateAndTime();

			currentFolder->collectionOfFolder[currentFolder->numberOfSubFolders].name = name;
			currentFolder->collectionOfFolder[currentFolder->numberOfSubFolders].numberOfSubFolders = 0;
			currentFolder->collectionOfFolder[currentFolder->numberOfSubFolders].linkToParentFolder=path;
			currentFolder->collectionOfFolder[currentFolder->numberOfSubFolders].collectionOfFiles = new File[2];
			currentFolder->collectionOfFolder[currentFolder->numberOfSubFolders].numberOfFiles = 2;
			currentFolder->collectionOfFolder[currentFolder->numberOfSubFolders].sizeOfCollectionOfFiles =0;
			currentFolder->numberOfSubFolders++;
		}
	}
	void readFile(string path)
	{
		bool pathCorrect = true;
		string name;
		Folder* targetFolder = getTargetFolder(path,name,pathCorrect,*this,1);
		if (pathCorrect)
		{
			targetFolder->accessedDateAndTime.timeAndDate = targetFolder->accessedDateAndTime.getUpdatedDateAndTime();
			for (int i = 0; i < targetFolder->sizeOfCollectionOfFiles; ++i)
			{
				targetFolder->collectionOfFiles[2].name;
				if (targetFolder->collectionOfFiles[i].name == name)
				{
					targetFolder->collectionOfFiles[i].accessedDateAndTime.timeAndDate = targetFolder->collectionOfFiles[i].accessedDateAndTime.getUpdatedDateAndTime();
					cout << targetFolder->collectionOfFiles[i].name << "         Accessed : " << targetFolder->collectionOfFiles[i].accessedDateAndTime << "         Creation : " << targetFolder->collectionOfFiles[i].creationDateAndTime << endl;
					cout << "Content: " << endl;
					cout << targetFolder->collectionOfFiles[i].content << endl;

				}
			}
		}
		else
			cout << "Path not correct" << endl;
	}
	void listFolder(string path)
	{
		bool pathCorrect = true;
		string name;
		Folder* targetFolder = getTargetFolder(path,name,pathCorrect,*this,0);

		if (pathCorrect)
		{
		targetFolder->accessedDateAndTime.timeAndDate = targetFolder->accessedDateAndTime.getUpdatedDateAndTime();
			cout << "			Files: " << endl;
			for (int i = 0; i < targetFolder->sizeOfCollectionOfFiles; ++i)
			{
				targetFolder->accessedDateAndTime.timeAndDate = targetFolder->accessedDateAndTime.getUpdatedDateAndTime();
				cout << targetFolder->collectionOfFiles[i].name<<"         Accessed : "<<targetFolder->collectionOfFiles[i].accessedDateAndTime <<"         Creation : "<<targetFolder->collectionOfFiles[i].creationDateAndTime << endl;

			}
			cout << "			Folders:" << endl;
			for (int i = 0; i < targetFolder->numberOfSubFolders; ++i)
			{
				targetFolder->collectionOfFolder[i].accessedDateAndTime.timeAndDate = targetFolder->collectionOfFolder[i].accessedDateAndTime.getUpdatedDateAndTime();
				cout << targetFolder->collectionOfFolder[i].name<< "        Accessed : "<< targetFolder->collectionOfFolder[i].accessedDateAndTime << "        Creation : "<< targetFolder->collectionOfFolder[i].creationDateAndTime << endl;
			}
		}
		else
			cout << "Path not correct" << endl;
	}	
	void removeFile(string path)
	{
		bool pathCorrect = true;
		string name;
		Folder* targetFolder = getTargetFolder(path, name, pathCorrect, *this, 1);
		if (pathCorrect)
		{
			for (int i = 0; i < targetFolder->sizeOfCollectionOfFiles; ++i)
			{
				if (targetFolder->collectionOfFiles[i].name == name)
				{
					for (int k = i; k < targetFolder->sizeOfCollectionOfFiles; ++k)
					{
						if (k == targetFolder->sizeOfCollectionOfFiles - 1)
							break;
						targetFolder->collectionOfFiles[k] = targetFolder->collectionOfFiles[k + 1];
					}
					targetFolder->sizeOfCollectionOfFiles--;
					targetFolder->accessedDateAndTime.timeAndDate = targetFolder->accessedDateAndTime.getUpdatedDateAndTime();
				}
			}
		}
	}
	void removeFolder(string path)
	{
		bool pathCorrect = true;
		string name;
		
		Folder* targetFolder = getTargetFolder(path, name, pathCorrect, *this, 1);
		if (pathCorrect)
		{
			targetFolder->accessedDateAndTime.timeAndDate = targetFolder->accessedDateAndTime.getUpdatedDateAndTime();

			for (int i = 0; i < targetFolder->numberOfSubFolders; ++i)
			{
				if (targetFolder->collectionOfFolder[i].name == name)
				{
					deleteFolder(targetFolder->collectionOfFolder[i]);
					for (int k = i; k < targetFolder->numberOfSubFolders; ++k)
					{
						if (k == targetFolder->numberOfSubFolders - 1)
							break;
						targetFolder->collectionOfFolder[k] = targetFolder->collectionOfFolder[k + 1];
					}
					Folder* temp = new Folder[targetFolder->numberOfSubFolders - 1];
					for (int i = 0; i < targetFolder->numberOfSubFolders-1; ++i)
					{
						temp[i] = targetFolder->collectionOfFolder[i];
					}
					delete[] targetFolder->collectionOfFolder;
					targetFolder->collectionOfFolder = temp;
					targetFolder->numberOfSubFolders--;
					i--;
				}
				
			}
		}
	}
	void deleteFolder(Folder folder)
	{
		
			for (int i = 0; i < folder.numberOfSubFolders; ++i)
			{
				deleteFolder(folder.collectionOfFolder[i]);
				for (int k = i; k < folder.numberOfSubFolders; ++k)
				{
					if (k == folder.numberOfSubFolders - 1)
						break;
					folder.collectionOfFolder[k] = folder.collectionOfFolder[k + 1];
				}
				Folder* temp = new Folder[folder.numberOfSubFolders - 1];
				for (int i = 0; i < folder.numberOfSubFolders - 1; ++i)
				{
					temp[i] = folder.collectionOfFolder[i];
				}
				delete[] folder.collectionOfFolder;
				folder.collectionOfFolder = temp;
				folder.numberOfSubFolders--;
				i--;
			}
			for (int i = 0; i < folder.sizeOfCollectionOfFiles; ++i)
			{

				for (int k = i; k < folder.sizeOfCollectionOfFiles; ++k)
				{
					if (k == folder.sizeOfCollectionOfFiles - 1)
						break;
					folder.collectionOfFiles[k] = folder.collectionOfFiles[k + 1];
				}
				File* temp = new File[folder.sizeOfCollectionOfFiles - 1];
				for (int i = 0; i < folder.sizeOfCollectionOfFiles - 1; ++i)
					temp[i] = folder.collectionOfFiles[i];
				delete[] folder.collectionOfFiles;
				folder.collectionOfFiles = temp;
				folder.sizeOfCollectionOfFiles--;
				i--;
			}
		
	}
};
Folder* getTargetFolder(string path,string& name,bool& pathCorrect,Filesystem& obj,int turn)
{

	int index = 0;
	for (int i = 0; path[i] != '\\' && path[i] != 0; ++i)
	{
		if (path[i] != obj.root.name[i])
		{
			pathCorrect = false;
			break;

		}
		index = i;
	}
	index++;
	index++;
	Folder* currentFolder = &obj.root;
	if (pathCorrect)
	{
		//		root\\OOP\\Assignment
		for (int i = index; path[i] != 0; ++i)
		{
			int count = 0;

			for (int j = i; path[j] != '\\' && path[j] != 0; ++j)
			{
				count++;
			}
			char* nextPath = new char[count + 1];
			int n = 0;
			bool pathFound = 0;
			for (; path[i] != '\\' && path[i] != 0; ++i)
			{
				nextPath[n] = path[i];
				n++;
			}
			nextPath[n] = '\0';
			bool found = false;
			for (int k = 0; k < currentFolder->numberOfSubFolders; ++k)
			{
				if (turn == 1&&path[i]=='\0')
				{
					name = nextPath;
					break;
				}
				if (currentFolder->collectionOfFolder[k].name == nextPath)
				{
					currentFolder = &currentFolder->collectionOfFolder[k];
					found = true;
					break;
				}
			}
			if (found == false)
			{
				if (turn == 0)
					pathCorrect = false;
				else if (path[i] == '\0')
					pathCorrect = true;

			}
			
			if (path[i] == '\0') {
				break;
			}
		}
	}
	return currentFolder;
}
int main()
{
	
  	Filesystem zaki;
	zaki.createFolder("root\\", "OOP");
	zaki.createFolder("root\\OOP", "Assignments"); // root\oop
	zaki.createFile("root\\OOP\\Assignments", "Assignment-4.txt","File explorer");
	zaki.createFile("root\\OOP\\Assignments", "Assignment-3.txt", "Vector");
	zaki.createFile("root\\OOP\\Assignments", "Assignment-2.txt", "Sparse Matrix");
	zaki.createFile("root\\OOP\\Assignments", "Assignment-1.txt", "pointers");
	zaki.createFolder("root\\OOP\\Assignments", "Good Assignment");
	zaki.createFolder("root\\OOP\\Assignments", "Good Assignment-1");
	zaki.createFolder("root\\OOP\\Assignments", "Good Assignment-2");
	zaki.listFolder("root\\OOP\\Assignments\\");
	zaki.removeFile("root\\OOP\\Assignments\\Assignment-1.txt");
	zaki.listFolder("root\\OOP\\Assignments");
	zaki.removeFolder("root\\OOP\\Assignments\\Good Assignment-2");
	zaki.listFolder("root\\OOP\\Assignments");


}
