CREATE TABLE members(uname TEXT PRIMARYKEY, first TEXT, last TEXT, j_date DATE, phone TEXT, email TEXT)
CREATE TABLE games(po_uname TEXT PRIMARYKEY, pt_uname TEXT PRIMARYKEY, po_score INT, pt_score INT,  FOREIGN KEY (po_uname) REFERENCES members (uname), FOREIGN KEY (pt_uname) REFERENCES members (uname))
CREATE TABLE history(wins INT, losses INT, h_score INT, win_date DATE, place TEXT, agains TEXT, uname TEXT PRIMARY KEY)

INSERT INTO members(uname, first, last, j_date, phone, email) VALUES ("shonei", "Teodor", "Todorov", 06-03-1999, "07999306162", "teodor.shyl@gmail.com"), ("shyl", "Ivane", "Vitkova", 12-03-2014, "0889555285", "shyl@gmail.com"), ("kipendy", "Vitko", "Vitkov", 03-09-1964, "07999306162", "vitko_vitkov@gmail.com")
INSERT INTO games(po_uname, pt_uname, po_score, pt_score) VALUES("shonei", "shyl", 13, 53), ("shonei", "kipendy", 31, 83), ("kipendy", "shonei", 92, 96), ("shonei", "shyl", 123, 96), ("shyl", "shonei", 76, 45), ("shonei", "kipnedy", 105, 32), ("kipnedy", "shyl", 24, 87), ("shyl", "shonei", 37, 53), ("kipendy", "shonei", 62, 53), ("shonei", "kipendy", 52, 32)
INSERT INTO history(uname, wins, losses, h_score, win_date, place, agains) VALUES("shonei", 7, 12, 123, 09-04-2013, "Vidin", "shyl"), ("shyl", 8, 2, 123, 09-02-2010, "Vidin", "shonei"), ("kipendy", 14, 9, 92, 02-06-2003, "Leeds", "Shonei")


-- Use second query to get the usernames and the long one to get the average score
SELECT (one + two)/2 AS score FROM (SELECT AVG(po_score) AS one FROM games WHERE po_uname == $uname), (SELECT AVG(pt_score) AS two FROM games WHERE pt_uname == $uname)
SELECT uname FROM history WHERE (wins + losses) > 9


-- Failed attemps at leaderboard query

--SELECT history.uname, (one + two)/2  FROM history
--JOIN 
--(SELECT AVG(games.po_score) FROM games INNER JOIN history ON history.uname=games.po_uname WHERE games.po_uname == history.uname) AS one 
--ON history.uname = games.po_uname JOIN 
--(SELECT AVG(games.pt_score) FROM games INNER JOIN history ON history.uname=games.pt_score WHERE games.pt_uname == history.uname) AS two
--ON history.uname = games.pt_uname
--WHERE (history.wins + history.losses) > 9


--SELECT AVG(po_score) AS one, po_uname AS uname FROM games
--INTERSECT
--SELECT AVG(pt_score) AS two, pt_uname AS uname FROM games


--SELECT (one + two)/2, uname AS score FROM 
--(SELECT uname AS uname FROM history),
--(SELECT AVG(po_score) AS one, po_uname AS oneu FROM games), 
--(SELECT AVG(pt_score) AS two, pt_uname AS twou FROM games)
--WHERE oneu == twou

--SELECT AVG(games.po_score) , history.uname FROM history INNER JOIN games ON history.uname = games.po_uname
--SELECT AVG(games.pt_score) , history.uname FROM history INNER JOIN games ON history.uname = games.pt_uname


--SELECT history.uname, score FROM history 
--JOIN (SELECT (one + two)/2  FROM (SELECT AVG(po_score) AS one FROM games WHERE po_uname == history.uname), (SELECT AVG(pt_score) AS two FROM games WHERE pt_uname == history.uname))
--ON 