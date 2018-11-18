# Host: localhost  (Version: 5.5.5-m3)
# Date: 2018-04-18 10:45:52
# Generator: MySQL-Front 5.3  (Build 4.13)

/*!40101 SET NAMES utf8 */;

#
# Source for table "admin"
#

DROP TABLE IF EXISTS `admin`;
CREATE TABLE `admin` (
  `Id` int(11) NOT NULL AUTO_INCREMENT,
  `uname` varchar(255) DEFAULT NULL COMMENT '账号',
  `upassword` varchar(255) DEFAULT NULL COMMENT '密码',
  PRIMARY KEY (`Id`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT COMMENT='管理员信息表';

#
# Data for table "admin"
#

INSERT INTO `admin` VALUES (1,'admin','admin'),(2,'1','1'),(3,'2','2'),(5,'3','3');

#
# Source for table "infor"
#

DROP TABLE IF EXISTS `infor`;
CREATE TABLE `infor` (
  `Id` int(11) NOT NULL AUTO_INCREMENT,
  `sno` varchar(255) DEFAULT NULL COMMENT '塔号',
  `date` varchar(255) DEFAULT NULL COMMENT '日期',
  `shuiwei` varchar(255) DEFAULT NULL COMMENT '水位',
  PRIMARY KEY (`Id`)
) ENGINE=InnoDB AUTO_INCREMENT=17 DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT COMMENT='水位值信息表';

#
# Data for table "infor"
#

INSERT INTO `infor` VALUES (1,'1','20180101','10'),(2,'2','20180101','12'),(3,'3','20180101','9'),(4,'4','20180101','18'),(5,'5','20180101','20'),(6,'6','20180101','31'),(7,'7','20180101','17'),(8,'8','20180101','40'),(9,'1','20180102','51'),(10,'2','20180102','23'),(11,'3','20180102','34'),(12,'4','20180102','34'),(13,'5','20180102','35'),(14,'6','20180102','87'),(15,'7','20180102','35'),(16,'8','20180102','97');

#
# Source for table "shuita"
#

DROP TABLE IF EXISTS `shuita`;
CREATE TABLE `shuita` (
  `Id` int(11) NOT NULL AUTO_INCREMENT,
  `sno` varchar(255) DEFAULT NULL COMMENT '水塔号',
  `sname` varchar(255) DEFAULT NULL COMMENT '水塔名',
  `place` varchar(255) DEFAULT NULL COMMENT '地区',
  PRIMARY KEY (`Id`)
) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT COMMENT='水塔信息表';

#
# Data for table "shuita"
#

INSERT INTO `shuita` VALUES (1,'1','水塔01','北京'),(2,'2','水塔02','北京'),(3,'3','水塔03','张家口'),(4,'4','水塔04','张家口'),(5,'5','水塔05','张家口'),(6,'6','水塔06','邢台'),(7,'7','水塔07','邢台'),(8,'8','水塔08','深圳');
