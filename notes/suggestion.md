this was suggested to be added after each chapter 
Design Decisions
----------------

Decision:
The tutorial redraws the whole screen every refresh.

Alternative:
Only redraw changed rows.

Advantages:
- Simpler implementation.
- Easier reasoning.
- Less bookkeeping.

Disadvantages:
- More bytes written.
