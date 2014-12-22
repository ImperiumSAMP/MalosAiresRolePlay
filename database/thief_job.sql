-- phpMyAdmin SQL Dump
-- version 3.4.10.1deb1
-- http://www.phpmyadmin.net
--
-- Servidor: localhost
-- Tiempo de generación: 21-12-2014 a las 14:26:37
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
-- Estructura de tabla para la tabla `thief_job`
--

CREATE TABLE IF NOT EXISTS `thief_job` (
  `accountid` int(11) NOT NULL,
  `pFelonExp` int(11) NOT NULL,
  `pFelonLevel` int(11) NOT NULL DEFAULT '1',
  `pRobPersonLimit` int(11) NOT NULL,
  `pRobLastVictimPID` int(11) NOT NULL,
  `pTheftLastVictimPID` int(11) NOT NULL,
  `pTheftPersonLimit` int(11) NOT NULL,
  `pRob247Limit` int(11) NOT NULL,
  `pTheft247Limit` int(11) NOT NULL,
  `pRobHouseLimit` int(11) NOT NULL,
  `pRob2HouseLimit` int(11) NOT NULL,
  `pForceDoorLimit` int(11) NOT NULL,
  `pForceEngineLimit` int(11) NOT NULL,
  `pDesarmCarLimit` int(11) NOT NULL,
  PRIMARY KEY (`accountid`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
