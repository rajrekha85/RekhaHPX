/************************************************************************************************/
/****************************    Conway's Game of Life     *************************************/
/****************************    Developed By : Rekha Raj	***********************************/
/*********************************************************************************************/ 
#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <future>

using namespace std;

int sizeofGrid=20;
int actualGrid [20][20];
int buffergrid [20][20];
int printArray();
int checkNeighborCells();
int initialGrid();
int swapGrids();

int neighborCount = 0;
int counti=0;
int countj=0;
int numberOfCells = 0;

vector<vector<int> > bufferGrid_C ( 20, vector<int> ( 20 ) );

vector<future <vector<vector<int> >>> bufferGrid_Copy;

void wait ( int seconds )
{
	clock_t endwait;
	endwait = clock () + seconds * CLOCKS_PER_SEC ;
	while (clock() < endwait) {}
}

int main(int argc, char *argv[]){
	numberOfCells = atoi(argv[1]);
	clock_t t1,t2;
	t1=clock();
	int steps=40;

	counti = numberOfCells;
	countj = numberOfCells;

	cout<<"Conway's Game of Life"<<'\n';
	cout<<"**********************";
	cout<<'\n';
	cout<<"How It Works"<<'\n';
	cout<<"=============="<<'\n';
	cout<<"1. Any live cell with fewer than two live neighbours dies, as if caused by under-population." <<'\n'; 
	cout<<"2. Any live cell with two or three live neighbours lives on to the next generation."<<'\n';
	cout<<"3. Any live cell with more than three live neighbours dies, as if by overcrowding."<<'\n';
	cout<<"4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction."<<'\n';

	initialGrid();
	for(int i=0;i<steps;i++){
		wait(1);
		printArray();
		checkNeighborCells();
		swapGrids();
	}

	t2=clock();
	double elapsed_secs = double(t2 - t1) / CLOCKS_PER_SEC;
	cout<<'\n'<<"Time Taken : " << elapsed_secs<<" secs"<<'\n';
	system("PAUSE");
	return 0;
}

int printArray(){  
	system("cls");
	for(int i=0;i<sizeofGrid;i++){
		printf("\n");
		for(int j=0;j<sizeofGrid;j++){
			cout<<actualGrid[i][j]<<" ";
		}
	}

	return 0;
}
void tryingToParallelize(int row, int column, int icount, int jcount)
{	
	if(icount < 20 && jcount < 20)
	{
		neighborCount = 0;
		for(int i=row;i<=icount;i++)
		{
			//cout<<'\n';
			for(int j=column;j<=jcount;j++)
			{
				neighborCount = 0;
				if(actualGrid[i-1][j]==1){
					neighborCount+=1;
				}

				if(actualGrid[i-1][j-1]==1){
					neighborCount+=1;	
				}

				if(actualGrid[i-1][j+1]==1){
					neighborCount+=1;
				}

				if(actualGrid[i+1][j]==1){
					neighborCount+=1;
				}

				if(actualGrid[i+1][j+1]==1){
					neighborCount+=1;
				}

				if(actualGrid[i+1][j-1]==1){
					neighborCount+=1;
				}

				if(actualGrid[i][j-1]==1){
					neighborCount+=1;
				}

				if(actualGrid[i][j+1]==1){
					neighborCount+=1;
				}
				buffergrid[i][j]=0;

				if(actualGrid[i][j]==1){
					if(neighborCount==3||neighborCount==2){
						//bufferGrid_C[i][j]=1;
						buffergrid[i][j]=1;
					}
					else{
						//bufferGrid_C[i][j]=0;
						buffergrid[i][j]=0;
					}
				}

				if(actualGrid[i][j]==0&&neighborCount==3){
					//bufferGrid_C[i][j]=1;
					buffergrid[i][j]=1;
				}
			}
		}
	}
	//return bufferGrid_C;
}

int checkNeighborCells(){

	/*
	//All the possible neighbours of a particular cell
	grid[i-1][j]
	grid[i-1][j-1]
	grid[i-1][j+1]
	grid[i+1][j]
	grid[i+1][j+1]
	grid[i+1][j-1]
	grid[i][j+1]
	grid[i][j-1]
	*/
	bufferGrid_Copy.clear();
	int p = 0;
	for(int i=1;i<=sizeofGrid-1;i=i+numberOfCells){
		if(i==1)
			counti = numberOfCells;
		for(int j=1;j<=sizeofGrid-1;j=j+numberOfCells){   
			if(j==1)
				countj = numberOfCells;
			neighborCount=0;
			async(launch::async, tryingToParallelize, i , j, counti, countj);
			neighborCount=0;
			countj = countj + numberOfCells;
		}
		counti = counti + numberOfCells;
	}
	return 0;
}


//Game begins here... Initial set up
int initialGrid(){

	for(int i=0;i<sizeofGrid;i++){
		for(int j=0;j<sizeofGrid;j++){
			actualGrid[i][j]=0;
			buffergrid[i][j]=0;
		}
	}

	//Conway's Glider
	actualGrid[2][5]=1;
	actualGrid[3][6]=1;
	actualGrid[4][4]=1;
	actualGrid[4][5]=1;
	actualGrid[4][6]=1;

	//Conway's Game of Life (TOAD)
	/*actualGrid[2][2]=1;
	actualGrid[2][3]=1;
	actualGrid[2][4]=1;
	actualGrid[3][1]=1;
	actualGrid[3][2]=1;
	actualGrid[3][3]=1;*/



	//Conway's Game of Life (Glider Gun)
	/*actualGrid[5][1]=1;
	actualGrid[5][2]=1;
	actualGrid[6][1]=1;
	actualGrid[6][2]=1;
	actualGrid[3][13]=1;
	actualGrid[3][14]=1;

	actualGrid[4][12]=1;
	actualGrid[4][16]=1;
	actualGrid[5][11]=1;
	actualGrid[5][17]=1;
	actualGrid[6][11]=1;
	actualGrid[6][15]=1;
	actualGrid[6][17]=1;
	actualGrid[6][18]=1;

	actualGrid[7][11]=1;
	actualGrid[7][17]=1;
	actualGrid[8][12]=1;
	actualGrid[8][16]=1;

	actualGrid[9][13]=1;
	actualGrid[9][14]=1;

	actualGrid[1][25]=1;
	actualGrid[2][23]=1;
	actualGrid[2][25]=1;

	actualGrid[3][21]=1;
	actualGrid[3][22]=1;

	actualGrid[4][21]=1;
	actualGrid[4][22]=1;

	actualGrid[5][21]=1;
	actualGrid[5][22]=1;

	actualGrid[6][23]=1;
	actualGrid[6][25]=1;

	actualGrid[7][25]=1;

	actualGrid[3][35]=1;
	actualGrid[3][36]=1;

	actualGrid[4][35]=1;
	actualGrid[4][36]=1;*/

	return 0;
}

//Change states
int swapGrids(){

	for(int i=0;i<sizeofGrid;i++){
		for(int j=0;j<sizeofGrid;j++){
			//actualGrid[i][j]=bufferGrid_C[i][j];
			actualGrid[i][j]=buffergrid[i][j];
		}
	}
	return 0;
}