-- delete existing data
delete from track;
delete from cd;
delete from artist;


-- Now the data inserts

-- First the artist (or group) tables 
insert into artist(id, name) values(1, 'Pink Floyd');
insert into artist(id, name) values(2, 'Genesis');
insert into artist(id, name) values(3, 'Einaudi');
insert into artist(id, name) values(4, 'Melanie C');

-- Then the cd table
insert into cd(id, title, artist_id, catalogue) values(1, 'Dark Side of the Moon', 1, 'B000024D4P');
insert into cd(id, title, artist_id, catalogue) values(2, 'Wish You Were Here', 1, 'B000024D4S');
insert into cd(id, title, artist_id, catalogue) values(3, 'A Trick of the Tail', 2, 'B000024EXM');
insert into cd(id, title, artist_id, catalogue) values(4, 'Selling England By the Pound', '2', 'B000024E9M');
insert into cd(id, title, artist_id, catalogue) values(5, 'I Giorni', 3, 'B000071WEV');
insert into cd(id, title, artist_id, catalogue) values(6, 'Northern Star', 4, 'BOOO04YMST');

-- populate the tracks
insert into track(cd_id, track_id, title) values(1, 1, 'Speek to me');
insert into track(cd_id, track_id, title) values(1, 2, 'Breathe');

