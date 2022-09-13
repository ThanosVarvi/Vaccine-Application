#!/bin/bash

##check for wrong arguments

if [ $# -ne 4 ]; then
	echo "Wrong number of arguments"
	exit 1;
fi

if [ $3 -le 0 ]; then
	echo "Number of numlines can't be negative number"
	exit 1;
fi

if [ $4 -le -1 ]; then
	echo "Duplicates allowed can't be negative number"
	exit 1;
fi

echo $line

##viruses file

mapfile -t value1 < $1
value1=$(printf $value1|tr -d '\n') 
#printf '%s\n' "${value1[@]}"

echo $line

##countries file

mapfile -t value2 < $2
value2=$(printf $value2|tr -d '\n') 
#printf '%s\n' "${value2[@]}"

echo $line
echo The inputFile.txt is being generated...
echo $line


i=1
while [ $i -le $3 ]
do

	
	if [[ $4 -eq 1 && $i -gt 2 ]];
	then
		ranumber=$((1 + $RANDOM % 99))
		if [[ ranumber -gt 49 ]] #pi8anotita 50% gia duplicate
		then
			id=$id #to id na meinei to idio
		else
			id=$((1 + $RANDOM % 9999))
		fi
	else
		id=$((1 + $RANDOM % 9999))
	fi
	
	ran=$((4 + $RANDOM % 8))
	rann=$((4 + $RANDOM % 8))

	cap1=$(echo {A..Z} | tr -d ' ')
	cap2=$(echo {A..Z} | tr -d ' ')

	s1=$(echo {a..z} | tr -d ' ')
	s2=$(echo {a..z} | tr -d ' ')

	c1=""
	k=1
	while [[ $k -le ran ]]; 
	do
		if [[ $k -eq ran ]]
		then
			string1=${cap1:$((RANDOM%26+1)):1}
			c1=$string1$c1
			((k=k+1))			
		else
			string1=${s1:$((RANDOM%26+1)):1}
			c1=$string1$c1
			((k=k+1))
		fi
	done
	
	c2=""
	j=1
	while [[ $j -le rann ]]; 
	do
		if [[ $j -eq rann ]]
		then
			string2=${cap2:$((RANDOM%26+1)):1}
			c2=$string2$c2
			((j=j+1))			
		else
			string2=${s2:$((RANDOM%26+1)):1}
			c2=$string2$c2
			((j=j+1))
		fi
	done

	first=$c1
	last=$c2
    age=$((1 + RANDOM % 120))
	country=${value2[RANDOM%${#value2[@]}]}
    virus=${value1[RANDOM%${#value1[@]}]}

	v=$(($RANDOM % 2))

	if [[ $v -eq 0 ]]
	then
  		vaccined="NO"
	else
		vaccined="YES"
	fi

	if [[ "$vaccined" = "YES" ]]
	then
		day=$((1 + RANDOM % 29))
		month=$((1 + RANDOM % 11))
		year=$((1920 + RANDOM % 100))

		day=$(printf "%02d" $day)
		month=$(printf "%02d" $month)

  		date="$day-$month-$year"
	else
		date=" "
	fi



	country=${country/$'\n'}
	virus="${virus/$'\n'}"

	output="$id $first $last ${country::-1} $age ${virus::-1} $vaccined $date"
    printf "%s\n" "$output" >> inputFile.txt
    i=$(( $i + 1 ))
done

echo $line
echo Your inputFile.txt has been created succesfully.
echo $line

