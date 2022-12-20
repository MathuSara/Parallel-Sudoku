#include <iostream>
#include <queue>
#include <vector>
#include <chrono>
#include <mpi.h>

using namespace std;
using namespace std::chrono;

// declare function prototypes
void search_empty_cell(int arr[9][9], deque<int> prevI, deque<int> prevJ, deque<int> prevNum, deque<int> temp_prevI, deque<int> temp_prevJ, deque<int> temp_prevNum);
void sudoBackTrack(int arr[9][9], deque<int> prevI, deque<int> prevJ, deque<int> prevNum, deque<int> temp_prevI, deque<int> temp_prevJ, deque<int> temp_prevNum);

int notfoundinRow(int arr[9][9], int i, int num)
{
	for (int j = 0; j < 9; j++)
	{
		if (num == arr[i][j])
		{
			return 0;
		}
		else
		{
			continue;
		}
	}
	return 1;
	
}

int notfoundinColumn(int arr[9][9], int j, int num)
{
	for (int i = 0; i < 9; i++)
	{
		if (num == arr[i][j])
		{
			return 0;
		}
		else
		{
			continue;
		}
	}
	return 1;
}

int notfoundinCell(int i, int j, int arr[9][9], int num)
{
	int cell_or_i = int(i / 3) * 3;
	int cell_or_j = int(j / 3) * 3;

	for (int i = cell_or_i; i < (cell_or_i + 3); i++)
	{
		for (int j = cell_or_j; j < (cell_or_j + 3); j++)
		{
			if (arr[i][j] == num)
			{
				return 0;
			}
			else
			{
				continue;
			}
		}
	}
	return 1;
}



void dispSudoku(int arr[9][9])
{
	cout << endl;
	cout << endl;
	for (int i = 0; i < 9; i++)
	{
		cout << "                                     ";
		for (int j = 0; j < 9; j++)
		{
			if (arr[i][j] == 0)
			{
				cout << "." << "   ";
			}
			else
			{
				cout << arr[i][j] << "   ";
			}
		}
		cout << endl;
		cout << endl;
	}
		

}

void search_empty_cell(int arr[9][9], deque<int> prevI, deque<int> prevJ, deque<int> prevNum, deque<int> temp_prevI, deque<int> temp_prevJ, deque<int> temp_prevNum)
{
	if (prevNum.back() == 0 && !prevNum.empty())
	{
		temp_prevNum.push_back(prevNum.back()); temp_prevI.push_back(prevI.back()); temp_prevJ.push_back(prevJ.back());
		prevNum.pop_back(); 
		prevI.pop_back(); 
		prevJ.pop_back();
		sudoBackTrack(arr, prevI, prevJ, prevNum, temp_prevI, temp_prevJ, temp_prevNum);
	}
	else if (prevNum.back() != 0 && !prevNum.empty())
	{
		temp_prevNum.push_back(prevNum.back()); temp_prevI.push_back(prevI.back()); temp_prevJ.push_back(prevJ.back());
		prevNum.pop_back(); prevI.pop_back(); prevJ.pop_back();
		search_empty_cell(arr, prevI, prevJ, prevNum, temp_prevI, temp_prevJ, temp_prevNum);
	}
	if (temp_prevNum.empty())
	{
		return;
	}
}

