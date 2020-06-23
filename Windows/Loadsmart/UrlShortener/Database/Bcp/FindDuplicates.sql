-- Check for duplicates
select
    NumberID,
    count(*)
from
    RandomChars
group by
    NumberID
having count(*) > 1


-- Remove all records
delete from RandomChars
