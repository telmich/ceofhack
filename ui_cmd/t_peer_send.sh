#!/bin/sh

i=0
while ./ui_cmd_peer_send telmich_new hallo$i; do
   i=$(($i+1)) ;
done
echo $i
