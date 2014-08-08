CREATE TABLE IF NOT EXISTS `thief_job` (
  `accountid` int(11) NOT NULL,
  `pFelonExp` int(11) NOT NULL,
  `pFelonLevel` int(11) NOT NULL,
  `pRobPersonLimit` int(11) NOT NULL,
  `pRobLastVictimPID` int(11) NOT NULL,
  `pTheftLastVictimPID` int(11) NOT NULL,
  `pTheftPersonLimit` int(11) NOT NULL,
  `pRob247Limit` int(11) NOT NULL,
  `pTheft247Limit` int(11) NOT NULL,
  `pRobHouseLimit` int(11) NOT NULL,
  `pRobLastHouseID` int(11) NOT NULL,
  `pTheftLastHouseID` int(11) NOT NULL,
  `pTheftHouseLimit` int(11) NOT NULL,
  PRIMARY KEY (`accountid`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;


insert into thief_job (accountid, pFelonExp, pFelonLevel, pRobPersonLimit, pRobLastVictimPID, pTheftLastVictimPID, pTheftPersonLimit, pRob247Limit, pTheft247Limit, pRobHouseLimit, pRobLastHouseID, pTheftLastHouseID, pTheftHouseLimit) select id, pFelonExp, pFelonLevel, pRobPersonLimit, pRobLastVictimPID, pTheftLastVictimPID, pTheftPersonLimit, pRob247Limit, pTheft247Limit, pRobHouseLimit, 0, 0, 0 from accounts;