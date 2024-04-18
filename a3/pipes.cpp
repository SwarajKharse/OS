#include <iostream>
#include <unistd.h>

using namespace std;

int main() {
    int pipe1[2], pipe2[2];
    int status1, status2;
    int pid;
    char pipe1msg[20];
    char pipe2msg[20];
    char readmessage[20];
    status1 = pipe(pipe1);

    if (status1 == -1) {
        cout << "Pipe 1 not created" << endl;
        return 1;
    }
    status2 = pipe(pipe2);

    if (status2 == -1) {
        cout << "Pipe 2 not created" << endl;
        return 1;
    }
    pid = fork();

    if (pid != 0) {
        close(pipe1[0]);
        close(pipe2[1]);
        cout << "Enter Parent msg to Child: ";
        cin >> pipe1msg;
        cout << "In Parent: Writing to pipe 1 – Message is " << pipe1msg << endl;
        write(pipe1[1], pipe1msg, sizeof(pipe1msg));
        read(pipe2[0], readmessage, sizeof(readmessage));
        cout << "In Parent: Reading from pipe 2 – Message is " << readmessage << endl;
    } else {
        close(pipe1[1]);
        close(pipe2[0]);
        read(pipe1[0], readmessage, sizeof(readmessage));
        cout << "In Child: Reading from pipe 1 – Message is " << readmessage << endl;
        cout << "Enter Child msg to Parent: ";
        cin >> pipe2msg;
        cout << "In Child: Writing to pipe 2 – Message is " << pipe2msg << endl;
        write(pipe2[1], pipe2msg, sizeof(pipe2msg));
    }
    return 0;
}
