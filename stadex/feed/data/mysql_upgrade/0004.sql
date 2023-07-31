CREATE TABLE IF NOT EXISTS `stradex_base`.`holiday` (
	`id`	INT UNSIGNED NOT NULL AUTO_INCREMENT,
	`date` BIGINT UNSIGNED NOT NULL,
	PRIMARY KEY(`id`)
);
INSERT INTO `stradex_base`.`holiday` (`date`) VALUES (20210101);
INSERT INTO `stradex_base`.`holiday` (`date`) VALUES (20210211);
INSERT INTO `stradex_base`.`holiday` (`date`) VALUES (20210212);
INSERT INTO `stradex_base`.`holiday` (`date`) VALUES (20210215);
INSERT INTO `stradex_base`.`holiday` (`date`) VALUES (20210216);
INSERT INTO `stradex_base`.`holiday` (`date`) VALUES (20210217);
INSERT INTO `stradex_base`.`holiday` (`date`) VALUES (20210405);
INSERT INTO `stradex_base`.`holiday` (`date`) VALUES (20210501);
INSERT INTO `stradex_base`.`holiday` (`date`) VALUES (20210503);
INSERT INTO `stradex_base`.`holiday` (`date`) VALUES (20210504);
INSERT INTO `stradex_base`.`holiday` (`date`) VALUES (20210505);
INSERT INTO `stradex_base`.`holiday` (`date`) VALUES (20210614);
INSERT INTO `stradex_base`.`holiday` (`date`) VALUES (20210920);
INSERT INTO `stradex_base`.`holiday` (`date`) VALUES (20210921);
INSERT INTO `stradex_base`.`holiday` (`date`) VALUES (20211001);
INSERT INTO `stradex_base`.`holiday` (`date`) VALUES (20211004);
INSERT INTO `stradex_base`.`holiday` (`date`) VALUES (20211005);
INSERT INTO `stradex_base`.`holiday` (`date`) VALUES (20211006);
INSERT INTO `stradex_base`.`holiday` (`date`) VALUES (20211007);

UPDATE `stradex_base`.`version` set `version` = 4;