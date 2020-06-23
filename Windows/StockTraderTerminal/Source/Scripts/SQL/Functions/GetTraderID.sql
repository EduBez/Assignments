--
--  GetTraderID
--
create function GetTraderID
(
    rUserName     varchar(100),
    rPassword     varchar(100)
)
returns int(11)
begin
    -- Declare Variable
    declare wTraderID int default -1;

    -- Retrieve TraderID
    select
        TraderID
    into
        wTraderID
    from
        Trader
    where
        UserName = rUserName and Password = rPassword;

    return wTraderID;
end

