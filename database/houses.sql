-- phpMyAdmin SQL Dump
-- version 3.4.10.1deb1
-- http://www.phpmyadmin.net
--
-- Servidor: localhost
-- Tiempo de generación: 23-12-2014 a las 00:52:54
-- Versión del servidor: 5.5.34
-- Versión de PHP: 5.3.10-1ubuntu3.9

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Base de datos: `isamptest`
--

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `houses`
--

CREATE TABLE IF NOT EXISTS `houses` (
  `Id` int(11) NOT NULL,
  `Owned` tinyint(1) NOT NULL DEFAULT '0',
  `OwnerSQLID` int(11) NOT NULL DEFAULT '0',
  `OwnerName` text NOT NULL,
  `OutsideX` float NOT NULL DEFAULT '0',
  `OutsideY` float NOT NULL DEFAULT '0',
  `OutsideZ` float NOT NULL DEFAULT '0',
  `OutsideAngle` float NOT NULL DEFAULT '0',
  `OutsideInterior` int(11) NOT NULL DEFAULT '0',
  `OutsideWorld` int(11) NOT NULL DEFAULT '0',
  `InsideX` float NOT NULL DEFAULT '0',
  `InsideY` float NOT NULL DEFAULT '0',
  `InsideZ` float NOT NULL DEFAULT '0',
  `InsideAngle` float NOT NULL DEFAULT '0',
  `InsideInterior` int(11) NOT NULL DEFAULT '0',
  `InsideWorld` int(11) NOT NULL DEFAULT '0',
  `HousePrice` int(11) NOT NULL DEFAULT '0',
  `Money` int(11) NOT NULL DEFAULT '0',
  `Locked` tinyint(1) NOT NULL DEFAULT '0',
  `Radio` smallint(6) NOT NULL DEFAULT '0',
  `Marijuana` smallint(6) NOT NULL DEFAULT '0',
  `LSD` smallint(6) NOT NULL DEFAULT '0',
  `Ecstasy` smallint(6) NOT NULL DEFAULT '0',
  `Cocaine` smallint(6) NOT NULL DEFAULT '0',
  `Tenant` text NOT NULL,
  `IncomeAccept` tinyint(1) NOT NULL DEFAULT '0',
  `Income` tinyint(1) NOT NULL DEFAULT '0',
  `IncomePrice` int(11) NOT NULL DEFAULT '0',
  `IncomePriceAdd` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`Id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 DELAY_KEY_WRITE=1 ROW_FORMAT=DYNAMIC;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
