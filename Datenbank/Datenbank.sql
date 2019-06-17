use swt;
create table if not exists NUTZER(
	NUTZERID int not null auto_increment,
	primary key(NUTZERID),
	PASSWORT varchar(50) not null
);

create Table if not exists TEAM(
TEAMID int not null auto_increment,
primary key(TEAMID), 
TEAMNAME varchar(50),
b int(10) default 0
size int default 0 ;

);

create table if not exists GRUPPE (

	GRUPPEID int not null auto_increment,
	primary key(GRUPPEID),
	GRUPPENAME varchar(50),
	SIZE int,
	Mitglieder varchar(50),
	Beschreibung varchar(200),
	TEAMID int default null
	hour int default 0;
	minute int default 0;
 	day_of_the_week int default 0;
  	Thema varchar(50) default "GROUP";
		
	
);


create table if not exists STUDENT (
	NUTZERID INTEGER not null,
    foreign KEY (NUTZERID) references NUTZER(NUTZERID),
	EMAIL varchar(30),
	MATRIKELNUMMER INTEGER not null auto_increment,
    primary key(MATRIKELNUMMER)
	NAME varchar(20),
	VORNAME varchar(20)	
);


CREATE TABLE IF NOT EXISTS RIGHT_CLASS (
    RIGHT_CLASS_ID INTEGER NOT NULL AUTO_INCREMENT,
    PRIMARY KEY (RIGHT_CLASS_ID),
    RIGHT_CLASS_NAME VARCHAR(10) NOT NULL
);

create table if not exists RIGHT_CLASS_HAS(
	RIGHT_CLASS_HAS_ID int not null auto_increment,
	primary key(RIGHT_CLASS_HAS_ID),
	RIGHT_CLASS_ID INTEGER not null,
    foreign key (RIGHT_CLASS_ID) references RIGHT_CLASS(RIGHT_CLASS_ID),
	RECHT int default 0
);

create table if not exists AUFGABENKOMPLEX(
	AUFGABENKOMPLEXID int not null auto_increment,
    primary key(AUFGABENKOMPLEXID)
	DESCRIPION VARCHAR(30)
	MAX int,
	HUERDE decimal not null,
	BEWERTET_VON_MAX int
);

create table if not exists AUFGABE(
	AUFGABEID int not null auto_increment,
	primary key(AUFGABEID),
	AUFGABENKOMPLEXID int not null,
	foreign key (AUFGABENKOMPLEXID) references AUFGABENKOMPLEX(AUFGABENKOMPLEXID),
	
);



create table if not exists DOZENT(
	NUTZERID int not null ,
	foreign key (NUTZERID) references NUTZER(NUTZERID),	
	vorname varchar(20),
	nachname varchar(20),
	DozentenID int primary key auto_increment;
);

create table if not exists MODUL(
	MODULID int not null auto_increment primary key,
	MODUL_NAME varchar(30) not null
);

create table if not exists TEAM_GRUPPE (
	TEAM_GRUPPEID int not null auto_increment,
	TERMIN date,
	GRUPPEID int not null,
	TEAMID int not null,
    primary key (TEAM_GRUPPEID) , 
	foreign key (GRUPPEID) references GRUPPE(GRUPPEID),
	foreign key (TEAMID) references TEAM(TEAMID) 
);


create table if not exists DOZENT_TEAM (
	DOZENT_TEAMID int not null auto_increment,
	DOZENTID int not null,
    TEAMID int not null,
	primary key (DOZENT_TEAMID),
    foreign key (DOZENTID) references DOZENT(NUTZERID),
    foreign key (TEAMID) references TEAM(TEAMID)
);

create table if not exists DOZENT_GRUPPE (
	DOZENT_GRUPPEID int not null auto_increment, 
    DOZENTID int not null,
    GRUPPEID int not null,
    primary key (DOZENT_GRUPPEID),
    foreign key (DOZENTID) references DOZENT(NUTZERID),
    foreign key (GRUPPEID) references GRUPPE(GRUPPEID)

);
create table if not exists TEAM_GRUPPE (
	TEAM_GRUPPEID int not null auto_increment,
	TERMIN date,
	GRUPPEID int not null,
	TEAMID int not null,
    primary key (TEAM_GRUPPEID) ,
	foreign key (GRUPPEID) references GRUPPE(GRUPPEID),
	foreign key (TEAMID) references TEAM(TEAMID)
);


