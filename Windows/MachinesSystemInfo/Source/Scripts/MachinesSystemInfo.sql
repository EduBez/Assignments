-- MySQL dump 10.13  Distrib 5.7.12, for Win64 (x86_64)
--
-- Host: localhost    Database: machinessysteminfo
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
-- Table structure for table `machineregistry`
--

DROP TABLE IF EXISTS `machineregistry`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `machineregistry` (
  `MachineID` varchar(30) NOT NULL,
  `Email` varchar(254) DEFAULT NULL,
  `MemoryLimit` varchar(5) DEFAULT NULL,
  `CpuLimit` varchar(5) DEFAULT NULL,
  `ProcessesLimit` varchar(5) DEFAULT NULL,
  PRIMARY KEY (`MachineID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `machineregistry`
--

LOCK TABLES `machineregistry` WRITE;
/*!40000 ALTER TABLE `machineregistry` DISABLE KEYS */;
/*!40000 ALTER TABLE `machineregistry` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `machineutilization`
--

DROP TABLE IF EXISTS `machineutilization`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `machineutilization` (
  `MachineID` varchar(30) NOT NULL,
  `CaptureTime` datetime NOT NULL,
  `MemoryUsage` varchar(5) DEFAULT NULL,
  `CpuUsage` varchar(5) DEFAULT NULL,
  `ProcessesCount` varchar(5) DEFAULT NULL,
  `AlertWarning` tinyint(1) DEFAULT NULL,
  PRIMARY KEY (`MachineID`,`CaptureTime`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `machineutilization`
--

LOCK TABLES `machineutilization` WRITE;
/*!40000 ALTER TABLE `machineutilization` DISABLE KEYS */;
/*!40000 ALTER TABLE `machineutilization` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2016-10-26 23:39:37
