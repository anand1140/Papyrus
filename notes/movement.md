21-07-2026
========

Goal
-----
- Implement **Page_up** and **page_down** keys
- Implement **Home** and **End** keys
- Implement the DELETE key , this wont do anythign for now 

New Concepts
------------
- page up and page down keys send <esc>[5~ , <esc>[6~ . respectively 
- Home and End keys send can send multiple possible escape sequences depending
on the os unlike the page up and pagedown keys like <esc>[1~ , <esc>[7~ ,
<esc>[H , or <esc>OH
- similarly the End key can send <esc>[4~ , <esc>[8~ , <esc>[F, or <esc>OF 
- DELETE key sends <esc>[3~
- we cannot directly initialize or create a variable inside of a switch
statement 

Questions
---------
-do we really need page up and down thing 
- most mordern computer don't have home key or like end key , i didn't
encounter any usage of home and end keys while using any of hte modern text
editors . 

Experiments
-----------

LEARNINGS
-----------
- A single key might have multiple possible escape sequences . 

Mistakes
--------
