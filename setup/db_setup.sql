DROP TABLE IF EXISTS botuser;

CREATE TABLE botuser(
    id integer primary key,
    name varchar(32),
    surname varchar(32),
    phone_number varchar(32),
    email varchar(32)
);