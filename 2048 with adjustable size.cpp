//2048 with adjustable size.cpp
#include <iostream>
#include <iomanip>
#include "rnd.h"
#include <ctime>
#include <Windows.h>
using namespace std;

int main(){
	srand(time(NULL));
	bool FPM;	//having found possible moves, don't need to inspect more
	bool MDF;	//modification occured, can start a new iteration
	while(1){
		//initialize
		system("CLS");
		cout<<"2048 with adjustable size    by Eric Yu 2015/6/23"<<endl
			<<"                                e841018@gmail.com"<<endl
			<<"Enter the size you want: ";
		short n;	//size
		while(cin>>n){
			if(n<2) cout<<"Too small. Please enter again: ";
			else break;
		}
		unsigned short a[n][n];
		memset(a,0,sizeof(short)*n*n);
		int score=0;
		//game start
		while(1){
			//generate----------------------------------
			short r0,r1;	//temporary rnd results
			do{
				r0=rnd(0,n-1);
				r1=rnd(0,n-1);
			}while(0!=a[r0][r1]);
			a[r0][r1]=2;
			score+=2;
			//print----------------------------------
			system("CLS");
			cout<<"2048 with adjustable size    by Eric Yu 2015/6/23"<<endl
				<<"                                e841018@gmail.com"<<endl
				<<"score: "<<score<<endl;
			//top row
			cout<<"┌───";
			for(short i=0,k=n-1;i<k;++i) cout<<"┬───";
			cout<<"┐"<<endl;
			//body
			for(short i=0,k=n-1;i<k;++i){
				//content
				for(short j=0;j<n;++j){
					if(0==a[i][j]) cout<<"│      ";
					else cout<<"│"<<setw(6)<<a[i][j];
				}
				cout<<"│"<<endl;
				//separation line
				cout<<"├───";
				for(short i=0,k=n-1;i<k;++i) cout<<"┼───";
				cout<<"┤"<<endl;
			}
			//last row of body
			for(short j=0;j<n;++j){
				if(0==a[n-1][j]) cout<<"│      ";
				else cout<<"│"<<setw(6)<<a[n-1][j];
			}
			cout<<"│"<<endl;
			//bottom
			cout<<"└───";
			for(short i=0,k=n-1;i<k;++i) cout<<"┴───";
			cout<<"┘"<<endl;
			//instructions
			cout<<"Use arrow keys."<<endl
				<<"　↑"<<endl
				<<"←　→"<<endl
				<<"　↓"<<endl
				<<"Enter 0 to exit."<<endl;
			//inspect whether game is over----------------------------------
			FPM=0;
			while(1){
				//if find a zero then break
				for(short i=0;i<n;++i){
					for(short j=0;j<n;++j){
						if(0==a[i][j]){
							FPM=1;
							break;
						}
					}
					if(FPM) break;
				}
				if(FPM) break;
				//if find horizontally adjacent same number then break
				for(short i=0;i<n;++i){
					for(short j=1;j<n;++j){
						if(a[i][j-1]==a[i][j]){
							FPM=1;
							break;
						}
					}
					if(FPM) break;
				}
				if(FPM) break;
				//if find vertically adjacent same number then break
				for(short j=0;j<n;++j){
					for(short i=1;i<n;++i){
						if(a[i-1][j]==a[i][j]){
							FPM=1;
							break;
						}
					}
					if(FPM) break;
				}
				break;
			}
			if(0==FPM) break;	//no possible moves, game over
			//detect keyboard event and modify----------------------------------
			MDF=0;
			while(1){
				Sleep(50);
				//0 for exiting
				if(GetAsyncKeyState(0x30)) return 0;
				//left
				if(GetAsyncKeyState(VK_LEFT)){
					for(short i=0;i<n;++i){
						short z=n-1;	//n-"number of zeros at end"
						//examine if all zeros
						while((0==a[i][z])&&(z>-1)) --z;
						++z;
						if(0==z) continue;
						//eliminate zeros
						for(short j=0;j<z-1;++j){
							while(0==a[i][j]){
								for(short k=j+1;k<z;++k) a[i][k-1]=a[i][k];
								a[i][z-1]=0;
								MDF=1;
								--z;
							}
						}
						if(0==z) continue;
						//combine
						for(short j=1;j<z;++j){
							if(a[i][j-1]==a[i][j]){
								a[i][j-1]<<=1;
								for(short k=j+1;k<z;++k) a[i][k-1]=a[i][k];
								a[i][z-1]=0;
								MDF=1;
								--z;
							}
						}
					}
					if(MDF) break;
				}
				//right
				if(GetAsyncKeyState(VK_RIGHT)){
					for(short i=0;i<n;++i){
						short z=0;	//number of zeros at start
						//examine if all zeros
						while((0==a[i][z])&&(z<n)) ++z;
						if(n==z) continue;
						//eliminate zeros
						for(short j=n-1;j>z;--j){
							while(0==a[i][j]){
								for(short k=j-1;k>z-1;--k) a[i][k+1]=a[i][k];
								a[i][z]=0;
								MDF=1;
								++z;
							}
						}
						if(n==z) continue;
						//combine
						for(short j=n-2;j>z-1;--j){
							if(a[i][j+1]==a[i][j]){
								a[i][j+1]<<=1;
								for(short k=j-1;k>z-1;--k) a[i][k+1]=a[i][k];
								a[i][z]=0;
								MDF=1;
								++z;
							}
						}
					}
					if(MDF) break;
				}
				//up
				if(GetAsyncKeyState(VK_UP)){
					for(short j=0;j<n;++j){
						short z=n-1;	//n-"number of zeros at end"
						//examine if all zeros
						while((0==a[z][j])&&(z>-1)) --z;
						++z;
						if(0==z) continue;
						//eliminate zeros
						for(short i=0;i<z-1;++i){
							while(0==a[i][j]){
								for(short k=i+1;k<z;++k) a[k-1][j]=a[k][j];
								a[z-1][j]=0;
								MDF=1;
								--z;
							}
						}
						if(0==z) continue;
						//combine
						for(short i=1;i<z;++i){
							if(a[i-1][j]==a[i][j]){
								a[i-1][j]<<=1;
								for(short k=i+1;k<z;++k) a[k-1][j]=a[k][j];
								a[z-1][j]=0;
								MDF=1;
								--z;
							}
						}
					}
					if(MDF) break;
				}
				//down
				if(GetAsyncKeyState(VK_DOWN)){
					for(short j=0;j<n;++j){
						short z=0;	//number of zeros at start
						//examine if all zeros
						while((0==a[z][j])&&(z<n)) ++z;
						if(n==z) continue;
						//eliminate zeros
						for(short i=n-1;i>z;--i){
							while(0==a[i][j]){
								for(short k=i-1;k>z-1;--k) a[k+1][j]=a[k][j];
								a[z][j]=0;
								MDF=1;
								++z;
							}
						}
						if(n==z) continue;
						//combine
						for(short i=n-2;i>z-1;--i){
							if(a[i+1][j]==a[i][j]){
								a[i+1][j]<<=1;
								for(short k=i-1;k>z-1;--k) a[k+1][j]=a[k][j];
								a[z][j]=0;
								MDF=1;
								++z;
							}
						}
					}
					if(MDF) break;
				}
			}//end of "detect keyboard event and modify"
		}//end of "game start"
		//game over
		cout<<endl
			<<"Game over."<<endl
			<<"Play again?(y/n) ";
		char pa;	//play again?
		while(cin>>pa){
			switch(pa){
				case'Y':
				case'y':
					break;		//end switch
				case'N':
				case'n':
					return 0;	//end program
				default:
					cout<<"Invalid. Please enter again: ";
					continue;	//restart while
			}
			break;	//end while
		}//end of "game over"
	}
}
