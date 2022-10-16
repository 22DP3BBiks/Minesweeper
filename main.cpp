#include <iostream>
#include <conio.h>

#define SPACE 32
#define ENTER 13
#define ARROW_KEY_RIGHT 77
#define ARROW_KEY_DOWN 80
#define ARROW_KEY_UP 72
#define ARROW_KEY_LEFT 75

void clear(int n){
    for(int i = 0;i<n;++i) std::cout << "\n";
}

bool isNumber(const std::string& str){
    for (char const &c : str) if (std::isdigit(c) == 0) return false;
    return true;
}

int checker(int n, int k, int width, int height, bool *mineGrid){
    bool left = true, up = true, down = true, right = true;
    if(k+1==width) right=false;
    if(k == 0) left=false;
    //std::cout << (n+1) << " " << height*2 << " ";
    if((n+1)==height*2) down=false;
    if(n == 1) up=false;
    //std::cout << (k+1==width) << " " << (k == 0) << " " << ((n+1)==height*2) << " " << (n == 1) << " ";
    int x = 0;
    if(left) x+=*(mineGrid+(n/2)*height+(k-1));
    if(right) x+=*(mineGrid+(n/2)*height+(k+1));
    if(up) x+=*(mineGrid+((n/2)-1)*height+k);
    if(down) x+=*(mineGrid+((n/2)+1)*height+k);
    if(left && up) x+=*(mineGrid+((n/2)-1)*height+(k-1));
    if(left && down) x+=*(mineGrid+((n/2)+1)*height+(k-1));
    if(right && up) x+=*(mineGrid+((n/2)-1)*height+(k+1));
    if(right && down) x+=*(mineGrid+((n/2)+1)*height+(k+1));
    //std::cout << mineGrid[n/2][k-1] << " " << mineGrid[n/2][k+1] << " " << mineGrid[(n/2)-1][k] << " " << mineGrid[(n/2)+1][k] << " " << mineGrid[(n/2)-1][k-1] << " " << mineGrid[(n/2)+1][k-1] << " " << mineGrid[(n/2)-1][k+1] << " " << mineGrid[(n/2)+1][k+1];
    return x;
}

void zeroFill(int y, int x, int *arr, int width, int height, bool *mineGrid, bool *open){
    
}

//void newMine(bool *mineGrid, int height,int width){
//    while(true){
//        int n = rand() % height;
//        int x = rand() % width;
//        if (!mineGrid[n][x]){
//            mineGrid[n][x] = true;
//            break;
//        }
//    }
//}


