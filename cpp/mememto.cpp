#include<iostream>
#include<string>
#include<vector>

using namespace std;

/* Mememto Pattern 
 * The code is referenced from 
 * https://en.wikipedia.org/wiki/Memento_pattern */

class Disk {
    friend class ComputerOriginator;
    private:
       /* If necessary, only the originator that created a
        * mememto is allowed to use it */
       const string data;
       Disk(const string & d): data(d) {}
       const string &ReadData() const {
           return data;
       }
};

class ComputerOriginator {
    public:
        Disk CreateDiskMememto() {
            return Disk(data);
        }

        void DownloadSomeData(const string &d) {
            data = d;
        }
        
        void UseData() {
            cout << data << endl;
        };
        
        void RestoreDiskMemento(const Disk &d) {
            data = d.ReadData();
        }
    private:
        string data;
};

void MementoTestCode() {
    /* Here is the Caretaker */
    ComputerOriginator co;
    co.DownloadSomeData("music ...");
    co.UseData();
    Disk d = co.CreateDiskMememto(); 
    co.DownloadSomeData("video ...");
    co.UseData();
    co.RestoreDiskMemento(d);
    co.UseData();
}

int main() {
    MementoTestCode();
}
