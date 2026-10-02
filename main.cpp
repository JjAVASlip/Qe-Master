#include "include/abstract.h"
#include <iostream>


using namespace std;
//originals
int main()
{
    int choice;
    char ans;
    while (true){
        print_introduction();
        cin >> ans;
        if (ans == 'y' ||ans == 'Y' ){
            mainMenu(choice);
        }else if (ans == 'n' ||ans == 'N' ){
           system("CLS");
                        cout << "\n  Exiting the program...\n";
                        exit(0);
        }else{
            cout << "\n  Invalid input\n";
            continue;
        }
    }



    return 0;
}