void sudoBackTrack(int arr[9][9], deque<int> prevI, deque<int> prevJ, deque<int> prevNum, deque<int> temp_prevI, deque<int> temp_prevJ, deque<int> temp_prevNum)
{

		if (prevNum.back() == 0)
		{
			search_empty_cell(arr, prevI, prevJ, prevNum, temp_prevI, temp_prevJ, temp_prevNum);
		}
		else
		{
			string solved_cell_flag = "false"; //flag to check if cell has been solved
			int i = prevI.back(); int j = prevJ.back(); int numSel = prevNum.back() + 1;
		
			while (!temp_prevNum.empty())
			{
				///////vector implementation///////////////////////////////////////////////
				int c = 0;
				vector<int>numSel_V;
				while (c < 9)
				{
					if (numSel > 9)
					{
						numSel_V.push_back(numSel - 9);
					}
					else
					{
						numSel_V.push_back(numSel);
					}
					numSel++; c++;
				}

				///////////////////////////////////////////////////////////////////////////
				for (int iter = 0; iter < 9; iter++)
				{
					int num = numSel_V[iter];
					int notfoundinRo = notfoundinRow(arr, i, num);
					int notfoundinCol = notfoundinColumn(arr, j, num);
					int notfoundinC = notfoundinCell(i, j, arr, num);
					if (notfoundinRo == 1 && notfoundinCol == 1 && notfoundinC == 1)
					{
						// assign choosen number to empty cell
						arr[i][j] = num;
						prevNum.pop_back(), prevI.pop_back(), prevJ.pop_back();
						//populate queues with i,j and num values for filled cell
						prevI.push_back(i); prevJ.push_back(j);prevNum.push_back(num);
						i = temp_prevI.back(); j = temp_prevJ.back(); num = temp_prevNum.back();
						temp_prevI.pop_back(); temp_prevJ.pop_back(); temp_prevNum.pop_back();
						prevI.push_back(i); prevJ.push_back(j); prevNum.push_back(num);
						solved_cell_flag = "true";
						dispSudoku(arr);
						break;
					}
				}
				// check if at the beginning of the dequeue containing sudoku location and if no number choosen above select previous choice since that is the only choice.
				if (prevNum.size() == 1)
				{
					int num = 0;
					solved_cell_flag = "true";
					i = temp_prevI.back(); j = temp_prevJ.back(); num = temp_prevNum.back();
					temp_prevI.pop_back(); temp_prevJ.pop_back(); temp_prevNum.pop_back();
					prevI.push_back(i); prevJ.push_back(j); prevNum.push_back(num);
				}
				if (solved_cell_flag == "false")
				{
					arr[i][j] = 0;
					prevNum.back() = 0;
					search_empty_cell(arr, prevI, prevJ, prevNum, temp_prevI, temp_prevJ, temp_prevNum);
				}
				solved_cell_flag = "false";
				numSel = 1;

			}
			search_empty_cell(arr, prevI, prevJ, prevNum, temp_prevI, temp_prevJ, temp_prevNum);
		}
	
}


void solveSudoku(int arr[9][9], deque<int> prevI, deque<int> prevJ, deque<int> prevNum, deque<int> temp_prevI, deque<int> temp_prevJ, deque<int> temp_prevNum)
{
	int cnt = 0;
	string cell_unsolved_flag = "false";
	string exit_loop = "false";
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (arr[i][j] != 0)
			{
				continue;
			}
			else
			{
				for (int num = 1; num < 10; num++)
				{
					int notfoundinRo = notfoundinRow(arr, i,num);
					int notfoundinCol = notfoundinColumn(arr, j,num);
					int notfoundinC = notfoundinCell(i, j, arr, num);
					if (notfoundinRo == 1 && notfoundinCol == 1 && notfoundinC == 1)
					{
						arr[i][j] = num;
						cnt++;
						exit_loop = "true";
						//populate queues with i,j and num values for filled cell
						prevI.push_back(i);
						prevJ.push_back(j);
						prevNum.push_back(num);
						break;
					}
				}
				if (exit_loop == "false")
				{
					cnt++;
					//populate queues with i,j and 0 value for unfilled cell
					prevI.push_back(i);
					prevJ.push_back(j);
					prevNum.push_back(0);
					cell_unsolved_flag = "true"; //flag to check if all sudoku empty cells have been solved
					exit_loop = "false";
				}
				exit_loop = "false";
			}
		}
	}
	
	if (cell_unsolved_flag == "true")
	{
		// pass queues for i,j and num values of previous solved empty cells into SudoBackTrack() function to solve remaining unsolved cells
		search_empty_cell(arr, prevI, prevJ, prevNum, temp_prevI, temp_prevJ, temp_prevNum);

	}
	
}

bool parallelSudokuSolver(int arr[9][9], int argc, char** argv, vector<int> numSel_V, deque<int> prevI, deque<int> prevJ, deque<int> prevNum, deque<int> temp_prevI, deque<int> temp_prevJ, deque<int> temp_prevNum)
{
	{
		int cnt = 0;
		string cell_unsolved_flag = "false";
		string exit_loop = "false";
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (arr[i][j] != 0)
				{
					continue;
				}
				else
				{
					for (int iter = 0; iter < 9; iter++)
					{
						int num = numSel_V[iter];
						int notfoundinRo = notfoundinRow(arr, i, num);
						int notfoundinCol = notfoundinColumn(arr, j, num);
						int notfoundinC = notfoundinCell(i, j, arr, num);
						if (notfoundinRo == 1 && notfoundinCol == 1 && notfoundinC == 1)
						{
							arr[i][j] = num;
							cnt++;
							exit_loop = "true";
							//populate queues with i,j and num values for filled cell
							prevI.push_back(i);
							prevJ.push_back(j);
							prevNum.push_back(num);
							break;
						}
					}
					if (exit_loop == "false")
					{
						cnt++;
						//populate queues with i,j and 0 value for unfilled cell
						prevI.push_back(i);
						prevJ.push_back(j);
						prevNum.push_back(0);
						cell_unsolved_flag = "true"; //flag to check if all sudoku empty cells have been solved
						exit_loop = "false";
					}
					exit_loop = "false";
				}
			}
		}
	
		if (cell_unsolved_flag == "true")
		{
			// pass queues for i,j and num values of previous solved empty cells into SudoBackTrack() function to solve remaining unsolved cells
			search_empty_cell(arr, prevI, prevJ, prevNum, temp_prevI, temp_prevJ, temp_prevNum);

		}
		
	}
	return true;
}

