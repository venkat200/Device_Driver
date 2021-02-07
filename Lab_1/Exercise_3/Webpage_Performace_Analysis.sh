#!/bin/sh

# the output log file
FILE=/media/sf_VM_Shared_Folder/DD/Lab_1/Exercise_3/Britannica_Webpage.out
# the output webpage file
WEB_FILE=/media/sf_VM_Shared_Folder/DD/Lab_1/Exercise_3/Britannica_Webpage.html

# the url to retrieve
# URL=https://www.reddit.com/r/tech/
URL=https://www.britannica.com/browse/Geography-Travel

# writing header information to the log download file
start_date=`date`
echo "-----------------------------START OF WEBPAGE FILE DOWNLOAD-----------------------------" > $FILE
echo "" >> $FILE
echo "START TIME       : $start_date" >> $FILE
echo "CHECK THE END OF PAGE FOR START AND END TIME AND DATE" >> $FILE
echo "" >> $FILE
echo "DOWNLOAD CONTENT : " >> $FILE
echo "" >> $FILE

# feedback to user for start of download
echo "Downloading Webpage $URL ...."
echo ""
echo "Progress and Performance Stats ...."
echo ""

# retrieve the web page using curl command
# time the process with the time command
## time (curl --connect-timeout 100 $URL) >> $FILE
# redirect output from cmd to two files without showing in console
time (curl --connect-timeout 100 $URL) | tee -a $FILE >>$WEB_FILE 
 
# writing footer information to the log download file
echo "" >> $FILE
end_date=`date`

echo "START TIME : $start_date" >> $FILE
echo "END TIME   : $end_date" >> $FILE
echo "" >> $FILE

echo ""
echo "Webpage Response Time Analysis "
echo ""
echo "Testing $URL ...."
# reponse time stats for the url
curl -s -w '\nLookup Time 	    :\t%{time_namelookup}
Connect Time        :\t%{time_connect}
Pre-transfer Time   :\t%{time_pretransfer}
Start-transfer Time :\t%{time_starttransfer}
\nTotal Time          :\t%{time_total}\n' -o /dev/null $URL
