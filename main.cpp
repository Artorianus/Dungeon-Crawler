#include <bits/stdc++.h>
#define f first
#define s second
using namespace std;
const int N = 10;

int playField[N][N], DirectionsX[4] = {-1, 0, 1, 0}, DirectionsY[4] = {0, 1, 0, -1}, PosX, PosY, Traps[N][N], cnt;
int seed = chrono::high_resolution_clock::now().time_since_epoch().count();
auto xRand = bind( uniform_int_distribution<int>(0,N-1), mt19937(seed) );
auto yRand = bind( uniform_int_distribution<int>(0,N-1), mt19937(seed*23) );

void Game(int playerPosX, int playerPosY, int field[N][N]);

void sideOutput( int playerPosX, int playerPosY, int field[N][N] ){
    int plsHldr;
    cout << "Enter '1' to proceed the game: ";
    cin >> plsHldr;
    system("cls");
    Game( playerPosX, playerPosY, field );
}

bool outOfBorders( int x, int y ){
    if( x >= 0 && x < N && y >= 0 && y < N )
        return false;
    return true;
}

void Game( int playerPosX, int playerPosY, int field[N][N] ){
    string Command;
    if( field[playerPosX][playerPosY] == 1 || outOfBorders( playerPosX, playerPosY ) ){
        cout << "Game over...";
        system("pause");
        return;
    }
    if( field[playerPosX][playerPosY] == 3 ){
        cout << "You won the game!";
        system("pause");
        return;
    }
    field[playerPosX][playerPosY] = 2;
    for( int i = 0; i < N; i++ ){
        for( int j = 0; j < N; j++ ){
            cout << field[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << '\n' << "Enter 'legend' for the map legend, 'help' for command list or movement comand: ";
    cin >> Command;
    if( Command == "legend" ){
        cout << "'0' - Empty space" << '\n' << "'1' - A trap" << '\n' << "'2' - The player" << '\n' << "'3' - Finish" << '\n' << "You need to move to finish to win the game, but touching traps or getting out of borders will give you a game over" << '\n';
        sideOutput( playerPosX, playerPosY, field );
    }
    else{
        if( Command == "help" ){
            cout << "'down' moves hero one cell down" << '\n';
            cout << "'left' moves hero one cell left" << '\n';
            cout << "'up' moves hero one cell up" << '\n';
            cout << "'right' moves hero one cell right" << '\n';
            cout << "Enter '1' to proceed the game: ";
            sideOutput( playerPosX, playerPosY, field );
        }
        else{
            field[playerPosX][playerPosY] = 0;
            system("cls");
            if( Command == "down" )
                Game( playerPosX+1, playerPosY, field );
            if( Command == "up" )
                Game( playerPosX-1, playerPosY, field );
            if( Command == "left" )
                Game( playerPosX, playerPosY-1, field );
            if( Command == "right" )
                Game( playerPosX, playerPosY+1, field );
        }
    }
    system("cls");
    return;
}

bool pathAvailable( int field[N][N] ){
    int used[N][N];
    for( int i = 0; i < N; i++ ){
        for( int j = 0; j < N; j++ )
            used[i][j] = 0;
    }
    used[0][0]++;
    vector <pair<int, int>> Qu = {}, globalQu = {};
    globalQu.push_back( {0, 0} );
    while( globalQu.size() ){
        for( auto i : globalQu ){
            for( int j = 0; j < 4; j++ ){
                if( !outOfBorders(i.f+DirectionsX[j], i.s+DirectionsY[j]) ){
                    if( !used[i.f+DirectionsX[j]][i.s+DirectionsY[j]] && !field[i.f+DirectionsX[j]][i.s+DirectionsY[j]] ){
                        used[i.f+DirectionsX[j]][i.s+DirectionsY[j]]++;
                        Qu.push_back( {i.f+DirectionsX[j], i.s+DirectionsY[j]} );
                    }
                }
            }
        }
        globalQu = Qu;
        Qu = {};
    }
    if( used[N-1][N-1] )
        return true;
    else
        return false;
}

void Roll(){
    int x = xRand(), y = yRand();
    playField[x][y]++;
    if( !pathAvailable( playField ) || playField[0][0] == 1 || Traps[x][y] )
        playField[x][y]--,
        Roll();
    else
        Traps[x][y]++,
        cnt++;
    return;
}

void createField( int field[N][N] ){
    for( int i = 0; i < (N/2)*N; i++ ){
        Roll();
    }
    return;
}

int main()
{
    createField(playField);
    playField[N-1][N-1] = 3;
    cout << cnt << endl;
    Game( 0, 0, playField );
    system("cls");
    return 0;
}
