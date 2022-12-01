# Operating Systems Custom Commands
A C program which builds a shell environment with custom commands utilizing advanced programming techniques including process creation and control, file descriptors, signals, and pipes.

## How to install & run
Clone the repository from Github on a Linux virtual machine </br>
Enter the terminal and create an executable file </br>
Run ``` gcc shell.c tree.c list.c path.c exit.c -o shell ``` and execute ./shell </br>


## Shell Format
![Screenshot 2022-11-30 181105](https://user-images.githubusercontent.com/60550186/204937426-bdd0e625-091a-40f6-8e5c-67bfda680a88.png)

## Custom Commands
_shell*_ - An environment that will execute the rest of the commands. The shell won't terminate unless the exit command gets executed. The shell displays a different command prompt (i.e. something other than $ and >). </br></br>
_tree*_ - Create a new directory called Dir0. Then, it will change the working directory to Dir0. Create three empty text files namely, t1.txt, t2.txt, t3.txt and one empty directory called Dir1 inside it. </br></br>
_list*_ - Clear the terminal screen and print a detailed list of all content of the current directory to the terminal and t1.txt. Finally, it will change the name of the text file to tree.txt. </br></br>
_path*_ - Print the path of the current directory to the terminal and t2.txt, and change the name of the text file to path.txt. Concatenate the content of tree.txt and path.txt into t3.txt and change the last to log.txt. Finally, delete tree.txt and path.txt. </br></br>
_exit*_ - Print a list of the last four commands to the terminal, a detailed list of all content of the current directory. Finally, wait for the user to hit the "return" key to terminate the shell and return the control to the original shell program on your machine. </br></br>

## Project Running

## Collaborators
tree* - https://github.com/EstimadaE </br>
list* - https://github.com/khadillacs </br>
path* - https://github.com/PatrickLisiecki </br>
exit* - https://github.com/OscarJ202 </br>
