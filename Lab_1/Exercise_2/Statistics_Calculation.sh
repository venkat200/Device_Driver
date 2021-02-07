#!/bin/bash

# global variable contains number of data points
countOfDataPoints=0     
# Scale to be used by bc. Nine decimal places.    
scale_decimalPrecision=5      
# data points array
declare -a dataPoints	

# check for data file as argument in cmd
if [ ! -z "$1" ]  
then
	# ASCII text file
	dataFile="$1" 
else            
	dataFile=InputData.dat
fi              

# check for the file existance
# error code to return for data file error      
dataFileError=90 
if [ ! -e "$dataFile" ]
then
	echo "\""$dataFile"\" does not exist!"
	exit $dataFileError
fi


# function to compute mean
Mean()
{
	local total=0         
	local mean=0         
	local numberOfDataPoints=0         

	# reading data points value one at a time in while loop
	while read value   
	do
		total=$(echo "scale=$scale_decimalPrecision; $total + $value" | bc)
		(( dataPoints[numberOfDataPoints]=value ))
		(( numberOfDataPoints++ ))
	done

	mean=$(echo "scale=$scale_decimalPrecision; $total / $numberOfDataPoints" | bc)

	# this function returns two values mean and numberOfDataPoints
	# comment "return $numberOfdataPoints" if numberOfdataPoints > 255
	echo $mean; return $numberOfDataPoints   
	
} <"$dataFile"	# feeding in data file to the function

# function to compute standard deviation
StandardDeviation()
{
	# mean passed as a first argument to StandardDeviation() function
	local mean=$1  
	# number of data points passed as a second argument to StandardDeviation() function
	local numberOfData=$2     
	# variance
	local sumOfSquareDifferences=0    
	# average of sum of square differences
	local averageOfSSD=0   
	local standardDeviation=0  

	while read value 
	do
		# compute difference between mean and value
		difference=$(echo "scale=$scale_decimalPrecision; $mean - $value" | bc)
		# square the difference
		differenceSquare=$(echo "scale=$scale_decimalPrecision; $difference * $difference" | bc) 
		sumOfSquareDifferences=$(echo "scale=$scale_decimalPrecision; $sumOfSquareDifferences + $differenceSquare" | bc)
	done

	averageOfSSD=$(echo "scale=$scale_decimalPrecision; $sumOfSquareDifferences / $numberOfData" | bc)
	standardDeviation=$(echo "scale=$scale_decimalPrecision; sqrt($averageOfSSD)" | bc) 
	echo $standardDeviation                            

} <"$dataFile"	# rewinds data file to the function



# Mean() function returns two values
mean=$(Mean); countOfDataPoints=$?   
# calling StandardDeviation() and passing mean and countOfDataPoints as arguments
standard_deviation=$(StandardDeviation $mean $countOfDataPoints)
variance=$(echo "scale=$scale_decimalPrecision; $standard_deviation * $standard_deviation" | bc)  

echo
echo "Statistics calculation from $dataFile file"
echo
echo "Number of Data Points = $countOfDataPoints"
echo "Mean (Average)        = $mean"
echo "Variance              = $variance"
echo "Standard Deviation    = $standard_deviation"
echo

exit