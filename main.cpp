#include <iostream>
#ifdef __linux__
#include <cstdio>
int (*getch)() = std::getchar;
#define ENTER 10
#define ARROW_KEY_RIGHT 67
#define ARROW_KEY_DOWN 66
#define ARROW_KEY_UP 65
#define ARROW_KEY_LEFT 68
#else
#include <conio.h>
#define ENTER 13
#define ARROW_KEY_RIGHT 77
#define ARROW_KEY_DOWN 80
#define ARROW_KEY_UP 72
#define ARROW_KEY_LEFT 75
#endif
#define C 99
#define SPACE 32

bool debug=false;

void clear(int n){
    for(int i = 0;i<n;++i) std::cout << "\n";
}

bool isNumber(const std::string& str){
    for (char const &c : str) if (std::isdigit(c) == 0) return false;
    return true;
}

int checker(int y, int x, int &width, int &height, bool *mineGrid){
    //if(debug) std::cout << std::endl << y << " " << x << " " << width << " " << height << " " << mineGrid << std::endl;
    bool left = true, up = true, down = true, right = true;
    if(x+1==width) right=false;
    if(x == 0) left=false;
    if(y+1==height) down=false;
    if(y == 0) up=false;
    int c = 0;
    c+= left && mineGrid[y*width+x-1];
    c+= right && mineGrid[y*width+x+1];
    c+= up && mineGrid[(y-1)*width+x];
    c+= down && mineGrid[(y+1)*width+x];
    c+= left && up && mineGrid[(y-1)*width+x-1];
    c+= left && down && mineGrid[(y+1)*width+x-1];
    c+= right && up && mineGrid[(y-1)*width+x+1];
    c+= right && down && mineGrid[(y+1)*width+x+1];
    return c;
}