create table if not exists DOZENT_TEAM (
	DOZENT_TEAMID int not null auto_increment,
	DOZENTID int not null,
    TEAMID int not null,
	primary key (DOZENT_TEAMID),
    foreign key (DOZENTID) references DOZENT(NUTZERID),
    foreign key (TEAMID) references TEAM(TEAMID)
);

create table if not exists DOZENT_GRUPPE (
	DOZENT_GRUPPEID int not null auto_increment,
    DOZENTID int not null,
    GRUPPEID int not null,
    primary key (DOZENT_GRUPPEID),
    foreign key (DOZENTID) references DOZENT(NUTZERID),
    foreign key (GRUPPEID) references GRUPPE(GRUPPEID)

);



create table if not exists STUDENT_TEAM (
	STUDENT_TEAMID int not null auto_increment,
	TEAMID int not null,
    MATRIKELNUMMER int not null,
    primary key (STUDENT_TEAMID),
    foreign key (TEAMID) references TEAM(TEAMID),
    foreign key (MATRIKELNUMMER) references STUDENT(MATRIKELNUMMER)
);

create table if not exists AUFGABENKOMPLEX_TEAM (
	AUFGABENKOMPLEX_TEAMID int not null auto_increment,
    TEAMID int not null,
    AUFGABENKOMPLEXID int not null,
    primary key(AUFGABENKOMPLEX_TEAMID),
    foreign key(TEAMID) references TEAM(TEAMID),
    foreign key(AUFGABENKOMPLEXID) references AUFGABENKOMPLEX(AUFGABENKOMPLEXID)
);

create table if not exists AUFGABENKOMPLEX_STUDENT (
	AUFGABENKOMPLEX_STUDENTID int not null auto_increment,
	MATRIKELNUMMER int not null,
    AUFGABENKOMPLEXID int not null,
    primary key(AUFGABENKOMPLEX_STUDENTID),
    foreign key(MATRIKELNUMMER) references STUDENT(MATRIKELNUMMER),
    foreign key(AUFGABENKOMPLEXID) references AUFGABENKOMPLEX(AUFGABENKOMPLEXID)
);

/* this one might never be used anyways but I still implement it tho
	this table just as easily implemented tho only one team per group

 */
create table if not exists AUFGABENKOMPLEX_GRUPPE (
	AUFGABENKOMPLEX_GRUPPEID int not null auto_increment,
    GRUPPEID int not null,
    AUFGABENKOMPLEXID int not null,
	primary key (AUFGABENKOMPLEX_GRUPPEID),
    foreign key(GRUPPEID) references GRUPPE(GRUPPEID),
    foreign key(AUFGABENKOMPLEXID) references AUFGABENKOMPLEX(AUFGABENKOMPLEXID)
);


create table AUSWERTUNGSFUNKTION (
	ID int not null auto_increment,
    AUSWERTUNGSFUNKTIONID int not null,
    AUFGABENKOMPLEXID int not null,
    primary key(ID),
    foreign key (AUFGABENKOMPLEXID) references AUFGABENKOMPLEX(AUFGABENKOMPLEXID)

);
create table NUTZER_RIGHT_CLASS (
	NUTZER_RIGHT_CLASSID int not null auto_increment,
    primary key (NUTZER_RIGHT_CLASSID),
    RIGHT_CLASS_ID int not null,
    NUTZERID int not null,
    foreign key (NUTZERID) references NUTZER(NUTZERID),
    foreign key (RIGHT_CLASS_ID) references RIGHT_CLASS(RIGHT_CLASS_ID)
);


create table WUNSCHGRUPPEN (
	WUNSCHGRUPPENID int not null auto_increment,
	GRUPPEID int not null,
	primary key (WUNSCHGRUPPENID),
	foreign key (GRUPPEID) references GRUPPE(GRUPPEID));


create table if not exists NEWS_TABLE (
	 Zeitpunkt DATETIME not null,
	 primary key (ZEITPUNKT),
	 News LONGTEXT not null
);
