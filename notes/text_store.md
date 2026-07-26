26 - 07 - 2026
========

Goal
-----
Implement storing a line of text mechamics 

New Concepts
------------
- getline() method 
- ssize_t 


Implementation details
----------------------
- a custom type is required to handle the stroing of data(**papyrusrow**) as it will be a
sequence of characters , so a pointer and the length of the string of
characters is required , so a custom type is what wil make thing easy . 
- add the type into editorConfig so that we can track information at a central
location 
- initialize the number of rows to 0 as we initalize the editor state in
initEditor() function .  

Questions
---------

Experiments
-----------

Mistakes
--------