void zeroFill(int y, int x, int &width, int &height, bool *mineGrid, bool *open){
    if (checker(y, x, width, height, mineGrid) == 0 && !open[y*width+x]){
        open[y*width+x]=true;
        if(y+1 != height){
            if(checker(y+1, x, width, height, mineGrid) == 0){
                zeroFill(y+1 ,x,width ,height ,mineGrid,open);
            }else if(!open[(y+1)*width+x]){
                open[(y+1)*width+x]=true;
            }
        }
        if(y > 0){
            if(checker(y-1, x, width, height, mineGrid) == 0){
                zeroFill(y-1 ,x ,width ,height ,mineGrid,open);
            }else if(!open[(y-1)*width+x]){
                open[(y-1)*width+x]=true;
            }
        }
        if(x+1 != width){
            if(checker(y,x+1,width,height,mineGrid) == 0){
                zeroFill(y ,x+1 ,width ,height ,mineGrid,open);
            }else if(!open[y*width+x+1]){
                open[y*width+x+1]=true;
            }
        }
        if(x > 0){
            if(checker(y,x-1,width,height,mineGrid) == 0){
                zeroFill(y ,x-1 ,width ,height ,mineGrid,open);
            }else if(!open[y*width+x-1]){
                open[y*width+x-1]=true;
            }
        }
    }else{
        open[y*width+x]=true;
    }
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
    //system("stty -echo");
    //std::cout << getch() << " " << getch() << " " << getch() << " " << getch() << std::endl;
    std::string difficulty[] = {"Beginner\t9\t9\t10", "Intermediate 16\t16\t40","Expert\t16\t30\t99", "Custom\t?\t?\t?"};
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
                case C:
                    debug=!debug;
                    clear(100);
                    break;
                case SPACE:
                    clear(100);
                    break;
                case ENTER:
                    if(difficultyIndex == 3) {
                        bool validSize = false, validMineAmount = false;
                        std::string inSize;
                        while (!validSize || !validMineAmount){
                            if(!validSize) {
                                std::cout << "Ievadiet lauka lielus rutis(AugstumsxPlatums), piemeram, 5x5 vai 10x10:"
                                          << std::endl;
                                std::cin >> inSize;
                                int n = inSize.find('x');
                                if (n == std::string::npos) inSize.find('X');
                                if (n != std::string::npos && n < inSize.length() && n > 0) {
                                    std::string temp;
                                    for (int i = 0; i < n; ++i) temp += inSize[i];
                                    if (isNumber(temp) && !temp.empty()) height = std::stoi(temp);
                                    temp = "";
                                    for (int i = n + 1; i < inSize.length(); ++i) temp += inSize[i];
                                    if (isNumber(temp) && !temp.empty()) width = std::stoi(temp);
                                    if ((height * width) > 1) validSize = true;
                                }
                            }
                            if(!validMineAmount){
                                std::cout << "Ievadiet minu daudzumu:" << std::endl;
                                std::cin >> mines;
                                if(mines>0) validMineAmount = true;

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
                #ifdef __linux__
                case 27:
                    if(getch() != 91) break;
                #else
                case 224:
                #endif
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
                        default:
                            clear(100);
                            break;
                    }
                    break;
                default:
                    clear(100);
                    break;
            }
        }
        srand (time(nullptr));
        if(mines>width*height-1) mines = width*height-1;
        bool mineGrid[height*width], marker[height*width], open[height*width];
        for(int i = 0; i<height*width; ++i){
            marker[i] = false;
            mineGrid[i] = false;
            open[i] = false;
        }
        for(int i = 0; i < mines; ++i){
            while(true){
                int n = rand() % height;
                int x = rand() % width;
                if (!mineGrid[n*width+x]){
                    mineGrid[n*width+x] = true;
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
            if(debug) {
                std::cout << " Is mine: " << mineGrid[mouse[0]*width+mouse[1]]<< std::endl;
                std::cout << " Mines Around: " << checker(mouse[0],mouse[1],width, height, mineGrid) << std::endl;
                std::cout << " Mouse index: " << mouse[0] << "h " << mouse[1] <<"w " << std::endl;
            }
            std::cout << " Mines left: " << mines-markedCount << std::endl;
            for(int n = 0; n<height*2+1;++n) {
                if(n%2 == 1){
                    std::cout << " |";
                    for(int k=0;k<width;++k) {
                        std::string res;
                        res += mouse[0] == n/2 && mouse[1] == k ? '[' : ' ';
                        if(open[n/2*width+k] && !mineGrid[n/2*width+k]){
                            res+=std::to_string(checker(n/2, k, width, height, mineGrid));
                        } else if(marker[n/2*width+k]){
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
            for(int i = 0; i<height*width;++i){
                if(marker[i] && mineGrid[i] || open[i] || !open[i] && mineGrid[i]) ++openCount;
            }
            if(width*height == openCount) {
                std::cout << " You Win!" << std::endl;
                --screenIndex;
            }
            switch (getch()) {
                case C:
                    debug=!debug;
                    break;
                case ENTER:
                    marker[mouse[0]*width+mouse[1]]=!marker[mouse[0]*width+mouse[1]];
                    marker[mouse[0]*width+mouse[1]] ? ++markedCount : --markedCount;
                    break;
                case SPACE:
                    if(mouse[2] && mineGrid[mouse[0]*width+mouse[1]]){
                        while(true){
                            int n = rand() % height;
                            int x = rand() % width;
                            if (!mineGrid[n*width+x]){
                                mineGrid[mouse[0]*width+mouse[1]] = false;
                                mineGrid[n*width+x] = true;
                                break;
                            }
                        }
                    }
                    mouse[2] = 0;
                    zeroFill(mouse[0], mouse[1], width, height, mineGrid, open);
                    if(mineGrid[mouse[0]*width+mouse[1]] && open[mouse[0]*width+mouse[1]]) {
                        std::cout << " !!!GAME OVER!!!" << std::endl;
                        --screenIndex;
                        break;
                    }
                    break;
                #ifdef __linux__
                case 27:
                    if(getch() != 91) break;
                #else
                case 224:
                #endif
                    switch (getch()) {
                        case ARROW_KEY_DOWN:
                            if(mouse[0]+1!=height) mouse[0]+=1;
                            break;
                        case ARROW_KEY_UP:
                            if(mouse[0] != 0) mouse[0]-=1;
                            break;
                        case ARROW_KEY_RIGHT:
                            if(mouse[1]+1!= width) mouse[1]+=1;
                            break;
                        case ARROW_KEY_LEFT:
                            if(mouse[1] != 0) mouse[1]-=1;
                            break;
                    }
                    break;
            }
        }
    }
    return 0;
}