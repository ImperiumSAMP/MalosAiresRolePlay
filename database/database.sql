-- phpMyAdmin SQL Dump
-- version 3.4.10.1deb1
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Jan 07, 2014 at 08:00 PM
-- Server version: 5.5.34
-- PHP Version: 5.3.10-1ubuntu3.8

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `isamptest`
--

-- --------------------------------------------------------

--
-- Table structure for table `accounts`
--

CREATE TABLE IF NOT EXISTS `accounts` (
  `Id` int(11) NOT NULL AUTO_INCREMENT,
  `Name` text NOT NULL,
  `Password` text NOT NULL,
  `Ip` text NOT NULL,
  `Level` int(11) NOT NULL DEFAULT '1',
  `AdminLevel` int(11) NOT NULL DEFAULT '0',
  `DonateRank` int(11) NOT NULL DEFAULT '0',
  `AccountBlocked` tinyint(1) NOT NULL DEFAULT '0',
  `Tutorial` tinyint(1) NOT NULL DEFAULT '1',
  `Sex` tinyint(1) NOT NULL DEFAULT '0',
  `Age` int(11) NOT NULL DEFAULT '18',
  `Exp` int(11) NOT NULL DEFAULT '0',
  `pHealth` float NOT NULL DEFAULT '100',
  `pArmour` float NOT NULL,
  `CashMoney` int(20) NOT NULL DEFAULT '1200',
  `BankMoney` int(20) NOT NULL DEFAULT '200',
  `Skin` int(11) NOT NULL DEFAULT '3',
  `Drugs` int(11) NOT NULL DEFAULT '0',
  `Materials` int(11) NOT NULL DEFAULT '0',
  `Job` int(11) NOT NULL DEFAULT '0',
  `JobTime` int(11) NOT NULL DEFAULT '0',
  `pJobAllowed` int(1) NOT NULL DEFAULT '1',
  `PlayingHours` int(11) NOT NULL DEFAULT '0',
  `LastConnected` datetime NOT NULL,
  `PayCheck` int(11) NOT NULL DEFAULT '0',
  `pPayTime` int(11) NOT NULL,
  `Faction` int(11) NOT NULL DEFAULT '0',
  `Rank` int(11) NOT NULL DEFAULT '0',
  `HouseKey` int(11) NOT NULL DEFAULT '0',
  `BizKey` int(11) NOT NULL DEFAULT '0',
  `SpawnPoint` tinyint(1) NOT NULL DEFAULT '0',
  `Warnings` int(11) NOT NULL DEFAULT '0',
  `CarLic` tinyint(1) NOT NULL DEFAULT '0',
  `FlyLic` tinyint(1) NOT NULL DEFAULT '0',
  `WepLic` tinyint(1) NOT NULL DEFAULT '0',
  `PhoneNumber` int(11) NOT NULL DEFAULT '0',
  `PhoneCompany` int(11) NOT NULL DEFAULT '0',
  `PhoneBook` int(11) NOT NULL DEFAULT '0',
  `ListNumber` tinyint(1) NOT NULL DEFAULT '1',
  `Jailed` tinyint(1) NOT NULL DEFAULT '0',
  `JailedTime` int(11) NOT NULL DEFAULT '0',
  `Products` int(11) NOT NULL DEFAULT '0',
  `pX` float NOT NULL DEFAULT '0',
  `pY` float NOT NULL DEFAULT '0',
  `pZ` float NOT NULL DEFAULT '0',
  `pA` float NOT NULL DEFAULT '0',
  `pInterior` int(11) NOT NULL DEFAULT '0',
  `pWorld` int(11) NOT NULL DEFAULT '0',
  `pVeh1` int(11) NOT NULL DEFAULT '0',
  `pVeh2` int(11) NOT NULL DEFAULT '0',
  `pRegStep` int(11) NOT NULL DEFAULT '1',
  `pOrigin` int(11) NOT NULL DEFAULT '0',
  `pCamX` float NOT NULL DEFAULT '0',
  `pCamY` float NOT NULL DEFAULT '0',
  `pCamZ` float NOT NULL DEFAULT '0',
  `pCamLookAtX` float NOT NULL DEFAULT '0',
  `pCamLookAtY` float NOT NULL DEFAULT '0',
  `pCamLookAtZ` float NOT NULL DEFAULT '0',
  `pHospitalized` int(11) NOT NULL,
  `pPoints` int(11) NOT NULL,
  `pWantedLevel` int(11) NOT NULL,
  `pAccusedOf` varchar(64) NOT NULL,
  `pCantWork` tinyint(1) NOT NULL DEFAULT '0',
  `pJobLimitCounter` int(11) NOT NULL,
  `pInv0` varchar(16) NOT NULL,
  `pInv1` varchar(16) NOT NULL,
  `pBMLimit` int(11) NOT NULL,
  `pAccusedBy` varchar(24) NOT NULL,
  `pFelonExp` int(11) NOT NULL,
  `pFelonLevel` int(11) NOT NULL DEFAULT '1',
  `pRobPersonLimit` int(11) NOT NULL,
  `pRobHouseLimit` int(11) NOT NULL,
  `pRob247Limit` int(11) NOT NULL,
  `pRobLastVictimPID` int(11) NOT NULL,
  `pTheftPersonLimit` int(11) NOT NULL,
  `pTheft247Limit` int(11) NOT NULL,
  `pTheftLastVictimPID` int(11) NOT NULL,
  `pMuteB` int(11) NOT NULL,
  `pRentCarID` int(11) NOT NULL DEFAULT '0',
  `pRentCarRID` int(11) NOT NULL DEFAULT '-1',
  `pLighter` int(11) NOT NULL DEFAULT '0',
  `pCigarettes` int(11) NOT NULL DEFAULT '0',
  `pFightStyle` int(11) NOT NULL,
  `pMarijuana` int(11) NOT NULL,
  `pLSD` int(11) NOT NULL,
  `pEcstasy` int(11) NOT NULL,
  `pCocaine` int(11) NOT NULL,
  PRIMARY KEY (`Id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 CHECKSUM=1 DELAY_KEY_WRITE=1 ROW_FORMAT=DYNAMIC AUTO_INCREMENT=10 ;

-- --------------------------------------------------------

--
-- Table structure for table `adminmsg`
--

CREATE TABLE IF NOT EXISTS `adminmsg` (
  `message` text NOT NULL,
  `author` varchar(24) NOT NULL,
  `date` int(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Table structure for table `bans`
--

CREATE TABLE IF NOT EXISTS `bans` (
  `pID` int(11) NOT NULL,
  `pName` varchar(24) NOT NULL,
  `pIP` varchar(16) NOT NULL,
  `banDate` datetime NOT NULL,
  `banEnd` datetime NOT NULL,
  `banReason` text NOT NULL,
  `banIssuerID` int(11) NOT NULL,
  `banIssuerName` varchar(24) NOT NULL,
  `banActive` int(11) NOT NULL,
  `banPanel` varchar(8) NOT NULL DEFAULT 'No'
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Table structure for table `buildings`
--

CREATE TABLE IF NOT EXISTS `buildings` (
  `blFaction` int(11) NOT NULL DEFAULT '0',
  `blID` int(11) NOT NULL,
  `blEntranceFee` int(11) NOT NULL DEFAULT '0',
  `blOutsideInt` int(11) NOT NULL DEFAULT '0',
  `blInsideInt` int(11) NOT NULL DEFAULT '0',
  `blLocked` tinyint(1) NOT NULL DEFAULT '1',
  `blPickupModel` int(11) NOT NULL DEFAULT '0',
  `blName` text NOT NULL,
  `blText` text NOT NULL,
  `blText2` text NOT NULL,
  `blOutsideX` float NOT NULL DEFAULT '0',
  `blOutsideY` float NOT NULL DEFAULT '0',
  `blOutsideZ` float NOT NULL DEFAULT '0',
  `blOutsideAngle` float NOT NULL DEFAULT '0',
  `blInsideX` float NOT NULL DEFAULT '0',
  `blInsideY` float NOT NULL DEFAULT '0',
  `blInsideZ` float NOT NULL DEFAULT '0',
  `blInsideAngle` float NOT NULL DEFAULT '0',
  `blInsideWorld` int(11) NOT NULL DEFAULT '0',
  `blMaterials` int(11) NOT NULL,
  `blDrugs` int(11) NOT NULL,
  PRIMARY KEY (`blID`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Table structure for table `business`
--

CREATE TABLE IF NOT EXISTS `business` (
  `bID` int(11) NOT NULL,
  `bName` text NOT NULL,
  `bOwnerID` int(11) NOT NULL,
  `bOwnerName` text NOT NULL,
  `bOutsideX` float NOT NULL,
  `bOutsideY` float NOT NULL,
  `bOutsideZ` float NOT NULL,
  `bOutsideAngle` float NOT NULL,
  `bOutsideInt` int(11) NOT NULL,
  `bInsideX` float NOT NULL,
  `bInsideY` float NOT NULL,
  `bInsideZ` float NOT NULL,
  `bInsideInt` int(11) NOT NULL,
  `bInsideAngle` float NOT NULL,
  `bEnterable` int(11) NOT NULL,
  `bPrice` int(11) NOT NULL,
  `bEntranceCost` int(11) NOT NULL,
  `bTill` int(11) NOT NULL,
  `bLocked` tinyint(1) NOT NULL,
  `bType` int(11) NOT NULL,
  `bProducts` int(11) NOT NULL,
  PRIMARY KEY (`bID`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 DELAY_KEY_WRITE=1 ROW_FORMAT=DYNAMIC;

-- --------------------------------------------------------

--
-- Table structure for table `factions`
--

CREATE TABLE IF NOT EXISTS `factions` (
  `Id` int(11) NOT NULL AUTO_INCREMENT,
  `Type` int(11) NOT NULL DEFAULT '0',
  `Name` text NOT NULL,
  `Materials` int(11) NOT NULL DEFAULT '0',
  `Drugs` int(11) NOT NULL DEFAULT '0',
  `Bank` int(20) NOT NULL DEFAULT '0',
  `Rank1` text NOT NULL,
  `Rank2` text NOT NULL,
  `Rank3` text NOT NULL,
  `Rank4` text NOT NULL,
  `Rank5` text NOT NULL,
  `Rank6` text NOT NULL,
  `Rank7` text NOT NULL,
  `Rank8` text NOT NULL,
  `Rank9` text NOT NULL,
  `Rank10` text NOT NULL,
  `Skin1` int(11) NOT NULL DEFAULT '0',
  `Skin2` int(11) NOT NULL DEFAULT '0',
  `Skin3` int(11) NOT NULL DEFAULT '0',
  `Skin4` int(11) NOT NULL DEFAULT '0',
  `Skin5` int(11) NOT NULL DEFAULT '0',
  `Skin6` int(11) NOT NULL DEFAULT '0',
  `Skin7` int(11) NOT NULL DEFAULT '0',
  `Skin8` int(11) NOT NULL DEFAULT '0',
  `Skin9` int(11) NOT NULL DEFAULT '0',
  `Skin10` int(11) NOT NULL DEFAULT '0',
  `JoinRank` int(11) NOT NULL DEFAULT '0',
  `UsesSkins` tinyint(1) NOT NULL DEFAULT '0',
  `RankAmount` int(11) NOT NULL DEFAULT '0',
  `AllowJob` tinyint(1) NOT NULL DEFAULT '1',
  `fMissionVeh` int(11) NOT NULL,
  PRIMARY KEY (`Id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 DELAY_KEY_WRITE=1 ROW_FORMAT=DYNAMIC AUTO_INCREMENT=17 ;

-- --------------------------------------------------------

--
-- Table structure for table `houses`
--

CREATE TABLE IF NOT EXISTS `houses` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `Owned` tinyint(1) NOT NULL DEFAULT '0',
  `Owner` text NOT NULL,
  `EntranceX` float NOT NULL DEFAULT '9999',
  `EntranceY` float NOT NULL DEFAULT '0',
  `EntranceZ` float NOT NULL DEFAULT '0',
  `EntranceInterior` int(11) NOT NULL DEFAULT '0',
  `ExitX` float NOT NULL DEFAULT '0',
  `ExitY` float NOT NULL DEFAULT '0',
  `ExitZ` float NOT NULL DEFAULT '0',
  `ExitInterior` int(11) NOT NULL DEFAULT '0',
  `Rentable` tinyint(1) NOT NULL DEFAULT '0',
  `RentCost` int(11) NOT NULL DEFAULT '0',
  `HousePrice` int(11) NOT NULL DEFAULT '0',
  `Materials` int(11) NOT NULL DEFAULT '0',
  `Drugs` int(11) NOT NULL DEFAULT '0',
  `Money` int(11) NOT NULL DEFAULT '0',
  `Locked` tinyint(1) NOT NULL DEFAULT '0',
  `PickupID` int(11) NOT NULL DEFAULT '0',
  `EntranceAngle` float NOT NULL DEFAULT '0',
  `ExitAngle` float NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 DELAY_KEY_WRITE=1 ROW_FORMAT=DYNAMIC AUTO_INCREMENT=201 ;

-- --------------------------------------------------------

--
-- Table structure for table `jobs`
--

CREATE TABLE IF NOT EXISTS `jobs` (
  `id` int(11) NOT NULL,
  `jType` int(11) NOT NULL DEFAULT '0',
  `jTakeX` float NOT NULL DEFAULT '99999',
  `jTakeY` float NOT NULL DEFAULT '99999',
  `jTakeZ` float NOT NULL DEFAULT '99999',
  `jTakeW` int(11) NOT NULL DEFAULT '0',
  `jTakeI` int(11) NOT NULL DEFAULT '0',
  `jName` text NOT NULL,
  `jSkin` int(11) NOT NULL DEFAULT '0',
  `jLevelReq` int(11) NOT NULL DEFAULT '0',
  `jLimit` tinyint(11) NOT NULL DEFAULT '1',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 DELAY_KEY_WRITE=1 ROW_FORMAT=DYNAMIC;

-- --------------------------------------------------------

--
-- Table structure for table `log_admin`
--

CREATE TABLE IF NOT EXISTS `log_admin` (
  `logid` int(11) NOT NULL AUTO_INCREMENT,
  `pID` int(11) NOT NULL,
  `pName` text NOT NULL,
  `pIP` text NOT NULL,
  `date` datetime NOT NULL,
  `text` text NOT NULL,
  PRIMARY KEY (`logid`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=3 ;

-- --------------------------------------------------------

--
-- Table structure for table `log_money`
--

CREATE TABLE IF NOT EXISTS `log_money` (
  `logid` int(11) NOT NULL AUTO_INCREMENT,
  `pID` int(11) NOT NULL,
  `pName` text NOT NULL,
  `pIP` text NOT NULL,
  `date` datetime NOT NULL,
  `text` text NOT NULL,
  PRIMARY KEY (`logid`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=7 ;

-- --------------------------------------------------------

--
-- Table structure for table `news`
--

CREATE TABLE IF NOT EXISTS `news` (
  `message` text NOT NULL,
  `author` varchar(24) NOT NULL,
  `date` int(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Table structure for table `server`
--

CREATE TABLE IF NOT EXISTS `server` (
  `sVehiclePricePercent` int(11) NOT NULL,
  `sMOTD` text NOT NULL,
  `sPlayersRecord` int(11) NOT NULL,
  `ID` int(11) NOT NULL AUTO_INCREMENT,
  `svLevelExp` int(11) NOT NULL,
  `sDrugRawMats` int(11) NOT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=2 ;

-- --------------------------------------------------------

--
-- Table structure for table `vehicles`
--

CREATE TABLE IF NOT EXISTS `vehicles` (
  `VehSQLID` int(11) NOT NULL AUTO_INCREMENT,
  `VehModel` int(11) NOT NULL DEFAULT '411',
  `VehPosX` float NOT NULL DEFAULT '9999',
  `VehPosY` float NOT NULL DEFAULT '0',
  `VehPosZ` float NOT NULL DEFAULT '0',
  `VehAngle` float NOT NULL DEFAULT '0',
  `VehColor1` int(11) NOT NULL DEFAULT '0',
  `VehColor2` int(11) NOT NULL DEFAULT '0',
  `VehFaction` int(11) NOT NULL DEFAULT '0',
  `VehJob` int(11) NOT NULL,
  `VehDamage1` int(11) NOT NULL DEFAULT '0',
  `VehDamage2` int(11) NOT NULL DEFAULT '0',
  `VehDamage3` int(11) NOT NULL DEFAULT '0',
  `VehDamage4` int(11) NOT NULL DEFAULT '0',
  `VehType` int(11) NOT NULL DEFAULT '0',
  `VehOwnerID` int(11) NOT NULL,
  `VehLocked` tinyint(1) NOT NULL DEFAULT '0',
  `VehFuel` int(11) NOT NULL DEFAULT '100',
  `VehEngine` tinyint(1) NOT NULL DEFAULT '0',
  `VehBonnet` tinyint(1) NOT NULL DEFAULT '0',
  `VehBoot` tinyint(1) NOT NULL DEFAULT '0',
  `VehLights` tinyint(1) NOT NULL DEFAULT '0',
  `VehOwnerSlot` int(11) NOT NULL DEFAULT '0',
  `VehDamaged` tinyint(1) NOT NULL DEFAULT '0',
  `VehTrunkSlot0` varchar(16) NOT NULL,
  `VehTrunkSlot1` varchar(16) NOT NULL,
  `VehTrunkSlot2` varchar(16) NOT NULL,
  `VehTrunkSlot3` varchar(16) NOT NULL,
  `VehHP` float NOT NULL,
  `VehPlate` varchar(7) NOT NULL,
  `VehOwnerName` text NOT NULL,
  `VehCompSlot0` int(11) NOT NULL,
  `VehCompSlot1` int(11) NOT NULL,
  `VehCompSlot2` int(11) NOT NULL,
  `VehCompSlot3` int(11) NOT NULL,
  `VehCompSlot4` int(11) NOT NULL,
  `VehCompSlot5` int(11) NOT NULL,
  `VehCompSlot6` int(11) NOT NULL,
  `VehCompSlot7` int(11) NOT NULL,
  `VehCompSlot8` int(11) NOT NULL,
  `VehCompSlot9` int(11) NOT NULL,
  `VehCompSlot10` int(11) NOT NULL,
  `VehCompSlot11` int(11) NOT NULL,
  `VehCompSlot12` int(11) NOT NULL,
  `VehCompSlot13` int(11) NOT NULL,
  `VehMarijuana` int(11) NOT NULL,
  `VehLSD` int(11) NOT NULL,
  `VehEcstasy` int(11) NOT NULL,
  `VehCocaine` int(11) NOT NULL,
  PRIMARY KEY (`VehSQLID`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 DELAY_KEY_WRITE=1 ROW_FORMAT=DYNAMIC AUTO_INCREMENT=1002 ;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;