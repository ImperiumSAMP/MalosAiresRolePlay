-- phpMyAdmin SQL Dump
-- version 3.4.10.1deb1
-- http://www.phpmyadmin.net
--
-- Servidor: localhost
-- Tiempo de generación: 11-02-2015 a las 18:56:04
-- Versión del servidor: 5.5.34
-- Versión de PHP: 5.3.10-1ubuntu3.15

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
-- Estructura de tabla para la tabla `log_vehicles`
--

CREATE TABLE IF NOT EXISTS `log_vehicles` (
  `VehID` int(11) NOT NULL,
  `pName` text CHARACTER SET utf8 NOT NULL,
  `pID` int(11) NOT NULL,
  `tName` text CHARACTER SET utf8 NOT NULL,
  `tID` int(11) NOT NULL,
  `Date` datetime NOT NULL,
  `Command` text CHARACTER SET utf8 NOT NULL,
  `Params` text CHARACTER SET utf8 NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
