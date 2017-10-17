CREATE TABLE members(uname TEXT PRIMARYKEY, first TEXT, last TEXT, j_date DATE, phone TEXT, email TEXT);
CREATE TABLE games(po_uname TEXT PRIMARYKEY, pt_uname TEXT PRIMARYKEY, po_score INT, pt_score INT,  FOREIGN KEY (po_uname) REFERENCES members (uname), FOREIGN KEY (pt_uname) REFERENCES members (uname));
CREATE TABLE history(wins INT, losses INT, h_score INT, win_date DATE, place TEXT, agains TEXT, uname TEXT PRIMARY KEY);

CREATE TRIGGER update_po_wins AFTER INSERT ON games BEGIN UPDATE history SET wins = wins + 1 WHERE uname == new.po_uname AND new.po_score > new.pt_score; END;
CREATE TRIGGER update_po_losses AFTER INSERT ON games BEGIN UPDATE history SET losses = losses + 1 WHERE uname == new.po_uname AND new.po_score < new.pt_score; END;
CREATE TRIGGER update_pt_wins AFTER INSERT ON games BEGIN UPDATE history SET wins = wins + 1 WHERE uname == new.pt_uname AND new.pt_score > new.po_score; END;
CREATE TRIGGER update_pt_losses AFTER INSERT ON games BEGIN UPDATE history SET wins = wins + 1 WHERE uname == new.pt_uname AND new.pt_score < new.po_score; END;

INSERT INTO members(uname, first, last, j_date, phone, email) VALUES ("shonei", "Teodor", "Todorov", 06-03-1999, "07999306162", "teodor.shyl@gmail.com"), ("shyl", "Ivane", "Vitkova", 12-03-2014, "0889555285", "shyl@gmail.com"), ("kipendy", "Vitko", "Vitkov", 03-09-1964, "07999306162", "vitko_vitkov@gmail.com");
INSERT INTO games(po_uname, pt_uname, po_score, pt_score) VALUES("shonei", "shyl", 13, 53), ("shonei", "kipendy", 31, 83), ("kipendy", "shonei", 92, 96), ("shonei", "shyl", 123, 96), ("shyl", "shonei", 76, 45), ("shonei", "kipnedy", 105, 32), ("kipnedy", "shyl", 24, 87), ("shyl", "shonei", 37, 53), ("kipendy", "shonei", 62, 53), ("shonei", "kipendy", 52, 32);
INSERT INTO history(uname, wins, losses, h_score, win_date, place, agains) VALUES("shonei", 7, 12, 123, 09-04-2013, "Vidin", "shyl"), ("shyl", 8, 2, 123, 09-02-2010, "Vidin", "shonei"), ("kipendy", 14, 9, 92, 02-06-2003, "Leeds", "Shonei");

-- Use second query to get the usernames and the long one to get the average score
SELECT (one + two)/2 AS score FROM (SELECT AVG(po_score) AS one FROM games WHERE po_uname == $uname), (SELECT AVG(pt_score) AS two FROM games WHERE pt_uname == $uname);
SELECT uname FROM history WHERE (wins + losses) > 9;


-- VERSION 2 OF THE DATABASE
-- IT INTRODUCES A SMALL CHANGE TO HELP WITH AVERAGE SCORE
-- For the case of the scrabble database I would use this.
-- The data being stored won't be huge plus data storega has become cheap.
-- I am putting priority on the ease of development and maintanance.

CREATE TABLE members(uname TEXT PRIMARYKEY, first TEXT, last TEXT, j_date DATE, phone TEXT, email TEXT);
CREATE TABLE games(po_uname TEXT PRIMARYKEY, pt_uname TEXT PRIMARYKEY, po_score INT, pt_score INT,  FOREIGN KEY (po_uname) REFERENCES members (uname), FOREIGN KEY (pt_uname) REFERENCES members (uname));
CREATE TABLE history(wins INT, losses INT, total INT, h_score INT, win_date DATE, place TEXT, agains TEXT, uname TEXT PRIMARY KEY);

CREATE TRIGGER update_po_wins AFTER INSERT ON games BEGIN UPDATE history SET wins = wins + 1 WHERE uname == new.po_uname AND new.po_score > new.pt_score; END;
CREATE TRIGGER update_po_losses AFTER INSERT ON games BEGIN UPDATE history SET losses = losses + 1 WHERE uname == new.po_uname AND new.po_score < new.pt_score; END;
CREATE TRIGGER update_pt_wins AFTER INSERT ON games BEGIN UPDATE history SET wins = wins + 1 WHERE uname == new.pt_uname AND new.pt_score > new.po_score; END;
CREATE TRIGGER update_pt_losses AFTER INSERT ON games BEGIN UPDATE history SET wins = wins + 1 WHERE uname == new.pt_uname AND new.pt_score < new.po_score; END;

CREATE TRIGGER update_total_po AFTER INSERT ON games BEGIN UPDATE history SET total = total + new.po_score WHERE uname == new.po_uname; END;
CREATE TRIGGER update_total_pt AFTER INSERT ON games BEGIN UPDATE history SET total = total + new.pt_score WHERE uname == new.pt_uname; END;

INSERT INTO members(uname, first, last, j_date, phone, email) VALUES ("shonei", "Teodor", "Todorov", 06-03-1999, "07999306162", "teodor.shyl@gmail.com"), ("shyl", "Ivane", "Vitkova", 12-03-2014, "0889555285", "shyl@gmail.com"), ("kipendy", "Vitko", "Vitkov", 03-09-1964, "07999306162", "vitko_vitkov@gmail.com");
INSERT INTO games(po_uname, pt_uname, po_score, pt_score) VALUES("shonei", "shyl", 13, 53), ("shonei", "kipendy", 31, 83), ("kipendy", "shonei", 92, 96), ("shonei", "shyl", 123, 96), ("shyl", "shonei", 76, 45), ("shonei", "kipnedy", 105, 32), ("kipnedy", "shyl", 24, 87), ("shyl", "shonei", 37, 53), ("kipendy", "shonei", 62, 53), ("shonei", "kipendy", 52, 32);
INSERT INTO history(uname, wins, losses, h_score, win_date, place, agains, total) VALUES("shonei", 7, 12, 123, 09-04-2013, "Vidin", "shyl", 12643), ("shyl", 8, 2, 123, 09-02-2010, "Vidin", "shonei", 34562), ("kipendy", 14, 9, 92, 02-06-2003, "Leeds", "Shonei", 12643);

SELECT  total / (wins + losses), uname FROM history;