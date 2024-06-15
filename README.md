This project was a semestral work in C++ using OOP and data structures to process .csv file with all territorial units of CR. 
Using iterators, predicates and templates to make algorithms universal. Project focused on being efficient with space and time while searching through data.

Program consists of 4 levels, which can be started and reviewed in terminal. Each level has different way of filtering and searching data stored in different data structures.
First level is searching through vectors of Kraje - Regions, SOORP - Administrative Districts of Municipalities with Extended Powers, Obce - Municipalities and find those containing string input.
Second level works with hierarchy to work with nested territorial units and moving up and down in levels of hierarchy to see only specific Obce of chosen Kraj.
Forth level expands on the second and sorts the filtered data based on the alphabetical properties of their names (in czech alphabet) using quick sort.
Third level uses Binary Search Tree to store duplicities in names using implicit list for the collisions.
