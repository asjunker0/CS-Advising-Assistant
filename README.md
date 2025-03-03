# CS Advising Assistant Project
CS 300: DSA Analysis and Design
<br/>
<br/>(From the SNHU CS-210 Syllabus)
<br/>Students will develop code as well as use non-coding development methodologies in algorithmic design and problem-solving. Students will use advanced algorithmic designs to evaluate complex data structures to aid in problem-solving.

# Course Competencies
This course covers the following competencies, which represent the knowledge and skills relevant to the field:
<br/>CS-30398: Apply non-coding development methodologies for outlining an algorithmic design
<br/>CS-30399: Develop code using algorithms and data structures to solve basic programming problems
<br/>CS-30400: Evaluate complex data structures that solve a given problem using advanced algorithmic designs

# Software and Tools
Microsoft Visual Studio 2019

# DSA Analysis and Design Project Overview
__Project Summary and Solution__<br/>
This course presents a problem of data structures and algorithm efficiency. The project program navigates a loaded university class list by printing all courses in alphanumeric order or one specific course and its details. The focus of this project was to design and implement an algorithm optimized for performance in sorting. In this project, I implemented a hash table to do so.

__Approach & Data Structures__<br/>
Approaching this problem included analyzing time and space complexity to determine the most efficient data structure for this task. Understanding Big-O notation influenced my choice in the implemented data structure. 

__Challenges & Solutions__<br/>
This project was as difficult as any I have worked on, and I ran into small roadblocks that are extremely common. For example, the program would not take my input unless I put it in twice. This problem was caused by an extra newline character being left in the input buffer when switching between cin and getline() in C++. This was resolved by using cin.ignore() before calling getline(), ensuring the input was read correctly. Of course, I encountered more challenging roadblocks like hash collisions, where multiple keys were mapping to the same index in my hash table. This led to incorrect data retrieval and unexpected output in my program. To solve this, I used separate chaining with linked lists, which allows multiple courses to be stored at the same index without overwriting existing entries.

__Software Design & Development__<br/>
This project has opened up the idea of choosing the correct data structure specific to each problem. I think about how data is stored and the best way to access it before writing the code. Using these algorithms, recursions, and tree structures has expanded my ability to design efficient programs.

__Code Maintainability & Adaptability__<br/>
I followed programming principles that kept my code modular and expandable. Each function must have its own responsibility to maintain that. Hash table collisions were handled dynamically through chaining, and this program can handle an unlimited number of courses at a given index, allowing for scalability. Though not required, I implemented input validation for invalid or unexpected inputs to prevent errors or crashing. I also utilized bubble sorting for displaying courses in alphanumerical order, which prioritized sorting for user experience by quickly finding and displaying courses.
This project reinforced the importance of writing scalable, adaptable, and maintainable code. By focusing on modular design, proper memory management, and collision handling, my hash table implementation proves to be efficient and extensible for future improvements.
