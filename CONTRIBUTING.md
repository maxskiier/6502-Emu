# Contributing to the 6502-Emu/emu65 project
Hello! Thanks for checking out the CONTRIBUTING.md file.  
This contains the style guide, and in the future will include other things that you will want to know to join or create a pull request.

## Style Guide (Naming Conventions)
These are the current naming conventions for the 6502-Emu/emu65 project:
### Classes and structs:
- Utilize PascalCase for new classes and structs  
    - Already existing classes and structs use camelCase
### Outside of structs/classes:  
- Variable names:  
    - camelCase  
- Function names:  
    - camelCase  
### Members of a class/struct:
- Variable names:
    - camelCase  
        - If you wish, you may to prepend `m_` to the name  
- Function names:  
    - camelCase
### Members of an enum:
- PascalCase
- SCREAMING_SNAKE_CASE
## Style Guide (Syntax Conventions)
These are the current syntax conventions for the 6502-Emu/emu65 project:  
### Classes and Structs:
- Brackets should be placed below the definition  
- Private members should be defined first, then public members
### Functions:
- Brackets should be placed below the definition
- Definitions should be on one line
### Variables:
- Brace definition (e.g., `int number(42);`) should ideally use one line, however multiple may be used for readability  
- Otherwise, definitions should be one one line  
- Increment operator:  
    - The postfix increment should be used primarially  
        - `i++;`  
    - Utilize the prefix increment where needed however  
        - `++i;`
