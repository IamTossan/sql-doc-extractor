DELIMITER //
CREATE PROCEDURE country_hos
(IN con CHAR(20))
BEGIN
--  ===============================================
--  Name: country_hos
--  Description: get infos from countries by continent
--  Inputs:
--      con {char[20]}: continent
--  Outputs:
--      Name {varchar[50]}: name of the country
--      HeadOfState {int}
--  ===============================================
  SELECT Name, HeadOfState FROM Country
  WHERE Continent = con;
END //
DELIMITER ;
