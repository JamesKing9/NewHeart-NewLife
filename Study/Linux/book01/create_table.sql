#CD表
create table cd (
    id integer auto_increment not null primary key,
    title varchar(70) not null,
    artist_id integer not null,
    catalogue varchar(30) not null,
    notes varchar(100)
    );

#artist表
#   包含id列 和 艺术家name列
create table artist (
    id integer auto_increment not null primary key,
    name varchar(100) not null
);

#track表
create table track (
    cd_id integer not null,
    track_id integer not null,
    title varchar(70),
    primary key(cd_id, track_id)
);
