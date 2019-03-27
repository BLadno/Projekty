create table adresy
(
	id serial NOT NULL,
	kod_pocztowy character varying(15) NOT NULL,
	miasto character varying(50) NOT NULL,
	ulica character varying(50) NOT NULL,
	CONSTRAINT adresy_pkey PRIMARY KEY (id)
);
CREATE TABLE statusy
(
  id serial NOT NULL,
  opis character varying(30) NOT NULL,
  CONSTRAINT statusy_pkey PRIMARY KEY (id)
);
CREATE TABLE realizacja
(
  id serial NOT NULL,
  opis character varying(250) NOT NULL,
  CONSTRAINT realizacja_pkey PRIMARY KEY (id)
);
create table produkt
(
	id serial NOT NULL,
	opis character varying(250) NOT NULL,
	cena float NOT NULL,
	CONSTRAINT produkt_pkey PRIMARY KEY (id)
);
create table klienci 
(
	id serial NOT NULL,
	login character varying(50) NOT NULL,
	password character varying(30) NOT NULL,
	name character varying(250) NOT NULL,
	adres integer NOT NULL,
	tel character varying(15) NOT NULL,
	CONSTRAINT klienci_pkey PRIMARY KEY (id),
	CONSTRAINT fk_klienci_adresy FOREIGN KEY (adres)
		REFERENCES adresy (id) MATCH SIMPLE
		ON UPDATE NO ACTION ON DELETE NO ACTION
);
CREATE TABLE zamowienie
(
	id serial NOT NULL,
	klient integer NOT NULL,
	adres integer NOT NULL,
	sposob_realizacji integer NOT NULL,
	data_przyjecia timestamp(2) without time zone NOT NULL,
	termin_realizacji timestamp(2) without time zone,
	data_realizacji timestamp(2) without time zone,
	opis character varying(250),
	status integer NOT NULL,
	CONSTRAINT zamowienie_pkey PRIMARY KEY (id),
	CONSTRAINT fk_zamowienie_klient FOREIGN KEY (klient)
		REFERENCES klienci (id) MATCH SIMPLE
		ON UPDATE NO ACTION ON DELETE NO ACTION,
	CONSTRAINT fk_zamowienie_adresy FOREIGN KEY (adres)
		REFERENCES adresy (id) MATCH SIMPLE
		ON UPDATE NO ACTION ON DELETE NO ACTION,
	CONSTRAINT fk_zamowienie_realizacja FOREIGN KEY (sposob_realizacji)
		REFERENCES realizacja (id) MATCH SIMPLE
		ON UPDATE NO ACTION ON DELETE NO ACTION,
	CONSTRAINT fk_zamowienie_statusy FOREIGN KEY (status)
		REFERENCES statusy (id) MATCH SIMPLE
		ON UPDATE NO ACTION ON DELETE NO ACTION
);
create table koszyk
(
	id serial NOT NULL,
	id_zam integer NOT NULL,
	produkt integer NOT NULL,
	ilosc integer NOT NULL,
	CONSTRAINT koszyk_pkey PRIMARY KEY (id),
	CONSTRAINT fk_koszyk_id_zam FOREIGN KEY (id_zam)
		REFERENCES zamowienie (id) MATCH SIMPLE
		ON UPDATE NO ACTION ON DELETE NO ACTION,
	CONSTRAINT fk_koszyk_produkt FOREIGN KEY (produkt)
		REFERENCES produkt (id) MATCH SIMPLE
		ON UPDATE NO ACTION ON DELETE NO ACTION
);


insert into adresy (kod_pocztowy,miasto,ulica) values ('02-490','Wrocław','Kopalniania 1/1');
insert into adresy (kod_pocztowy,miasto,ulica) values ('02-491','Warszawa','Sloneczna 3');
insert into adresy (kod_pocztowy,miasto,ulica) values ('02-492','Poznań','Batalionow wlochy 1');
insert into adresy (kod_pocztowy,miasto,ulica) values ('02-493','Warszawa','Kolorowa 6');
insert into adresy (kod_pocztowy,miasto,ulica) values ('02-494','Gdańsk','Modlinska 9');
insert into adresy (kod_pocztowy,miasto,ulica) values ('03-694','Wrocław','Zwycięska 6');


insert into statusy (opis) values ('kompletowanie zamowienia');
insert into statusy (opis) values ('w realizacji');
insert into statusy (opis) values ('zakonczone');

insert into realizacja (opis) values ('przesylka kurierska: platnosc przy odbiorze');
insert into realizacja (opis) values ('przesylka kurierska: platnosc przelewem');
insert into realizacja (opis) values ('odbior osobisty: platnosc przy odbiorze');

insert into produkt (opis,cena) values ('karta graficzna gtx 1050ti','679');
insert into produkt (opis,cena) values ('karta graficzna gtx 1060','1000');
insert into produkt (opis,cena) values ('karta graficzna gtx 1070','1500');
insert into produkt (opis,cena) values ('procesor intel core i3','400');
insert into produkt (opis,cena) values ('procesor intel core i5','800');
insert into produkt (opis,cena) values ('procesor intel core i7','1200');
insert into produkt (opis,cena) values ('pamiec ram ddr4 2x2GB','200');
insert into produkt (opis,cena) values ('pamiec ram ddr4 2x4GB','400');
insert into produkt (opis,cena) values ('pamiec ram ddr4 2x8GB','900');
insert into produkt (opis,cena) values ('laptop hp','2200');
insert into produkt (opis,cena) values ('laptop lenovo','1600');
insert into produkt (opis,cena) values ('laptop asus','1300');

