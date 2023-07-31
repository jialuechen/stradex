alter table `stradex_base`.`stocktypeinfo` modify column `minTradeNumber` double not null default 1;
alter table `stradex_base`.`stocktypeinfo` modify column `maxTradeNumber` double not null default 1;
UPDATE `stradex_base`.`version` set `version` = 2;
