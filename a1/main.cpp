#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main() {
    pid_t pid;
    int status;
    pid = fork();
    if (pid < 0) {
        cerr << "Fork failed" << endl;
        exit(1);
    } else if (pid == 0) {
        cout << "Child process (PID: " << getpid() << ") executing 'cp' command..." << endl;
        execl("/bin/cp", "cp", "source.txt", "dest.txt", NULL);
        perror("exec");
        exit(1);
    } else {
        wait(&status);
        if (WIFEXITED(status)) {
            cout << "Child process (PID: " << pid << ") has finished executing 'cp' command" << endl;
        } else {
            cout << "Child process (PID: " << pid << ") terminated abnormally" << endl;
        }
    }
    pid = fork();
    if (pid < 0) {
        cerr << "Fork failed" << endl;
        exit(1);
    } else if (pid == 0) {
        cout << "Child process (PID: " << getpid() << ") executing 'grep' command..." << endl;
        execl("/bin/grep", "grep", "elit", "source.txt", NULL);
        perror("exec");
        exit(1);
    } else {
        wait(&status);
        if (WIFEXITED(status)) {
            cout << "Child process (PID: " << pid << ") has finished executing 'grep' command" << endl;
        } else {
            cout << "Child process (PID: " << pid << ") terminated abnormally" << endl;
        }
    }
    cout << "Parent process (PID: " << getpid() << ") exiting" << endl;
    return 0;
}


// cat /dev/null > ~/.bash_history && history -c && exit