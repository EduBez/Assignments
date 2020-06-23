--
--  ViewTransactions
--
create procedure ViewTransactions
(
    rUserName     varchar(100),
    rPassword     varchar(100)
)
begin
    -- Declare Variable
    declare wTraderID int;

    -- Retrieve TraderID
    set wTraderID = GetTraderID(rUserName, rPassword);

    -- View Transaction
    select
        TraderID,
        StockID,
        Quantity,
        DateTime,

        case OpType
            when 'B' then 'BUY'
            when 'S' then 'SELL'
        end as 'Operation',

        case Status
            when 0 then 'Success'
            when 1 then 'Error - Do not have suficient funds'
            when 2 then 'Error - Stock code not found in portfolio'
            when 3 then 'Error - Do not have enough stock quantity'
        end as 'Status'
    from
        Transaction
    where
        TraderID = wTraderID
    order by
        StockID,
        DateTime,
        Operation,
        Status;
end