int main(int argc, char** argv)
{
	deque<int> prevI; //this deque data structure keeps track of the i values of all the empty cells being filled
	deque<int> prevJ; //this deque data structure keeps track of the j values of all the empty cells being filled
	deque<int> prevNum; //this deque data structure keeps track of the number selection of all the empty cells being filled
	deque<int> temp_prevI; //temporary deque data structure to store data from prevI
	deque<int> temp_prevJ; //temporary deque data structure to store data from prevJ
	deque<int> temp_prevNum; //temporary deque data structure to store data from prevNum
	
	//Very Easy puzzle with 20 empty cells
	int arr[9][9] = {
		{5, 3, 0, 0, 7, 0, 0, 1, 2},
		{6, 7, 0, 0, 9, 5, 3, 4, 8},
		{1, 9, 8, 3, 4, 0, 0, 6, 7},
		{8, 5, 9, 7, 6, 0, 4, 2, 3},
		{4, 2, 0, 8, 5, 3, 0, 9, 1},
		{7, 1, 0, 9, 2, 4, 0, 5, 6},
		{9, 6, 0, 0, 0, 7, 2, 8, 4},
		{2, 8, 7, 4, 0, 0, 0, 0, 5},
		{3, 4, 5, 2, 8, 6, 1, 7, 9}
	};
	
	//Very Easy puzzle with 20 empty cells
	int arr1[9][9] = {
		{5, 3, 0, 0, 7, 0, 0, 1, 2},
		{6, 7, 0, 0, 9, 5, 3, 4, 8},
		{1, 9, 8, 3, 4, 0, 0, 6, 7},
		{8, 5, 9, 7, 6, 0, 4, 2, 3},
		{4, 2, 0, 8, 5, 3, 0, 9, 1},
		{7, 1, 0, 9, 2, 4, 0, 5, 6},
		{9, 6, 0, 0, 0, 7, 2, 8, 4},
		{2, 8, 7, 4, 0, 0, 0, 0, 5},
		{3, 4, 5, 2, 8, 6, 1, 7, 9}
	};
	
	/*
	//Medium puzzle with 43 empty cells
	int arr[9][9] = {
		{3,0,0,0,2,9,5,0,1},
		{1,0,8,3,0,0,4,2,9},
		{0,0,6,5,0,0,3,6,0},
		{0,0,0,0,7,6,0,0,0},
		{0,0,0,1,3,8,0,0,7},
		{8,0,0,9,0,0,6,0,0},
		{4,6,0,0,5,0,8,0,2},
		{0,8,0,6,0,3,0,4,0},
		{7,3,5,4,8,0,0,9,0}
	};
	*/
	/*
	//Medium puzzle with 43 empty cells
	int arr1[9][9] = {
		{3,0,0,0,2,9,5,0,1},
		{1,0,8,3,0,0,4,2,9},
		{0,0,6,5,0,0,3,6,0},
		{0,0,0,0,7,6,0,0,0},
		{0,0,0,1,3,8,0,0,7},
		{8,0,0,9,0,0,6,0,0},
		{4,6,0,0,5,0,8,0,2},
		{0,8,0,6,0,3,0,4,0},
		{7,3,5,4,8,0,0,9,0}
	};
	*/
		
	/*
	//hard puzzle
		int arr1[9][9] = {
		{5,3,0,0,7,0,0,0,0},
		{6,0,0,1,9,5,0,0,0},
		{0,9,8,0,0,0,0,6,0},
		{8,0,0,0,6,0,0,0,3},
		{4,0,0,8,0,3,0,0,1},
		{7,0,0,0,2,0,0,0,6},
		{0,6,0,0,0,0,2,8,0},
		{0,0,0,4,1,9,0,0,5},
		{0,0,0,0,8,0,0,7,9}
	};
	*/

	//MPI Initiallization
	int nprocs, mypid; // declaring number of processors and process id
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &mypid);
	MPI_Status status;
	bool parallel_comp = false;
	
	if (mypid > 0 && mypid < 5)
	{
		vector<int> numSel_V;
		if (mypid == 1)
		{
			for (int i = 1; i < 10; i++)
			{
				numSel_V.push_back(i);
			}
			// Get starting time
			auto start = high_resolution_clock::now();
			parallel_comp = parallelSudokuSolver(arr1, argc, argv, numSel_V, prevI, prevJ, prevNum, temp_prevI, temp_prevJ, temp_prevNum);
			// Get ending time
			auto stop = high_resolution_clock::now();

			MPI_Send(&parallel_comp, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
			bool display_sudoku = false;
			MPI_Recv(&display_sudoku, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			if (display_sudoku)
			{
				dispSudoku(arr1);
				auto exec_duration = duration_cast<microseconds>(stop - start);
				cout << "Total time of execution for process 1 is " << exec_duration.count() << " microseconds" << endl;
				cout << endl;
			}
		}
		if (mypid == 2)
		{
			for (int i = 2; i < 10; i++)
			{
				numSel_V.push_back(i);
			}
			numSel_V.push_back(1);
			// Get starting time
			auto start = high_resolution_clock::now();
			parallel_comp = parallelSudokuSolver(arr1, argc, argv, numSel_V, prevI, prevJ, prevNum, temp_prevI, temp_prevJ, temp_prevNum);
			// Get ending time
			auto stop = high_resolution_clock::now();

			MPI_Send(&parallel_comp, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
			bool display_sudoku = false;
			MPI_Recv(&display_sudoku, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			if (display_sudoku)
			{
				dispSudoku(arr1);
				auto exec_duration = duration_cast<microseconds>(stop - start);
				cout << "Total time of execution for process 2 is " << exec_duration.count() << " microseconds" << endl;
				cout << endl;
			}
		}
		if (mypid == 3)
		{
			for (int i = 3; i < 10; i++)
			{
				numSel_V.push_back(i);
			}
			numSel_V.push_back(1); numSel_V.push_back(2);
			// Get starting time
			auto start = high_resolution_clock::now();
			parallel_comp = parallelSudokuSolver(arr1, argc, argv, numSel_V, prevI, prevJ, prevNum, temp_prevI, temp_prevJ, temp_prevNum);
			// Get ending time
			auto stop = high_resolution_clock::now();

			MPI_Send(&parallel_comp, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
			bool display_sudoku = false;
			MPI_Recv(&display_sudoku, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			if (display_sudoku)
			{
				dispSudoku(arr1);
				auto exec_duration = duration_cast<microseconds>(stop - start);
				cout << "Total time of execution for process 3 is " << exec_duration.count() << " microseconds" << endl;
				cout << endl;
			}
		}
		if (mypid == 4)
		{
			for (int i = 4; i < 10; i++)
			{
				numSel_V.push_back(i);
			}
			numSel_V.push_back(1); numSel_V.push_back(2); numSel_V.push_back(3);
			// Get starting time
			auto start = high_resolution_clock::now();
			parallel_comp = parallelSudokuSolver(arr1, argc, argv, numSel_V, prevI, prevJ, prevNum, temp_prevI, temp_prevJ, temp_prevNum);
			// Get ending time
			auto stop = high_resolution_clock::now();
			
			MPI_Send(&parallel_comp, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
			bool display_sudoku = false;
			MPI_Recv(&display_sudoku, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			if (display_sudoku)
			{
				dispSudoku(arr1);
				auto exec_duration = duration_cast<microseconds>(stop - start);
				cout << "Total time of execution for process 4 is " << exec_duration.count() << " microseconds" << endl;
				cout << endl;
			}
		}
	}


	if (mypid == 0)
	{
		MPI_Recv(&parallel_comp, 1, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &status);
		if (parallel_comp)
		{
			cout << "parallel_comp " << parallel_comp << endl;
			cout << "**************************************Sudoku Implemented Sequentially******************************************** " << endl;
			dispSudoku(arr);
			// Get starting time
			auto start = high_resolution_clock::now();
			solveSudoku(arr, prevI, prevJ, prevNum, temp_prevI, temp_prevJ, temp_prevNum);
			// Get ending time
			auto stop = high_resolution_clock::now();
			dispSudoku(arr);
			auto exec_duration = duration_cast<microseconds>(stop - start);
			cout << "Total time of execution is " << exec_duration.count() << " microseconds" << endl;
			cout << endl;
			cout << "**************************************Sudoku Implemented in Parallel*********************************************" << endl;
			bool display_sudoku = true;
			MPI_Send(&display_sudoku, 1, MPI_INT, status.MPI_SOURCE, 1, MPI_COMM_WORLD);
			return 0;
		}
	}
	MPI_Finalize();
}
