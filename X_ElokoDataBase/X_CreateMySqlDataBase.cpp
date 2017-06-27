#include "stdafx.h"
#include "X_CreateMySqlDataBase.h"

//*******************************************************
//*	Id * FileName *   Sp(n)Md5   *    Sp(n + 1)Md5      *
//*******************************************************
//*														*
//*														*
//*******************************************************

/* Create DataName

drop database if exists DataName; //如果存在DataName则删除

create database DataName; //建立库DataName

use DataName; //打开库DataName

CREATE DATABASE 数据库名;

GRANT SELECT,INSERT,UPDATE,DELETE,CREATE,DROP,ALTER ON datawin7filecheckmd5.* TO datawin7filecheckmd5@localhost IDENTIFIED BY 'datawin7filecheckmd5';

SET PASSWORD FOR '数据库名'@'localhost' = OLD_PASSWORD('密码');
*/

/*   Create DataName table

create table Win7Md5Check(nIndex int(3) not null primary key auto_increment,FileName varchar(200),ServicePack varchar(32),ServicePack1 varchar(32),AlterData date,Description varchar(256));

create table WinVistaMd5Check(nIndex int(3) not null primary key auto_increment,FileName varchar(200),ServicePack1 varchar(32),ServicePack2 varchar(32),AlterData date,Description varchar(256));

create table WinXpMd5Check(nIndex int(3) not null primary key auto_increment,FileName varchar(200),ServicePack2 varchar(32),ServicePack3 varchar(32),AlterData date,Description varchar(256));

create table SoftWareName(nIndex int(3) not null primary key auto_increment,FileName varchar(200),ServicePack2 varchar(32),ServicePack3 varchar(32),AlterData date,Description varchar(256));

create table GameName(nIndex int(3) not null primary key auto_increment,FileName varchar(200),ServicePack2 varchar(32),ServicePack3 varchar(32),AlterData date,Description varchar(256));

alter table Win7Md5Check add Description varchar(256) default '0'

*/

/* Insert DataName values
insert into Win7Md5Check values("","","","","");
insert into Win7Md5Check values("","calc.exe","","60b7c0fead45f2066e5b805a91f4f0fc","2012-12-12","windows计算器程序");
*/

/* 修改表中数据
语法：update 表名 set 字段=新值,… where 条件
update mytable set name='Mary' where id=1;
*/

/*
Select ServicePack1 from win7md5check where FileName='calc.exe'
*/