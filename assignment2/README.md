# Assignment 2: Knight Problem - Recursion

## Description
The knight will have some starting position, and the programs job
is to construct a tour (write the knight move counter) onto each element of the board to construct
a knight tour on a given (n x n) board and given the knight’s initial coordinates. You will need to use a
recursive back tracking approach (using a heuristic approach defined later in this write up). 

### Steps
1. Set the board[r][c] with tourIndex
2. Check if the board is full if so, return true
3. Get all the available moves from location [r, c]
4. Pick the available move with the minimal onward moves
5. Make a recursive call to this function, pass in the new r and c values using the chosen available move from the above step 2
6. If the function returns true then simply return true, otherwise go back to step 4 but pick the next smallest onward moves from available moves

## Sample Run
```
Enter board dimension: 8
Enter initial knight position: 4 5

Knight FTW

A B C D E F G H
A 24 33 10 5 26 31 12 3
B 9 6 25 32 11 4 27 30
C 34 23 8 49 36 29 2 13
D 7 48 35 58 1 50 37 28
E 22 59 20 47 56 63 14 41
F 19 46 57 64 51 40 55 38
G 60 21 44 17 62 53 42 15
H 45 18 61 52 43 16 39 54

Functions called: 64

Another go? y

Enter board dimension: 8
Enter initial knight position: 8 8

Knight FTW

A B C D E F G H
A 63 10 29 26 41 12 31 16
B 28 25 64 11 30 15 42 13
C 9 62 27 54 43 40 17 32
D 24 51 44 61 36 53 14 39
E 45 8 59 52 55 38 33 18
F 50 23 48 37 60 35 56 3
G 7 46 21 58 5 2 19 34
H 22 49 6 47 20 57 4 1
Functions called: 64

Another go? n

```
