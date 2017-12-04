SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL,ALLOW_INVALID_DATES';

CREATE SCHEMA IF NOT EXISTS `monitor_zssw` DEFAULT CHARACTER SET utf8 COLLATE utf8_bin ;
USE `monitor_zssw` ;

-- -----------------------------------------------------
-- Table `monitor_zssw`.`events_types`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `monitor_zssw`.`events_types` (
  `id` INT(11) NOT NULL AUTO_INCREMENT COMMENT 'The ordinal number of a event\'s type.',
  `name_of_event_type` VARCHAR(25) NOT NULL COMMENT 'The short name (mnemonics) of a event\'s type.',
  `description_of_event_type` VARCHAR(120) NULL DEFAULT NULL COMMENT 'The detailed description of a event\'s type.',
  `point_or_time_interval` INT(11) NOT NULL DEFAULT '0' COMMENT 'The nature of a event\'s type: 0 if the event has a point nature, 1 if the event has an time interval nature and both the begin and the end should be recorder.',
  PRIMARY KEY (`id`),
  UNIQUE INDEX `by_name_of_type` (`name_of_event_type` ASC))
ENGINE = InnoDB
AUTO_INCREMENT = 3
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_bin
COMMENT = 'The catalog of types of registered events.';


-- -----------------------------------------------------
-- Table `monitor_zssw`.`events`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `monitor_zssw`.`events` (
  `id` INT(11) UNSIGNED NOT NULL AUTO_INCREMENT COMMENT 'The ordinal number of a record in the table.',
  `name_of_event_type` VARCHAR(25) NOT NULL COMMENT 'The identified of the type of a registered event.',
  `timestamp` DATETIME NOT NULL COMMENT 'The timestamp of an event\'s record.',
  `begin_or_end` INT(1) UNSIGNED NULL DEFAULT NULL COMMENT 'The part of events which have a continous nature is recorder twice: on the begin and on the end. In this case value of the field will be 0 (for the begin) or 1 (for the end). If the event don\'t needs to be recorder twice - the event is recorder with value /* comment truncated */ /* "null" in this field.*/',
  `value` DECIMAL(9,2) NULL DEFAULT NULL COMMENT 'Some value (eg. temperature) associated with this event.',
  `failure` INT(1) NULL DEFAULT NULL COMMENT 'The specific field for some records with end of the event. Value of the field inform about type of the end of the work. Possibility value of the field 0 (for the correctly end of the work) or 1 (for the failure end of the work).',
  PRIMARY KEY (`id`),
  INDEX `by_type` (`name_of_event_type` ASC),
  CONSTRAINT `by_type`
    FOREIGN KEY (`name_of_event_type`)
    REFERENCES `monitor_zssw`.`events_types` (`name_of_event_type`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_bin
COMMENT = 'The table contains record of all registered events.';


-- -----------------------------------------------------
-- Table `monitor_zssw`.`shots_details`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `monitor_zssw`.`shots_details` (
  `id` INT(11) UNSIGNED NOT NULL AUTO_INCREMENT COMMENT 'An unique ID.',
  `event_id` INT(11) UNSIGNED NOT NULL COMMENT 'An ID of the associated event',
  `active_ammo_type` VARCHAR(30) NULL COMMENT 'A type of the active ammo.',
  `active_target_type` VARCHAR(30) NULL COMMENT 'A type of the active target.',
  `active_target_name` VARCHAR(255) NULL COMMENT 'A name of the active target.',
  `active_target_distance` INT NULL COMMENT 'A distance to the active target.',
  `active_target_azimuth` DOUBLE NULL COMMENT 'An azimuth to the active target.',
  `active_target_elevation` DOUBLE NULL COMMENT 'An elevation to the active target.',
  `active_target_owner` VARCHAR(30) NULL COMMENT 'An owner of the active target.',
  `active_target_latitude` DOUBLE NULL COMMENT 'An latitude of the active target.',
  `active_target_longitude` DOUBLE NULL DEFAULT NULL COMMENT 'An longitude of the active target.',
  `active_target_altitude` INT NULL COMMENT 'An altitude of the active target.',
  `ballistic_solution_super_elevation` DOUBLE NULL COMMENT 'A super elevation of a solution reported by the ballistic calculator',
  `ballistic_solution_drift` DOUBLE NULL COMMENT 'A drift of a solution reported by the ballistic calculator',
  `ballistic_solution_time_of_flight` DOUBLE NULL COMMENT 'A time of flight of a solution reported by the ballistic calculator',
  `ballistic_solution_abm_turn_cnt` DOUBLE NULL COMMENT 'An ABM turn counter of solution reported by the ballistic calculator.',
  `air_temperature` DOUBLE NULL COMMENT 'A temperature reported by the meteo device.',
  `pressure` DOUBLE NULL COMMENT 'A pressure reported by the meteo device.',
  `wind_speed` DOUBLE NULL COMMENT 'A wind speed reported by the meteo device',
  `wind_direction` DOUBLE NULL COMMENT 'A wind direction reported by the meteo device.',
  `azimuth_position` DOUBLE NULL COMMENT 'A position reported by the azimuth STS11',
  `azimuth_speed` DOUBLE NULL COMMENT 'A speed reported by the azimuth STS11',
  `elevation_position` DOUBLE NULL COMMENT 'A position reported by the elevation STS11.',
  `elevation_speed` DOUBLE NULL COMMENT 'A speed reported by the elevation STS11.',
  `latitude` DOUBLE NULL COMMENT 'A latitude reported by the Talin.',
  `longitude` DOUBLE NULL COMMENT 'A longitude reported by the Talin.',
  `altitude` INT NULL COMMENT 'An altitude reported by the Talin.',
  `pitch` DOUBLE NULL COMMENT 'A pitch reported by the Talin.',
  `yaw` DOUBLE NULL COMMENT 'A yaw reported by the Talin.',
  `roll` DOUBLE NULL COMMENT 'A roll reported by the Talin.',
  `velocity` DOUBLE NULL COMMENT 'A roll reported by the Talin.',
  `milliseconds` INT(3) NULL DEFAULT NULL COMMENT 'Milliseconds from timestamp.',
  `spike_flaps_position` INT NULL COMMENT 'A flaps position reported by the STS13.',
  `spike_elevation_position` DOUBLE NULL COMMENT 'A position in elevation reported by the STS13.',
  `spike_elevation_speed` DOUBLE NULL COMMENT 'A speed in elevation reported by the STS13.',
  `spike_seeker_status` INT NULL COMMENT 'A seeker status of the SPIKE.',
  `spike_selected_msl` INT NULL COMMENT 'A selected Msl of the SPIKE.',
  `spike_trajectory` INT NULL COMMENT 'A trajectory of the SPIKE.',
  PRIMARY KEY (`id`),
  INDEX `by_event_id` (`event_id` ASC),
  CONSTRAINT `by_event_id`
    FOREIGN KEY (`event_id`)
    REFERENCES `monitor_zssw`.`events` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_bin
COMMENT = 'The table which contains details about shots. It\'s a kind of /* comment truncated */ /* extension of the events table.*/';


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
