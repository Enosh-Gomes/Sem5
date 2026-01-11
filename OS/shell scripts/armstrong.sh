echo "Enter a number:"
read num

n=$num
original=$num
digits=0

while [ $n -gt 0 ]
do
	n=$(($n/10))
	digits=$(($digits+1))
done

n=$num
sum=0

while [ $n -gt 0 ]
do 
	digit=$(($n%10))
	pow=1
	i=0
	
	while [ $i -lt $digits ]
	do
		pow=$(($pow * $digit))
		i=$(($i+1))
	done
	
	sum=$(($sum+$pow))
	n=$(($n/10))
done

j=$digits

pow=1
i=$j
	
while [ $i -gt 1 ]
do
	pow=$(($pow * 10))
	i=$(($i-1))
done

while [ $j -gt 0 ]
do	
	n=$num
	n=$((n/pow))
	
	if [ $pow -eq 1 ]
	then
		pow=10
	fi
	
	digit=$((n%pow))	
	pow=$((pow/10))
		
	echo -n "$digit^$digits"
	
	if [ $j -gt 1 ]
	then
		echo -n " + "	
	fi
	j=$((j-1))
done

echo " = $sum"

if [ $sum -eq $original ]
then
	echo "$original is an Armstrong number."
else
	echo "$original is not an Armstrong number."
fi
