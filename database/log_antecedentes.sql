-- phpMyAdmin SQL Dump
-- version 4.2.11
-- http://www.phpmyadmin.net
--
-- Servidor: 127.0.0.1
-- Tiempo de generación: 19-02-2015 a las 10:08:55
-- Versión del servidor: 5.6.21
-- Versión de PHP: 5.6.3

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Base de datos: `isamp_test`
--

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `log_antecedentes`
--

CREATE TABLE IF NOT EXISTS `log_antecedentes` (
  `pID` int(11) NOT NULL,
  `pName` text CHARACTER SET utf8 NOT NULL,
  `pIP` text CHARACTER SET utf8 NOT NULL,
  `date` datetime NOT NULL,
  `pAntecedentes` text CHARACTER SET utf8 NOT NULL,
  `tID` int(11) NOT NULL,
  `tName` text CHARACTER SET utf8 NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
