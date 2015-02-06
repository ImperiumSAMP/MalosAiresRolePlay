CREATE TABLE IF NOT EXISTS `commands` (
  `command` varchar(64) NOT NULL,
  `level` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`command`),
  KEY `level` (`level`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;