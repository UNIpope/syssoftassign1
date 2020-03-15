#!/bin/bash
check=$(auditctl -l -k int)

if [ ${#check} -eq 0 ] || [ "$check" == "No rules" ]
    then 
        echo "no loggin making rule"
        auditctl -w /srv/int/ -p rwxa -k int
    else
        echo "rule already in place"
fi
