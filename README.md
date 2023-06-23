# Custom Shell+
A C program which builds a shell environment with custom commands utilizing advanced programming techniques including process creation and control, file descriptors, signals, and pipes.

## How to install & run
- Clone the repository from Github on a Linux virtual machine
- Enter the terminal and run ``` gcc shell.c tree.c list.c path.c exit.c -o shell ``` 
- Run the executable file in the terminal using ``` ./shell ```


## Shell Format
![Screenshot 2022-11-30 181105](https://user-images.githubusercontent.com/60550186/204937426-bdd0e625-091a-40f6-8e5c-67bfda680a88.png)

## Custom Commands
_shell*_ - An environment in which the following commands will be executed. The shell will not quit unless the exit command is executed. The shell shows a different command prompt (one that does not include $ and >). </br></br>
_tree*_ - Make a directory named Dir0. The working directory will then be changed to Dir0. Create three empty text files, t1.txt, t2.txt, and t3.txt, as well as one empty directory called Dir1 within it. </br></br>
_list*_ - Clear the terminal screen and output a detailed list of the current directory's contents to the terminal and t1.txt. Finally, it will rename the text file to tree.txt. </br></br>
_path*_ - Print the current directory's path to the terminal and t2.txt, and rename the text file path.txt. Concatenate the contents of tree.txt and path.txt into t3.txt and rename it log.txt. Finally, remove tree.txt and path.txt from the directory. </br></br>
_exit*_ - Print a list of the previous four commands to the terminal, as well as a full list of the current directory's contents. Finally, wait for the user to press the "return" key to end the shell and return control to the actual shell software on your system. </br>

## Project Running
![2022-12-01 00-42-42](https://user-images.githubusercontent.com/60550186/204976739-52f93856-e6ba-4568-a77e-7d12dff93acd.gif)

## Collaborators
shell* - https://github.com/Chris41700 </br>
tree* - https://github.com/EstimadaE </br>
list* - https://github.com/khadillacs </br>
path* - https://github.com/PatrickLisiecki </br>
exit* - https://github.com/OscarJ202 </br>
