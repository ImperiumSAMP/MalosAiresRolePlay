CREATE TABLE IF NOT EXISTS `commands` (
  `command` varchar(64) NOT NULL,
  `level` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`command`),
  KEY `level` (`level`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

INSERT INTO commands VALUES('/resetcars', 20);
INSERT INTO commands VALUES('/admincmds', 1);
INSERT INTO commands VALUES('/saltartuto', 3);
INSERT INTO commands VALUES('/tutorial', 3);
INSERT INTO commands VALUES('/teleayuda', 1);
INSERT INTO commands VALUES('/getpos', 1);
INSERT INTO commands VALUES('/ajail', 2);
INSERT INTO commands VALUES('/traer', 1);
INSERT INTO commands VALUES('/gotopos', 1);
INSERT INTO commands VALUES('/goto', 1);
INSERT INTO commands VALUES('/gotols', 1);
INSERT INTO commands VALUES('/gotospawn', 1);
INSERT INTO commands VALUES('/gotolv', 1);
INSERT INTO commands VALUES('/gotosf', 1);
INSERT INTO commands VALUES('/gotobanco', 1);
INSERT INTO commands VALUES('/descongelar', 1);
INSERT INTO commands VALUES('/congelar', 1);
INSERT INTO commands VALUES('/setcoord', 1);
INSERT INTO commands VALUES('/setint', 1);
INSERT INTO commands VALUES('/setvw', 1);
INSERT INTO commands VALUES('/darlider', 4);
INSERT INTO commands VALUES('/clima', 4);
INSERT INTO commands VALUES('/gmx', 20);
INSERT INTO commands VALUES('/exit', 20);
INSERT INTO commands VALUES('/tod', 20);
INSERT INTO commands VALUES('/payday', 20);
INSERT INTO commands VALUES('/verf', 2);
INSERT INTO commands VALUES('/checkinv', 1);
INSERT INTO commands VALUES('/slap', 2);
INSERT INTO commands VALUES('/muteb', 1);
INSERT INTO commands VALUES('/fly', 1);
INSERT INTO commands VALUES('/jetx', 3);
INSERT INTO commands VALUES('/cambiarnombre', 3);
INSERT INTO commands VALUES('/kick', 1);
INSERT INTO commands VALUES('/crearcuenta', 1);
INSERT INTO commands VALUES('/banear', 2);
INSERT INTO commands VALUES('/ban', 2);
INSERT INTO commands VALUES('/a', 1);
INSERT INTO commands VALUES('/admin', 1);
INSERT INTO commands VALUES('/desbanear', 4);
INSERT INTO commands VALUES('/money', 20);
INSERT INTO commands VALUES('/givemoney', 20);
INSERT INTO commands VALUES('/sethp', 2);
INSERT INTO commands VALUES('/setarmour', 3);
INSERT INTO commands VALUES('/givegun', 4);
INSERT INTO commands VALUES('/skin', 1);
INSERT INTO commands VALUES('/setadmin', 20);
INSERT INTO commands VALUES('/advertir', 4);
INSERT INTO commands VALUES('/mute', 1);
INSERT INTO commands VALUES('/check', 1);
INSERT INTO commands VALUES('/mps', 2);
INSERT INTO commands VALUES('/rerollplates', 20);
INSERT INTO commands VALUES('/set', 2);
INSERT INTO commands VALUES('/ao', 1);
INSERT INTO commands VALUES('/exp10de', 6);
INSERT INTO commands VALUES('/sinfo', 4);
INSERT INTO commands VALUES('/togglegooc', 2);
INSERT INTO commands VALUES('/ppvehiculos', 20);
INSERT INTO commands VALUES('/up', 1);
INSERT INTO commands VALUES('/gametext', 4);
INSERT INTO commands VALUES('/unknowngametext', 20);
INSERT INTO commands VALUES('/aservicio', 1);