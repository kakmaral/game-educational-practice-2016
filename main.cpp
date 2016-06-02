#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>

using namespace std;

int N=20, M=25, B=10, coordinates_x, y=8, beams[3], empty_x[3], speed=200;
long long score=0, level=1;
char arr[100][100], symbol;
char flappy = '#';
bool exitgame = false, showLevel=true;

void showTime() {
    cout << endl << endl;
    if(showLevel) {
        showLevel=false;
        for(int i=3; i>=1; i--) {
            if(i==1)
                cout << i;
            else
                cout << i << "..";
            Sleep(1000);
        }
    }
}

void showLevels() {
   if(level == 1) {
        cout << "@@       @@@@@@   @        @    @@@@@@   @@             @@" << endl;
        cout << "@@       @@        @      @     @@       @@            @@@" << endl;
        cout << "@@       @@@@@@     @    @      @@@@@    @@     @@@@@   @@" << endl;
        cout << "@@       @@          @  @       @@       @@             @@" << endl;
        cout << "@@@@@    @@@@@@       @@        @@@@@    @@@@@@         @@" << endl;
        showTime();
   }

   if(level == 2) {
        cout << "@@       @@@@@@   @        @    @@@@@@   @@             @@@@@@@" << endl;
        cout << "@@       @@        @      @     @@       @@                  @@" << endl;
        cout << "@@       @@@@@@     @    @      @@@@@    @@     @@@@@   @@@@@@@" << endl;
        cout << "@@       @@          @  @       @@       @@             @@     " << endl;
        cout << "@@@@@    @@@@@@       @@        @@@@@    @@@@@@         @@@@@@@" << endl;
        showTime();
        speed=150;
   }

   if(level == 3) {
        cout << "@@       @@@@@@   @        @    @@@@@@   @@             @@@@@@@" << endl;
        cout << "@@       @@        @      @     @@       @@                  @@" << endl;
        cout << "@@       @@@@@@     @    @      @@@@@    @@     @@@@@   @@@@@@@" << endl;
        cout << "@@       @@          @  @       @@       @@                  @@" << endl;
        cout << "@@@@@    @@@@@@       @@        @@@@@    @@@@@@         @@@@@@@" << endl;
        showTime();
        speed=100;
   }

   if(level == 4) {
        cout << "@@       @@@@@@   @        @    @@@@@@   @@              @@  @@" << endl;
        cout << "@@       @@        @      @     @@       @@              @@  @@" << endl;
        cout << "@@       @@@@@@     @    @      @@@@@@   @@     @@@@@    @@@@@@" << endl;
        cout << "@@       @@          @  @       @@       @@                  @@" << endl;
        cout << "@@@@@    @@@@@@       @@        @@@@@@   @@@@@@              @@" << endl;
        showTime();
        speed=50;
   }
}

void showTable() {
   system("cls");

   showLevels();

    if(exitgame) {
         for(int i=0; i<N; i++)
            arr[i][beams[0]]=' ';

         for(int i=0; i<N; i++) {
            for(int j=beams[0]+1; j<=beams[2]+1; j++)
                arr[i][j]=(char)219;
            }

        for(int i=empty_x[0]; i<=empty_x[2]; i++) {
            for(int j=beams[0]+1; j<=beams[2]+1; j++)
                arr[i][j] = ' ';
        }

        arr[coordinates_x][y]=flappy;
        for(int i=0; i<N; i++) {
             cout << "\t\t";
            for(int j=0; j<M; j++)
                if(i==0 || j==0 || i==N-1 || j==M-1)
                    cout << (char)219;
                else
                    cout << arr[i][j];
            cout << endl;
        }
        Sleep(1000);
        exit(0);
    }

    else if(symbol == 'w')
        coordinates_x-=2;
    else
        coordinates_x++;

    for(int i=0; i<N; i++) {
        for(int j=beams[0]; j<=beams[2]; j++)
            arr[i][j]=(char)219;
    }

    for(int i=empty_x[0]; i<=empty_x[2]; i++) {
        for(int j=beams[0]; j<=beams[2]; j++)
            arr[i][j] = ' ';
    }

    arr[coordinates_x][y]=flappy;

    for(int i=0; i<N; i++) {
        cout << "\t\t";
        for(int j=0; j<M; j++)
            if(i==0 || j==0 || i==N-1 || j==M-1)
                cout << (char)219;
            else
                cout << arr[i][j];
        cout << endl;
    }

    for(int i=0; i<N; i++)
        arr[i][beams[2]]=' ';

    for(int i=0; i<3; i++)
        beams[i]--;

    if(beams[2] < 0) {
        beams[0]= M-1;
        beams[1]=beams[0]+1;
        beams[2]=beams[0]+2;
    }

    arr[coordinates_x][y]=' ';
    symbol = ' ';
}

