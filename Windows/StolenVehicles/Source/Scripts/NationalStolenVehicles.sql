-- MySQL dump 10.13  Distrib 5.7.12, for Win64 (x86_64)
--
-- Host: localhost    Database: nationalstolenvehicles
-- ------------------------------------------------------
-- Server version	5.7.16-log

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `stolenvehicles`
--

DROP TABLE IF EXISTS `stolenvehicles`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `stolenvehicles` (
  `Registration` varchar(13) NOT NULL,
  `Make` varchar(30) DEFAULT NULL,
  `Model` varchar(5) DEFAULT NULL,
  `Owner` varchar(100) DEFAULT NULL,
  PRIMARY KEY (`Registration`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `stolenvehicles`
--

LOCK TABLES `stolenvehicles` WRITE;
/*!40000 ALTER TABLE `stolenvehicles` DISABLE KEYS */;
INSERT INTO `stolenvehicles` VALUES ('10029228101DE','Acura','CT','Madeline Lane'),('10029228101KY','AlfaRomeo','ES','Alex Rhodes'),('10029228101MT','AstonMartin','GX','Betsy Smith'),('10029228101OH','Audi','IS','Adam Reed'),('10029229101DE','Bentley','CT','Bob Abbott'),('10029229101KY','BMW','ES','Fredrick Barker'),('10029229101MT','Bugatti','GX','Jake Yates'),('10029229101OH','Buick','IS','Kim Swanson'),('20029228101FL','Cadillac','CT','Ervin Lopez'),('20029228101LA','Chevrolet','ES','Don Hill'),('20029228101NE','Chrysler','GX','Sherman Wright'),('20029228101OK','Daewoo','IS','Estelle Burgess'),('20029229101FL','Dodge','CT','Carol Newman'),('20029229101LA','Eagle','ES','Kristine Potter'),('30029228101GA','Ferrari','GX','Diane Carter'),('30029228101ME','Fiat','IS','Rene Harper'),('30029228101NV','Fisker','CT','Eugene Jennings'),('30029228101OR','Ford','ES','Kara Snyder'),('40029228101AK','Geo','GX','Shannon Lucas'),('40029228101CA','GMC','IS','Christine Steele'),('40029228101MD','Honda','CT','Terrell Hicks'),('40029228101NH','Hummer','ES','Emanuel Hubbard'),('40029228101PA','Hyundai','GX','Tara Holt'),('44002922810HI','Infiniti','IS','Ken Scott'),('50029228101AZ','Isuzu','CT','Gerardo Doyle'),('50029228101ID','Jaguar','ES','Shelia Barton'),('50029228101MA','Jeep','GX','Sadie Burton'),('50029228101NJ','Kia','IS','Robin Norton'),('50029228101RI','Lamborghini','CT','Ollie Obrien'),('60029228101AR','LandRover','ES','Mark Russell'),('60029228101IL','Acura','GX','Lindsey Rice'),('60029228101MI','AlfaRomeo','IS','Leland Glover'),('60029228101NM','AstonMartin','CT','Julian Austin'),('60029228101SC','Audi','ES','Sheila Pratt'),('60029238101NM','Bentley','GX','Lance Herrera'),('70029228101CA','BMW','IS','Angelo Greene'),('70029228101IN','Bugatti','CT','John Keller'),('70029228101MN','Buick','ES','Stuart Phelps'),('70029228101NY','Cadillac','GX','Leticia Blair'),('70029228101SD','Chevrolet','IS','Christian Howell'),('80029228101CO','Chrysler','CT','Leigh Mccoy'),('80029228101IA','Daewoo','ES','Shaun Taylor'),('80029228101MS','Dodge','GX','Gustavo Miles'),('80029228101NC','Eagle','IS','Roberto Graham'),('80029228101TN','Ferrari','CT','Johnnie Banks'),('90029228101CT','Fiat','ES','Leslie Mcdonald'),('90029228101KS','Fisker','GX','Donnie Cortez'),('90029228101MO','Ford','IS','Harold Walters'),('90029228101ND','Geo','CT','Felix Lawrence'),('90029228101TX','GMC','ES','Alberta Rowe');
/*!40000 ALTER TABLE `stolenvehicles` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `vehiclesearchlog`
--

DROP TABLE IF EXISTS `vehiclesearchlog`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `vehiclesearchlog` (
  `VehiclesSearchLogID` int(11) NOT NULL AUTO_INCREMENT,
  `FieldSearched` varchar(100) DEFAULT NULL,
  `ValueSearched` varchar(100) DEFAULT NULL,
  `LogDate` datetime DEFAULT NULL,
  PRIMARY KEY (`VehiclesSearchLogID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `vehiclesearchlog`
--

LOCK TABLES `vehiclesearchlog` WRITE;
/*!40000 ALTER TABLE `vehiclesearchlog` DISABLE KEYS */;
/*!40000 ALTER TABLE `vehiclesearchlog` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2016-10-15 16:10:14
