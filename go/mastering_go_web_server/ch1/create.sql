create database social_network;


 CREATE TABLE `users` (
  `user_id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `user_nickname` varchar(32) NOT NULL,
  `user_first` varchar(32) NOT NULL,
  `user_last` varchar(32) NOT NULL,
  `user_email` varchar(32) NOT NULL,
  PRIMARY KEY (`user_id`),
  UNIQUE KEY `user_nickname` (`user_nickname`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 ;

CREATE TABLE `users_relationships` (
  `users_relationship_id` int(13) NOT NULL,
  `from_user_id` int(10) NOT NULL,
  `to_user_id` int(10) NOT NULL,
  `users_relationship_type` varchar(10) NOT NULL,
  `users_relationship_timpestamp` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`users_relationship_id`),
  KEY `from_user_id` (`from_user_id`),
  KEY `to_user_id` (`to_user_id`),
  KEY `from_user_id_to_user_id` (`from_user_id`,`to_user_id`),
  KEY `from_user_id_to_user_id_users_relationship_type` (`from_user_id`,`to_user_id`,`users_relationship_type`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1

alter table users add unique index user_email (user_email);
