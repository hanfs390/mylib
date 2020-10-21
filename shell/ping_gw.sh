#!/bin/sh

echo `date` >> /root/ping_gw.log
h=`date |awk '{print $4}'|awk -F ":" '{print $1}'`
m=`date |awk '{print $4}'|awk -F ":" '{print $2}'`
if [ $h -eq 3 ]&&[ $m -ge 0 ]&&[ $m -le 10 ]; then
	echo 0 > /root/reboot_count
fi

gwip=`route | grep 'default' | awk '{print $2}'`
count=0
for i in $(seq 1 10)
do
	ping -c 1 $gwip > /dev/null 2>&1
	if [ $? -eq 0 ];then
		count=0
	else
		let count=$count+1
	fi
	sleep 6
done

touch /root/reboot_count
reboot_count=`cat /root/reboot_count`
if [ $count -gt 7 ];then
	# disconnect
	if [ ! $reboot_count ] || [ $reboot_count -lt 3 ];then
		let reboot_count=reboot_count+1
		echo $reboot_count > /root/reboot_count
		touch /root/ping_gw.log
		log_size=`ls -l /root/ping_gw.log | awk '{ print $5 }'`
		if [ $log_size -gt 204800 ];then #max size 200Kbytes
			rm /root/ping_gw.log
		fi
		echo "***********************************************************************" >> /root/ping_gw.log
		echo "Reboot AP and ONU because AP - GW $gwip disconnect" >> /root/ping_gw.log
		echo $(date) >> /root/ping_gw.log
		ps >> /root/ping_gw.log
		cat /proc/meminfo >> /root/ping_gw.log
		top -n 1 >> /root/ping_gw.log
		dmesg -c >> /root/ping_gw.log
		echo "***********************************************************************" >> /root/ping_gw.log
		
		echo "start reboot gpon"
		(
			sleep 1
			echo "root"
			sleep 2
			echo "Pon521"
			sleep 2
			echo "reboot";
			sleep 3
		)|telnet 192.168.2.1
		reboot -f
	else
		wifi down
	fi
else
	#connect
	if [ $reboot_count -ge 3 ];then
		wifi up
	fi
	echo 0 > /root/reboot_count
fi
