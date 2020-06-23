--
--  ViewPortfolio
--
create procedure ViewPortfolio
(
    rUserName     varchar(100),
    rPassword     varchar(100)
)
begin
    -- Declare Variable
    declare wTraderID int;

    -- Retrieve TraderID
    set wTraderID = GetTraderID(rUserName, rPassword);

    -- View Portfolio
    select
        P.TraderID    ,
        P.StockID     ,
        S.CompanyName ,
        P.Quantity    ,
        P.TotalCost   ,
        S.LastSalePrice
    from
        Portfolio P
    join
        Stock S
    on
        S.StockID = P.StockID
    where
       P.TraderID = wTraderID
    order by
        S.StockID;
end

