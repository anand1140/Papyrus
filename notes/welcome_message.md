Day 4
========

Goal
-----
understand how to print the welcome message and how to calculate the
position of the message

New Concepts
------------
- padding = (screencols - welcomemessagesize) / 2
- use a whle loop to print the padding space 
- stor the welcome message into the buffer by appending it
- use the snprintf() method to get the size of welcome message and also
format and assign the message into the welcome buffer


Questions
---------
# Why dosent the welcome message stay in the editor forever ?
Well that's obvious if the welcome message stays in the editor forever then
where will the writer type and it's also of no use after one starts writing
, what should matter is that the user is able to use it , instead of
constatnly looking at the welcome message .

# If the terminal window is resized , what would happen to the welcome message
?
if the terminal window is resized the welcome message should be resized ,
that too accoording to a formula for calculatign the relavtive distance from
the edges .

# How would you center the text ?
- if screen width = 80
- and screen hight = 20
the message shouldn't start from the exact middle as we will be goig down
from there writng the mesage it will look like the messagt is printed int he
second half , what should be done is the message should start from
somewher above the middle line that is form 1/3 fo the screen hight maybe ,
and shold be at equal distance from both the side edges , meaning width wise 
so the formula for the hight should be 1/3*height and the ratio of the width
should be somewhat 1:2:1 

# is redrawing the entire screen each keypress a good decision , what
# if the terminal size is really big
well for this one i think redrawing all teh screen isn't good isnt it beter
to render or update to teh position of the cursor only and leave the
remaining portion 

Experiments
-----------

Mistakes
--------
