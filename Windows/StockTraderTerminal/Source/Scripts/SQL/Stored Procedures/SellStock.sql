--
--  SellStock StoredProc
--
create procedure SellStock
(
    rUserName     varchar(100)  ,
    rPassword     varchar(100)  ,
    rStockID      varchar(30)   ,
    rQuantity     int           ,
    rPrice        decimal(10, 2)
)
begin
    -- Declare local variables
    declare   wCost       decimal(10, 2);
    declare   wNewCost    decimal(10, 2);
    declare   wQuantity   int;

    -- Operation Status Codes

    -- 0  =>  Success
    -- 1  =>  DON'T have suficient funds
    -- 2  =>  Stock NOT found in Portfolio
    -- 3  =>  DON'T have enough stock quantity

    -- Retrieve TraderID and BalanceCash
    select
        @TraderID    := TraderID ,
        @BalanceCash := BalanceCash    
    from
        Trader
    where
        UserName = rUserName and Password = rPassword;

    -- Check Portfolio for this stock
    select
        @RecCnt := COUNT(*)
    from
        Portfolio
    where
        TraderID = @TraderID and StockID = rStockID;

    -- Stock found in Portfolio
    if @RecCnt > 0
    then
        -- Retrieve Portfolio Quantity and TotalCost
        select
            @Quantity  := Quantity,
            @TotalCost := TotalCost
        from
            Portfolio
        where
            TraderID = @TraderID and StockID = rStockID;
    
        -- DON'T have enough stock quantity
        if rQuantity > @Quantity
        then
            -- Update Transaction
            insert into
                Transaction
            values
                (@TraderID, rStockID, rQuantity, NOW(), 'S', 3);

        -- DO have enough stock quantity
        else
            -- Calculate cost
            set wCost := rQuantity * rPrice;

            -- Update new quantity
            set wQuantity := @Quantity - rQuantity;

            -- Update new total cost
            -- Doubt: is this correct ???
            set wNewCost := /*@TotalCost -*/ wCost;

            -- Update balance cash
            update
                Trader
            set
                BalanceCash = (@BalanceCash + wCost)
            where
                TraderID = @TraderID;

            -- Update Portfolio
            update
                Portfolio
            set
               Quantity  = wQuantity/*,*/
               -- TotalCost = wNewCost
            where
                TraderID = @TraderID and StockID = rStockID;

            -- Update Stock
            update
                Stock
            set
               LastSalePrice  = rPrice
            where
                StockID = rStockID;

            -- Update Transaction
            insert into
                Transaction
            values
                (@TraderID, rStockID, rQuantity, NOW(), 'S', 0);
        end if;

    -- Stock NOT found in Portfolio
    else
        -- Update Transaction
        insert into
            Transaction
        values
            (@TraderID, rStockID, rQuantity, NOW(), 'S', 2);
    end if;
end

