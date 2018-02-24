#!/bin/bash
for i in {1..10}
do
mysql -u root -ps obuwie_db < ~/ObuwieManager/schema/instert_zamowienie.sql
done
