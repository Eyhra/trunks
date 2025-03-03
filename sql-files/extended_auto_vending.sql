CREATE TABLE `cart_bkp_inventory` (
 `id` int(11) NOT NULL AUTO_INCREMENT,
 `char_id` int(11) NOT NULL DEFAULT '0',
 `nameid` int(10) unsigned NOT NULL DEFAULT '0',
 `amount` int(11) NOT NULL DEFAULT '0',
 `equip` int(11) unsigned NOT NULL DEFAULT '0',
 `identify` smallint(6) NOT NULL DEFAULT '0',
 `refine` tinyint(3) unsigned NOT NULL DEFAULT '0',
 `attribute` tinyint(4) NOT NULL DEFAULT '0',
 `card0` int(10) unsigned NOT NULL DEFAULT '0',
 `card1` int(10) unsigned NOT NULL DEFAULT '0',
 `card2` int(10) unsigned NOT NULL DEFAULT '0',
 `card3` int(10) unsigned NOT NULL DEFAULT '0',
 `option_id0` smallint(5) NOT NULL DEFAULT '0',
 `option_val0` smallint(5) NOT NULL DEFAULT '0',
 `option_parm0` tinyint(3) NOT NULL DEFAULT '0',
 `option_id1` smallint(5) NOT NULL DEFAULT '0',
 `option_val1` smallint(5) NOT NULL DEFAULT '0',
 `option_parm1` tinyint(3) NOT NULL DEFAULT '0',
 `option_id2` smallint(5) NOT NULL DEFAULT '0',
 `option_val2` smallint(5) NOT NULL DEFAULT '0',
 `option_parm2` tinyint(3) NOT NULL DEFAULT '0',
 `option_id3` smallint(5) NOT NULL DEFAULT '0',
 `option_val3` smallint(5) NOT NULL DEFAULT '0',
 `option_parm3` tinyint(3) NOT NULL DEFAULT '0',
 `option_id4` smallint(5) NOT NULL DEFAULT '0',
 `option_val4` smallint(5) NOT NULL DEFAULT '0',
 `option_parm4` tinyint(3) NOT NULL DEFAULT '0',
 `expire_time` int(11) unsigned NOT NULL DEFAULT '0',
 `bound` tinyint(3) unsigned NOT NULL DEFAULT '0',
 `unique_id` bigint(20) unsigned NOT NULL DEFAULT '0',
 `enchantgrade` tinyint(3) unsigned NOT NULL DEFAULT '0',
 PRIMARY KEY (`id`),
 KEY `char_id` (`char_id`)
) ENGINE=MyISAM AUTO_INCREMENT=553 DEFAULT CHARSET=utf8;

ALTER TABLE `vendings` ADD COLUMN `autotrade` TINYINT(4) unsigned NOT NULL AFTER `sit`;
ALTER TABLE `vendings` ADD COLUMN `extended_vending_item` int(10) unsigned NOT NULL DEFAULT '0' AFTER `sit`;

REPLACE INTO `item_db2_re` (`id`,`name_aegis`,`name_english`,`type`,`price_sell`,`weight`) VALUES (30000,'Zeny','Zeny','Etc',10,10);
REPLACE INTO `item_db2_re` (`id`,`name_aegis`,`name_english`,`type`,`price_sell`,`weight`) VALUES (30001,'Cash','Cash','Etc',10,10);
REPLACE INTO `item_db2` (`id`,`name_aegis`,`name_english`,`type`,`price_sell`,`weight`) VALUES (30000,'Zeny','Zeny','Etc',10,10);
REPLACE INTO `item_db2` (`id`,`name_aegis`,`name_english`,`type`,`price_sell`,`weight`) VALUES (30001,'Cash','Cash','Etc',10,10);

ALTER TABLE `char` ADD `autovend_id` INT(11) UNSIGNED NOT NULL DEFAULT '0' AFTER `save_y`; 
ALTER TABLE `char` ADD `autovend_posy` SMALLINT(5) UNSIGNED NOT NULL DEFAULT '0' AFTER `save_y`;
ALTER TABLE `char` ADD `autovend_posx` SMALLINT(5) UNSIGNED NOT NULL DEFAULT '0' AFTER `save_y`;
ALTER TABLE `char` ADD `autovend_mapid` VARCHAR(11) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '0' AFTER `save_y`;
ALTER TABLE `char` ADD `autovend_check` TINYINT(1) NOT NULL DEFAULT '0' AFTER `save_y`;

ALTER TABLE `picklog` CHANGE `type` `type` ENUM('T','V','P','M','S','N','D','O','U','A','R','G','E','I','B','L','K','X','$','F','Y','Z','Q','H','W') CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT 'P';


