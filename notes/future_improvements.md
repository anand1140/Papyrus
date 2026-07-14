## Future Improvement: Capacity-based Append Buffer

Current design:
- realloc() on every append.

Potential improvement:
- Add a `capacity` member.
- Grow capacity exponentially (e.g., double it).
- Only call realloc() when capacity is exceeded.

Questions:
- How does std::vector do this?
- How much memory does this waste?
- Why is doubling preferred over adding one byte at a time?

## Future Improvement: Add a capacity field to the append buffer.

Current design
- the buffer struct contains only the length so each time a new append is done
  buffer increases  by the exact size of the new sequence of characters and
realloc has to be called each time we append the buffer , that's not
efficient 

## Consider partial redraws instead of full redraws.

Current design :
- each keypress refreshes the full screen . this is simple and working but
isn't performant 

Potential Improvemnt:
- a diff based rendering

Questions:
- How do the modern editors implement this
- how do they manage the two staes using which the diff is calculated
- What new constructs might be used 

## Measure rendering time before optimizing.

