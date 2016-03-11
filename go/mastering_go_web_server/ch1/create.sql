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

