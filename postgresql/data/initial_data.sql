create type sex_enum as enum ('male', 'female');
create table users
(
    id SERIAL primary key,
    email VARCHAR(255) unique not null,
    password VARCHAR(64) not null,
    name VARCHAR(255) not null,
    sex SEX_ENUM not null,
    birth DATE not null,
    is_admin BOOL default(false) not null
);

create table category_schemas
(
    id SERIAL primary key,
    owner_id INT not null references users (id),
    name VARCHAR(255) not null,
    schema JSON not null
);
create table categories
(
    id SERIAL primary key,
    category_schema_id INT not null references category_schemas (id),
    sex SEX_ENUM,
    age_min INT,
    age_max INT,
    weight_min INT,
    weight_max INT
);