# smart_cd
A smart CLI tool quickly lead you to complex paths.  
**NOTE : Only on windows.**

## Installation

## Windows  
[1] **Download from Github**.  
    You can get it at the release page.

[2] **Build from source**.  
```shell
git clone https://github.com/sun-xx/smart_cd.git
make
```
  Then add build/scd.exe to Path.   

## Usage  
```
scd            //list the history paths and go with a number choice.
scd f          //list the paths in the order of frequency, and go with a number choice.
scd m          //list the paths marked, and go with the mark's name.
scd m your-path    //go straight to the marked path
scd your-path      //go to your-path. It will be recorded by scd.exe.
 ```
**NOTE : You can edit marks in the marks.txt.**   
**The style is: [markname],[your-path]. NO SPACES AROUND "," ALLOWED.**   
Example:  
```
eb,d:/documents/ebooks/
g,e:/storage/games/
```
