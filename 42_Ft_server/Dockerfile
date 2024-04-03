# Get debian image official -> tag buster : buster version debian #
FROM debian:buster-slim

# Copy all of my source files to image/APP (debian) #
# Allocate the work folder path #
COPY . /APP
WORKDIR /APP

# Install outil #
## wget     : download file in website
## openssl  : ssl use
RUN apt-get update \
    && apt-get install -y wget \
                            openssl \
                            vim

# Install nginx #
RUN apt-get install -y nginx

# Install mariadb #
RUN apt-get install -y mariadb-server \
                        mariadb-client

# Install PHP #
RUN apt-get install -y php7.3-fpm \
                        php7.3-common \
                        php7.3-json \
                        php7.3-gd \
                        php7.3-cli \
                        php7.3-mbstring \
                        php7.3-xml \
                        php7.3-opcache \
                        php7.3-mysql \
                        php7.3-bcmath \
                        php7.3-zip

# Run script #
CMD ["bash", "./srcs/init.sh"]