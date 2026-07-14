# What mistakes did i make?
2/07/2026

# what problem existed ?

We were making a call to write each time a key was pressed . 

# How did unix solve it ?

By using a buffer to fist store multiple characters , then passing it to the
write() method , this reduced the number of suitches one has to make from
user to kernel mode

# which functions were introduced ?
memcpy()
write() - it writes from a buffer to a flediscriptor 

# Whay are they designed this way?
so that instead to only witing a character , multiple butes can be written
, and the number of butes to be written from the buffer can also be defined 

# What confused me?
How we will output or buffer cursor movements, clear screen codes and etc ,
because to buffer we need and input , suppose the user presses a cursor key then
the contrle signal will be buffered and then outputted to the standard output
,wont it take a lot of time 

# What mistakes did i make?



