DROP TABLE IF EXISTS users;

CREATE TABLE users (
    id          serial PRIMARY KEY,
    name        varchar (50) NOT NULL,
    fname       varchar (50) NOT NULL,
    username    varchar (16) NOT NULL UNIQUE,
    password    varchar NOT NULL,
    email       varchar (50) NOT NULL,
    birthday    date,
    sex         varchar (1),
    sex_o       varchar (1),
    location    varchar (100),
    bio         varchar (200),
    online      date,
    tag_l       varchar (20) [],
    like_l      varchar (50) [],
    consult_l   varchar (50) [],
    black_l     varchar (50) [],
    reported_l  varchar (50) [],
    image_l     varchar (50) []
);