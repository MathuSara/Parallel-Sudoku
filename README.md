# Parallel-Sudoku
<b>Introduction:</b><br>
For this project, my teammates and I implemented a Sudoku solver both using sequential and parallel programming to evaluate the efficiency of both methods in solving a Sudoku puzzle. The open mpi library was used for the parallel implementation on a High-Performance Computing Center (HPCC).

<b>Implementation</b><br><br>
<b>Sequential Implementation:</b><br><br>
The sudoku solver was writing with c++ code. It was written within a single main() function from which a “void solveSudoku()” will be called to implement the sequential sudoku solver. The sudoku board was implemented as a 2D array which will be passed into the “solveSudoku()” function. Deque data structures were used in the code to contain data corresponding to the empty cells in the sudoku and a <vector> was used to contain number choices to be filled into an empty cell. Within the function, (1) two nested for loops where used to navigate through the entire 2D array. From within the for loops, if the iterators(i,j) were on a filled box (represented by a
number other than 0 in the 2D array) the iterators will skip but if the iterators where on an empty box (represented by a non-zero number) a for loop will take a number from the vector which will then be checked against three functions (foundinCell,foundinRow and foundinCol) to check that the number was not in a cell, row or column. If the above functions all returned ‘false’ the number could then be used to fill the empty cell. This step continues for as many empty cells can be filled. In the end, all the empty cells might be filled, or some might be empty. If some cells are empty an algorithm like the Backtracking algorithm is called. The algorithm consists of two functions “search_empty_cell()” and “sudoBackTrack()”. The search_empty_cell() searches dequeues containing data corresponding to the empty cells for data indicating an empty cell. Once it finds it, it calls sudoBackTrack() to backtrack through the deque until a data corresponding to a filled cell is encountered and then another number is chosen to fill that cell after checking against constraints if it passes the function attempts to solve next box otherwise another backtracking takes place. This process continues until all the cells have been filled.<br><br>
<b>Parallel Implementation:<br>
For the parallel implementation, “open-mpi” library is used in the C++ source code. The parallel implementation involves using multiple processes (4 in this case) to each implement different number permutations of 1 – 9 to attempt to fill an empty cell. Whichever process solves the sudoku puzzle first returns its solution and aborts the other process. This will make the sudoku solver more efficient.<br><br>
<b>Results:</b><br>
<img width="404" alt="image" src="https://user-images.githubusercontent.com/82628360/208703879-40bc1750-d6d7-4fd3-98f4-bf1d82fe361c.png"><br>
<img width="357" alt="image" src="https://user-images.githubusercontent.com/82628360/208704019-7396dcf5-9c0f-4a5e-8cbf-24c9fe9a086f.png">
<br><br>

<b>Conclusion and Discussion:</b><br>
By using different number permutations with different processes, the sudoku implementation time is reduced as can be seen in figures above with Sequential implementation taking 82 microseconds to execute while Process 1 (the first process to complete for the parallel process) takes 54 microseconds.
The complexity of the sudoku solver increases depending on the number of empty cells to be filled. With medium to hard puzzles (greater than 45 empty cells), more recursion calls need to be made within the backing algorithm which leads to a Stack Overflow or segmentation fault on C++. The Backtracking algorithm needs to be implemented more efficiently to combat this issue.