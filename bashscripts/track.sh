#!/bin/bash


#sudo auditctl -l -k dem
#sudo ausearch -k dem | grep type >> log.txt
#sudo auditctl -w /srv/int/ -p rwxa -k dem

check=$(auditctl -l -k live)

if [ ${#check} -eq 0 ]
    then 
        echo "yes:loggin"

        while true
        do
            ausearch -k live | grep type > log.txt
        done
    else
        echo "no"
        auditctl -w /srv/live/ -p rwxa -k live

        while true
        do
            ausearch -k live | grep type > log.txt
        done
        
fi
