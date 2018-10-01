DELIMITER //
CREATE PROCEDURE country_hos
(IN con CHAR(20))
BEGIN
--  ===============================================
--  Name: country_hos
--  Description: get infos from countries by continent
--  Inputs:
--      con: continent
--  Outputs:
--      Name: name of the country
--      HeadOfState
--  ===============================================
  SELECT Name, HeadOfState FROM Country
  WHERE Continent = con;
END //
DELIMITER ;
