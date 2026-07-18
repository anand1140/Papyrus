10/07/2026
========

Goal
-----
To learn how to implement cursor movements , that how to manipulate them with
keypresses , register the keypress then map it to the desired behaviour

New Concepts
------------
- seperation of concern using functions 
- decision making or flow of controle devitation using switch statement
- to register keypress we use the **editorReadKey()** method and to proces it we use
the switch statement inside of **editorProcessKeypress()** but one thing we have
seperated the concern of implementing the behavior of keypress into
**editorMoveCursor()**
- to map arrow key presses to cusor movement we have to account for multiple
characters in the escape sequence provided when we read an arrow key
- In eiditor read key we have to first check if we have read an escape key
  '\x1b' if so then read the next two characters as arrow keys are 3 bytes
long so the 2nd and 3rd bytes are '[' and one of the characters from A, B, C, D,
if so then  return appropriate signals as the return type .
- because we have set the value of enums as 1000 , 1001 and so on hence we
also change the return type from char to int  return appropriate signals as
char tupe cannot accomodat such large values . 
- editorReadKey() hides the complexity of decoding escape sequences. The rest of the editor never needs to know that arrow keys are actually three bytes long—it simply receives ARROW_LEFT, ARROW_RIGHT, etc.

Questions
---------
- why decrementing the E.cy-- moves the cursor above wheras
incrementing E.cx++ moves the cursor downwards
- the implementation seems quite simple 
- why don't we just use the j , k ,l and h keys for navigation , why did we
change it to arrow keys 

Prediction
----------
- the welcome message should be gone when user starts moving the cursor 

Experiments
-----------
- Add boundary checking so that the cursor cannot go to positions like ( -5 ,
  20) etc. 
- Cursor cannot go above row 0 . left to row 0 and should not go beyond the
  screen 

Mistakes
--------
- earlier i didn't knew which construct was holding the data about the teminal
windwo dimesions , so i drew the flow control diamgram starting from the main
method to all the subsequent calls 
- realised it was editorConfig struct that had it
