#!/bin/bash
for i in {1..600}
do
mysql -u root -ps obuwie_db < ~/ObuwieManager/schema/instert_model.sql
done
