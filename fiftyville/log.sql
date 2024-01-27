-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Find out what happened
select description
    from    crime_scene_reports
    where   year = 2021
    and     day = 28
    and     month = 7
    and     street = 'Humphrey Street';

-- Find out what they all said
select name, transcript
    from    interviews
    where   year = 2021
    and     day = 28
    and     month = 7;

-- The first witness said that the thief got inside a car, so we can investigate it first
select name from people where license_plate in (select license_plate from bakery_security_logs where year = 2021 and day = 28 and month = 7 and hour = 10 and minute > 15 and minute < 25 and activity = 'exit');
-- Get all the names of the callers that day with a duration of less than a minute
select caller from phone_calls where year = 2021 and day = 28 and month = 7 and duration <= 60;
-- Get the names of the people who withdrew money that day
select name from people where id in ( select person_id from bank_accounts where account_number in ( select account_number from atm_transactions where year = 2021 and day = 28 and month = 7 and transaction_type = 'withdraw'));
-- Get informations about all the flights the next day
select full_name, city, id from airports; -- Find out the id of Fiftyville
-- Get a list of all the people who are taking the earliest flight out of Fiftyville
select name from people where passport_number in (select passport_number from passengers where flight_id = (select id from flights where year = 2021 and day = 29 and month = 7 and origin_airport_id = 8 order by hour, minute limit 1));

-- Now finally find the name of the person in the earliest flight, who withdrew money the day before, the name of the owner of the car and the caller with a duration less than 60 seconds
select name from people where passport_number in (select passport_number from passengers where flight_id = (select id from flights where year = 2021 and day = 29 and month = 7 and origin_airport_id = 8 order by hour, minute limit 1)) and phone_number in (select caller from phone_calls where year = 2021 and day = 28 and month = 7 and duration <= 60) and name in (select name from people where id in ( select person_id from bank_accounts where account_number in ( select account_number from atm_transactions where year = 2021 and day = 28 and month = 7 and transaction_type = 'withdraw'))) and name in (select name from people where license_plate in (select license_plate from bakery_security_logs where year = 2021 and day = 28 and month = 7 and hour = 10 and minute > 15 and minute < 25 and activity = 'exit'));
-- The thief is Bruce

select name from people where phone_number = (select receiver from phone_calls where caller = (select phone_number from people where name = 'Bruce') and year = 2021 and day = 28 and month = 7 and duration <= 60);
-- The accomplice is Robin

select city from airports where id = (select destination_airport_id from flights where year = 2021 and day = 29 and month = 7 and origin_airport_id = 8 order by hour, minute limit 1);
-- The city the thief is flying to is New York City