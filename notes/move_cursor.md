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

Questions
---------
- why decrementing the E.cy-- moves the cursor above wheras
incrementing E.cx++ moves the cursor downwards
- the implementation seems quite simple 

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
