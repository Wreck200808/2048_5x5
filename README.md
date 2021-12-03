# 2048_5x5 
Group No.:2   
Group members:Lu Xiaoyi(3035770678) & Yu Wenfan (3035772274)   
Topic:2048_5x5

Game Discription: 2048_5x5 is a game similar to the original 2048 but have more features. There are 5*5, 25 in total boxes in the game. There can be number like 2, 4, 8 or larger in the box or the box is empty. There is no limitation on the largest number. You can slide all the numbers in one direction and the same number will be added and combined into one number. Then one empty box in the line of the opposite slide direction will be filled in 2 or 4 randomly. When there is no empty box for new number, the game is over and the largest number will be recorded. After you enter the game, you are asked to type the command and press "enter" to carry out the order. There are 8 legal commands in total. 
  "a", "d", "w", "s" represent slide the boxes to left, right, up, down respectively. 
  "q" means using a prop to guarantee the the next number is 8 while you have only 3 props at the start of the game. 
  "z" means revoke your last slide action. 
  "x" means restart the game. 
  "e" means exit the game. If you exit the unfinished game, you will automatically continue this game when you enter the game next time. 

Features to implement: For the basic game rules, the game rules will first be explained and the game board will be shown on the interface. Then the player is asked to input the command, i.e. which one of the four directions to move. If the player wants to use the prop, he can input the corresponding word. The changed board be displayed again. Unless the game is over, the loop will continue. After the game is over, the final score will be displayed.

Code Requirement:
1(Generation of random game sets or events): The occuring position of the next new number will be randomly generated.
2(Data structures for storing game status): The numbers on the board will be stored in an matrix array. The score and game stages will be stored in variables.
3(Dynamic memory management): Due to our game rules, the size of the array storing data is fixed 5*5. When the numbers are combined or added, the array will use functions to modify.
4(File input/output (e.g., for loading/saving game status): When the player exit the unfinished game. the numbers in the array will be stored in a text file. When the game reloads, the numbers will be extracted from the text file automatically.
5(Program codes in multiple files): Most game features will be realized in functions stored in mutiple files.

Compilation and execution instructions: "make 2048" for compilation and "./2048" for execution in the directory.
