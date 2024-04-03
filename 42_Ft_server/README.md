# 42 project : ft_server

## Index

* [Presentation](#Presentation)
* [Main_file](#Main_file)
* [How_to_run](#How_to_run)

## Presentation 

Discover the "docker" technology and use it to install a complete web server.

## Main_file

[__Docker_file_content__](./Dockerfile)  
[__Script_file_content__](./srcs/init.sh)  
[__Server_file_content__](./srcs/website_autoindex_on)  

## How_to_run

`Docker image build command :`  

    docker build -t "name"

`Docker container run command :`  

    docker run -it -p 80:80 -p 443:443 "name"