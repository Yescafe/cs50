-- Keep a log of any SQL queries you execute as you solve the mystery.

-- 10 点 15 分的时候面包店发生了偷窃
select description from crime_scene_reports where month = 7 and day = 28;

-- 从采访中得知，
-- Ruth 说，在抢劫后的 10 分钟内看到小偷进车离开
-- Eugene 说他不知道小偷的名字，但是他认出来他了。今早早些时候，他在 Leggett Street 的 ATM 取钱
-- Raymond 说小偷离开了之后，他们打了不到一分钟的电话。电话里小偷说他们要坐明天最早的一班飞机离开 Fiftyville，并且告诉电话的另一端（帮凶）买飞机票
select name, transcript from interviews where month = 7 and day = 28;

-- 多表联查，进行分析
select a.name aname, a.passport_number, a.license_plate alp, d.receiver, e.name, e.passport_number from people a
inner join (
  select person_id from bank_accounts a
  inner join (
    select account_number an from atm_transactions
    where month = 7 and day = 28 and atm_location = "Leggett Street"
    and transaction_type = "withdraw"
  ) b on a.account_number = b.an    -- 找到当天在 Leggett Street 取过钱的人的 id
) b on a.id = b.person_id    -- 找到这些取过钱的人的 id 与他们的 license plate 对应
inner join (
  select license_plate lp from bakery_security_logs
  where month = 7 and day = 28 and hour = 10 and minute > 15 and minute <= 25
  and activity = "exit"       -- 在案发时间点附近出去面包店的人的 id 信息
) c on alp = c.lp
inner join (
  select caller, people.name pname, receiver, duration from phone_calls
  inner join people on people.phone_number = phone_calls.caller
  where month = 7 and day = 28 and duration < 60        -- 当天打了一分钟时长以内电话的
) d on aname = d.pname
inner join people e on e.phone_number = d.receiver
inner join (
  select aa.passport_number pn from passengers aa
  inner join (
    select * from flights where month = 7 and day = 29
    order by hour asc, minute asc limit 1               -- 7 月 29 号第一班飞机
  ) bb on aa.flight_id = bb.id                          -- 找到所有乘客的护照号
) f on f.pn = a.passport_number;                        -- 跟之前分析出来的人比对，最终将范围缩小到一条通话记录的两方

-- 最终锁定到的这条记录，通话的两方分别为小偷和他的协助者

-- 最后只需要查出这一班飞机的目的地地点即可
select airports.city from (
  select * from flights where month = 7 and day = 29
  order by hour asc, minute asc limit 1
) the_flight
inner join airports on airports.id = the_flight.destination_airport_id;