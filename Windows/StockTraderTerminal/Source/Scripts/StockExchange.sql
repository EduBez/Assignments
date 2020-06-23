CREATE DATABASE  IF NOT EXISTS `stockexchange` /*!40100 DEFAULT CHARACTER SET utf8 */;
USE `stockexchange`;
-- MySQL dump 10.13  Distrib 5.7.17, for Win64 (x86_64)
--
-- Host: localhost    Database: stockexchange
-- ------------------------------------------------------
-- Server version	5.7.18-log

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
-- Table structure for table `portfolio`
--

DROP TABLE IF EXISTS `portfolio`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `portfolio` (
  `TraderID` int(11) NOT NULL,
  `StockID` varchar(30) NOT NULL,
  `Quantity` int(11) DEFAULT NULL,
  `TotalCost` decimal(10,2) DEFAULT NULL,
  PRIMARY KEY (`TraderID`,`StockID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `portfolio`
--

LOCK TABLES `portfolio` WRITE;
/*!40000 ALTER TABLE `portfolio` DISABLE KEYS */;
/*!40000 ALTER TABLE `portfolio` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `stock`
--

DROP TABLE IF EXISTS `stock`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `stock` (
  `StockID` varchar(30) NOT NULL,
  `CompanyName` varchar(200) DEFAULT NULL,
  `LastSalePrice` decimal(10,2) DEFAULT NULL,
  PRIMARY KEY (`StockID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `stock`
--

LOCK TABLES `stock` WRITE;
/*!40000 ALTER TABLE `stock` DISABLE KEYS */;
INSERT INTO `stock` VALUES ('AAPL','Apple',148.96),('AMZN','Amazon.com',934.15),('ATVI','Activision Blizzard',53.83),('CTSH','Cognizant Technology',63.22),('CYTR','Cytrx',0.49),('DRRX','Durect',0.80),('DRYS','Dryships',0.99),('FCEL','Fuelcell Energy',1.05),('INTC','Intel',36.82),('MSFT','Microsoft',69.00),('NFLX','Netflix',156.60),('NVDA','Nvidia',103.86),('TOPS','Top Ships Inc',0.22);
/*!40000 ALTER TABLE `stock` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `trader`
--

DROP TABLE IF EXISTS `trader`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `trader` (
  `TraderID` int(11) NOT NULL AUTO_INCREMENT,
  `UserName` varchar(100) DEFAULT NULL,
  `Password` varchar(100) DEFAULT NULL,
  `BalanceCash` decimal(10,2) DEFAULT NULL,
  PRIMARY KEY (`TraderID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `trader`
--

LOCK TABLES `trader` WRITE;
/*!40000 ALTER TABLE `trader` DISABLE KEYS */;
/*!40000 ALTER TABLE `trader` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `transaction`
--

DROP TABLE IF EXISTS `transaction`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `transaction` (
  `TraderID` int(11) NOT NULL,
  `StockID` varchar(30) NOT NULL,
  `Quantity` int(11) DEFAULT NULL,
  `DateTime` datetime NOT NULL,
  `OpType` varchar(1) DEFAULT NULL,
  `Status` int(11) DEFAULT NULL,
  PRIMARY KEY (`TraderID`,`StockID`,`DateTime`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `transaction`
--

LOCK TABLES `transaction` WRITE;
/*!40000 ALTER TABLE `transaction` DISABLE KEYS */;
/*!40000 ALTER TABLE `transaction` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping events for database 'stockexchange'
--

--
-- Dumping routines for database 'stockexchange'
--
/*!50003 DROP FUNCTION IF EXISTS `GetTraderID` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` FUNCTION `GetTraderID`(
    rUserName     varchar(100),
    rPassword     varchar(100)
) RETURNS int(11)
begin
    -- Declare Variable
    declare wTraderID int default -1;

    -- Retrieve TraderID
    select
        TraderID
    into
        wTraderID
    from
        Trader
    where
        UserName = rUserName and Password = rPassword;

    return wTraderID;
end ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `BuyStock` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `BuyStock`(
    rUserName     varchar(100)  ,
    rPassword     varchar(100)  ,
    rStockID      varchar(30)   ,
    rQuantity     int           ,
    rPrice        decimal(10, 2)
)
begin

    -- Declare local variables
    declare   wCost       decimal(10, 2);
    declare   wNewCost    decimal(10, 2);
    declare   wQuantity   int;

    -- Operation Status Codes

    -- 0  =>  Success
    -- 1  =>  DON'T have suficient funds
    -- 2  =>  Stock NOT found in Portfolio
    -- 3  =>  DON'T have enough stock quantity

    -- Retrieve TraderID and BalanceCash
    select
        @TraderID    := TraderID ,
        @BalanceCash := BalanceCash    
    from
        Trader
    where
        UserName = rUserName and Password = rPassword;

    -- Calculate cost
    set wCost := rQuantity * rPrice;
        
    -- We DON'T have suficient funds
    if wCost > @BalanceCash
    then
        -- Update Transaction
        insert into
            Transaction
        values
            (@TraderID, rStockID, rQuantity, NOW(), 'B', 1);
    end if;

    -- We DO have suficient funds
    if wCost <= @BalanceCash
    then
        -- Update balance cash
        update
            Trader
        set
            BalanceCash = (@BalanceCash - wCost)
        where
            TraderID = @TraderID;

        -- Check Portfolio for this stock
        select
            @RecCnt := COUNT(*)
        from
            Portfolio
        where
            TraderID = @TraderID and StockID = rStockID;

        -- No records found
        if @RecCnt = 0
        then
            -- Portfolio
            insert into
                Portfolio
            values
                (@TraderID, rStockID, rQuantity, wCost);

        -- Records found
        else
            -- Retrieve current values
            select
                @Quantity  := Quantity,
                @TotalCost := TotalCost
            from
                Portfolio
            where
                TraderID = @TraderID and StockID = rStockID;

            -- Update new quantity
            set wQuantity := @Quantity + rQuantity;

            -- Update new total cost
            -- Doubt: is this correct ???
            set wNewCost := /*@TotalCost +*/ wCost;

             -- Update Portfolio
             update
                 Portfolio
             set
                Quantity  = wQuantity,
                TotalCost = wNewCost
             where
                 TraderID = @TraderID and StockID = rStockID;
        end if;

        -- Update Transaction
        insert into
            Transaction
        values
            (@TraderID, rStockID, rQuantity, NOW(), 'B', 0);

    end if;
end ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `SellStock` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `SellStock`(
    rUserName     varchar(100)  ,
    rPassword     varchar(100)  ,
    rStockID      varchar(30)   ,
    rQuantity     int           ,
    rPrice        decimal(10, 2)
)
begin
    -- Declare local variables
    declare   wCost       decimal(10, 2);
    declare   wNewCost    decimal(10, 2);
    declare   wQuantity   int;

    -- Operation Status Codes

    -- 0  =>  Success
    -- 1  =>  DON'T have suficient funds
    -- 2  =>  Stock NOT found in Portfolio
    -- 3  =>  DON'T have enough stock quantity

    -- Retrieve TraderID and BalanceCash
    select
        @TraderID    := TraderID ,
        @BalanceCash := BalanceCash    
    from
        Trader
    where
        UserName = rUserName and Password = rPassword;

    -- Check Portfolio for this stock
    select
        @RecCnt := COUNT(*)
    from
        Portfolio
    where
        TraderID = @TraderID and StockID = rStockID;

    -- Stock found in Portfolio
    if @RecCnt > 0
    then
        -- Retrieve Portfolio Quantity and TotalCost
        select
            @Quantity  := Quantity,
            @TotalCost := TotalCost
        from
            Portfolio
        where
            TraderID = @TraderID and StockID = rStockID;
    
        -- DON'T have enough stock quantity
        if rQuantity > @Quantity
        then
            -- Update Transaction
            insert into
                Transaction
            values
                (@TraderID, rStockID, rQuantity, NOW(), 'S', 3);

        -- DO have enough stock quantity
        else
            -- Calculate cost
            set wCost := rQuantity * rPrice;

            -- Update new quantity
            set wQuantity := @Quantity - rQuantity;

            -- Update new total cost
            -- Doubt: is this correct ???
            set wNewCost := /*@TotalCost -*/ wCost;

            -- Update balance cash
            update
                Trader
            set
                BalanceCash = (@BalanceCash + wCost)
            where
                TraderID = @TraderID;

            -- Update Portfolio
            update
                Portfolio
            set
               Quantity  = wQuantity/*,*/
               -- TotalCost = wNewCost
            where
                TraderID = @TraderID and StockID = rStockID;

            -- Update Stock
            update
                Stock
            set
               LastSalePrice  = rPrice
            where
                StockID = rStockID;

            -- Update Transaction
            insert into
                Transaction
            values
                (@TraderID, rStockID, rQuantity, NOW(), 'S', 0);
        end if;

    -- Stock NOT found in Portfolio
    else
        -- Update Transaction
        insert into
            Transaction
        values
            (@TraderID, rStockID, rQuantity, NOW(), 'S', 2);
    end if;
end ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `ViewPortfolio` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `ViewPortfolio`(
    rUserName     varchar(100),
    rPassword     varchar(100)
)
begin
    -- Declare Variable
    declare wTraderID int;

    -- Retrieve TraderID
    set wTraderID = GetTraderID(rUserName, rPassword);

    -- View Portfolio
    select
        P.TraderID    ,
        P.StockID     ,
        S.CompanyName ,
        P.Quantity    ,
        P.TotalCost   ,
        S.LastSalePrice
    from
        Portfolio P
    join
        Stock S
    on
        S.StockID = P.StockID
    where
       P.TraderID = wTraderID
    order by
        S.StockID;
end ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `ViewTransactions` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `ViewTransactions`(
    rUserName     varchar(100),
    rPassword     varchar(100)
)
begin
    -- Declare Variable
    declare wTraderID int;

    -- Retrieve TraderID
    set wTraderID = GetTraderID(rUserName, rPassword);

    -- View Transaction
    select
        TraderID,
        StockID,
        Quantity,
        DateTime,

        case OpType
            when 'B' then 'BUY'
            when 'S' then 'SELL'
        end as 'Operation',

        case Status
            when 0 then 'Success'
            when 1 then 'Error - Do not have suficient funds'
            when 2 then 'Error - Stock code not found in portfolio'
            when 3 then 'Error - Do not have enough stock quantity'
        end as 'Status'
    from
        Transaction
    where
        TraderID = wTraderID
    order by
        StockID,
        DateTime,
        Operation,
        Status;
end ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2017-05-12 14:02:09
