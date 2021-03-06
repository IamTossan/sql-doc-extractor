DELIMITER //
CREATE PROCEDURE country_hos
(IN con CHAR(20))
BEGIN
--  ===============================================
--  Name: country_hos
--  Description: get infos from countries by continent
--  ===============================================
  SELECT Name, HeadOfState FROM Country
  WHERE Continent = con;
END //
DELIMITER ;
