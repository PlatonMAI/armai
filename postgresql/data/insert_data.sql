insert into users (email, password, name, sex, birth, is_admin)
VALUES
('user1@example.com', 'password1', 'Платон < 18 1', 'male', '2010-01-01', false),
('user2@example.com', 'password2', 'Платон < 18 2', 'male', '2010-01-01', false),
('user3@example.com', 'password3', 'Платон < 18 3', 'male', '2010-01-01', false),

('user4@example.com', 'password4', 'Платон > 18 1', 'male', '2000-01-01', false),
('user5@example.com', 'password5', 'Платон > 18 2', 'male', '2000-01-01', false),
('user6@example.com', 'password6', 'Платон > 18 3', 'male', '2000-01-01', false),
('user7@example.com', 'password7', 'Платон > 18 4', 'male', '2000-01-01', false),


('user8@example.com', 'password8', 'Злата < 18 1', 'female', '2010-01-01', false),
('user9@example.com', 'password9', 'Злата < 18 2', 'female', '2010-01-01', false),
('user10@example.com', 'password10', 'Злата < 18 3', 'female', '2010-01-01', false),

('user11@example.com', 'password11', 'Злата > 18 1', 'female', '2000-01-01', false),
('user12@example.com', 'password12', 'Злата > 18 2', 'female', '2000-01-01', false),
('user13@example.com', 'password13', 'Злата > 18 3', 'female', '2000-01-01', false),
('user14@example.com', 'password14', 'Злата > 18 4', 'female', '2000-01-01', false);


insert into participants (user_id, competition_id)
values
(29, 6),
(30, 6),
(31, 6),
(32, 6),
(33, 6),
(34, 6),
(35, 6),
(36, 6),
(37, 6),
(38, 6),
(39, 6),
(40, 6),
(41, 6),
(42, 6);

update participants
set confirm = true
where user_id in (29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42);