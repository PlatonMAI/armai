create type sex_enum as enum ('male', 'female');
create table users
(
    id SERIAL primary key,
    email VARCHAR(255) unique not null,
    password VARCHAR(64) not null,
    name VARCHAR(255) not null,
    sex SEX_ENUM not null,
    birth DATE not null,
    is_admin BOOL default(false) not null,
    wins_armfights INT not null default(0),
	wins_competitions INT not null default(0)
);

create table category_schemas
(
    id SERIAL primary key,
    owner_id INT not null references users (id),
    name VARCHAR(255) not null
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

create type hand_enum as enum ('left', 'right');
create type status_enum as enum ('registration', 'confirmation', 'weighing', 'in_process', 'finished');

create table teams
(
    id SERIAL primary key,
    owner_id INT not null references users (id),
    name VARCHAR(255) not null,
    wins_armfights INT not null default(0),
	wins_competitions INT not null default(0)
);

create table competitions
(
    id SERIAL primary key,
    owner_id INT not null references users (id),
    name VARCHAR(255) not null,
    hand HAND_ENUM,
    category_schema_id INT not null references category_schemas (id),
    status STATUS_ENUM not null default('registration')
);

create table participants
(
    id SERIAL primary key,
    user_id INT not null references users (id),
    competition_id INT not null references competitions (id),
    team_id INT references teams (id),
    confirm BOOL not null default(false),
    weight INT,
    age INT,
    category_id INT references categories (id)
    UNIQUE(user_id, competition_id)
);

create table armfights
(
    id SERIAL primary key,
    category_id INT not null references categories (id),
    competition_id INT not null references competitions (id),
    participant_first_id INT references participants (id),
    participant_second_id INT references participants (id),
    armfight_first_id INT references armfights (id),
    armfight_second_id INT references armfights (id),
    hand HAND_ENUM not null,
    winner_id INT references participants (id)
);