bool passLucky() {
    if(beams[2]==0)
        return true;
    else
        return false;
}

void showScore() {
    if(beams[2] == y-2) {
        score++;
        if(score%5==0 && score!=0) {
            level++;
            showLevel=true;
        }
    }

    cout << "Your score: " << score << endl << endl << endl;
}

bool gameOver() {
    int returnTrue=0;

    if(coordinates_x >= N-2 || coordinates_x <= 1)
        return false;

    else if(symbol == 'w' && arr[coordinates_x-1][y] == (char)219)
        return false;

    else if(symbol == 'w' && arr[coordinates_x-2][y] == (char)219) {
        exitgame = true;
        coordinates_x--;
    }

    else if(symbol == 'w' && arr[coordinates_x-2][y+1] == (char)219) {
        if(arr[coordinates_x-1][y+1] != (char)219) {
            exitgame = true;
            coordinates_x--;
        }
        else
            return false;
    }

    else if(symbol == 'w' && coordinates_x == empty_x[0] && beams[0] == y)
        exitgame = true;

    else if(symbol == 'w' && coordinates_x <= empty_x[1] && beams[0] == y) {
        exitgame = true;
        coordinates_x--;
    }

    else if(symbol != 'w' && arr[coordinates_x+1][y] == (char)219)
        return false;

    else if(coordinates_x < empty_x[0]-1 && y == beams[0])
        return false;

    else if(symbol != 'w' && coordinates_x >= empty_x[2] && beams[0] == y)
        return false;

    for(int j=beams[0]; j<=beams[2]; j++)
        if(y==j+1) {
            for(int k=0; k<=2; k++) {
                if(coordinates_x == empty_x[k]) {
                  returnTrue++;
                }
                else if(k==2 && returnTrue==0) {
                    /*cout << empty_x[0] << " " << empty_x[1] << " " << empty_x[2] << endl << coordinates_x;
                    cout << endl << beams[0] << " " << beams[1] << " " << beams[2];
                    */
                    return false;
                }
            }
        }

    return true;
}

int main() {
    bool continueGame=false;
    system("MODE CON COLS=65 LINES=35");
    coordinates_x = 7;
    beams[0]= M-1;
    beams[1]=beams[0]+1;
    beams[2]=beams[0]+2;

    srand(time(0));
    empty_x[0] = (rand()%(N-10))+5;

    while(true) {
        if(passLucky())
            empty_x[0] = (rand()%(N-10))+5;

        empty_x[1] = empty_x[0]+1;
        empty_x[2] = empty_x[0]+2;
        //empty_x[3] = empty_x[0]+3;

        if(kbhit())
            symbol = getch();

        if(!gameOver() || exitgame==true) {
            cout << "GAME OVER!" << endl;
            char cont;
            while(true) {
                cout << "Print 'c' to continue the game or 's' to stop it" << endl;
                cin >> cont;
                if(cont == 'c') {
                    continueGame=true;
                    break;
                }
                else if(cont == 's')
                    exit(0);
            }
        }

        if(continueGame) {
            continueGame=false;
            arr[coordinates_x][y]=' ';
            score=0;
            level=1;
            for(int i=0; i<N; i++) {
                for(int j=beams[0]; j<=beams[2]; j++)
                    arr[i][j]=' ';
            }
            coordinates_x = 7;
            beams[0]= M-1;
            beams[1]=beams[0]+1;
            beams[2]=beams[0]+2;
        }

        showTable();

        showScore();

        Sleep(speed);
    }


    return 0;
}
