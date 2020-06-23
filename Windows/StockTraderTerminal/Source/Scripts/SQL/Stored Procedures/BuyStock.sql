--
--  BuyStock StoredProc
--
create procedure BuyStock
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

    -- Calculate cost
    set wCost := rQuantity * rPrice;
        
    -- We DON'T have suficient funds
    if wCost > @BalanceCash
    then
        -- Update Transaction
        insert into
            Transaction
        values
            (@TraderID, rStockID, rQuantity, NOW(), 'B', 1);
    end if;

    -- We DO have suficient funds
    if wCost <= @BalanceCash
    then
        -- Update balance cash
        update
            Trader
        set
            BalanceCash = (@BalanceCash - wCost)
        where
            TraderID = @TraderID;

        -- Check Portfolio for this stock
        select
            @RecCnt := COUNT(*)
        from
            Portfolio
        where
            TraderID = @TraderID and StockID = rStockID;

        -- No records found
        if @RecCnt = 0
        then
            -- Portfolio
            insert into
                Portfolio
            values
                (@TraderID, rStockID, rQuantity, wCost);

        -- Records found
        else
            -- Retrieve current values
            select
                @Quantity  := Quantity,
                @TotalCost := TotalCost
            from
                Portfolio
            where
                TraderID = @TraderID and StockID = rStockID;

            -- Update new quantity
            set wQuantity := @Quantity + rQuantity;

            -- Update new total cost
            -- Doubt: is this correct ???
            set wNewCost := /*@TotalCost +*/ wCost;

             -- Update Portfolio
             update
                 Portfolio
             set
                Quantity  = wQuantity,
                TotalCost = wNewCost
             where
                 TraderID = @TraderID and StockID = rStockID;
        end if;

        -- Update Transaction
        insert into
            Transaction
        values
            (@TraderID, rStockID, rQuantity, NOW(), 'B', 0);

    end if;
end