int main() {
    std::string difficulty[] = {"Beginner\t9\t9\t10", "Intermediate 16\t16\t40","Expert\t16\t30\t99", "Custom"};
    int height = 0, width = 0;
    clear(100);
    while(true){
        int difficultyIndex = 0, screenIndex = 0, mines = 0;
        while(screenIndex == 0){
            std::cout << "\t\tHeight\tWidth\tMines" << std::endl;
            for(int i = 0; i < 4;++i){
                std::cout << (i==difficultyIndex ? "[X]:" : "[ ]:") << difficulty[i] << std::endl;
            }
            switch (getch()) {
                case SPACE:
                    clear(100);
                    break;
                case ENTER:
                    if(difficultyIndex == 3) {
                        bool validSize = false, validMineAmount = false;
                        int inMineAmount = 0;
                        std::string inSize;
                        while (!validSize || !validMineAmount){
                            if(!validSize) {
                                std::cout << "Ievadiet lauka lielus rutis(AugstumsxPlatums), piemeram, 5x5 vai 10x10:"
                                          << std::endl;
                                std::cin >> inSize;
                                int n = inSize.find('x');
                                if (n == std::string::npos) inSize.find('X');
                                if (n != std::string::npos && n < inSize.length() && n > 0) {
                                    std::string temp = "";
                                    for (int i = 0; i < inSize.length() - n - 1; ++i) temp += inSize[i];
                                    if (isNumber(temp) && !temp.empty()) height = std::stoi(temp);
                                    temp = "";
                                    for (int i = n + 1; i < inSize.length(); ++i) temp += inSize[i];
                                    if (isNumber(temp) && !temp.empty()) width = std::stoi(temp);
                                    if (height * width > 1) validSize = true;
                                }
                            }
                            std::cout << "Ievadiet minu daudzumu:" << std::endl;
                            std::cin >> inMineAmount;
                            if(inMineAmount>0) {
                                mines = inMineAmount;
                                validMineAmount = true;
                            }
                        }
                        ++screenIndex;
                    }else if (difficultyIndex == 2){
                        mines = 99;
                        height = 16;
                        width = 30;
                        ++screenIndex;
                    }else if (difficultyIndex == 1){
                        mines = 40;
                        height = 16;
                        width = 16;
                        ++screenIndex;
                    }else if(difficultyIndex == 0){
                        mines = 10;
                        height = 9;
                        width = 9;
                        ++screenIndex;
                    }
                    clear(100);
                    break;
                case 224:
                    switch (getch()) {
                        case ARROW_KEY_DOWN:
                            if (difficultyIndex < 3) {
                                ++difficultyIndex;
                            }
                            clear(100);
                            break;
                        case ARROW_KEY_UP:
                            if (difficultyIndex > 0) {
                                --difficultyIndex;
                            }
                            clear(100);
                            break;
                    }
                    break;
            }
        }
        srand (time(nullptr));
        int maxmines = width*height-1;
        if(mines>maxmines) mines = maxmines;
        bool mineGrid[height][width], marker[height][width], open[height][width];
        for(int i = 0; i<height; ++i){
            for(int n = 0;n<width; ++n){
                marker[i][n] = false;
                mineGrid[i][n] = false;
                open[i][n] = false;
            }
        }
        for(int i = 0; i < mines; ++i){
            while(true){
                int n = rand() % height;
                int x = rand() % width;
                if (!mineGrid[n][x]){
                    mineGrid[n][x] = true;
                    break;
                }
            }
        }
        /*  0-----
         *  | 9 |
         *  |---+
         * */

        int mouse[3] = {rand() % height,rand() % width, 1}, markedCount=0;
        while (screenIndex==1) {
            clear(100+height);
            //std::cout << " Mouse index: " << mouse[0] << "h " << mouse[1] <<"w " << std::endl;
            std::cout << " Mines left: " << mines-markedCount << std::endl;
            for(int n = 0; n<height*2+1;++n) {
                if(n%2 == 1){
                    std::cout << " |";
                    for(int k=0;k<width;++k) {
                        std::string res = "";
                        res += mouse[0] == n/2 && mouse[1] == k ? '[' : ' ';
                        if(open[n/2][k]){
                            res+=std::to_string(checker(n, k, width, height, * mineGrid));
                        } else if(marker[n/2][k]){
                            res+='M';
                        } else{
                            res+='?';
                        }
                        res += mouse[0] == n/2 && mouse[1] == k ? ']' : ' ';
                        std::cout << res << "|";
                    }
                }else if (n == 0 || n+1 == height*2+1){
                    std::cout << " 0";
                    for(int k=0;k<width;++k){
                        std::cout << (k+1==width ? "---0" : "----");
                    }
                }else if(n%2 == 0){
                    std::cout << " |";
                    for(int k=0;k<width;++k){
                        std::cout << (k+1==width ? "---|" : "---+");
                    }
                }
                std::cout << std::endl;
            }
            int openCount = 0;
            for(int i = 0; i<height;++i){
                for(int x = 0; x<width;++x){
                    if(marker[i][x] && mineGrid[i][x]) ++openCount;
                    if(open[i][x]) ++openCount;
                }
            }
            if(width*height == openCount) {
                std::cout << "You Win!" << std::endl;
                --screenIndex;
            }
            switch (getch()) {
                case ENTER:
                    if(marker[mouse[0]][mouse[1]]){
                        marker[mouse[0]][mouse[1]]=false;
                        --markedCount;
                    }else{
                        marker[mouse[0]][mouse[1]]=true;
                        ++markedCount;
                    }
                    break;
                case SPACE:
                    if(mouse[2] && mineGrid[mouse[0]][mouse[1]]){
                        mineGrid[mouse[0]][mouse[1]] = false;
                        while(true){
                            int n = rand() % height;
                            int x = rand() % width;
                            if (!mineGrid[n][x]){
                                mineGrid[n][x] = true;
                                break;
                            }
                        }
                    }
                    mouse[2] = 0;
                    open[mouse[0]][mouse[1]] = true;
                    if(mineGrid[mouse[0]][mouse[1]] && open[mouse[0]][mouse[1]]){
                        std::cout << "!!!GAME OVER!!!" << std::endl;
                        --screenIndex;
                        break;
                    }
                    if(checker(mouse[0],mouse[1], width, height, *mineGrid) == 0){
                        int p[2] = {mouse[0], mouse[1]};
                        zeroFill(mouse[0], mouse[1], p, width, height, *mineGrid, *open);
                    }
                    break;
                case 224:
                    switch (getch()) {
                        case ARROW_KEY_DOWN:
                            if(mouse[0]<height-1) mouse[0]+=1;
                            break;
                        case ARROW_KEY_UP:
                            if(mouse[0] > 0) mouse[0]-=1;
                            break;
                        case ARROW_KEY_RIGHT:
                            if(mouse[1] != width-1) mouse[1]+=1;
                            break;
                        case ARROW_KEY_LEFT:
                            if(mouse[1]> 0) mouse[1]-=1;
                            break;
                    }
                    break;
            }
        }
    }
    return 0;
}