insert into klienci (login,password,name,adres,tel) values ('adrian321','123','Adrian',1,'123 456 789');
insert into klienci (login,password,name,adres,tel) values ('adam543','qwerty','Adam',2,'214 234 324');
insert into klienci (login,password,name,adres,tel) values ('krzysztof412','321','Krzysztof',3,'213 213 432');
insert into klienci (login,password,name,adres,tel) values ('stefan574','zaqxsw','Stefan',4,'345 546 546');
insert into klienci (login,password,name,adres,tel) values ('xyz124','asdf','Eustachy',5,'124 123 534');

insert into zamowienie (klient,adres,status,sposob_realizacji,data_przyjecia,termin_realizacji,data_realizacji) values (1,1,3,1,'2016-11-05','2016-11-10','2016-11-07');
insert into zamowienie (klient,adres,status,sposob_realizacji,data_przyjecia,termin_realizacji,data_realizacji) values (2,2,3,2,'2016-11-06','2016-11-11','2016-11-08');
insert into zamowienie (klient,adres,status,sposob_realizacji,data_przyjecia,termin_realizacji,data_realizacji) values (3,3,2,3,'2016-11-07','2016-11-12','2016-11-09');
insert into zamowienie (klient,adres,status,sposob_realizacji,data_przyjecia,termin_realizacji,data_realizacji) values (4,4,2,2,'2016-11-08','2016-11-13','2016-11-10');
insert into zamowienie (klient,adres,status,sposob_realizacji,data_przyjecia,termin_realizacji,data_realizacji) values (5,5,1,1,'2016-11-09','2016-11-14','2016-11-11');
insert into zamowienie (klient,adres,status,sposob_realizacji,data_przyjecia,termin_realizacji,data_realizacji) values (1,6,1,1,'2016-11-10','2016-11-15','2016-11-12');

insert into koszyk (id_zam,produkt,ilosc) values (1,1,1);
insert into koszyk (id_zam,produkt,ilosc) values (1,4,1);
insert into koszyk (id_zam,produkt,ilosc) values (1,7,1);
insert into koszyk (id_zam,produkt,ilosc) values (2,2,1);
insert into koszyk (id_zam,produkt,ilosc) values (2,5,1);
insert into koszyk (id_zam,produkt,ilosc) values (2,8,1);
insert into koszyk (id_zam,produkt,ilosc) values (3,3,1);
insert into koszyk (id_zam,produkt,ilosc) values (3,6,1);
insert into koszyk (id_zam,produkt,ilosc) values (3,9,1);
insert into koszyk (id_zam,produkt,ilosc) values (4,4,1);
insert into koszyk (id_zam,produkt,ilosc) values (5,5,1);
insert into koszyk (id_zam,produkt,ilosc) values (6,10,1);
CREATE OR REPLACE  VIEW "v_klienci" ("id", "login", "name", "tel", "kod_pocztowy", "miasto", "ulica") AS 
	select k.id,k.login,k.name,k.tel,a.kod_pocztowy,a.miasto,a.ulica
	from klienci k,adresy a
	where k.adres=a.id;
CREATE OR REPLACE  VIEW "v_wszystko" ("id", "login", "name", "tel", "Adres klienta","id_zam","Adres dostawy","status","sposob realizacji","data przyjecia","termin realizacji","data realizacji","produkt","cena za 1szt","ilosc") AS 
	select k.id,k.login,k.name,k.tel,
	a.kod_pocztowy||' '||a.miasto||' '||a.ulica,
	z.id,
	a2.kod_pocztowy||' '||a2.miasto||' '||a2.ulica,
	s.opis, r.opis,
	z.data_przyjecia, z.termin_realizacji, z.data_realizacji,
	p.opis,p.cena,k2.ilosc
	from klienci k ,adresy a,adresy a2, zamowienie z,statusy s, realizacja r, koszyk k2, produkt p
	where k.adres=a.id
	and z.adres=a2.id
	and k.id=z.klient
	and z.status=s.id
	and z.sposob_realizacji=r.id
	and z.id=k2.id_zam
	and p.id=k2.produkt
	order by k.id;

create or replace function zamowienie(x integer) 
returns table (id_zam int,produkt varchar,cena float,ilosc int) as $$
	select k2.id_zam,p.opis,p.cena,k2.ilosc from koszyk k2, produkt p
	where id_zam=$1
	and p.id=k2.produkt;
$$ language SQL;

create or replace function klient(x integer) 
returns table (id int,login varchar,name varchar,tel varchar,kod_pocztowy varchar,miasto varchar,ulica varchar) as $$
	select k.id,k.login,k.name,k.tel,a.kod_pocztowy,a.miasto,a.ulica
	from klienci k,adresy a
	where k.id=$1 
	and k.adres=a.id;
$$ language SQL;