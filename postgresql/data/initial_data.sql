create table users
(
    id SERIAL primary key,
    email VARCHAR(255) unique not null,
    password VARCHAR(64) not null,
    name VARCHAR(255) not null,
    birth DATE not null,
    is_admin BOOL default(false) not null
);
